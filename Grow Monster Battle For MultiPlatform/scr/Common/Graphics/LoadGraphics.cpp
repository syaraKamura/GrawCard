/*
				ファイル名		:LoadGraphics.cpp
				作成者			:
				作成日時		:2019/03/20
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "LoadGraphics.h"

namespace graphics {

	int Loader::LoadResource(std::string fileName) {

		char filePath[1024]={};

		strcatDx(filePath, fileName.c_str());

#ifdef __WINDOWS__ 
#ifdef  __MY_DEBUG__

		RESORCES_PATH(filePath);

#endif
#endif
		
		int handle = DxLib::FileRead_open(filePath);

		if (handle == 0) {
			Debug::LogPrintf("Not Exist Graphics File.(%s)\n");
			return -1;
		}

		DxLib::FileRead_close(handle);

		return DxLib::LoadGraph(filePath);
	}

	void Loader::DestoryResource(int handle) {
		DxLib::DeleteGraph(handle);
	}


	bool LoadGraphics::Load(std::string fileName,std::string tag) {
		if (mLoader.LoadASync(fileName)) {
			mTag.insert(std::make_pair(tag, fileName));
			return true;
		}
		return false;
	}

	void LoadGraphics::Destroy(int handle) {
		mLoader.DestoryResource(handle);
	}

	void LoadGraphics::Destroy(std::string tag) {
		
		auto it = mTag.find(tag);

		if (it != mTag.end()) {
			std::string& fileName = (*it).second;
			mLoader.Destory(fileName);
		}

	}

	int LoadGraphics::Get(std::string tag) {

		auto it = mTag.find(tag);

		if (it != mTag.end()) {
			std::string fileName = (*it).second;
			return mLoader.Get(fileName);
		}

		return -1;
	}
}