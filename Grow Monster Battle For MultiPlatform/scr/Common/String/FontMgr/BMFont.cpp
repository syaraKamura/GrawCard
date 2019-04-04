/*
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

#include "FontData.inc"

#include "BMFont.h"


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


	for (int i = 0; i < ArrySize(FONT_DATA_TBL); i++) {
		mFontData[i].id = FONT_DATA_TBL[i].id;
		mFontData[i].posX = FONT_DATA_TBL[i].posX;
		mFontData[i].posY = FONT_DATA_TBL[i].posY;
		mFontData[i].offX = FONT_DATA_TBL[i].offX;
		mFontData[i].offY = FONT_DATA_TBL[i].offY;
		mFontData[i].width = FONT_DATA_TBL[i].width;
		mFontData[i].height = FONT_DATA_TBL[i].height;
		mFontData[i].xadvance = FONT_DATA_TBL[i].xadvance;
	}

	//mFontHandle = LoadGraph(filePath);
	//mFontHandle = ComRes::Instance()->GetGraphicHandle(ComRes::eComResName_BMFont)->GetHandle();
	mFontHandle = graphics::LoadGraphics::GetInstance()->Get(graphicsTable::GetGraphTag(graphicsTable::eGraphTag_BMFont));
			
	//strcpy(mString, "あいうえお 0123456789 abcdefghijklmnopqrstuvwxyz にほんご　日本語　ニホンゴ");
	//StrCopyW(mString, L"");

	mStrId = std::vector<int>();

	this->SetString("");

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
				FONT_DATA_t font = mFontData[num];
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
	for (unsigned int i = 0; i < mStrId.size(); i++) {
		int id = mStrId[i];
		int fontSize = 48;		
		//int strPosX = i * fontSize;
		
		FONT_DATA_t font = mFontData[id];
		if (i > 0) {
			if (oldFontSize == 24 && font.xadvance == 48) {
				strPosX += 24;
			}
			else if (oldFontSize == 48 && font.xadvance == 24){
				strPosX += 48;
			}
			else {
				strPosX += font.xadvance;
			}
			
		}
		oldFontSize = font.xadvance;
		int drawX = posX + strPosX + font.offX ;
		int drawY = posY + font.offY;
		DxLib::DrawRectGraph(drawX, drawY, font.posX, font.posY, font.width, font.height, mFontHandle, TRUE, FALSE);
	}

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