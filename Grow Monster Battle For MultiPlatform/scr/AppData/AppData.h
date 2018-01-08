/*
				ファイル名		:AppData.h
				作成者			:
				作成日時		:2017/01/04
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __APP_DATA_H__
#define __APP_DATA_H__

#include "SaveData/SaveData.h"

class AppData {

private:

	SaveData* mSaveData;
	static AppData mInst;

private:

	AppData();
	

public:

	~AppData();

	static AppData GetInstance();

	void Save();
	void Load();

	SaveData* GetSaveData();
	void SetSaveData(SaveData saveData);

	bool Exits();


};

#endif // __APP_DATA_H__