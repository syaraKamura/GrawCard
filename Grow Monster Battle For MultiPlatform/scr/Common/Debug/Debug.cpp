/*
		ファイル名		:Debug.cpp
		作成者			:
		作成日時		:2017/12/30
		ソース説明		:デバッグ


		備考



!*/

#include"Common/GameCommon.h"
#include "Debug.h"

#if __ANDROID__

#include <android/log.h>
#define  LOG_TAG	"GrawCard"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#endif // __ANDROID__

static const int DEBUG_WINDOW_LEFT = 0;
static const int DEBUG_WINDOW_TOP = 0;
static const int DEBUG_WINDOW_RIGHT = (600.0f * WINDOW_WIDTH / WINDOW_BASE_WIDTH);
static const int DEBUG_WINDOW_BOTTOM = (WINDOW_HEIGHT * WINDOW_HEIGHT / WINDOW_BASE_HEIGHT);

static const int INFOBOARD_MAX = 100;

enum eDEBUG_PRINT_TYPE {
	eDEBUG_PRINT_TYPE_None,
	eDEBUG_PRINT_TYPE_Warning,
	eDEBUG_PRINT_TYPE_Error,
};

struct POSITION {
	float x;
	float y;
};

struct INFOBOARD_DATA {
	char info[1024];
	int count;
	bool isSet;
	POSITION pos;
	unsigned int color;
};

Debug::DEBUG_LOG_t Debug::mDebugStrings[DEBUG_LOG_NUM] = {};
int Debug::mDebugLogCnt = 0;
bool Debug::mIsVisibleInfoBard = true;

int mInfobardPosY = 0;


INFOBOARD_DATA mInfoBoardData[INFOBOARD_MAX];

void InfoBard_Init() {

	memset(mInfoBoardData, 0, sizeof(INFOBOARD_DATA) * INFOBOARD_MAX);
	for (int i = 0; i < INFOBOARD_MAX; i++) {
		mInfoBoardData[i].isSet = false;
	}
	mInfobardPosY = 0;
}


void InfoBoard_Update() {

	for (int i = 0; i < INFOBOARD_MAX; i++) {
		INFOBOARD_DATA& data = mInfoBoardData[i];
		if (data.isSet == true) {
			data.count++;
			if (data.count < 30) {
				data.pos.x = WINDOW_WIDTH - 1200.0f * data.count / 30.0f;
			}
			if (data.count >= 210 && data.count <= 240) {
				int t = data.count - 210;
				data.pos.x = WINDOW_WIDTH - 1200.0f * (1 - t / 30.0f);
			}
			if (data.count >= 241) {
				data.isSet = false;
			}
		}
	}
}

void InfoBoard_Draw() {
	for (int i = 0; i < INFOBOARD_MAX; i++) {
		INFOBOARD_DATA& data = mInfoBoardData[i];
		if (data.isSet == true) {
			int x = data.pos.x;
			int y = data.pos.y;
			int width = WINDOW_WIDTH;
			int height = y + 20;
			DrawBox(x, y, width, height, GetColor(255, 255, 255), TRUE);
			DrawString(x, y, data.info, data.color);
		}
	}
}

unsigned int _GetColor(eDEBUG_PRINT_TYPE type) {
	switch (type) {
		case eDEBUG_PRINT_TYPE_None:
			return GetColor(0, 0, 0);
		case eDEBUG_PRINT_TYPE_Warning:
			return GetColor(255, 255, 0);
		case eDEBUG_PRINT_TYPE_Error:
			return GetColor(255, 0, 0);
	}
}

void InfoBard_SetString(const char* info,eDEBUG_PRINT_TYPE type) {
	
	for (int i = 0; i < INFOBOARD_MAX; i++) {
		INFOBOARD_DATA& data = mInfoBoardData[i];
		if (data.isSet == false) {
			strcpyDx(data.info,info);
			data.count = 0;
			data.color = _GetColor(type);
			data.pos.x = WINDOW_WIDTH;
			data.pos.y = mInfobardPosY;
			mInfobardPosY += 20;
			if (mInfobardPosY >= WINDOW_HEIGHT - 20) {
				mInfobardPosY = 0;
			}
			data.isSet = true;
			break;
		}
	}

}

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

	InfoBard_Init();

}

void Debug::Finalize() {

}

bool Debug::Updata() {

	if (ChcekActive() == false) {
		InfoBoard_Update();
		return false;
	}

	if (mDebugList != NULL) {
		mDebugList->Update();
	}

	return true;
}

void Debug::Draw() {

	if (mIsActive == false) {
		InfoBoard_Draw();
		return;
	}

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

	LOGI(buffer);

#endif	// __WINDOWS__
	if (mIsVisibleInfoBard == true) {
		InfoBard_SetString(buffer, eDEBUG_PRINT_TYPE_None);
	}

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

	LOGE(buffer);
	

#endif
	if (mIsVisibleInfoBard == true) {
		InfoBard_SetString(buffer, eDEBUG_PRINT_TYPE_Error);
	}
#endif

}

