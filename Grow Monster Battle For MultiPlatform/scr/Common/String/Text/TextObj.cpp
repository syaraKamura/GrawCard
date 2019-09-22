/*
				ファイル名		:TextObj.h
				作成者			:
				作成日時		:2019/09/19
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "TextObj.h"


TextObj::TextObj() {

}
TextObj::~TextObj() {}

void TextObj::SetColor(COLOR_t color) {
	mBMFont.SetColor(color);
}

void TextObj::SetAlpha(unsigned int alpha) {
	if (alpha > 255) {
		alpha = 255;
	}
	mBMFont.SetAlpha(alpha);
}

void TextObj::Draw(int x, int y, const char* pText, eFontSize size/* = eFontSize::M*/) {
	mBMFont.SetFontSize(size);
	mBMFont.SetString(pText);
	mBMFont.Draw(x, y, true);
}

//====================================================
// グローバル関数化
//====================================================
void TextObj_DrawText(int x, int y, COLOR_t Color, const char* pText, eFontSize size/* = eFontSize::M*/) {
	static TextObj s_mTextObj{};
	s_mTextObj.SetColor(Color);
	s_mTextObj.Draw(x, y, pText, size);
}
void TextObj_DrawFormatText(int x, int y, COLOR_t Color, eFontSize size, const char* pText, ...) {
	va_list ap;
	char buffer[1024];
	va_start(ap, pText);
	vsprintfDx(buffer, pText, ap);
	va_end(ap);

	TextObj_DrawText(x, y, Color, buffer, size);
}