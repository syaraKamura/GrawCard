/*
				ファイル名		:ResourceLoader.cpp
				作成者			:
				作成日時		:2018/05/12
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "ResourceLoader.h"


ResourceLoader::ResourceLoader() {
	
}

ResourceLoader::~ResourceLoader() {

}

int ResourceLoader::LoadResource(std::string fileName) {
	return -1;
}

void ResourceLoader::DestoryResource(int handle) {

}

bool ResourceLoader::CheckFileExists(std::string fileName) {
#ifdef __MY_DEBUG__
#ifdef __WINDOWS__
	char filePath[2048];
	strcpyDx(filePath, fileName.c_str());

	RESORCES_PATH(filePath);

	FILE *fp;
	fopen_s(&fp, filePath, "r");
	if (fp == nullptr) {
		Debug::LogPrintf("Not Exist File.(%s)\n", fileName.c_str());
		return false;
	}
	fclose(fp);
#endif // __WINDOWS__
#endif // __MY_DEBUG__
	return true;
}
/*

非同期読み読み込み
*/
bool ResourceLoader::LoadASync(std::string fileName,int* pOutHandle) {

	int handle = -1;
	if (CheckFileExists(fileName) == false ) {
		return false;
	}
	SetUseASyncLoadFlag(TRUE);
	
	handle = LoadResource(fileName);

	SetUseASyncLoadFlag(FALSE);


	if (handle == -1)	return false;
	if (pOutHandle != nullptr) {
		*pOutHandle = handle;
	}
	
	mResourceList.insert(std::make_pair(fileName,handle));
	
	return true;
}

int ResourceLoader::Get(std::string fileName) {

	auto it = mResourceList.find(fileName);
	int handle = -1;

	if(it != mResourceList.end())
	{
		if ((*it).first == fileName) {
			handle = (*it).second;
			while (CheckHandleASyncLoad(handle) == TRUE) {
				ProcessMessage();
			}

			return handle;
		}
	}

	//一覧になければ読み込みを開始する
	if (LoadASync(fileName)) {
		return Get(fileName);
	}
	
	return -1;
}


bool ResourceLoader::Destory(std::string fileName) {
	
	auto it = mResourceList.find(fileName);
	
	if (it != mResourceList.end()) {

		DestoryResource((*it).second);
		mResourceList.erase((*it).first);

		return true;
	}
	return false;
}