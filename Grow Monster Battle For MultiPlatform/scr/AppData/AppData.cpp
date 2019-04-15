/*
				ファイル名		:AppData.cpp
				作成者			:
				作成日時		:2018/01/04
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "AppData.h"

AppData* AppData::mInst = nullptr;

AppData::AppData() {
	mSaveData = new SaveData();
}

AppData::~AppData() {
	Delete (mSaveData);
}

AppData* AppData::GetInstance() {
	if (mInst == nullptr) {
		Create();
	}
	return mInst;
}


bool AppData::Exits() {
	if (mSaveData == nullptr) {
		Debug::ErorrMessage("mSaveData is Not Create Instance.");
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
	
	//読み込みが失敗したら読み込み前のデータを設定
	if (mSaveData->Load(mSaveData) == false) {
		mSaveData = mBackupSaveData;
	}

}

SaveData* AppData::GetSaveData() const {
	if (mSaveData == nullptr) {
		Debug::ErorrMessage("mSaveData is Not Create Instance.");
		return nullptr;
	}
	return mSaveData;
}


void AppData::SetSaveData(SaveData saveData) {
	mSaveData = &saveData;
}


void AppData::Create() {
	mInst = new AppData();
}

void AppData::Destory() {
	Delete(mInst);
}