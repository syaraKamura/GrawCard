/*
				ファイル名		:Joypad.h
				作成者			:
				作成日時		:2018/01/11
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __JOYPAD_H__
#define __JOYPAD_H__

#include "InputBase.h"

class Joypad : public InputBase {

private:

	enum eInputState {
		eInputState_Off,	//押していない
		eInputState_On,		//押している
	};

public:

	//キーコード
	enum eJoypadXInput {
		eJoypadXInput_Up = XINPUT_BUTTON_DPAD_UP,
		eJoypadXInput_Down = XINPUT_BUTTON_DPAD_DOWN,
		eJoypadXInput_Left = XINPUT_BUTTON_DPAD_LEFT,
		eJoypadXInput_Rigth = XINPUT_BUTTON_DPAD_RIGHT,
		eJoypadXInput_Start = XINPUT_BUTTON_START,
		eJoypadXInput_Back = XINPUT_BUTTON_BACK,
		eJoypadXInput_Left_Push = XINPUT_BUTTON_LEFT_THUMB,
		eJoypadXInput_Right_Push = XINPUT_BUTTON_RIGHT_THUMB,
		eJoypadXInput_Left_Shoulder = XINPUT_BUTTON_LEFT_SHOULDER,
		eJoypadXInput_Right_Shoulder = XINPUT_BUTTON_RIGHT_SHOULDER,
		eJoypadXInput_A = XINPUT_BUTTON_A,
		eJoypadXInput_B = XINPUT_BUTTON_B,
		eJoypadXInput_X = XINPUT_BUTTON_X,
		eJoypadXInput_Y = XINPUT_BUTTON_Y,
		eJoypadXInput_Num,

	};

	enum eAnalogAxis {
		eAnalogAxis_Horizontal,	//水平方向
		eAnalogAxis_Vertical,	//垂直方向
	};

private:

	//ジョイパッドの押下判定用
	int mjoypadXInput[eJoypadXInput_Num];

	//ジョイパットのタイプ
	int mPadType;

	//アナログスティックの入力判定
	float mLeftAnalogInputX;
	float mLeftAnalogInputY;
	float mRightAnalogInputX;
	float mRightAnalogInputY;

	XINPUT_STATE mInput;

public:

	Joypad(int padType = DX_INPUT_PAD1);

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
		左スティック
		int	axis	:取得する方向 0:水平方向 1:垂直方向
		return -1.0 ~ 1.0f
	*/
	float GetLeftAnalogAxis(int axis);

	/*
		右スティック
		int	axis	:取得する方向 0:水平方向 1:垂直方向
		return -1.0 ~ 1.0f
	*/
	float GetRightAnalogAxis(int axis);

	/*
		左スティックの角度を取得する
		return 度数法 0 ~ 360
	*/
	float GetLeftAnalogAngleDegree();

	/*
		左スティックの角度を取得する
		return 弧度法
	*/
	float GetLeftAnalogAngleRadian();

};


#endif // __JOYPAD_H__