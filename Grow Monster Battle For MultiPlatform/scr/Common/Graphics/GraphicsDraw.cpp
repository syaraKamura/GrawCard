/*
				ファイル名		:GraphicsDraw.cpp
				作成者			:
				作成日時		:
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include<stdio.h>
#include "GraphicsDraw.h"

GraphicsDraw::GraphicsDraw() {

	mBasePosX = 0;
	mBasePosY = 0;

	mPosX = 0;
	mPosY = 0;
	mAlpha = 255;
	mPrio = 0;
	mScale = 1.0;
	mAngle = 0.0;

	mIsVisible = true;
	mIsRelese = false;

}

GraphicsDraw::~GraphicsDraw() {}

int GraphicsDraw::GetPositionX() { 
	return mPosX; 
}

int GraphicsDraw::GetPositionY() { 
	return mPosY; 
}

int GraphicsDraw::GetAlpah() { 
	return mAlpha; 
}

void GraphicsDraw::SetAlpha(int alpha) { 
	if (alpha < 0) {
		alpha = 0;
	}
	else if (alpha >= 255) {
		alpha = 255;
	}
	mAlpha = alpha; 
}

void GraphicsDraw::SetPosition(int posX, int posY) {
	mPosX = posX;
	mPosY = posY;
}

void GraphicsDraw::SetPriorty(int prio) {
	mPrio = prio;
}

int GraphicsDraw::GetPriorty() {
	return mPrio;
}

double GraphicsDraw::GetScale() {
	return mScale;
}

/*
	弧度法で角度を返却する
*/
double GraphicsDraw::GetAngleRadian() {
	return mAngle;
}

/*
	度数法で角度を返却する
*/
double GraphicsDraw::GetAngleDegree() {
	const double PI = 3.14159265359;
	return mAngle * PI / 180.0;
}

void GraphicsDraw::SetScale(double scale) {
	
	if (scale < 0.1) {
		scale = 0.1;
	}

	mScale = scale;
}

/*
	弧度法で角度を設定する
*/
void GraphicsDraw::SetAngleRadian(double rad) {
	mAngle = rad;
}

/*
	度数法で角度を設定する
*/
void GraphicsDraw::SetAngleDegree(double deg) {
	const double PI = 3.14159265359;
	mAngle = deg * 180.0 / PI;
}


void GraphicsDraw::SetVisible(bool visible) {
	mIsVisible = visible;
}

void GraphicsDraw::ReleseRequest() {
	mIsRelese = true;
}

bool GraphicsDraw::IsVisible() {
	return mIsVisible;
}

bool GraphicsDraw::IsRelese() {
	return mIsRelese;
}

void GraphicsDraw::GetSize(int* width, int* height) {
	if (width != NULL) {
		*width = mWidth;
	}
	if (height != NULL) {
		*height = mHeight;
	}
}

void GraphicsDraw::SetBasePosition(int basePosX, int basePosY) {
	mBasePosX = basePosX;
	mBasePosY = basePosY;
}

int GraphicsDraw::GetBasePositionX() {
	return mBasePosX;
}

int GraphicsDraw::GetBasePositionY() {
	return mBasePosY;
}