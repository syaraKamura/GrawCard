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
	bool mIsRelese;

	int mPosX;
	int mPosY;
	int mAlpha;

	int mWidth;
	int mHeight;

	int mPrio;	//プライオリティ

public:

	GraphicsDraw();
	virtual ~GraphicsDraw();

	virtual void Draw(int posX, int posY, int alpha) = 0;
	virtual void Relese() = 0;

	int GetPositionX();
	int GetPositionY();
	int GetAlpah();

	void  SetAlpha(int alpha);
	void SetPosition(int posX, int posY);

	void SetPriorty(int prio);
	int GetPriorty();

	void SetVisible(bool visible);
	void ReleseRequest();

	bool IsVisible();
	bool IsRelese();


};


#endif // __GRAPHICS_DRAW_H__