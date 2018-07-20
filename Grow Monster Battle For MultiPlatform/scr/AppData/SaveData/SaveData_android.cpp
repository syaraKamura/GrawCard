/*
		ファイル名		:SaveData.cpp
		作成者			:
		作成日時		:2017/12/31
		ソース説明		:


		備考



!*/

#include "Common/GameCommon.h"
#include "SaveData.h"
#include "Common/FileIO/WriteBynary.h"
#include "Common/FileIO/ReadBynary.h"

#ifdef __ANDROID__

SaveData::SaveData() {
	strcpyDx(mVersion, "1.00");
}

SaveData::~SaveData() {

}

SaveData* SaveData::Load() {
	SaveData* data = new SaveData();

	const char* path = GetFilePath();

	FILE *fp;
	fp = fopen(path, "rb");

	if (fp == NULL) {
		Debug::LogPrintf("not Found File.(%s)", path);
		return NULL;
	}

	/*
	ここに保存するデータを追加する
	*/

	const int divSizeNum = GetAilmentSize(BASE_SIZE);

	//セーブデータ分のバイトのデータを一つ書き込む
	fread(data, BASE_SIZE, divSizeNum, fp);

	fclose(fp);

	if (data->HASTH != HASTH && strcmpDx(data->mVersion, mVersion) != 0) {
		Debug::LogPrintf("セーブデータが改ざんされています.", path);
		return NULL;
	}

	return data;
}

void SaveData::Save(SaveData save) {

	const char* path = GetFilePath();

	FILE *fp;
	fp = fopen(path, "wb");

	if (fp == NULL) {
		Debug::LogPrintf("not Found File.(%s)",path);
		return ;
	}


	/*
		ここに保存するデータを追加する
	*/

	const int divSizeNum = GetAilmentSize(BASE_SIZE);

	//セーブデータ分のバイトのデータを一つ書き込む
	fwrite(&save, sizeof(save), divSizeNum,fp);

	fclose(fp);


	WriteBynary* mFile = new WriteBynary();

	mFile->Open("Test_%s",path);

	mFile->WriteInt(save.HASTH);

	//モンスターボックス
	int monsterNum = save.GetMonsterBox()->Count();

	mFile->WriteInt(monsterNum);

	for (int i = 0; i < monsterNum; i++) {

		int level = save.GetMonsterBox()->GetMonster(i).GetLevel();
		const char* name = save.GetMonsterBox()->GetMonster(i).GetName();
		int type = (int)save.GetMonsterBox()->GetMonster(i).GetType();
		int exp = save.GetMonsterBox()->GetMonster(i).GetExp();
		int nextExp = save.GetMonsterBox()->GetMonster(i).GetNextExp();
		int hp = save.GetMonsterBox()->GetMonster(i).GetHp();
		int maxHp = save.GetMonsterBox()->GetMonster(i).GetHpMax();
		int mp = save.GetMonsterBox()->GetMonster(i).GetMp();
		int maxMp = save.GetMonsterBox()->GetMonster(i).GetMpMax();
		int atk = save.GetMonsterBox()->GetMonster(i).GetAttack();
		int def = save.GetMonsterBox()->GetMonster(i).GetDeffence();
		int spd = save.GetMonsterBox()->GetMonster(i).GetSpeed();
		int cost = save.GetMonsterBox()->GetMonster(i).GetCost();

		mFile->WriteInt(level);
		mFile->WriteString(name);
		mFile->WriteInt(type);
		mFile->WriteInt(exp);
		mFile->WriteInt(nextExp);
		mFile->WriteInt(hp);
		mFile->WriteInt(maxHp);
		mFile->WriteInt(mp);
		mFile->WriteInt(maxMp);
		mFile->WriteInt(atk);
		mFile->WriteInt(def);
		mFile->WriteInt(spd);
		mFile->WriteInt(cost);

	}

	//PlayerCharctor
	int level = save.GetPlayer()->GetLevel();
	const char* name = save.GetPlayer()->GetName();
	int gender = save.GetPlayer()->GetGender();
	int exp = save.GetPlayer()->GetExp();
	int nextExp = save.GetPlayer()->GetNextExp();
	int cost = save.GetPlayer()->GetCost();

	mFile->WriteInt(level);
	mFile->WriteString(name);
	mFile->WriteInt(gender);
	mFile->WriteInt(exp);
	mFile->WriteInt(nextExp);
	mFile->WriteInt(cost);
	
	//デッキ
	for (int i = 0; i < 5; i++) {

		Monster monster = *save.GetPlayer()->GetMonster(i);

		int level = monster.GetLevel();
		const char* name = monster.GetName();
		int type = (int)monster.GetType();
		int exp = monster.GetExp();
		int nextExp = monster.GetNextExp();
		int hp = monster.GetHp();
		int maxHp = monster.GetHpMax();
		int mp = monster.GetMp();
		int maxMp = monster.GetMpMax();
		int atk = monster.GetAttack();
		int def = monster.GetDeffence();
		int spd = monster.GetSpeed();
		int cost = monster.GetCost();

		mFile->WriteInt(level);
		mFile->WriteString(name);
		mFile->WriteInt(type);
		mFile->WriteInt(exp);
		mFile->WriteInt(nextExp);
		mFile->WriteInt(hp);
		mFile->WriteInt(maxHp);
		mFile->WriteInt(mp);
		mFile->WriteInt(maxMp);
		mFile->WriteInt(atk);
		mFile->WriteInt(def);
		mFile->WriteInt(spd);
		mFile->WriteInt(cost);

	}



}

/*
モンスターボックスのデータを返却する
*/
MonsterBox* SaveData::GetMonsterBox() {
	return &mMonsterBox;
}

/*
プレイヤーデータを返却する
*/
Player* SaveData::GetPlayer() {
	return &mPlayer;
}

/*
	セーブデータが存在するか確認する
	return	true	:存在している
	false	:存在していない
*/
bool SaveData::Exists() {

	const char* path = GetFilePath();

	FILE *fp;
	fp = fopen(path, "rb");

	if (fp == NULL) {
		return false;
	}

	fclose(fp);

	return true;
}


/*
設定した最小サイズで割り切れるようにサイズを調整して返却する
int	size	:最小サイズ
return アライメント後のサイズ
*/
int SaveData::GetAilmentSize(int size) {
	return GetAilmentSize(size, sizeof(SaveData));
}

/*
設定した最小サイズで割り切れるようにサイズを調整して返却する
int	size	:最小サイズ
return アライメント後のサイズ
*/
int SaveData::GetAilmentSize(int size, size_t dataSize) {

	int baseSize = size;

	if (dataSize % baseSize != 0) {
		dataSize += baseSize - (dataSize % baseSize);
	}

	const int divSizeNum = dataSize / baseSize;

	return  divSizeNum;
}

/*
セーブデータのファイルパスを返却する
*/
const char* SaveData::GetFilePath() {
	
	static char path[256] = {};

	GetExternalDataPath(path, sizeof(path));

	strcatDx(path, "/");
	strcatDx(path, SAVE_DATA_PATH);

	return path;
}

#endif	//__ANDROID__
