/*
				ファイル名		:TblLoaderMgr.cpp
				作成者			:
				作成日時		:2019/02/17
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "TblLoader.h"
#include "TblLoaderMgr.h"

namespace loader {

	TblLoaderMgr* TblLoaderMgr::mInstance = nullptr;

	TblLoaderMgr::TblLoaderMgr() {

	}

	TblLoaderMgr::~TblLoaderMgr() {

		Delete(mInstance);

	}

	void TblLoaderMgr::Create() {

		if (mInstance == nullptr) {
			mInstance = new TblLoaderMgr();
			int order = TaskMgr::getInstance().Add(mInstance);
			mInstance->mOrder = order;
		}

	}

	TblLoaderMgr* TblLoaderMgr::GetInstance() {
		if (mInstance == nullptr) {
			Create();
		}
		return mInstance;
	}

	TblLoader* TblLoaderMgr::LoadRequest(const char* fileName, bool isAsync/* = false*/) {

		TblLoader* add = new TblLoader();
		add->LoadRequest(fileName, isAsync);
		mLoadList.push_back(add);

		return add;

	}

	bool TblLoaderMgr::Initialize() {
		return true;
	}

	void TblLoaderMgr::Finalize() {

	}
	
	void TblLoaderMgr::PreviousUpdate() {

	}

	void TblLoaderMgr::InputUpdate() {

	}

	bool TblLoaderMgr::Updata() {

		for (int i = 0; i < mLoadList.size(); i++) {
			mLoadList[i]->Update();
		}
		return true;
	}

	void TblLoaderMgr::PostUpdate() {

		// 読み込みが終わったもしくはファイルが存在していなければロードリストから除外する
		for (auto itr = mLoadList.begin(); itr != mLoadList.end(); ) {
			TblLoader* load = *itr;
			if (load->IsExist() == false || load->IsLoadEnd() == true) {
				mLoadList.erase(itr);
				itr = mLoadList.begin();
				continue;
			}
			itr++;
		}

	}

	void TblLoaderMgr::Draw() {

	}

}


