/*
				ファイル名		:MobileInput.cpp
				作成者			:
				作成日時		:2018/10/05
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "MobileInput.h"
#include "InputBase.h"
#include "Mouse.h"
#include "Touch.h"

struct InputTable_t {
	MobileInput::eMobilInput type;
	Mouse::eInputType moueInputType;
	Touch::eTouchInput touchInput;
};

static const struct InputTable_t INPUT_TABLE[MobileInput::eMobilInput_NUM]{
	{ MobileInput::eMobilInput_Input0,Mouse::eInputType_Left,Touch::eTouchInput_1 },
	{ MobileInput::eMobilInput_Input1,Mouse::eInputType_Right,Touch::eTouchInput_2 },
	{ MobileInput::eMobilInput_Input2,Mouse::eInputType_Middle,Touch::eTouchInput_3 },
	{ MobileInput::eMobilInput_Input3,Mouse::eInputType_1,Touch::eTouchInput_4 },
};


MobileInput::MobileInput() : InputBase(){
	
#ifdef  __WINDOWS__
	mInputBase = new Mouse();
#elif __ANDROID__
	mInputBase = new Touch();
#endif

}

MobileInput::~MobileInput() {
	delete(mInputBase);
}

int MobileInput::ConvertCode(int code) {

	if (code < 0 || code >= MobileInput::eMobilInput_NUM) return -1;

#ifdef  __WINDOWS__
	return INPUT_TABLE[code].moueInputType;
#elif __ANDROID__
	return INPUT_TABLE[code].touchInput;
#endif		
}

bool MobileInput::Update() {
	
#ifdef  __WINDOWS__
	Mouse* input = dynamic_cast<Mouse*>(mInputBase);
#elif __ANDROID__
	Touch* input = dynamic_cast<Touch*>(mInputBase);
#endif

	if (input == NULL) return false;

	return input->Update();
}

/*
押下
return	true	:押された
false	:押されていない
*/
bool  MobileInput::Press(int code) {
	code = ConvertCode(code);
	if (code == -1) return false;

	return  mInputBase->Press(code);
}

/*
繰り返し
return	true	:繰り返し入力中
false	:繰り返し入力中ではない
*/
bool  MobileInput::Repeate(int code) {
	code = ConvertCode(code);
	if (code == -1) return false;
	return  mInputBase->Repeate(code);
}

/*
解放
return	true	:解放されている
false	:解放されていない
*/
bool  MobileInput::Relese(int code) {
	code = ConvertCode(code);
	if (code == -1) return false;
	return  mInputBase->Relese(code);
}


/*
入力されている
return	true	:入力されている
false	:入力されていない
*/
bool MobileInput::On(int code) {
	code = ConvertCode(code);
	if (code == -1) return false;
	return  mInputBase->On(code);
}

/*
入力されていない
return	true	:入力されていない
false	:入力されている
*/
bool  MobileInput::Off(int code) {
	code = ConvertCode(code);
	if (code == -1) return false;
	return  mInputBase->Off(code);
}

/*
フリックデータを返却する
int	axis	:取得方向 0:水平方向 1:垂直方向

*/
int  MobileInput::GetFlick(int code, int axis) {

	code = ConvertCode(code);
	if (code == -1) return false;

	Touch* input = NULL;
#ifdef __ANDROID__
	input = dynamic_cast<Touch*>(mInputBase);
#endif

	if (input == NULL) return 0;
	
	return input->GetFlick(code, axis);

}


/*
フリックの角度を度数法で返却する
*/
float  MobileInput::GetFlickAngleDegree(int code) {
	Touch* input = NULL;
#ifdef __ANDROID__
	input = dynamic_cast<Touch*>(mInputBase);
#endif

	code = ConvertCode(code);
	if (code == -1) return false;

	if (input == NULL) return 0.0f;

	return input->GetFlickAngleDegree(code);

}


/*
フリックの角度を弧度法で返却する
*/
float  MobileInput::GetFlickAngleRadian(int code) {
	Touch* input = NULL;
#ifdef __ANDROID__
	input = dynamic_cast<Touch*>(mInputBase);
#endif

	code = ConvertCode(code);
	if (code == -1) return false;

	if (input == NULL) return 0.0f;

	return input->GetFlickAngleRadian(code);

}

/*
座標を返却する
*/
int  MobileInput::GetPositionX(int code) {
	
#ifdef __WINDOWS__
	Mouse* input = dynamic_cast<Mouse*>(mInputBase);
#elif __ANDROID__
	Touch* input = dynamic_cast<Touch*>(mInputBase);
#endif

	code = ConvertCode(code);
	if (code == -1) return false;

	if (input == NULL) return 0;

	int posX = 0;
	int posY = 0;
#ifdef __WINDOWS__
	input->GetPosition(&posX, &posY);
#elif __ANDROID__
	posX = input->GetPositionX(code);
#endif

	return posX;

}

int MobileInput::GetPositionY(int code) {
#ifdef __WINDOWS__
	Mouse* input = dynamic_cast<Mouse*>(mInputBase);
#elif __ANDROID__
	Touch* input = dynamic_cast<Touch*>(mInputBase);
#endif

	code = ConvertCode(code);
	if (code == -1) return false;

	if (input == NULL) return 0;

	int posX = 0;
	int posY = 0;
#ifdef __WINDOWS__
	input->GetPosition(&posX, &posY);
#elif __ANDROID__
	posY = input->GetPositionY(code);
#endif

	return posY;
}

