/*
				ファイル名		:Loader.cpp
				作成者			:
				作成日時		:2018/05/20
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include <fstream>
#include <Common/GameCommon.h>
#include "Loader.h"

Loader* Loader::mInst = NULL;

Loader::Loader() {
	
}

Loader::~Loader() {

}

void Loader::Create() {	
	mInst = new Loader();
}

void Loader::Destory() {
	delete mInst;
}

Loader* Loader::Instance(){
	return mInst;
}

File* Loader::CreateFile(File** file,const char* filePath) {

	if (*file == NULL) {

		Debug::ErorrMessage("引数[file]がNULLポインターです。");
		return NULL;
	}

	*file = new File(filePath);
	mFileList.push_back(*file);

	return *file;
}

void Loader::DeleteFile(File** file) {

	if ((*file) == NULL) return;
	if (mFileList.size() == 0) return;

	for (auto itr = mFileList.begin(); itr != mFileList.end(); itr++) {

		if ((*itr) == (*file)) {
			Delete((*file));
			mFileList.erase(itr);
			(*file) = NULL;
		}
	}

}

void Loader::Update() {

	if (mFileList.size() == 0) return;

	for (auto itr = mFileList.begin(); itr != mFileList.end(); itr++) {
		File* i = (*itr);

		//読み込みが終了していないファイルを読み込む
		if (i->IsReady() == false) {
			
			std::ifstream file;


			//読み込み
			file.open(i->mFileName, std::ios::in);

			if (!file.is_open()) {
				Debug::ErorrMessage("ファイルを開けませんでした.");
				break;
			}

			int begin = (int)file.tellg();
			file.seekg(0, file.end);
			int end = (int)file.tellg();

			int size = end - begin;

			

			char* data = new char[size + 1];

			file.clear();
			file.seekg(0, file.beg);

			file.read(data, size);

			if (data != NULL) {
				i->mSize = size;
				i->mFileData = (const char*)data;
			}

			file.close();

			DeleteArry(data);

			break;
		}
	}

}