/*
				ファイル名		:TblLoader.cpp
				作成者			:
				作成日時		:2019/02/17
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "TblLoader.h"

namespace loader {


	TblLoader::TblLoader() {
		mStateCnt = eState_Load;
		mIsAsync = false;
		mIsLoadEnd = false;
		mTableData = nullptr;
		mHandle = 0;
		memset(mFilePath, 0, sizeof(char) * 1024);
	}

	TblLoader::~TblLoader() {

	}

	bool TblLoader::LoadRequest(const char* filePath, bool isAsync /*= false*/) {

#ifdef __MY_DEBUG__
#ifdef __WINDOWS__
		RESORCES_PATH(mFilePath);
		strcatDx(mFilePath, "/");
#endif // __WINDOWS___
#endif
		
		strcatDx(mFilePath, filePath);

		mIsAsync = isAsync;


		return true;

	}

	void TblLoader::Update() {

		switch (mStateCnt) {
		case eState_Load:
			mHandle = DxLib::FileRead_open(mFilePath, mIsAsync ? TRUE : FALSE);
			if (mHandle == 0) {
				mStateCnt = eState_Error;
				mIsExist = false;
			}
			else {
				if (mIsAsync == true) {

					mStateCnt = eState_Wait;
				}
				else {

					mStateCnt = eState_Read;
				}
				mIsLoadEnd = false;
				mIsExist = true;
			}
			break;
		case eState_Wait:

			if (DxLib::CheckHandleASyncLoad(mHandle) == TRUE) {
				return;
			}


			mStateCnt = eState_Read;

			break;
		case eState_Read:
		{
			Header header;
			DxLib::FileRead_read(&header, sizeof(Header), mHandle);
			FileData* fileData = new FileData[header.dataNum];
			DxLib::FileRead_read(fileData, sizeof(FileData) * header.dataNum, mHandle);

			Data* resultData = new Data[header.dataNum];
			for (int i = 0; i < header.dataNum; i++) {
				FileData& data = *(fileData + i);
				char* buffer = new char[data.endOffset];
				DxLib::FileRead_read(buffer, data.endOffset, mHandle);
				(resultData + i)->buffer = buffer;
				(resultData + i)->dataSize = data.endOffset;

			}
			DxLib::FileRead_close(mHandle);


			TblData tdlData;
			tdlData.id = 0;
			tdlData.header = header;
			tdlData.fileData = fileData;
			tdlData.data = resultData;

			mTableData = new TblData(tdlData);
			mStateCnt = eState_End;
		}
		break;
		case eState_End:
			Debug::LogPrintf("tdlファイルの読み込み完了.(%s)\n", mFilePath);
			mIsLoadEnd = true;
			mStateCnt = eState_Exit;
			break;
		case eState_Error:
			Debug::ErorrMessage("tdlファイルの読み込みに失敗しました.\n(%s)", mFilePath);
			mStateCnt = eState_Exit;
			break;
		}

	}

	TblLoader::TblData& TblLoader::GetTableData() const {
		return *mTableData;
	}

	bool TblLoader::IsLoadEnd() {
		return mIsLoadEnd;
	}

	bool TblLoader::IsExist() {
		return mIsExist;
	}

}

