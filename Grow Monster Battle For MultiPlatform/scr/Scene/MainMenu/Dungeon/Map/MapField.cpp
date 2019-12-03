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
#include "Common/Script/ScriptBase.h"
#include "Scene/MainMenu/Dungeon/Battle/BattleBase.h"
#include "Scene/MainMenu/Dungeon/Battle/BattleMgr.h"

#include "Common/String/CharConverter/CharConverter.h"

#include "Map.h"
#include "MapField.h"

using namespace battle;

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

	mStoryTask = -1;
	mStoryData = nullptr;

	mBatlleTask = -1;

	mButton = new ReturnButton(this);

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
	
	mStoryTask = -1;
	mStoryData = nullptr;
	mBatlleTask = -1;

	mButton = new ReturnButton(this);

}

MapField::~MapField() {

	//mMapImageHandle->Relese();
	mMapImageHandle->ReleseRequest();
	//Delete(mMapImageHandle);

	for (int i = 0; i < mMapIcons.size(); i++) {
		Delete(mMapIcons[i]);
	}
	
	Delete(mStoryData);
	Delete(mButton);

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

		if (mLoader->IsExist() == false) {
			TaskMgr::getInstance().RequestKill(this->mTaskId);
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
#ifdef __WINDOWS__
			char* title = tmp.title;
#else
			int byte = 0;
			char* title = CharConverter::sjis_to_utf8(tmp.title, &byte);
#endif
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

		for (int i = 0; i < this->mMapIcons.size(); i++) {
			this->mMapIcons[i]->SetDrawFlag(true);
		}
		mState = eState_Main;
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
			mState = eState_Story;
		}

#ifdef __MY_WINDOWS__
		if (Keyboard_Press(KEY_INPUT_X)) {
			TaskMgr::getInstance().RequestKill(mTaskId);
		}
#endif	// __MY_WINDOWS__

	}
		break;
	case eState_Story:

		if (mStoryData->beforADV == -1) {
			mState = eState_Battle;
		}
		else {
			// ストーリー再生
			// ストーリー再生終了確認
			if (UpdateStory(mStoryData->beforADV)) {
				mState = eState_Battle;
			}
		}

		break;
	case eState_Battle:

		//バトル開始
		//バトル終了確認
		//バトル後ストーリー再生
		if (UpdataBattle(mStoryData->battleId)) {
			if (UpdateStory(mStoryData->afterADV)) {
				mState = eState_Fade;
			}
		}
		
		break;
	case eState_Exit:

		break;
	}

	mButton->Update();

	return true;
}

void MapField::PostUpdate() {

}

void MapField::Draw() {

	if (mState != eState_Main) {
		mMapImageHandle->SetVisible(false);
		return;
	}
	else {
		mMapImageHandle->SetVisible(true);
	}

	mButton->Draw();

	//this->mMapImageHandle->Draw();

	for (int i = 0; i < this->mMapIcons.size(); i++) {
		this->mMapIcons[i]->Draw();
	}

}



bool MapField::UpdateStory(int storyNo) {

	if (storyNo == -1) {
		return true;
	}
	
	if (mStoryTask == -1) {
		char path[1024];
		sprintfDx(path, "ADV_%04d.txt", storyNo);
		mStoryTask = TaskMgr::getInstance().Add(new AdvScript::ScriptBase(path));
		Fade::GetInstance()->FadeIn(0.3f);
		for (int i = 0; i < this->mMapIcons.size(); i++) {
			this->mMapIcons[i]->SetDrawFlag(false);
		}
	}
	else {
		if (Fade::GetInstance()->IsFadeEnd() == false) return false;
		AdvScript::ScriptBase* story = dynamic_cast<AdvScript::ScriptBase*>(TaskMgr::getInstance().GetTask(mStoryTask));

		if (story->IsEnd()) {
			story->RequestKill();
			mStoryTask = -1;
			Fade::GetInstance()->FadeIn(0.3f);
			return true;
		}
	}
	return false;
}

bool MapField::UpdataBattle(int battleNo) {

	//if (battleNo == -1) {
	//	return true;
	//}

	if (mBatlleTask == -1) {
#ifdef false
		mBatlleTask = TaskMgr::getInstance().Add(new BattleBase());
#else
		SaveData* save = AppData::GetInstance()->GetSaveData();
		Player* player = save->GetPlayer();
		//mBatlleTask = TaskMgr::getInstance().Add(new BattleBase(player));
		mBatlleTask = TaskMgr::getInstance().Add(BattleMgr::New());
#endif
	}
	else {
#if false
		BattleBase* battle = dynamic_cast<BattleBase*>(TaskMgr::getInstance().GetTask(mBatlleTask));
		if (battle == nullptr) {
			mBatlleTask = -1;
			return true;
		}
#else 

		if (BattleMgr::IsIntatance()) {
			return true;
		}

#endif
	}


	return false;
}