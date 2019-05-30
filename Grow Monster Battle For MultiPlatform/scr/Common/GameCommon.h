#ifndef __GAME_COMMON_H__
#define __GAME_COMMON_H__

#include "DxLib.h"
#include "../pre-processor.h"
#include "Common/Task/TaskMgr.h"
#include "Common/Fade/Fade.h"
#include "Common/Graphics/LoadGraphics.h"
#include "Common/Graphics/Graphics.h"
#include "Common/Graphics/GraphicsMulti.h"
#include "Common/Graphics/GraphicsDrawMgr.h"
#include "Common/Sound/SoundMgr.h"
#include "Common/CommonResource/CommonResource.h"
#include "Common/XML/XmlPurser.h"
#include "Common/Effect/Effect.h"

#include "Common/Debug/Debug.h"
#include "Common/Debug/DebugList.h"

#include "AppData/AppData.h"
#include "AppData/Character/Monster/MonsterMgr.h"

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

#ifdef __WINDOWS__
	#include <Windows.h>
	#include "win32/KeyBoard.h"

	//#include "win32/MouseInput.h"
#endif
#ifdef __ANDROID__
	//#include "Android/TouchInput.h"
#endif

#include "Input/ClickInput.h"

#define WINDOW_BASE_WIDTH 1920
#define WINDOW_BASE_HEIGHT 1080
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080


#define Delete(x) {if(x != nullptr){delete x;x = nullptr;}}
#define DeleteArry(x) {if(x!= nullptr){delete[] x;x = nullptr;}}
#define ArrySize(x) (sizeof(x)/sizeof(x[0]))

#ifdef __WINDOWS__
#ifdef __MY_DEBUG__
#define RESORUCES_ENV_NAME "GC_DATA_ROOT"		//リソース環境変数名
#define __USE_OUTSIDE_DIRECTORY__				//外部ファイルディレクトリのリソースを読み込む

#ifdef __USE_OUTSIDE_DIRECTORY__
#define RESORCES_PATH(path) {					\
		std::string output;						\
		char env[256];								\
		GetDupenv(RESORUCES_ENV_NAME,&output);	\
		strcpyDx(env, output.c_str());					\
		strcatDx(env, "/");						\
		strcatDx(env, path);						\
		strcpyDx((char*)path,env);				\
}
#else
#define RESORCES_PATH(path)
#endif

/*
	環境変数取得
	return	true	:成功
			false	:失敗
	備考			:http://d.hatena.ne.jp/nurs/20150104/1420384422 を参考にしました
*/
inline bool GetDupenv(const char* env,std::string* val) {
	
	char* buf = 0;
	size_t sz = 0;
	if (_dupenv_s(&buf, &sz, env) == 0)
	{
		
		if (buf == NULL)
		{
			//環境変数が存在していなかった
			return false;
		}
		
		*val = buf;
		free(buf);
	}
	else
	{
		return false;
	}
	return true;
}

#endif

#endif

typedef void(*pointer_func)(void);


namespace my_std {

	template < typename T >
	inline std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}

};

#endif 