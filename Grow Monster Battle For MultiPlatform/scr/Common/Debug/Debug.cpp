/*
		ファイル名		:Debug.cpp
		作成者			:
		作成日時		:2017/12/30
		ソース説明		:デバッグ


		備考



!*/

#include"Common/GameCommon.h"
#include "Debug.h"

static const int DEBUG_WINDOW_LEFT = 0;
static const int DEBUG_WINDOW_TOP = 0;
static const int DEBUG_WINDOW_RIGHT = (600.0f * WINDOW_WIDTH / WINDOW_BASE_WIDTH);
static const int DEBUG_WINDOW_BOTTOM = (WINDOW_HEIGHT * WINDOW_HEIGHT / WINDOW_BASE_HEIGHT);

Debug::Debug() {
	mIsActive = false;
	mIsAssert = false;
	mOldAllocSize = 0;
	mOldAllocNum = 0;
}

Debug::~Debug() {}

bool Debug::ChcekActive() {

#ifdef __WINDOWS__
	if (Keyboard_Press(KEY_INPUT_N) == true) {
		mIsActive = ((mIsActive == true) ? false : true);
	}
#else 

	if (Touch_On(0) && Touch_Press(1)) {
		mIsActive = ((mIsActive == true) ? false : true);
	}

#endif

	return mIsActive;
}

void Debug::Initialize() {
	mOldAllocSize = DxGetAllocSize();
	mOldAllocNum = DxGetAllocNum();
}

void Debug::Finalize() {

}

bool Debug::Updata() {

	if (ChcekActive() == false) {
		return false;
	}

	return true;
}

void Debug::Draw() {

	if (mIsActive == false) return;

	//下地
	DrawBox(DEBUG_WINDOW_LEFT, DEBUG_WINDOW_TOP, DEBUG_WINDOW_RIGHT, DEBUG_WINDOW_BOTTOM, GetColor(123, 123, 123), TRUE);
	
	//一行目
	DrawString(0, 0, "デバッグメニュー", GetColor(0, 255, 0));

	size_t nowAlloc = DxGetAllocSize();
	float alloc = (nowAlloc - mOldAllocSize) / 1024.0f;
	int allocNum = DxGetAllocNum() - mOldAllocNum;
	DrawFormatString(DEBUG_WINDOW_LEFT, DEBUG_WINDOW_BOTTOM - 20, GetColor(255, 255, 255), "Alloc:%0.2fkb,NUM:%d", alloc,allocNum);

}