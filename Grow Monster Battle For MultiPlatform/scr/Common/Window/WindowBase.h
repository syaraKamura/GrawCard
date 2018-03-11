/*
				ファイル名		:WindowBase.h
				作成者			:
				作成日時		:2018/03/07
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __WINDOW_BASE_H__
#define __WINDOW_BASE_H__

class WindowBase {

protected:

	//座標
	int mPosX;
	int mPosY;
	
	//サイズ
	int mWidth;
	int mHeight;

	//画像ハンドル
	int mGraphImage;

public :

	virtual ~WindowBase() {}
	virtual void Draw() = 0;

	void SetPosition(int posX, int posY);
	void SetSize(int width,int height);

};

#endif // __WINDOW_BASE_H__