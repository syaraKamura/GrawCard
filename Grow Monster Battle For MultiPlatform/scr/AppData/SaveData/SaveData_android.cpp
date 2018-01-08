/*
		ファイル名		:SaveData.cpp
		作成者			:
		作成日時		:2017/12/31
		ソース説明		:


		備考



!*/

#include "Common/GameCommon.h"
#include "SaveData.h"

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
	
	char path[256] = {};

	GetExternalDataPath(path, sizeof(path));

	strcatDx(path, "/");
	strcatDx(path, SAVE_DATA_PATH);

	return path;
}

#endif	//__ANDROID__
