﻿/*
				ファイル名		:Map.cpp
				作成者			:
				作成日時		:2018/11/24
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Common/Graphics/Button/Button.h"
#include "Common/Graphics/Button/ButtonGraph.h"
#include "Common/ResourceTable/GraphTable.h"

#include "Common/String/FontMgr/BMFont.h"

#include "Map.h"

typedef struct {
	int id;
	char name[128];
	int afterStoryNum;
	int battleId;
	int beforeStoryNum;
}QUEST_DATA_t;

typedef struct {
	int listId;
	char name[128];
}TEST_MAP_DATA_t;

typedef struct {
	int mapId;
	int questDataNum;
	std::vector<QUEST_DATA_t> questData;
};

static const TEST_MAP_DATA_t TEST_MAP_DATA[5] = {
	{0 , "はじまりの森"},
	{1 , "リーフの家"},
	{2 , "森を進もう"},
	{3 , "ダミー 1"},
	{4 , "ダミー 2"},
};

Map::Map() : TaskBase() {
	//mMapIcon = ComRes::Instance()->GetGraphicHandle(ComRes::eComResName_MapIcon);
	mMapIcon = new Graphics();
	mMapIcon->Initialize(graphicsTable::GetGraphTag(graphicsTable::eGraphTag_MapIcon));
	mMapIcon->SetPosition(0, 0);
	mAnimState = Map::eAnimState_None;
	mIsTouchEnable = true;
	mIsOpenSelectButton = false;

	mFontString = new BMFont();

	mButtonGraph = nullptr;

}

Map::Map(int posX,int posY,const char* mapTitle) : TaskBase() {
	
	//mMapIcon = new Graphics(*ComRes::Instance()->GetGraphicHandle(ComRes::eComResName_MapIcon));
	mMapIcon = new Graphics();
	mMapIcon->Initialize(graphicsTable::GetGraphTag(graphicsTable::eGraphTag_MapIcon));
	mMapIcon->SetPosition(posX, posY);

	GraphicsDrawMgr::GetInstance()->Add(mMapIcon, 0);

	mSelectButtonNum = -1;
	mSelectButtonMax = 0;

	mAnimState = Map::eAnimState_None;

	mIsTouchEnable = true;
	mIsOpenSelectButton = false;

	mFontString = new BMFont();

	strcpyDx(mMapTitleText, mapTitle);

	mButtonGraph = nullptr;
}

Map::~Map() {
	
	mMapIcon->ReleseRequest();
	GraphicsDrawMgr::GetInstance()->Remove(mOrderDrawGraphic);

	for (int i = 0; i < mSelectButtonMax; i++) {
		Delete(mButtons[i]);
	}
	mButtons.clear();

	Delete(mFontString);

}

void Map::Draw() {
	
	if (mMapIcon == NULL) return;

	//mMapIcon->Draw();

	mFontString->Draw(DUGEON_TITLE_POS_X, DUGEON_TITLE_POS_Y,true);
}

bool Map::Updata() {

	//if (mMapIcon == NULL) return true;

	switch (mAnimState) {
	case Map::eAnimState_In:
	{
		bool isNext = false;
		for (int i = 0; i < mButtons.size() - 1; i++) {
			int posX = mButtons[i]->GetPositionX();
			int posY = mButtons[i]->GetPositionY();
			float alpha = mButtons[i]->GetAlpha();

			posY -= 10;
			alpha += 255.0f / 10.0f;

			if (posY <= 100 * (i + 1)) {
				posY = 100 * (i + 1);
				isNext = true;
				alpha = 255.0f;
			}
			else {
				isNext = false;
			}

			mButtons[i]->SetPosition(posX, posY);
			mButtons[i]->SetAlpha(alpha);
		}

		if (isNext) {
			mAnimState = Map::eAnimState_None;
			mIsOpenSelectButton = true;
		}
	}
		break;
	case Map::eAnimState_Out:
	{
		bool isNext = false;
		for (int i = 0; i < mButtons.size() - 1; i++) {
			int posX = mButtons[i]->GetPositionX();
			int posY = mButtons[i]->GetPositionY();
			float alpha = mButtons[i]->GetAlpha();

			posY += 10;
			alpha -= 255.0f / 10.0f;

			if (posY > 100 + i * 165 ) {
				posY = 100 + i * 165 ;
				isNext = true;
				alpha = 0.0f;
			}
			else {
				isNext = false;
			}

			mButtons[i]->SetPosition(posX, posY);
			mButtons[i]->SetAlpha(alpha);
		}

		if (isNext) {
			mAnimState = Map::eAnimState_None;
			this->mButtonGraph->SetVisible(false);
			mIsOpenSelectButton = false;
			mFontString->SetString("");
		}
	}
		break;
	}

	if (mIsTouchEnable == true) {
		if (mButtonGraph != nullptr) {
			// ボタンの表示がされていない かつ マップアイコン画像をクリックを行ったか
			if (mButtonGraph->IsVisible() == false && mMapIcon->IsTouch()) {
				mButtonGraph->SetVisible(true);
				mAnimState = Map::eAnimState_In;
				//mFontString->SetString("テストああああ");
				mFontString->SetString(mMapTitleText);
			}
		}
	}
	
	return true;
}

void Map::PostUpdate() {
	//if (mMapIcon == NULL) return;

}

void Map::SetUp(StoryData* pinData,int size) {

	mButtonGraph = new ButtonGraph();

	for (int i = 0; i < size; i++) {
		StoryData& data = *(pinData + i);
		mStoryDataList.push_back(data);
		Button* btn = new Button(100, 100 + i * 165, 100, 60, data.title);
		//Button* btn = new Button(graphicsTable::eGraphTag_StoryButton,100, 100 + i * 165, data.title);
		btn->SetAlpha(0.0f);
		btn->SetOnListener(this);
		mButtonGraph->AddButton(btn);
		mButtons.push_back(btn);
	}


	Button* returnBtn = new Button(20, 20, 100, 60, "戻る");
	returnBtn->SetOnListener(this);
	mButtonGraph->AddButton(returnBtn);
	mButtons.push_back(returnBtn);

	mOrderDrawGraphic = GraphicsDrawMgr::GetInstance()->Add(mButtonGraph, 100);
	mButtonGraph->SetVisible(false);

	mSelectButtonMax = size;

}

int Map::GetIndex() {
	int selectNum = mSelectButtonNum;
	mSelectButtonNum = -1;
	return selectNum;
}

bool Map::GetStoryData(Map::StoryData* poutData) {
	int idx = GetIndex();
	if (idx == -1)return false;
	*poutData = mStoryDataList[idx];
	return true;
}

void Map::OnClick(View* view) {

	for (int i = 0; i < mSelectButtonMax; i++) {
		if (mButtons[i] == view) {
			mSelectButtonNum = i;
			break;
		}
	}

	if (mButtons[mSelectButtonMax] == view) {
		mAnimState = Map::eAnimState_Out;
		//this->mButtonGraph->SetVisible(false);
	}

}

bool Map::IsTouchEnable() {
	return mIsTouchEnable;
}

void Map::SetToucheEnable(bool enable) {
	mIsTouchEnable = enable;
}

/*
	ダンジョン選択ボタンが開いているか
	return	true	:開いている
			false	:開いていない
*/
bool Map::IsOpenSelectButton() {
	return mIsOpenSelectButton;
}

void Map::SetDrawFlag(bool isDraw) {

	for (int i = 0; i < mButtons.size(); i++) {
		mButtons[i]->SetVisible(isDraw);
	}

	mMapIcon->SetVisible(isDraw);

}