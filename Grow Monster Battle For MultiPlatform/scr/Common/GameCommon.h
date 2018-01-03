#ifndef __GAME_COMMON_H__
#define __GAME_COMMON_H__

#include "DxLib.h"
#include "../pre-processor.h"
#include "Common/Task/TaskMgr.h"
#include "Common/Fade/Fade.h"
#include "Common/Graphics/Graphics.h"
#include "Common/Graphics/GraphicsMulti.h"
#include "Common/Graphics/GraphicsDrawMgr.h"

#include "Common/Debug/Debug.h"

#include <math.h>
#include <string.h>

#ifdef __WINDOWS__
	#include "win32/KeyBoard.h"
#endif
#ifdef __ANDROID__
	#include "Android/Touch.h"
#endif

#define WINDOW_BASE_WIDTH 1920
#define WINDOW_BASE_HEIGHT 1080
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 750

#define Delete(x) {if(x!= NULL){delete x;x = 0;}}
#define DeleteArry(x) {if(x!= NULL){delete[] x;x = 0;}}

typedef void(*pointer_func)(void);





#endif 