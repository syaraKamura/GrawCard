/*
				ファイル名		:Mouse.cpp
				作成者			:
				作成日時		:2018/03/13
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "Mouse.h"


Mouse::Mouse() : InputBase(){
	memset(mData, 0, sizeof(MOUSE_DATA_t) * eInputType_Num);
	
}

/*
	更新
*/
bool Mouse::Update() {

	GetMousePoint(&mPositionX, &mPositionY);

	for (int i = 0; i < eInputType_Num; i++) {
		
		if (GetMouseInput() & INPUT_TABLE[i].code) {
			mData[i].Counter++;
			mData[i].ReleseCounter = 0;
		}else {
			mData[i].Counter = 0;
			mData[i].ReleseCounter ++;
		}
		
	}

#ifdef __WINDOWS__
	mWheel = DxLib::GetMouseWheelRotVolF();
#endif

	return true;
}

/*
	押下
	return	true	:押された
			false	:押されていない
*/
bool Mouse::Press(int code) {
	return  mData[code].Counter == 1;
}

/*
	繰り返し
	return	true	:繰り返し入力中
			false	:繰り返し入力中ではない
*/
bool Mouse::Repeate(int code) {
	return mData[code].Counter > 0 && mData[code].Counter % 20 == 0;
}


/*
	解放
	return	true	:解放されている
			false	:解放されていない
*/
bool Mouse::Relese(int code) {
	return  mData[code].ReleseCounter == 1;
}


/*
	入力されている
	return	true	:入力されている
			false	:入力されていない
*/
bool Mouse::On(int code) {
	return  mData[code].Counter > 0;
}


/*
	入力されていない
	return	true	:入力されていない
			false	:入力されている
*/
bool Mouse::Off(int code) {
	return  mData[code].ReleseCounter > 0;
}

void Mouse::GetPosition(int* posX, int* posY) {
	*posX = mPositionX;
	*posY = mPositionY;
}


