/*
				ファイル名		:StringClick.cpp
				作成者			:
				作成日時		:2018/10/11
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "StringBase.h"
#include "StringClick.h"


unsigned int StringClick::mColor = GetColor(255, 255, 255);
const char* StringClick::mString = NULL;
int StringClick::mStringLength = 0;
int StringClick::mFontSize = 18;
bool StringClick::mIsClick = false;

void StringClick::SetString(const char* str,int fontSize /* = 18*/) {
	mString = str;
	mFontSize = fontSize;
	mStringLength = StringBase::GetLength(str);
}

void StringClick::SetColor(unsigned int color) {
	mColor = color;
}

bool StringClick::IsInSide(StringClick::eClickType type,int code /* = 0 */) {
	
	bool ret = false;

	switch (type) {
	case StringClick::eClickType_On:
		ret = ClickInput::GetInstance()->On(code);
		break;
	case StringClick::eClickType_Press:
		ret = ClickInput::GetInstance()->Press(code);
		break;
	case StringClick::eClickType_Relese:
		ret = ClickInput::GetInstance()->Relese(code);
		break;
	}

	if (ret) {
		ret = mIsClick;
	}

	return ret;
}

void StringClick::Draw(int posX, int posY) {

	if (mString == NULL) return;

	int x = ClickInput::GetInstance()->GetPositionX(0);
	int y = ClickInput::GetInstance()->GetPositionY(0);

	int width = posX + mStringLength * mFontSize;
	int height = posY + mFontSize;

	mIsClick = false;
	if ((posX <= x && width >= x) &&
		(posY <= y && height >= y)) {
		mIsClick = true;
	}

	//int oldFontSize = DxLib::GetFontSize();
	//DxLib::SetFontSize(mFontSize);
	DxLib::DrawString(posX, posY, mString, mColor);
	//DxLib::SetFontSize(oldFontSize);
}