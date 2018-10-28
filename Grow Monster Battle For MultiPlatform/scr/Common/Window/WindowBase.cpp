/*
				ファイル名		:WindowBase.cpp
				作成者			:
				作成日時		:2018/03/07
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "WindowBase.h"


void WindowBase::SetPosition(int posX, int posY) {
	mPosX = posX;
	mPosY = posY;
}

void WindowBase::SetSize(int width, int height) {
	mWidth = width;
	mHeight = height;
}

