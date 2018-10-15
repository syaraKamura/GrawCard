/*
				ファイル名		:MobileInput.h
				作成者			:
				作成日時		:2018/10/05
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __MOBILEINPUT_H__
#define __MOBILEINPUT_H__

#include "InputBase.h"

class MobileInput : public InputBase{

public :

	enum eMobilInput {
		eMobilInput_Input0,
		eMobilInput_Input1,
		eMobilInput_Input2,
		eMobilInput_Input3,
		eMobilInput_NUM,
	};

private :
	InputBase* mInputBase;

private :

	int ConvertCode(int code);

public :
	
	MobileInput();
	~MobileInput();

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

	/*
	フリックデータを返却する
	int	axis	:取得方向 0:水平方向 1:垂直方向

	*/
	int GetFlick(int code, int axis);

	/*
	フリックの角度を度数法で返却する
	*/
	float GetFlickAngleDegree(int code);

	/*
	フリックの角度を弧度法で返却する
	*/
	float GetFlickAngleRadian(int code);

	/*
	座標を返却する
	*/
	int GetPositionX(int code);
	int GetPositionY(int code);




};

#endif // __MOBILEINPUT_H__