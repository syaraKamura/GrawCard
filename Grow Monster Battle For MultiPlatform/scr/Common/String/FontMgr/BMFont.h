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

	FONT_DATA_t mFontData[16384];

	wchar_t mString[1024];

	int mFontHandle;

	std::vector<int> mStrId;

public :


	BMFont();
	~BMFont();



	void SetString(const char* str);
	void Draw(int posX,int posY,bool isVisible);



};

#endif // __BMFONT_H__