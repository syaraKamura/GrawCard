/*
				ファイル名		:Easing.cpp
				作成者			:
				作成日時		:2018/07/21
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Easing.h"


float Easing::InQuad(float time, float totalTime, float min, float max) {

	max -= min;
	time /= totalTime;
	
	return max * time  * time + min;
}

float Easing::OutQuad(float time, float totalTime, float min, float max) {

	max -= min;
	time /= totalTime;

	return -max * time  * (time - 2.0f) + min;
	
}

float Easing::InOutQuad(float time, float totalTime, float min, float max) {

	max -= min;

	time /= totalTime;
	if (time / 2.0f < 1.0f) {
		return max / 2.0f * time*time + min;
	}

	time--;

	return -max * ((time) * (time - 2.0f) - 1.0f) + min;

}

float Easing::InCubic(float time, float totalTime, float min, float max) {
	
	max -= min;
	time /= totalTime;

	return max * time * time * time + min;

}

float Easing::OutCubic(float time, float totalTime, float min, float max) {

	max -= min;
	time /= totalTime - 1.0f;

	return max * (time * time * time + 1.0f) + min;
}

float Easing::InOutCubic(float time, float totalTime, float min, float max) {

	max -= min;
	time /= totalTime;

	if (time / 2.0f < 1.0f) {
		return max / 2.0f * time * time * time + min;
	}

	time -= 2.0f;

	return max / 2.0f * (time * time * time + 2.0f) + min;

}
