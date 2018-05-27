/*
				ファイル名		:File.cpp
				作成者			:
				作成日時		:2018/05/19
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include<Common/GameCommon.h>
#include<fstream>
#include "File.h"


File::File(const char* filePath) {

	this->mFileName = filePath;
	this->mSize = 0;
	this->mFileData = NULL;
}

File::~File() {
	DeleteArry(this->mFileData);
}

const char* File::GetFile() {
	return this->mFileData;
}

int  File::Size() {
	return mSize;
}

bool File::IsReady() {
	return (mSize > 0);
}