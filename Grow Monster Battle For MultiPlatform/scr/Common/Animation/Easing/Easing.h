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

private:

public :

	static float InQuad(float time, float totalTime, float min, float max);
	static float OutQuad(float time, float totalTime, float min, float max);
	static float InOutQuad(float time, float totalTime, float min, float max);
	
	static float InCubic(float time, float totalTime, float min, float max);
	static float OutCubic(float time, float totalTime, float min, float max);
	static float InOutCubic(float time, float totalTime, float min, float max);

};


#endif // __EASING_H__