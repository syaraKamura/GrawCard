/*
				ファイル名		:AppData.cpp
				作成者			:
				作成日時		:2018/01/04
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "AppData.h"


AppData::AppData() {
	mSaveData = new SaveData();
}

AppData::~AppData() {
	//delete (mSaveData);
}

AppData AppData::GetInstance() {
	static AppData mInst = AppData();
	return mInst;
}


bool AppData::Exits() {
	if (mSaveData == NULL) {
		Debug::LogPrintf("mSaveData is Not Create Instance.");
		return false;
	}
	return mSaveData->Exists();
}

void AppData::Save() {
	mSaveData->Save(*mSaveData);
}

void AppData::Load() {
	
	//読み込み前の状態をバックアップ
	SaveData* mBackupSaveData = mSaveData;
	
	mSaveData = mSaveData->Load();

	//読み込みが失敗したら読み込み前のデータを設定
	if (mSaveData == NULL) {
		mSaveData = mBackupSaveData;
	}

}

SaveData* AppData::GetSaveData() {
	if (mSaveData == NULL) {
		Debug::LogPrintf("mSaveData is Not Create Instance.");
		return NULL;
	}
	return mSaveData;
}


void AppData::SetSaveData(SaveData saveData) {
	mSaveData = &saveData;
}
