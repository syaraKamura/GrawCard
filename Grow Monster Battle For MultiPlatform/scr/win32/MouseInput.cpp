/*
				ファイル名		:MouseInput.cpp
				作成者			:
				作成日時		:2018/03/13
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include <stdio.h>
#include "MouseInput.h"

static Mouse* mMouse;

//キー入力されている
bool Mouse_On(Mouse::eInputType code) {
	return mMouse->On(code);
}

//キー入力されていない
bool Mouse_Off(Mouse::eInputType code) {
	return mMouse->Off(code);
}


//キーが押された状態から解放された
bool Mouse_Relese(Mouse::eInputType code) {
	return mMouse->Relese(code);
}


//キーが押され続けている
bool Mouse_Repeat(Mouse::eInputType code) {
	return mMouse->Repeate(code);
}


//キーが押された
bool Mouse_Press(Mouse::eInputType code) {
	return mMouse->Press(code);
}


void Mouse_GetPosition(int* posX, int* posY) {
	mMouse->GetPosition(posX, posY);
}


void Mouse_Initialize() {
	mMouse = new Mouse();
}

void Mouse_Finalize() {
	delete(mMouse);
	mMouse = NULL;
}

void Mouse_Updata() {
	if (mMouse == NULL) return;
	mMouse->Update();
}



