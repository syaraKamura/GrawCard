﻿/*
				ファイル名		:StringBase.cpp
				作成者			:
				作成日時		:2018/01/15
				ソース説明		:
					
					文字列基底クラス
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "StringBase.h"
#include "FontMgr/BMFont.h"
#include "FontMgr/FontMgr.h"
#include "CharConverter/CharConverter.h"

#define STRING_LINE_MAX (6)

StringBase::StringBase(){
	mFontMgr = NULL;
	mBMFont = NULL;
	mColor = GetColor(255, 255, 255);
	memset(mString, 0, sizeof(char) * 1024);
	memset(mDrawString, 0, sizeof(char) * 1024 * 6);
	mLine = 0;
	mPos = 0;
	mIsOnletter = false;
	mCounter = 0;
	mTotalPos = 0;
	mStrNum = 0;
}

StringBase::~StringBase() {

	Delete(mFontMgr);

}

/*
	更新処理
	bool isOnletter = false	:一文字ずつ表示させるか？
	true:	一文字ずつ表示する	false:すべて描画
	int length = 30			:一行に表示させる文字数(デフォルトは30文字)
	int interval  = 20		:文字を描画する間隔

	return			-1		:エラー
					0		:描画中
					1		:描画終了
					2		:表示インターバル中

*/
int StringBase::Update(bool isOnletter/* = false*/, int length/* = 30*/, int interval /* = 20*/) {

	mIsOnletter = isOnletter;

	//一文字ずつ表示させないなら処理を抜ける
	if (mIsOnletter == false) return eDrawState_DrawEnd;

	if (mString[mTotalPos] == '\0') {
		return eDrawState_DrawEnd;
	}


	mCounter++;
	if (mCounter % interval != 0) return eDrawState_DrawInterval;

	mNextLineLength = length;
	//int pos = mPos + mLine * mNextLineLength;

	if (mLine >= STRING_LINE_MAX) {
		Debug::ErorrMessage("これ以上改行することができません");
		return eDrawState_Error;
	}

	if (mString[mTotalPos] != '\0') {

		if (mStrNum >= mNextLineLength || mString[mTotalPos] == '\n') {
			mDrawString[mLine][mInputPos] = '\0';
			mPos = 0;
			mInputPos = 0;
			mStrNum = 0;
			mLine++;
			if (mString[mTotalPos] == '\n') {
				mTotalPos++;
			}
			return eDrawState_Drawing;
		}

		int num = this->GetCharBytes(&mString[mTotalPos]);

		if (num == 1) {
			mDrawString[mLine][mInputPos] = mString[mTotalPos];
			mInputPos++;
			mPos++;
			mTotalPos++;
		}
		else {
			for (int i = 0; i < num; i++) {
				mDrawString[mLine][mInputPos] = mString[mTotalPos];
				mInputPos++;
				mPos++;
				mTotalPos++;
			}
		}

		mStrNum ++;

		return eDrawState_Drawing;
	}
	return eDrawState_DrawEnd;
}

/*
	更新処理
	int length			:一行に表示させる文字数
*/
void StringBase::Update(int length) {
	
	mIsOnletter = true;

	if (mString[mTotalPos] == '\0') {
		return;
	}

	mNextLineLength = length;
	
	if (mLine >= STRING_LINE_MAX) {
		Debug::ErorrMessage("これ以上改行することができません");
		return ;
	}

	while(mString[mTotalPos] != '\0') {

		if (mStrNum >= mNextLineLength || mString[mTotalPos] == '\n') {
			mDrawString[mLine][mInputPos] = '\0';
			mPos = 0;
			mInputPos = 0;
			mStrNum = 0;
			mLine++;
			if (mString[mTotalPos] == '\n') {
				mTotalPos++;
			}
		}

		int num = this->GetCharBytes(&mString[mTotalPos]);

		if (num == 1) {
			mDrawString[mLine][mInputPos] = mString[mTotalPos];
			mInputPos++;
			mPos++;
			mTotalPos++;
		}
		else {
			for (int i = 0; i < num; i++) {
				mDrawString[mLine][mInputPos] = mString[mTotalPos];
				mInputPos++;
				mPos++;
				mTotalPos++;
			}
		}

		mStrNum++;
	}

}

