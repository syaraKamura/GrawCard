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

public :

	enum eAPPDATA_FLAG {
		eAPPDATA_FLAG_DipsOpenRogue = 100,

		eAPPDATA_FLAG_Max = SaveData::MAX_FLAGS,
	};

private:

	SaveData* mSaveData;
	static AppData* mInst;

private:

	AppData();
	
	~AppData();

public:

	

	static void Create();
	static void Destory();

	static AppData* GetInstance();

	void Save();
	void Load();

	SaveData* GetSaveData() const;
	void SetSaveData(SaveData saveData);

	bool Exits();


};

#endif // __APP_DATA_H__