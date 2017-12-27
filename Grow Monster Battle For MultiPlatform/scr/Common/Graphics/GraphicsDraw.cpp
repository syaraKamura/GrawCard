/*
				ファイル名		:GraphicsDraw.cpp
				作成者			:
				作成日時		:
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "GraphicsDraw.h"

GraphicsDraw::GraphicsDraw() {
	mPosX = 0;
	mPosY = 0;
	mAlpha = 255;
	mPrio = 0;

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