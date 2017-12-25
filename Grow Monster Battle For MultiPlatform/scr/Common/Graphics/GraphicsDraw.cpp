/*
				ファイル名		:GraphicsDraw.cpp
				作成者			:
				作成日時		:
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "GraphicsDraw.h"

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


