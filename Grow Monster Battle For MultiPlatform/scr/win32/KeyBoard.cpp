#include "DxLib.h"
#include "Keyboard.h"

//-------------------------- 固定定数
static const int KEY_MAX_NUM = 256;
static const int PAD_MAX_NUM = 32;

//-------------------------- スタティック変数定義
static int s_ReleseCount[KEY_MAX_NUM] = {0};	//キーが開放されている間カウントする
static int s_KeyInputCount[KEY_MAX_NUM];		//キーが押されている間カウントする


/*
	キー入力が入力されている時間を返却する
	int		keyCode	:入力しているキーコード番号
*/
static int _CheckHitKey(int keyCode){
	return s_KeyInputCount[keyCode];
}

/*
	キーが入力されている
	return	true	:	キーが入力されている
			false	:	キーが入力されていない
*/
bool Keyboard_On(int keyCode){
	return _CheckHitKey(keyCode) > 0;
}

/*
	キーが入力されていない
	return	true	:キーが入力されていない
			false	:キーが入力されている
*/
bool Keyboard_Off(int keyCode){
	return _CheckHitKey(keyCode) == 0;
}

/*
	キーが開放された
	return	true	:キーが開放された
			false	:キーが開放されていない
*/
bool Keyboard_Relese(int keyCode){
	if(_CheckHitKey(keyCode) > 0){
		s_ReleseCount[keyCode] = 0;
		return false;
	}
	s_ReleseCount[keyCode]++;
	return  s_ReleseCount[keyCode] == 1;
}

/*
	キーがリピートされている
	return	true	:キーが押されている
			false	:キーが押されていない
*/	
bool Keyboard_Repeat(int keyCode){
	return _CheckHitKey(keyCode) == 1 || (_CheckHitKey(keyCode) > 4 && _CheckHitKey(keyCode) % 20 == 0);
}

/*
	キーが押されている
	return	true	:キーが押された
			false	:キーが押されていない
*/
bool Keyboard_Press(int keyCode){
	return _CheckHitKey(keyCode) == 1;
}



/*
	キー入力更新
*/
void Keyboard_Updata(){

	char key[KEY_MAX_NUM] = {};
	GetHitKeyStateAll(key);

	for(int i = 0;i < KEY_MAX_NUM;i++){
		if(key[i] != 0){
			s_KeyInputCount[i]++;
		}else{
			s_KeyInputCount[i] = 0;
		}
	}
}