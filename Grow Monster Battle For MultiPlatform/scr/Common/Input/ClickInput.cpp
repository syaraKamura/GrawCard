/*
				ファイル名		:ClickInput.cpp
				作成者			:
				作成日時		:2018/10/07
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "MobileInput.h"
#include "ClickInput.h"


ClickInput* ClickInput::mInstance = NULL;

ClickInput::ClickInput() {
	this->mInput = new MobileInput();
}
ClickInput::~ClickInput() {
	Delete(this->mInput);
}

bool ClickInput::Create() {

	mInstance = new ClickInput();
	return true;

}

void ClickInput::Destroy() {
	Delete(mInstance);
}

ClickInput* ClickInput::GetInstance() {

	if (mInstance == NULL) {
		Create();
	}
	return mInstance;

}



bool ClickInput::Update() {

	if (this->mInput == NULL) return false;

	return this->mInput->Update();

}

/*
押下
return	true	:押された
false	:押されていない
*/
bool  ClickInput::Press(int code) {
	return  this->mInput->Press(code);
}

/*
繰り返し
return	true	:繰り返し入力中
false	:繰り返し入力中ではない
*/
bool  ClickInput::Repeate(int code) {
	return  this->mInput->Repeate(code);
}

/*
解放
return	true	:解放されている
false	:解放されていない
*/
bool  ClickInput::Relese(int code) {
	return  this->mInput->Relese(code);
}


/*
入力されている
return	true	:入力されている
false	:入力されていない
*/
bool ClickInput::On(int code) {
	return  this->mInput->On(code);
}

/*
入力されていない
return	true	:入力されていない
false	:入力されている
*/
bool  ClickInput::Off(int code) {
	return  this->mInput->Off(code);
}

/*
フリックデータを返却する
int	axis	:取得方向 0:水平方向 1:垂直方向

*/
int  ClickInput::GetFlick(int code, int axis) {

	if (this->mInput == NULL) return 0;
	return this->mInput->GetFlick(code, axis);

}


/*
フリックの角度を度数法で返却する
*/
float  ClickInput::GetFlickAngleDegree(int code) {

	if (this->mInput == NULL) return 0.0f;
	return this->mInput->GetFlickAngleDegree(code);

}


/*
フリックの角度を弧度法で返却する
*/
float  ClickInput::GetFlickAngleRadian(int code) {

	if (mInput == NULL) return 0.0f;
	return mInput->GetFlickAngleRadian(code);

}

/*
座標を返却する
*/
int  ClickInput::GetPositionX(int code) const {

	if (mInput == NULL) return 0;
	return this->mInput->GetPositionX(code);
	
}

int ClickInput::GetPositionY(int code) const {

	if (this->mInput == NULL) return 0;
	return this->mInput->GetPositionY(code);

}

