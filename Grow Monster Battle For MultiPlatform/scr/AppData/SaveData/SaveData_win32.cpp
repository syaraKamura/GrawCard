/*
		ファイル名		:SaveData.cpp
		作成者			:
		作成日時		:2017/12/31
		ソース説明		:


		備考



!*/

//fopneエラー回避
#define _CRT_SECURE_NO_WARNINGS

#include "Common/GameCommon.h"
#include "SaveData.h"
#include "Common/FileIO/WriteBynary.h"
#include "Common/FileIO/ReadBynary.h"

#ifdef __WINDOWS__

SaveData::SaveData() {
	strcpyDx(mVersion, "1.00");

	memset(mFlag.mFlags, 0, sizeof(unsigned int) * MAX_FLAGS);

}

SaveData::~SaveData() {

}

SaveData* SaveData::Load() {
	SaveData* data = new SaveData();

	const char *path = GetFilePath();

#if false
	FILE *fp;
	fp = fopen(path, "rb");

	if (fp == NULL) {
		Debug::LogPrintf("not Found File.(%s)", path);
		return NULL;
	}

	/*
	ここに保存するデータを追加する
	*/
	int divSizeNum = GetAilmentSize(BASE_SIZE);

	//セーブデータ分のバイトのデータを読み込む
	//fread(&data, BASE_SIZE, divSizeNum, fp);
	fread(data, sizeof(SaveData), 1, fp);

	fclose(fp);

	if (data->HASTH != HASTH && strcmpDx(data->mVersion, mVersion) != 0) {
		Debug::LogPrintf("セーブデータが改ざんされています.", path);
		return NULL;
	}

#endif

	ReadBynary* mFile = new ReadBynary();
	bool isHack = false;
	bool isUpdate = false;

	//ファイルの読み込みが成功していたら
	if (mFile->Open("Test_%s", path) == true) {

		int hash = 0;
		char version[10];

		mFile->ReadInt(&hash);

		if (hash != this->HASTH) {
			isHack = true;
		}

		if (isHack == false) {

			mFile->ReadString(version);

			if (strcmpDx(version, this->mVersion) != 0) {

				float nowVersion = atofDx(this->mVersion);
				float oldVersion = atofDx(version);

				if (nowVersion > oldVersion) {
					isUpdate = true;
				}

			}

			//PlayerCharctor
			int level;
			char name[256] = "";
			int gender;
			int exp;
			int nextExp;
			int cost;
			Player* player = data->GetPlayer();

			mFile->ReadInt(&level);
			mFile->ReadString(name);
			mFile->ReadInt(&gender);
			mFile->ReadInt(&exp);
			mFile->ReadInt(&nextExp);
			mFile->ReadInt(&cost);

			player->SetLevel(level);
			player->SetName(name);
			player->SetGender((Player::eGender)gender);
			player->SetExp(exp);
			player->SetNextExp(nextExp);
			player->SetCost(cost);



			//デッキ
			for (int i = 0; i < 5; i++) {



				int level;
				char name[256] = "";
				int type;
				int exp;
				int nextExp;
				int hp;
				int maxHp;
				int mp;
				int maxMp;
				int atk;
				int def;
				int spd;
				int cost;

				mFile->ReadInt(&level);
				mFile->ReadString(name);
				mFile->ReadInt(&type);
				mFile->ReadInt(&exp);
				mFile->ReadInt(&nextExp);
				mFile->ReadInt(&hp);
				mFile->ReadInt(&maxHp);
				mFile->ReadInt(&mp);
				mFile->ReadInt(&maxMp);
				mFile->ReadInt(&atk);
				mFile->ReadInt(&def);
				mFile->ReadInt(&spd);
				mFile->ReadInt(&cost);

				Monster monster;

				monster.SetLevel(level);
				monster.SetName(name);
				monster.SetType((Monster::eType)type);
				monster.SetExp(exp);
				monster.SetNextExp(nextExp);
				monster.SetHp(hp);
				monster.SetHpMax(maxHp);
				monster.SetMp(mp);
				monster.SetMpMax(maxMp);
				monster.SetAttack(atk);
				monster.SetDeffence(def);
				monster.SetSpeed(spd);
				monster.SetCost(cost);

				data->GetPlayer()->SetMonster(i, monster);
			}

			//モンスターボックス
			int monsterNum = 0;

			mFile->ReadInt(&monsterNum);

			MonsterBox* monsterBox = data->GetMonsterBox();

			for (int i = 0; i < monsterNum; i++) {

				int level;
				char name[256] = "";
				int type;
				int exp;
				int nextExp;
				int hp;
				int maxHp;
				int mp;
				int maxMp;
				int atk;
				int def;
				int spd;
				int cost;

				mFile->ReadInt(&level);
				mFile->ReadString(name);
				mFile->ReadInt(&type);
				mFile->ReadInt(&exp);
				mFile->ReadInt(&nextExp);
				mFile->ReadInt(&hp);
				mFile->ReadInt(&maxHp);
				mFile->ReadInt(&mp);
				mFile->ReadInt(&maxMp);
				mFile->ReadInt(&atk);
				mFile->ReadInt(&def);
				mFile->ReadInt(&spd);
				mFile->ReadInt(&cost);

				Monster monster;

				monster.SetLevel(level);
				monster.SetName(name);
				monster.SetType((Monster::eType)type);
				monster.SetExp(exp);
				monster.SetNextExp(nextExp);
				monster.SetHp(hp);
				monster.SetHpMax(maxHp);
				monster.SetMp(mp);
				monster.SetMpMax(maxMp);
				monster.SetAttack(atk);
				monster.SetDeffence(def);
				monster.SetSpeed(spd);
				monster.SetCost(cost);


				monsterBox->Add(monster);

			}
		}

		for (int i = 0; i < MAX_FLAGS; i++) {
			unsigned int flag = 0;
			mFile->ReadUInt(&flag);
			mFlag.mFlags[i] = flag;
		}


		mFile->Close();
	}

	Delete(mFile);

	if (isHack == true) {
		return NULL;
	}

	if (isUpdate == true) {
		this->Save(*data);
	}

	return data;
}

