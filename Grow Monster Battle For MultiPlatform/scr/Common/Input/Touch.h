/*
				ファイル名		:Touch.h
				作成者			:
				作成日時		:2018/01/13
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "InputBase.h"

class Touch : InputBase {

public :

	enum eTouchInput {
		eTouchInput_None = -1,
		eTouchInput_1,
		eTouchInput_2,
		eTouchInput_3,
		eTouchInput_4,
		eTouchInput_5,
		eTouchInput_6,
		eTouchInput_7,
		eTouchInput_8,
		eTouchInput_9,
		eTouchInput_10,
		eTouchInput_Num,
	};

	enum eFlickAxis{
		eFlickAxis_Horizontal,
		eFlickAxis_Vertical,
	};

private:

	typedef struct {
		int id;
		int device;
		int positionX;
		int positionY;
		int oldPositionX;
		int oldPositionY;
		int counter;
	}TOUCH_INFOMATION_t;

	//入力データ
	typedef struct {
		int inputNum;
		TOUCH_INFOMATION_t touch[eTouchInput_Num];
	}TOUCH_DATA_t;

private:

	TOUCH_DATA_t mInput;

private:

public :

	Touch();

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
	int GetFlick(int code,int axis);

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

#endif // __TOUCH_H__