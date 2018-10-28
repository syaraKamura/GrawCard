/*
				ファイル名		:Easing.h
				作成者			:
				作成日時		:2018/07/21
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __EASING_H__
#define __EASING_H__

class Easing {

public :

	enum eEasingType {
		eEasingType_None,
		eEasingType_InQuad,
		eEasingType_OutQuad,
		eEasingType_InOutQuad,
		eEasingType_InCubic,
		eEasingType_OutCubic,
		eEasingType_InOutCubic,
	};

private:

public :

	static float InQuad(float time, float totalTime, float min, float max);
	static float OutQuad(float time, float totalTime, float min, float max);
	static float InOutQuad(float time, float totalTime, float min, float max);
	
	static float InCubic(float time, float totalTime, float min, float max);
	static float OutCubic(float time, float totalTime, float min, float max);
	static float InOutCubic(float time, float totalTime, float min, float max);

	static float EasingValue(eEasingType type,float time, float totalTime, float min, float max);

};


#endif // __EASING_H__