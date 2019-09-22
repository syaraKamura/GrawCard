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

typedef struct COLOR {
	unsigned int r;	// 赤
	unsigned int g;	// 緑
	unsigned int b;	// 青
	int a;			// アルファ

	COLOR() {
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}

	COLOR(unsigned int r, unsigned int g, unsigned int b) {
		this->r = r;
		this->g = g;
		this->b = b;
		a = 255;
	}

	static COLOR White() { return COLOR(255, 255, 255); }
	static COLOR Black() { return COLOR(0, 0, 0); }

	static COLOR Red() { return COLOR(255, 0, 0); }
	static COLOR Blue() { return COLOR(0, 0, 255); }
	static COLOR Green() { return COLOR(0, 255, 0); }

	static COLOR Yellow() { return COLOR(255, 255, 0); }
	static COLOR Cyan() { return COLOR(0, 255, 255); }
	static COLOR Magenta() { return COLOR(255, 0, 255); }
	
	static COLOR Pink() { return COLOR(255, 192, 203); }

}COLOR_t;


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

	COLOR_t mColor;

	wchar_t mString[1024];

	int mFontHandle[(int)eFontSize::Max];

	std::vector<int> mStrId;

	eFontSize mFontSize;

public :


	BMFont();
	~BMFont();

	void SetFontSize(eFontSize Size);

	void SetColor(unsigned int r, unsigned int g, unsigned int b);
	void SetColor(COLOR_t color);
	void SetAlpha(int a);

	void SetString(const char* str);
	void Draw(int posX,int posY,bool isVisible);



};

#endif // __BMFONT_H__