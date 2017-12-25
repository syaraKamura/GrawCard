/*
				ファイル名		:GraphicsDraw.h
				作成者			:
				作成日時		:
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __GRAPHICS_DRAW_H__
#define __GRAPHICS_DRAW_H__

class GraphicsDraw {

protected:

	bool mIsVisible;	//表示フラグ
	bool mIsKill;

	int mPosX;
	int mPosY;
	int mAlpha;

	int mWidth;
	int mHeight;

public:

	virtual void Draw(int posX, int posY, int alpha) = 0;
	virtual void Relese() = 0;

	int GetPositionX();
	int GetPositionY();
	int GetAlpah();

	void  SetAlpha(int alpha);
	void SetPosition(int posX, int posY);

};


#endif // __GRAPHICS_DRAW_H__