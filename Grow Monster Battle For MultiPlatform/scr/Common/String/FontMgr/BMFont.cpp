﻿/*
				ファイル名		:BMFont.cpp
				作成者			:
				作成日時		:2018/11/07
				ソース説明		:
				
					ビットマップフォント
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "Common/ResourceTable/GraphTable.h"
#include "../StringBase.h"
#include <stdlib.h>


#include "BMFont.h"

typedef struct {
	unsigned int id;		// フォント番号
	int posX;
	int posY;
	int offX;
	int offY;
	int width;
	int height;
	int xadvance;
}FONT_BASE_DATA_t;

static FONT_BASE_DATA_t FONT_DATA_LIST[(int)eFontSize::Max][16384] = {

	// S
	{
		#include "Inc/Font_S.inc" 
	}, 
	
	// M
	{
		#include "Inc/Font_M.inc"
	},	

	// L
	{
		#include "Inc/Font_L.inc" 
	},	

};


static void StrCopyW(wchar_t* src, const wchar_t* dst) {
	
	for (int i = 0; *dst != L'\0'; i++) {
		*src = *dst;
		dst++;
		src++;
	}

	*src = L'\0';

}

BMFont::BMFont() {

	setlocale(LC_ALL, "jpn");

	for (int fontSize = 0; fontSize < (int)eFontSize::Max; fontSize++) {
		auto& Font = mFontData[fontSize];
		for (int i = 0; i < ArrySize(FONT_DATA_LIST[fontSize]); i++) {
			Font[i].id = FONT_DATA_LIST[fontSize][i].id;
			Font[i].posX = FONT_DATA_LIST[fontSize][i].posX;
			Font[i].posY = FONT_DATA_LIST[fontSize][i].posY;
			Font[i].offX = FONT_DATA_LIST[fontSize][i].offX;
			Font[i].offY = FONT_DATA_LIST[fontSize][i].offY;
			Font[i].width = FONT_DATA_LIST[fontSize][i].width;
			Font[i].height = FONT_DATA_LIST[fontSize][i].height;
			Font[i].xadvance = FONT_DATA_LIST[fontSize][i].xadvance;
		}
	}

	//mFontHandle = LoadGraph(filePath);
	//mFontHandle = ComRes::Instance()->GetGraphicHandle(ComRes::eComResName_BMFont)->GetHandle();
	mFontHandle[0] = graphics::LoadGraphics::GetInstance()->Get(graphicsTable::GetGraphTag(graphicsTable::eGraphTag_BMFont_S));
	mFontHandle[1] = graphics::LoadGraphics::GetInstance()->Get(graphicsTable::GetGraphTag(graphicsTable::eGraphTag_BMFont_M));
	mFontHandle[2] = graphics::LoadGraphics::GetInstance()->Get(graphicsTable::GetGraphTag(graphicsTable::eGraphTag_BMFont_L));
			
	//strcpy(mString, "あいうえお 0123456789 abcdefghijklmnopqrstuvwxyz にほんご　日本語　ニホンゴ");
	//StrCopyW(mString, L"");

	mStrId = std::vector<int>();

	this->SetString("");

	mFontSize = eFontSize::M;

}

BMFont::~BMFont() {
	//DxLib::DeleteGraph(mFontHandle);
}

void BMFont::Draw(int posX, int posY, bool isVisible) {

	if (isVisible == false) return;
	if (*mString == L'\0') return;

	wchar_t* tmp = (wchar_t*)mString;

	mStrId.clear();

	//int strLength = DxLib::GetStringLength(mString);
		
	for (; *tmp != L'\0';) {
		

#if true
		unsigned int ch = 0;
		ch = *tmp;
		tmp++;
#else
		int num = StringBase::GetCharBytes(tmp);

		if (num == -1) {
			Debug::ErorrMessage("文字のバイトの取得に失敗しました\n");
			break;
		}
		unsigned int ch = 0;
		unsigned char chr[3] = "";
		for (int j = 0; j < num; j++) {
			//Debug::LogPrintf("%x ", *tmp);

			unsigned int n = *tmp;

#if false
			if (j == 1) {
				unsigned int buf = n / 0x10;
				unsigned int buf2 = n - buf * 0x10;
				n = buf2 * 16 + buf;
			}
#endif

			ch = ch << (j*8);
			ch += n;
			
			chr[j] = n;
			tmp++;
		}
#endif

		
		int min = 0;
		int max = 9000;
		int num = 0;

		while (1) {
			if (max < min) {
				break;
			}
			else {
				num = min + (max - min) / 2;
				FONT_DATA_t font = mFontData[(int)mFontSize][num];
				if (font.id > ch) {
					max--;
				}
				else if (font.id < ch) {
					min++;
				}
				else {
					mStrId.push_back(num);
					break;
				}
			}
		}


#if false
		for (int j = 0; j < 16384; j++) {
			FONT_DATA_t font = mFontData[j];
			if (font.id == ch ){
			//if(strcmpDx((const TCHAR*)font.chr, (const TCHAR*)chr) == 0){
				mStrId.push_back(j);
				break;
			}
		}
#endif
	}

	int strPosX = 0;
	int oldFontSize = 0;
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, mColor.a);
	DxLib::SetDrawBright(mColor.r, mColor.g, mColor.b);
	for (unsigned int i = 0; i < mStrId.size(); i++) {
		int id = mStrId[i];
		int fontSize = 48;		
		//int strPosX = i * fontSize;
		
		FONT_DATA_t font = mFontData[(int)mFontSize][id];
		if (i > 0) {
			//if (oldFontSize == 24 && font.xadvance == 48) {
			//	strPosX += 24;
			//}
			//else if (oldFontSize == 48 && font.xadvance == 24){
			//	strPosX += 48;
			//}
			//else 
			//{
			//	strPosX += font.xadvance;
			//}

			if (font.xadvance > font.width) {
				strPosX += font.xadvance;
			}
			else {
				strPosX += font.width;
			}
			
		}
		oldFontSize = font.xadvance;
		int drawX = posX + strPosX + font.offX ;
		int drawY = posY + font.offY;
		DxLib::DrawRectGraph(drawX, drawY, font.posX, font.posY, font.width, font.height, mFontHandle[(int)mFontSize], TRUE, FALSE);
	}
	DxLib::SetDrawBright(255, 255, 255);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#if false
	for (int i = 0; i < 16384; i++) {
		int posX = i % 128 * 16;
		int posY = i / 128 * 16;
		FONT_DATA_t font = mFontData[i];
		DxLib::DrawRectGraph(posX, posY, font.posX, font.posY, font.width, font.height, mFontHandle, TRUE, FALSE);
		//Debug::LogPrintf("%s", font.chr);
	}

#endif

}

void BMFont::SetColor(unsigned int r, unsigned int g, unsigned int b){

	mColor.r = r;
	mColor.g = g;
	mColor.b = b;

}
void BMFont::SetColor(COLOR_t color) {
	SetColor(color.r, color.g, color.b);
}
void BMFont::SetAlpha(int a) {
	mColor.a = a;
}

void BMFont::SetString(const char* str) {

	//int length = StringBase::GetCharBytes(str);
	int length = strlen(str);
	
	// 文字を初期化
	for (int i = 0; i < 1024; i++) {
		mString[i] = L'\0';
	}

#ifdef __WINDOWS__
	size_t value;
	mbstowcs_s(&value, mString, str, 1024);
#else
	mbstowcs(mString, str, 1024);
#endif
	
	//DxLib::strcpyDx(mString, str);
	//StrCopyW(mString, str);
}

void BMFont::SetFontSize(eFontSize Size) {
	mFontSize = Size;
}
