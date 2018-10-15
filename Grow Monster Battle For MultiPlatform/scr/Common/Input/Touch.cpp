/*
				ファイル名		:Touch.cpp
				作成者			:
				作成日時		:2018/01/13
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Common/Input/Touch.h"

#define PI (3.14159265359f)

static const int REPEATE_TIME = 20;

Touch::Touch() : InputBase() {
	memset(&mInput, 0, sizeof(TOUCH_DATA_t));
}

/*
	更新処理
	return	true	:正常
	false	:異常発生
*/
bool Touch::Update() {

	mInput.inputNum = GetTouchInputNum();

	if (mInput.inputNum > eTouchInput_Num) {
		mInput.inputNum = eTouchInput_Num;
	}

	for (int i = 0; i < eTouchInput_Num; i++) {
		int posX = 0;
		int posY = 0;
		int device = 0;
		int result = GetTouchInput(i, &posX, &posY, NULL, &device);
		
		if (result == 0) {

			if (mInput.touch[i].counter < 0) {
				mInput.touch[i].counter = 0;
			}
			else {
				mInput.touch[i].counter++;
			}

			mInput.touch[i].id = i;
			mInput.touch[i].oldPositionX = mInput.touch[i].positionX;
			mInput.touch[i].oldPositionY = mInput.touch[i].positionY;
			mInput.touch[i].positionX = posX;
			mInput.touch[i].positionY = posY;
			mInput.touch[i].device = device;
			mInput.touch[i].releseCounter = 0;

			
		}
		else {
			mInput.touch[i].id = eTouchInput_None;
			mInput.touch[i].device = 0;
			

			if (mInput.touch[i].counter > 0) {
				mInput.touch[i].counter = 0;
				mInput.touch[i].releseCounter = 1;
				mInput.touch[i].positionX = mInput.touch[i].oldPositionX;
				mInput.touch[i].positionY = mInput.touch[i].oldPositionY;
			}
			else {
				mInput.touch[i].counter--;
				mInput.touch[i].releseCounter = 0;
				mInput.touch[i].positionX = 0;
				mInput.touch[i].positionY = 0;
				mInput.touch[i].oldPositionX = 0;
				mInput.touch[i].oldPositionY = 0;

			}
		}

	}


	return true;
}


/*
押下
*/
bool Touch::Press(int code) {
	return mInput.touch[code].counter == 1;
}

/*
繰り返し
*/
bool Touch::Repeate(int code) {
	return (mInput.touch[code].counter == 1 || (mInput.touch[code].counter > 1 && mInput.touch[code].counter % REPEATE_TIME == 0));
}

/*
解放
*/
bool Touch::Relese(int code) {

	if (this->On(code) == true) {
		return false;
	}

	return mInput.touch[code].releseCounter == 1;

}

/*
入力されている
*/
bool Touch::On(int code) {
	return (mInput.touch[code].counter > 0);
}

/*
入力されていない
*/
bool Touch::Off(int code) {
	return (mInput.touch[code].counter <= 0);
}


/*
フリックデータを返却する
int	axis	:取得方向 0:水平方向 1:垂直方向

*/
int Touch::GetFlick(int code,int axis) {
	
	int flick = 0;

	if (this->Press(code) == true) {
		//前回の座標を保存
		mInput.touch[code].oldPositionX = mInput.touch[code].positionX;
		mInput.touch[code].oldPositionY = mInput.touch[code].positionY;
	}
	if (this->Relese(code) == true) {
		switch (axis)
		{
		case eFlickAxis_Horizontal:
			flick = mInput.touch[code].oldPositionX - mInput.touch[code].positionX;
			break;
		case eFlickAxis_Vertical:
			flick = mInput.touch[code].oldPositionY - mInput.touch[code].positionY;
			break;
		}
	}

	return flick;
}

/*
フリックの角度を度数法で返却する
*/
float Touch::GetFlickAngleDegree(int code) {

	float x = (float)this->GetFlick(code, eFlickAxis_Horizontal);
	float y = (float)this->GetFlick(code, eFlickAxis_Vertical);
	float angle = 0.0f;

	angle = atan2f(y, x) * 180.0f / PI;

	return angle;

}

/*
フリックの角度を弧度法で返却する
*/
float Touch::GetFlickAngleRadian(int code) {

	//float x = (float)this->GetFlick(code, eFlickAxis_Horizontal);
	//float y = (float)this->GetFlick(code, eFlickAxis_Vertical);
	float angle = 0.0f;

	angle = this->GetFlickAngleDegree(code) * PI / 180.0f;

	return angle;

}

/*
座標を返却する
*/
int Touch::GetPositionX(int code) {
	return mInput.touch[code].positionX;
}

int Touch::GetPositionY(int code) {
	return mInput.touch[code].positionY;
}