/*
	フォント名からフォントデータの作成

	const char* fontName					:フォント名
	int size								:フォントサイズ
	int tick								:文字の太さ
	int fontType							:フォントタイプ
	
　		-1　　　　　　　　　　　　　　			: デフォルトフォント(DX_FONTTYPE_NORMAL と同じ)
　		DX_FONTTYPE_NORMAL　　　　　　			: ノーマルフォント
　		DX_FONTTYPE_EDGE　　　　　　　			: エッジつきフォント
　		DX_FONTTYPE_ANTIALIASING　　　　		: アンチエイリアスフォント
　		DX_FONTTYPE_ANTIALIASING_4X4　　	　	: アンチエイリアスフォント( 4x4サンプリング )
　		DX_FONTTYPE_ANTIALIASING_8X8　　　		: アンチエイリアスフォント( 8x8サンプリング )
　		DX_FONTTYPE_ANTIALIASING_EDGE_4X4　	: アンチエイリアス＆エッジ付きフォント( 4x4サンプリング )
　		DX_FONTTYPE_ANTIALIASING_EDGE_8X8　	: アンチエイリアス＆エッジ付きフォント( 8x8サンプリング ) )

	unsigned int edgeColor					:エッジの色
	return	true	:成功
			false	:失敗

*/
bool StringBase::FontCreate(const char* fontName, int size, int thick, int fontType, unsigned int edgeColor) {
	if (mFontMgr == NULL) {
		mFontMgr = new FontMgr();
	}
	return mFontMgr->CreateFontHandle(fontName, size,thick,fontType, edgeColor);
}

/*
	フォントファイルを読み込みフォントデータの作成(DxLibのTool(CreateDXFontData.exe)を使用しないと使えない)

	const char* fileName	:ＤＸフォントデータファイルのパス
	int edgeSize			:エッジのサイズ(0を指定するとなし)
	unsigned int edgeColor	:エッジの色
	return	true	:成功
			false	:失敗

*/
bool StringBase::FontCreate(const char* fileName, int edgeSize, unsigned int edgeColor) {
	if (mFontMgr == NULL) {
		mFontMgr = new FontMgr();
	}
	return mFontMgr->CreateFontHandle(fileName, edgeSize, edgeColor);
}

void StringBase::SetBitMapFont(BMFont* bmfont) {
	mBMFont = bmfont;
}


void StringBase::SetString(const char* string) {
	int size = strlenDx(string) + 1;
	SetString(string, size);

}

void StringBase::SetString(const char* string, unsigned int size) {

	if (strcmpDx(mString, string) != 0) {
		memset(mString, 0, sizeof(char) * 1024);
		strcpy_sDx(mString, size, string);
		mLine = 0;
		mPos = 0;
		memset(mDrawString, 0, sizeof(char) * STRING_LINE_MAX * 1024);
		mInputPos = 0;
		mCounter = 0;
		mTotalPos = 0;
		mStrNum = 0;
	}
}

void StringBase::SetColor(unsigned int color) {
	mColor = color;
}

/*
	文字列の描画を行う
	return 文字数を返却する
*/
int StringBase::DrawString(int posX, int posY, bool isDisp/* = true*/) {

	int length = 0;
	length = GetLength(mString);

	if (isDisp == false)	return length;

	//一文字ずつ出力が有効なら
	if (mIsOnletter == true) {
		
		for (int i = 0; i <= mLine; i++) {
			if (mFontMgr == NULL && mBMFont == NULL) {
				DxLib::DrawString(posX, posY + i * 20, mDrawString[i], mColor);
			}
			else if (mBMFont != NULL) {
				mBMFont->SetString(mDrawString[i]);
				mBMFont->Draw(posX, posY + i * 48, true);
			}
			else {
				mFontMgr->Draw(posX, posY + i * 20, mDrawString[i], mColor);
			}
		}

	}
	else {
		int size;
#ifdef __WINDOWS__
		const char* str = mString;
#else
		const char* str = CharConverter::sjis_to_utf8(mString, &size);
#endif
		if (mFontMgr == NULL && mBMFont == NULL) {
			DxLib::DrawString(posX, posY, str, mColor);
		}
		else if (mBMFont != NULL) {
			mBMFont->SetString(mString);
			mBMFont->Draw(posX, posY, true);
		}
		else {
			mFontMgr->Draw(posX, posY, str, mColor);
		}
	}

	return length;

}

int StringBase::DrawString(int posX, int posY, int alpha, bool isDisp/* = true*/) {

	int length = 0;
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	length = DrawString(posX, posY, isDisp);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	return length;
}


int StringBase::GetCharBytes(const void* string) {

	if (string == NULL) return 0;

	const char* str = (const char*)string;

	int bytes = 0;
#ifdef __WINDOWS__
	bytes = DxLib::GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, str);
#else

	int chrCodeFormat = DxLib::Get_wchar_t_CharCodeFormat();

	if (chrCodeFormat == -1) {
		chrCodeFormat = DX_CHARCODEFORMAT_UTF8;
	}

	bytes = DxLib::GetCharBytes(chrCodeFormat, str);

#endif

	return bytes;

}

int StringBase::GetLength(const char* string) {
	int length = 0;
	int lengthMax = strlenDx(string);
	const char* pchr = string;
	char ch = *pchr;
	while (length < lengthMax && ch != '\0') {
		int add = GetCharBytes(pchr);
		pchr += add;		
		length++;
		ch = *pchr;
	}
	return length;
}