#ifndef __PRE_PROCESSOR_H__
#define __PRE_PROCESSOR_H__

#ifndef NDEBUG
	#define __MY_DEBUG__

#ifdef _WINDOWS
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
	#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif // _WINDOWS

#endif

#ifdef _WINDOWS
	#define __MY_WINDOWS__
	#define __WINDOWS__
#endif

#endif	//__PRE_PROCESSOR_H__