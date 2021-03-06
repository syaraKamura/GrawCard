﻿/*
				ファイル名		:Easing.cpp
				作成者			:
				作成日時		:2018/07/21
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Easing.h"


float Easing::InQuad(float time, float totalTime, float min, float max) {

	
	time /= totalTime;
	
	return max * time  * time + min;
}

float Easing::OutQuad(float time, float totalTime, float min, float max) {

	
	time /= totalTime;

	return -max * time  * (time - 2.0f) + min;
	
}

float Easing::InOutQuad(float time, float totalTime, float min, float max) {

	time /= totalTime / 2.0f;
	if (time < 1.0f) {
		return max / 2.0f * time*time + min;
	}

	time--;

	return -max * (time * (time - 2.0f) - 1.0f) + min;

}

float Easing::InCubic(float time, float totalTime, float min, float max) {
	
	
	time /= totalTime;

	return max * time * time * time + min;

}

float Easing::OutCubic(float time, float totalTime, float min, float max) {

	
	time /= totalTime;
	time -= 1.0f;

	return max * (time * time * time + 1.0f) + min;
}

float Easing::InOutCubic(float time, float totalTime, float min, float max) {

	
	time /= totalTime / 2.0f;

	if (time < 1.0f) {
		return max / 2.0f * time * time * time + min;
	}

	time -= 2.0f;

	return max / 2.0f * (time * time * time + 2.0f) + min;

}

float Easing::EasingValue(Easing::eEasingType type, float time, float totalTime, float min, float max) {

	float ret = 0.0f;
	bool isReverse = false;
	max -= min;
	if (min > max) {
		//float buff = min;
		//min = max;
		//max = buff;
		//isReverse = true;
	}
	else if (min == max) {
		return min;
	}

	if (type == Easing::eEasingType_None) {
		
		time /= totalTime;
		ret =  max * time + min;
	}

	switch (type) {
	case Easing::eEasingType_InQuad:
		ret = InQuad(time, totalTime, min, max);
		break;
	case Easing::eEasingType_OutQuad:
		ret = OutQuad(time, totalTime, min, max);
		break;
	case Easing::eEasingType_InOutQuad:
		ret = InOutQuad(time, totalTime, min, max);
		break;
	case Easing::eEasingType_InCubic:
		ret = InCubic(time, totalTime, min, max);
		break;
	case Easing::eEasingType_OutCubic:
		ret = OutCubic(time, totalTime, min, max);
		break;
	case Easing::eEasingType_InOutCubic:
		ret = InOutCubic(time, totalTime, min, max);
		break;
	}

	return (isReverse == true ) ? min - ret: ret;
}