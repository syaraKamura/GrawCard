/*
				ファイル名		:joypad.cpp
				作成者			:
				作成日時		:2018/01/11
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "Joypad.h"

#ifdef __WINDOWS__

#define PI (3.14159265359f)

Joypad::Joypad(int padType) : InputBase() {
	
	mPadType = padType;

	int result = GetJoypadXInputState(mPadType, &mInput);
	if (result == -1) {
		mIsActive = false;
	}
	else {
		mIsActive = true;
	}

	memset(&mInput, 0, sizeof(XINPUT_STATE));
	memset(mjoypadXInput, 0, sizeof(int) * eJoypadXInput_Num);

	mLeftAnalogInputX = 0.0f;
	mLeftAnalogInputY = 0.0f;
	mRightAnalogInputX = 0.0f;
	mRightAnalogInputY = 0.0f;

}

/*
	更新処理
	return	true	:正常
			false	:異常発生
*/
bool Joypad::Update() {
	
	memset(&mInput, 0, sizeof(XINPUT_STATE));
	int result = GetJoypadXInputState(mPadType, &mInput);

	if (result == -1) {
		Debug::LogPrintf("ジョイパッドが接続されていません.\n");
		return false;
	}

	for (int i = 0; i < eJoypadXInput_Num; i++) {
		if (mInput.Buttons[i] == eInputState_On) {
			if (mjoypadXInput[i] < 0) {
				mjoypadXInput[i] = 0;
			}
			else {
				mjoypadXInput[i] ++;
			}
		}
		else if (mInput.Buttons[i] == eInputState_Off) {
			if (mjoypadXInput[i] > 0) {
				mjoypadXInput[i] = 0;
			}
			else {
				mjoypadXInput[i] --;
			}
		}
	}

	//左スティックX軸
	if (mInput.ThumbLX >= 0) {
		mLeftAnalogInputX = (float)mInput.ThumbLX / 32767.0f;
	}
	else {
		mLeftAnalogInputX = (float)mInput.ThumbLX / 32768.0f;
	}

	//左スティックY軸
	if (mInput.ThumbLY >= 0) {
		mLeftAnalogInputY = (float)mInput.ThumbLY / 32767.0f;
	}
	else {
		mLeftAnalogInputY = (float)mInput.ThumbLY / 32768.0f;
	}

	//右スティックX軸
	if (mInput.ThumbRX >= 0) {
		mRightAnalogInputX = (float)mInput.ThumbRX / 32767.0f;
	}
	else {
		mRightAnalogInputX = (float)mInput.ThumbRX / 32768.0f;
	}

	//右スティックY軸
	if (mInput.ThumbRY >= 0) {
		mRightAnalogInputY = (float)mInput.ThumbRY / 32767.0f;
	}
	else {
		mRightAnalogInputY = (float)mInput.ThumbRY / 32768.0f;
	}

	return true;
}


/*
	押下
*/
bool Joypad::Press(int code) {
	if (mIsActive == false) return false;
	return mjoypadXInput[code] == 0;
}

/*
	繰り返し
*/
bool Joypad::Repeate(int code) {
	if (mIsActive == false) return false;
	return (mjoypadXInput[code] == 0 || mjoypadXInput[code] % 4 == 0);
}

/*
	解放
*/
bool Joypad::Relese(int code) {
	if (mIsActive == false) return false;
	static int oldInput = 0;
	oldInput = mjoypadXInput[code];
	return (oldInput > 0 && mjoypadXInput[code] == 0);
}

/*
入力されている
*/
bool Joypad::On(int code) {
	if (mIsActive == false) return false;
	return (mjoypadXInput[code] >= 0);
}

/*
入力されていない
*/
bool Joypad::Off(int code){
	if (mIsActive == false) return true;
	return (mjoypadXInput[code] <= 0);
}

/*
	左スティック
	int	axis	:取得する方向 0:水平方向 1:垂直方向
	return -1.0 ~ 1.0f
*/
float Joypad::GetLeftAnalogAxis(int axis) {

	if (mIsActive == false) return 0.0f;

	float result = 0.0f;

	switch (axis) {
	case eAnalogAxis_Horizontal:
		result = mLeftAnalogInputX;
		break;
	case eAnalogAxis_Vertical:
		result = mLeftAnalogInputY;
		break;
	}
	return result;
}

/*
	右スティック
	int	axis	:取得する方向 0:水平方向 1:垂直方向
	return -1.0 ~ 1.0f
*/
float Joypad::GetRightAnalogAxis(int axis) {

	if (mIsActive == false) return 0.0f;

	float result = 0.0f;

	switch (axis) {
	case eAnalogAxis_Horizontal:
		result = mRightAnalogInputX;
		break;
	case eAnalogAxis_Vertical:
		result = mRightAnalogInputY;
		break;
	}

	return result;

}


/*
	左スティックの角度を取得する
	return 度数法 0 ~ 360
*/
float Joypad::GetLeftAnalogAngleDegree() {
	if (mIsActive == false) return 0.0f;
	float angle = atan2f(mLeftAnalogInputY, mLeftAnalogInputX) * 180.0f / PI;
	
	/*
	angle += 180.0f;

	if (angle >= 360.0f) {
		angle -= 360.0f;
	}
	*/

	return angle;
}

/*
	左スティックの角度を取得する
	return 弧度法
*/
float Joypad::GetLeftAnalogAngleRadian() {
	if (mIsActive == false) return 0.0f;
	return GetLeftAnalogAngleDegree() * PI / 180.0f;
}

#endif	//__WINDOWS__