/*
				ファイル名		:MapField.cpp
				作成者			:
				作成日時		:2018/12/22
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Common/FileLoader/TblLoader/TblLoader.h"
#include "Common/FileLoader/TblLoader/TblLoaderMgr.h"

#include "Map.h"
#include "MapField.h"

struct MapData {
	int id;
	char title[64];
	int posX;
	int posY;
	int storyId;
};


MapField::MapField() : TaskBase(){
	
	this->mMapImageHandle = new Graphics();
	this->mMapImageHandle->Load("Resources/Graphics/Map/forest.png");

	Map::StoryData storyData[5] = {
		{0 , "はじまりの森"},
		{1 , "リーフの家"},
		{2 , "森を進もう"},
		{3 , "ダミー 1"},
		{4 , "ダミー 2"},
	};

	Map* map1 = new Map(200.0f, 300.0f, "テスト１");
	map1->SetUp(storyData,5);
	
	this->mMapIcons.push_back(map1);
	//this->mMapIcons.push_back(new Map(380.0f,380.0f,"テスト２"));

	mStoryData = nullptr;

}

MapField::MapField(int stageNum) {

	char path[1024];
	sprintfDx(path, "Resources/Data/Table/StoryData/Stage%03d.dtl", stageNum);

	this->mMapImageHandle = new Graphics();
	this->mMapImageHandle->Load("Resources/Graphics/Map/forest.png");
	GraphicsDrawMgr::GetInstance()->Add(mMapImageHandle, 0);

	mLoader = loader::TblLoaderMgr::GetInstance()->LoadRequest(path);
	mState = eState_Wait;
	// 受け取ったステージ番号からステージを生成
		// マップ背景画像読み込み
		// マップデータ読み込み

	// クリア状況を取得
	

	mStoryData = nullptr;

}

MapField::~MapField() {

	//mMapImageHandle->Relese();
	mMapImageHandle->ReleseRequest();
	//Delete(mMapImageHandle);

	for (int i = 0; i < mMapIcons.size(); i++) {
		Delete(mMapIcons[i]);
	}
	
	Delete(mStoryData);

	mMapIcons.clear();

}

bool MapField::Initialize(){


	return true;
}

void MapField::Finalize(){

}

void MapField::PreviousUpdate(){

}

void MapField::InputUpdate() {

}

bool MapField::Updata(){
	
	switch (mState) {
	case eState_Wait:
		if (mLoader->IsLoadEnd()) {
			mState = eState_Read;
		}
		break;
	case eState_Read:
	{
		loader::TblLoader::TblData& data = mLoader->GetTableData();
		int num = data.GetDataNum(0, sizeof(MapData));
		MapData* mapData = new MapData[num];
		data.GetData(0, mapData);

		for (int i = 0; i < num; i++) {
			MapData tmp = mapData[i];
			int posX = tmp.posX;
			int posY = tmp.posY;
			char* title = tmp.title;
			int storyId = tmp.storyId;
			Map* map = new Map(posX, posY, title);

			int storyDataNum = data.GetDataNum(storyId, sizeof(Map::StoryData));
			Map::StoryData* stoyData = new Map::StoryData[storyDataNum];

			data.GetData(storyId, stoyData);
			map->SetUp(stoyData,storyDataNum);			
			this->mMapIcons.push_back(map);
			Delete(stoyData);
		}

		Delete(mapData);


		mState = eState_Main;
	}
		break;
	case eState_Fade:

		break;
	case eState_Main:
	{
		int openMapNum = -1;
		for (int i = 0; i < this->mMapIcons.size(); i++) {
			if (this->mMapIcons[i]->IsOpenSelectButton()) {
				openMapNum = i;
				break;
			}
		}

		Map::StoryData storyData;
		bool isExit = false;

		for (int i = 0; i < this->mMapIcons.size(); i++) {
			if (openMapNum >= 0 && openMapNum != i) {
				this->mMapIcons[i]->SetToucheEnable(false);
			}
			else {
				this->mMapIcons[i]->SetToucheEnable(true);
			}
			this->mMapIcons[i]->Updata();
			if (mMapIcons[i]->GetStoryData(&storyData)) {
				isExit = true;
			}
		}

		if (isExit) {
			if (mStoryData) {
				Delete(mStoryData)
			}

			mStoryData = new Map::StoryData();
			mStoryData->Set(storyData);
		}

#ifdef __MY_WINDOWS__
		if (Keyboard_Press(KEY_INPUT_X)) {
			TaskMgr::getInstance().RequestKill(mTaskId);
		}
#endif	// __MY_WINDOWS__

	}
		break;
	case eState_Story:

		break;
	case eState_Battle:

		break;
	case eState_Exit:

		break;
	}

	return true;
}

void MapField::PostUpdate() {

}

void MapField::Draw() {

	if (mState != eState_Main) return;

	//this->mMapImageHandle->Draw();

	for (int i = 0; i < this->mMapIcons.size(); i++) {
		this->mMapIcons[i]->Draw();
	}

}



