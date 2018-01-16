#include "Common/GameCommon.h"
#include "Common/Input/Keybaord.h"
#include "KeyBoard.h"

//-------------------------- 固定定数

//-------------------------- スタティック変数定義

Keyboard* mKey = NULL;

/*
	キーが入力されている
	return	true	:	キーが入力されている
			false	:	キーが入力されていない
*/
bool Keyboard_On(int keyCode){
	return mKey->On(keyCode);
}

/*
	キーが入力されていない
	return	true	:キーが入力されていない
			false	:キーが入力されている
*/
bool Keyboard_Off(int keyCode){
	return mKey->Off(keyCode);
}

/*
	キーが開放された
	return	true	:キーが開放された
			false	:キーが開放されていない
*/
bool Keyboard_Relese(int keyCode){
	return mKey->Relese(keyCode);
}

/*
	キーがリピートされている
	return	true	:キーが押されている
			false	:キーが押されていない
*/	
bool Keyboard_Repeat(int keyCode){
	return mKey->Repeate(keyCode);
}

/*
	キーが押されている
	return	true	:キーが押された
			false	:キーが押されていない
*/
bool Keyboard_Press(int keyCode){
	return mKey->Press(keyCode);
}


void Keyboard_Initialize() {
	mKey = new Keyboard();
}

void Keyboard_Finalize() {
	Delete(mKey);
}

/*
	キー入力更新
*/
void Keyboard_Updata(){
	mKey->Update();
}