void SaveData::Save(SaveData save) {

	const char *path = GetFilePath();

#if false
	FILE *fp;
	fp = fopen(path, "wb");

	if (fp == NULL) {
		Debug::LogPrintf("not Found File.(%s)", path);
		return;
	}

	/*
		ここに保存するデータを追加する
	*/

	int divSizeNum = GetAilmentSize(BASE_SIZE);

	
	//セーブデータ分のバイトのデータを一つ書き込む
	fwrite(&save, BASE_SIZE, divSizeNum, fp);

	fclose(fp);

#endif

	WriteBynary* mFile = new WriteBynary();

	mFile->Open("Test_%s", path);

	mFile->WriteInt(save.HASTH);
	
	mFile->WriteString(this->mVersion);
	

	//PlayerCharcter
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


	for (int i = 0; i < MAX_FLAGS;i++) {
		mFile->WriteUInt(mFlag.mFlags[i]);
	}

	mFile->Close();

	Delete(mFile)
}

/*
	セーブデータが存在するか確認する
	return	true	:存在している
			false	:存在していない
*/
bool SaveData::Exists() {

	const char *path = GetFilePath();

	FILE *fp;
	fp = fopen(path, "rb");

	if (fp == NULL) {
		return false;
	}

	fclose(fp);

	return true;
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
	設定した最小サイズで割り切れるようにサイズを調整して返却する
	int	size	:最小サイズ
	return アライメント後のサイズ
*/
int SaveData::GetAilmentSize(int size) {
	return GetAilmentSize(size, sizeof(SaveData));
}

/*
	指定番号のフラグを返却する
	int i	:	フラグ番号
	reutrn	:	0			:オフ
				1以上		:オン
*/
unsigned int SaveData::GetFlag(int i) {

	if (i < 0 || i >= MAX_FLAGS) {
		Debug::ErorrMessage("フラグデータの範囲外です");
		return 0;
	}
	return mFlag.mFlags[i];
}

/*
	フラグデータを返却する
	return	:	フラグデータ
*/
SaveData::FLAG_DATA_t* SaveData::GetFlagData() {
	return &mFlag;
}

/*
	フラグの状態
	int i			: フラグ番号
	return	true	:
			false	:
*/
bool SaveData::IsFlag(int i) {
	if (i < 0 || i >= MAX_FLAGS) {
		Debug::ErorrMessage("フラグデータの範囲外です");
		return 0;
	}
	return (mFlag.mFlags[i] == 1);
}

/*
	フラグの状態を設定する
	int i		: フラグ番号
	bool isFlag	: フラグを設定
*/
bool SaveData::SetFlag(int i, bool isFlag) {
	if (i < 0 || i >= MAX_FLAGS) {
		Debug::ErorrMessage("フラグデータの範囲外です");
		return 0;
	}
	return mFlag.mFlags[i] = isFlag ? 1 : 0;
}

/*
設定した最小サイズで割り切れるようにサイズを調整して返却する
int	size	:最小サイズ
return アライメント後のサイズ
*/
int SaveData::GetAilmentSize(int size,size_t dataSize) {

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
	return SAVE_DATA_PATH;
}



#endif	//__WINDOWS__