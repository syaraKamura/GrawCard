/*
				ファイル名		:StoryData.cpp
				作成者			:
				作成日時		:2019/03/02
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "Common/FileLoader/TblLoader/TblLoader.h"
#include "Common/FileLoader/TblLoader/TblLoaderMgr.h"
#include "StoryData.h"

namespace story {

	StoryData::StoryData() {
		mLoad = loader::TblLoaderMgr::GetInstance()->LoadRequest("Resources/Data/Table/StoryData/StoryData.dtl");
	}

	StoryData::~StoryData() {

	}

	void StoryData::LoadData() {
		
		if (mLoad->IsLoadEnd()) {

			loader::TblLoader::TblData tblData = mLoad->GetTableData();

			int dataNum = tblData.GetDataNum(0, sizeof(STORY_DATA));
			STORY_DATA* addData = new STORY_DATA[dataNum];
			tblData.GetData(0, addData);

			for (int i = 0; i < dataNum; i++) {
				STORY_DATA& data = *(addData + i);
				mStoryData.push_back(data);
			}


		}

	}

	void StoryData::Update() {
		mLoad->Update();
	}

	bool StoryData::IsLoadEnd() {
		return (mLoad->IsLoadEnd() || mLoad->IsExist() == false);
	}


	AdvScript::ScriptBase* StoryData::RequestADV(int idx) {
		AdvScript::ScriptBase* script = new AdvScript::ScriptBase();
		char fileNaem[256];
		sprintfDx(fileNaem,"ADV_%04d.txt",idx);
		return new AdvScript::ScriptBase(fileNaem);
	}

}