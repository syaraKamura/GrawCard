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

Debug::DEBUG_LOG_t Debug::mDebugStrings[DEBUG_LOG_NUM] = {};
int Debug::mDebugLogCnt = 0;

Debug::Debug() {
	mIsActive = false;
	mIsAssert = false;
	mOldAllocSize = 0;
	mOldAllocNum = 0;
	mDebugList = NULL;
	
}

Debug::~Debug() {

}

bool Debug::ChcekActive() {

#ifdef __WINDOWS__
	if (Keyboard_Press(KEY_INPUT_N) == true) {
		mIsActive = ((mIsActive == true) ? false : true);
	}
#else 

	//if (Touch_On(0) && Touch_Press(1)) {
	if (ClickInput::GetInstance()->On(0) && ClickInput::GetInstance()->Press(1)){
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

	if (mDebugList != NULL) {
		mDebugList->Update();
	}

	return true;
}

void Debug::Draw() {

	if (mIsActive == false) return;

#ifdef __ANDROID__
	// デバッグログを描画する(Andoroidのみ)

	unsigned int dbgStrColor = GetColor(255, 255, 255);
	for (int i = 0; i < DEBUG_LOG_NUM; i++) {
	
		DEBUG_LOG_t dbgLog = mDebugStrings[i];

		if (dbgLog.logType == 0) {
			dbgStrColor = GetColor(255, 255, 255);
		}
		else if (dbgLog.logType == 1) {
			dbgStrColor = GetColor(255,0, 0);
		}

		int posY = WINDOW_HEIGHT - 20;
		posY -= i * 20;

		DxLib::DrawString(1000, posY, dbgLog.str.c_str(), dbgStrColor);
	}

#endif

	//下地
	DrawBox(DEBUG_WINDOW_LEFT, DEBUG_WINDOW_TOP, DEBUG_WINDOW_RIGHT, DEBUG_WINDOW_BOTTOM, GetColor(123, 123, 123), TRUE);
	
	//一行目
	DrawString(0, 0, "デバッグメニュー", GetColor(0, 255, 0));

	//デバッグリスト描画
	if (mDebugList != NULL) {
		mDebugList->DrawDebugList();
	}

	//メモリのサイズと確保数
	size_t nowAlloc = DxGetAllocSize();
	float alloc = (nowAlloc - mOldAllocSize) / 1024.0f;
	int allocNum = DxGetAllocNum() - mOldAllocNum;
	DrawFormatString(DEBUG_WINDOW_LEFT, DEBUG_WINDOW_BOTTOM - 20, GetColor(255, 255, 255), "Alloc:%0.2fkb,NUM:%d", alloc,allocNum);

}


void Debug::DeleteList() {
	if (mDebugList != NULL) {
		Delete(mDebugList);
	}
}

/*
	出力ウィンドウに出力する(書式付き)
	const char*		str
	...
*/
void Debug::LogPrintf(const char* str, ...) {

#ifdef __MY_DEBUG__ 
	va_list ap;
	char buffer[1024];

	va_start(ap, str);
	vsprintfDx(buffer, str, ap);
	va_end(ap);
#ifdef __WINDOWS__
	OutputDebugString(buffer);
#elif __ANDROID__
	//printfDx(buffer);

	DEBUG_LOG_t add;
	add.logType = 0;
	add.str += buffer;
	mDebugStrings[mDebugLogCnt] = add;
	mDebugLogCnt = (mDebugLogCnt + 1) % DEBUG_LOG_NUM;

#endif	// __WINDOWS__

#endif //__MY_DEBUG__
}

void Debug::ErorrMessage(const TCHAR* str,...) {

#ifdef __MY_DEBUG__


	va_list ap;
	char buffer[1024 * 256];

	va_start(ap, str);
	vsprintfDx(buffer, str, ap);
	va_end(ap);
#ifdef __WINDOWS__
	MessageBox(NULL, _T(buffer), _T("エラーメッセージ"), MB_OK | MB_ICONERROR);
#elif __ANDROID__
	//printfDx(str);
	//AndroidNotification("エラーメッセージ", str);
	DEBUG_LOG_t add;
	add.logType = 1;
	add.str += buffer;
	mDebugStrings[mDebugLogCnt] = add;
	mDebugLogCnt = (mDebugLogCnt + 1) % DEBUG_LOG_NUM;

#endif

#endif

}

