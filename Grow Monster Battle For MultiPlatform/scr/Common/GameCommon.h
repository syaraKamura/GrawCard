#ifndef __GAME_COMMON_H__
#define __GAME_COMMON_H__

#include "DxLib.h"
#include "../pre-processor.h"
#include "Common/Task/TaskMgr.h"
#include "Common/Fade/Fade.h"
#include "Common/Graphics/Graphics.h"
#include "Common/Graphics/GraphicsMulti.h"
#include "Common/Graphics/GraphicsDrawMgr.h"
#include "Common/CommonResource/CommonResource.h"
#include "Common/XML/XmlPurser.h"

#include "Common/Debug/Debug.h"
#include "Common/Debug/DebugList.h"

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>

#ifdef __WINDOWS__
	#include <Windows.h>
	#include "win32/KeyBoard.h"
#endif
#ifdef __ANDROID__
	#include "Android/TouchInput.h"
#endif

#define WINDOW_BASE_WIDTH 1920
#define WINDOW_BASE_HEIGHT 1080
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 750

#define Delete(x) {if(x != NULL){delete x;x = NULL;}}
#define DeleteArry(x) {if(x!= NULL){delete[] x;x = NULL;}}

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