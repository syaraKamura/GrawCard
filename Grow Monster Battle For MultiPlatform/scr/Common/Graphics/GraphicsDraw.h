﻿/*
				ファイル名		:GraphicsDraw.h
				作成者			:
				作成日時		:
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __GRAPHICS_DRAW_H__
#define __GRAPHICS_DRAW_H__

#include "Common/ResourceLoader/ResourceLoader.h"

class GraphicsDraw : public ResourceLoader {

public :

	struct Color {
		int r;
		int g;
		int b;
	};

protected:


	int mHandle;
	char mFileName[1024];

	bool mIsVisible;	//表示フラグ
	bool mIsRelese;

	int mPosX;
	int mPosY;
	int mAlpha;
	
	Color mBright;

	int mBasePosX;
	int mBasePosY;

	double mScale;
	double mAngle;

	int mWidth;
	int mHeight;

	int mPrio;	//プライオリティ


public:

	GraphicsDraw();
	virtual ~GraphicsDraw();

	virtual void Draw(int posX, int posY, int alpha,double angle,double scale) = 0;
	virtual void Draw();
	virtual void Relese() = 0;

	int GetPositionX();
	int GetPositionY();
	int GetAlpah();

	void SetBasePosition(int basePosX, int basePosY);
	int GetBasePositionX();
	int GetBasePositionY();
	Color GetBright();

	double GetScale();

	/*
		弧度法で角度を返却する
	*/
	double GetAngleRadian();

	/*
		度数法で角度を返却する
	*/
	double GetAngleDegree();

	void SetScale(double scale);
	/*
		弧度法で角度を設定する
	*/
	void SetAngleRadian(double rad);

	/*
		度数法で角度を設定する
	*/
	void SetAngleDegree(double deg);

	void SetAlpha(int alpha);
	void SetBright(int r, int g, int b);
	void SetPosition(int posX, int posY);

	void SetPriorty(int prio);
	int GetPriorty();

	void SetVisible(bool visible);
	void ReleseRequest();

	bool IsVisible();
	bool IsRelese();

	void GetSize(int* width, int* height);

};


#endif // __GRAPHICS_DRAW_H__