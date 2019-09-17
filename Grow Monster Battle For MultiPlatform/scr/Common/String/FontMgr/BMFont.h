/*
				ファイル名		:BMFont.h
				作成者			:
				作成日時		:2018/11/07
				ソース説明		:
					
					ビットマップフォント
				
				備考
				
				
				
!*/

#ifndef __BMFONT_H__
#define __BMFONT_H__

#include <vector>

enum class eFontSize : int{
	S,
	M,
	L,
	Max,
};

class BMFont {

private:

public :

	typedef struct {
		//int fontHandle;			// フォント画像ハンドル
		unsigned int id;		// フォント番号
		unsigned char chr[3];
		int posX;
		int posY;
		int offX;
		int offY;
		int width;
		int height;
		int xadvance;
	}FONT_DATA_t;

	FONT_DATA_t mFontData[(int)eFontSize::Max][16384];

	wchar_t mString[1024];

	int mFontHandle[(int)eFontSize::Max];

	std::vector<int> mStrId;

	eFontSize mFontSize;

public :


	BMFont();
	~BMFont();

	void SetFontSize(eFontSize Size);

	void SetString(const char* str);
	void Draw(int posX,int posY,bool isVisible);



};

#endif // __BMFONT_H__