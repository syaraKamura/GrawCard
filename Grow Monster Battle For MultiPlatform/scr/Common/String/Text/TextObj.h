/*
				ファイル名		:TextObj.h
				作成者			:
				作成日時		:2019/9/19
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __TEXT_OBJ_H__
#define __TEXT_OBJ_H__

#include "../FontMgr/BMFont.h"


class TextObj {
	
private:

	BMFont mBMFont;

public:

	TextObj();
	~TextObj();

	void SetColor(COLOR_t color);
	void SetAlpha(unsigned int alpha);
	void Draw(int x,int y,const char* pText,eFontSize size = eFontSize::M);

};


//====================================================
// グローバル関数化
//====================================================
void TextObj_DrawText(int x, int y, COLOR_t Color, const char* pText, eFontSize size = eFontSize::M);
void TextObj_DrawFormatText(int x, int y, COLOR_t Color, eFontSize size, const char* pText, ...);

#endif // __TEXT_OBJ_H__