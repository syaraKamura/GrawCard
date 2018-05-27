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

/*

非同期読み読み込み
*/
bool ResourceLoader::LoadASync(std::string fileName) {

	int handle = -1;
	SetUseASyncLoadFlag(TRUE);
	
	handle = LoadResource(fileName);

	SetUseASyncLoadFlag(FALSE);


	if (handle == -1)	return false;
	
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

	//一覧になければ読み恋を開始する
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