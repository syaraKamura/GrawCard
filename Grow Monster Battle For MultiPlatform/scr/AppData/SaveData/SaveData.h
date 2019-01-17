/*
		ファイル名		:SaveData.h
		作成者			:
		作成日時		:2017/12/31
		ソース説明		:セーブデータ


		備考



!*/

#ifndef __SAE_DATA_H__
#define __SAE_DATA_H__

#define SAVE_HASH(S,A,V,E,N) ((S << 16) + (A << 8) + (V << 4) + (E << 2) + (N))
#define SAVE_DATA_PATH "saveData.txt"
#define BASE_SIZE (32)

#include "AppData/Character/Player/Player.h"
#include "AppData/Character/Monster/MonsterBox.h"

class SaveData {

public :

	static const int MAX_FLAGS = 1024;

private:

	const int HASTH = SAVE_HASH('M','A','K','E','0');

public:

	typedef struct FLAG_DATA_t {
		unsigned int mFlags[MAX_FLAGS];
	}FLAG_DATA_t;

private:

	char mVersion[4];

	//プレイヤーデータ
	Player mPlayer;

	//モンスターボックスデータ
	MonsterBox mMonsterBox;

	FLAG_DATA_t mFlag;

private:
	
	/*
		設定した最小サイズで割り切れるようにサイズを調整して返却する
		int	size	:最小サイズ
		return アライメント後のサイズ
	*/
	int GetAilmentSize(int size);
	int GetAilmentSize(int size, size_t dataSize);
	/*
		ファイルパスを返却する
	*/
	const char* GetFilePath();

public :

	SaveData();
	~SaveData();

	SaveData* Load();
	void Save(SaveData save);
	
	/*
		セーブデータが存在するか確認する
	*/
	bool Exists();

	MonsterBox* GetMonsterBox();
	Player* GetPlayer();

	unsigned int GetFlag(int i);
	FLAG_DATA_t* GetFlagData();
	bool IsFlag(int i);
	bool SetFlag(int i,bool isFlag);

};

#endif //__SAE_DATA_H__