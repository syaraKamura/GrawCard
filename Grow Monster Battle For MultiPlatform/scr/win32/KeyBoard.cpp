#include "Common/GameCommon.h"
#include "Common/Input/Keybaord.h"
#include "KeyBoard.h"

//-------------------------- �Œ�萔

//-------------------------- �X�^�e�B�b�N�ϐ���`

Keyboard* mKey = NULL;

/*
	�L�[�����͂���Ă���
	return	true	:	�L�[�����͂���Ă���
			false	:	�L�[�����͂���Ă��Ȃ�
*/
bool Keyboard_On(int keyCode){
	return mKey->On(keyCode);
}

/*
	�L�[�����͂���Ă��Ȃ�
	return	true	:�L�[�����͂���Ă��Ȃ�
			false	:�L�[�����͂���Ă���
*/
bool Keyboard_Off(int keyCode){
	return mKey->Off(keyCode);
}

/*
	�L�[���J�����ꂽ
	return	true	:�L�[���J�����ꂽ
			false	:�L�[���J������Ă��Ȃ�
*/
bool Keyboard_Relese(int keyCode){
	return mKey->Relese(keyCode);
}

/*
	�L�[�����s�[�g����Ă���
	return	true	:�L�[��������Ă���
			false	:�L�[��������Ă��Ȃ�
*/	
bool Keyboard_Repeat(int keyCode){
	return mKey->Repeate(keyCode);
}

/*
	�L�[��������Ă���
	return	true	:�L�[�������ꂽ
			false	:�L�[��������Ă��Ȃ�
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
	�L�[���͍X�V
*/
void Keyboard_Updata(){
	mKey->Update();
}