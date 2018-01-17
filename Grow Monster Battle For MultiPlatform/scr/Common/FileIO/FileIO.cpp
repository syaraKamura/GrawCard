/*
				ファイル名		:FileIO.cpp
				作成者			:
				作成日時		:2018/01/17
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "FileIO.h"


FileIO::FileIO() {
	mFilePointer = NULL;
	mAddress = 0;
	memset(mBuffer, 0, sizeof(unsigned char) * FILE_DATA_SIZE);
}


FileIO::~FileIO() {
	mFilePointer = NULL;
	mAddress = 0;
	memset(mBuffer, 0, sizeof(unsigned char) * FILE_DATA_SIZE);
}


