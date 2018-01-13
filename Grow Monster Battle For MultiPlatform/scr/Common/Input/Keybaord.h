/*
				ファイル名		:Keyboard/h
				作成者			:
				作成日時		:2018/01/13
				ソース説明		:キーボード入力
				
				
				備考
				
				
				
!*/

#ifndef __KEY_BOARD_H__
#define __KEY_BOARD_H__

#include "InputBase.h"

class Keyboard : InputBase {

private:

	enum eInputState {
		eInputState_Off,	//押していない
		eInputState_On,		//押している
	};

private:

	static const int KEY_NUM = 256;

private:

	int mInputKey[KEY_NUM];

public :

	Keyboard();

	/*
		押下
		return	true	:押された
		false	:押されていない
	*/
	bool Press(int code)override;

	/*
		繰り返し
		return	true	:繰り返し入力中
		false	:繰り返し入力中ではない
	*/
	bool Repeate(int code)override;

	/*
		解放
		return	true	:解放されている
		false	:解放されていない
	*/
	virtual bool Relese(int code)override;

	/*
		入力されている
		return	true	:入力されている
		false	:入力されていない
	*/
	bool On(int code) override;

	/*
		入力されていない
		return	true	:入力されていない
		false	:入力されている
	*/
	bool Off(int code)override;

	/*
		更新
	*/
	bool Update() override;

};

#endif // __KEY_BOARD_H__