/*
				ファイル名		:Button.h
				作成者			:
				作成日時		:2018/11/05
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "View.h"
class OnListener;
class Graphics;
class StringBase;

class Button : public View {

private:

	int mPosX;
	int mPosY;
	int mWidth;
	int mHeight;
	bool mIsPressed;
	char mStr[1024];
	Graphics* mGraph;
	OnListener* mLinstener;

	StringBase* mString;

	float mAlpha;

	bool mIsVisible;

public :
	/*
		コンストラクタ
		int posX		:表示座標
		int posY		:
		int width		:サイズ
		int height		:
		const char* str	:文字列
	*/
	Button(int posX,int posY,int width,int height,const char* str);
	Button(int graphicsTag,int posX, int posY, const char* str);
	Button(const char* fileName, int posX, int posY, const char* str);
	
	~Button() override;
	void Draw() override;
	bool Update() override;

	void SetVisible(bool visible);
	bool IsVisible();

	void SetPosition(int posX, int posY);
	void SetOnListener(OnListener* listener);

	int GetPositionX();
	int GetPositionY();

	float GetAlpha();
	void SetAlpha(float alpha);

};


#endif // __BUTTON_H__