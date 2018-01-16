/*
				ファイル名		:Keyboard.cpp
				作成者			:
				作成日時		:2018/01/13
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Keybaord.h"

static const int REPEATE_TIME = 20;

Keyboard::Keyboard() : InputBase() {

	memset(mInputKey, 0, sizeof(int) * KEY_NUM);

}

/*
押下
*/
bool Keyboard::Press(int code) {
	return mInputKey[code] == 1;
}

/*
繰り返し
*/
bool Keyboard::Repeate(int code) {
	return (mInputKey[code] == 1 || (mInputKey[code] > 1 && mInputKey[code] % REPEATE_TIME == 0));
}

/*
解放
*/
bool Keyboard::Relese(int code) {
	static int oldInput = 0;
	oldInput = mInputKey[code];
	return (oldInput > 0 && mInputKey[code] == 0);
}

/*
入力されている
*/
bool Keyboard::On(int code) {
	return (mInputKey[code] >= 0);
}

/*
入力されていない
*/
bool Keyboard::Off(int code) {
	return (mInputKey[code] <= 0);
}

/*
更新
*/
bool Keyboard::Update() {

	char key[KEY_NUM];

	GetHitKeyStateAll(key);

	for (int i = 0; i < KEY_NUM; i++) {
		if (key[i] == eInputState_On) {
			if (mInputKey[i] < 0) {
				mInputKey[i] = 0;
			}
			else {
				mInputKey[i] ++;
			}
		}
		else if (key[i] == eInputState_Off) {
			if (mInputKey[i] > 0) {
				mInputKey[i] = 0;
			}
			else {
				mInputKey[i] --;
			}
		}
	}

	return true;
}