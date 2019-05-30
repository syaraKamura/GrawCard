/*
				ファイル名		:GraphicsDraw.cpp
				作成者			:
				作成日時		:
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "GraphicsDraw.h"

GraphicsDraw::GraphicsDraw() {

	mHandle = 0;
	strcpyDx(mFileName, "");

	mBasePosX = 0;
	mBasePosY = 0;

	mPosX = 0;
	mPosY = 0;
	mAlpha = 255;
	mPrio = 0;
	mScale = 1.0;
	mAngle = 0.0;

	SetBright(255, 255, 255);

	mIsVisible = true;
	mIsRelese = false;

}

GraphicsDraw::~GraphicsDraw() {}

int GraphicsDraw::GetPositionX() { 
	return mPosX; 
}

int GraphicsDraw::GetPositionY() { 
	return mPosY; 
}

int GraphicsDraw::GetAlpah() { 
	return mAlpha; 
}

GraphicsDraw::Color GraphicsDraw::GetBright() {
	return mBright;
}

void GraphicsDraw::SetAlpha(int alpha) { 
	if (alpha < 0) {
		alpha = 0;
	}
	else if (alpha >= 255) {
		alpha = 255;
	}
	mAlpha = alpha; 
}

void GraphicsDraw::SetBright(int r, int g, int b) {
	mBright.r = r;
	mBright.g = g;
	mBright.b = b;
}

void GraphicsDraw::SetPosition(int posX, int posY) {
	mPosX = posX;
	mPosY = posY;
}

void GraphicsDraw::SetPriorty(int prio) {
	mPrio = prio;
}

int GraphicsDraw::GetPriorty() {
	return mPrio;
}

double GraphicsDraw::GetScale() {
	return mScale;
}

/*
	弧度法で角度を返却する
*/
double GraphicsDraw::GetAngleRadian() {
	return mAngle;
}

/*
	度数法で角度を返却する
*/
double GraphicsDraw::GetAngleDegree() {
	const double PI = 3.14159265359;
	return mAngle * PI / 180.0;
}

void GraphicsDraw::SetScale(double scale) {
	
	if (scale < 0.1) {
		scale = 0.1;
	}

	mScale = scale;
}

/*
	弧度法で角度を設定する
*/
void GraphicsDraw::SetAngleRadian(double rad) {
	mAngle = rad;
}

/*
	度数法で角度を設定する
*/
void GraphicsDraw::SetAngleDegree(double deg) {
	const double PI = 3.14159265359;
	mAngle = deg * 180.0 / PI;
}


void GraphicsDraw::SetVisible(bool visible) {
	mIsVisible = visible;
}

void GraphicsDraw::ReleseRequest() {
	mIsRelese = true;
}

bool GraphicsDraw::IsVisible() {
	return mIsVisible;
}

bool GraphicsDraw::IsRelese() {
	return mIsRelese;
}

void GraphicsDraw::GetSize(int* width, int* height) {

	if (mWidth == 0 || mHeight == 0) {
		GetGraphSize(mHandle, &mWidth, &mHeight);
	}

	if (width != NULL) {
		*width = mWidth;
	}
	if (height != NULL) {
		*height = mHeight;
	}
}

void GraphicsDraw::SetBasePosition(int basePosX, int basePosY) {
	mBasePosX = basePosX;
	mBasePosY = basePosY;
}

int GraphicsDraw::GetBasePositionX() {
	return mBasePosX;
}

int GraphicsDraw::GetBasePositionY() {
	return mBasePosY;
}

void GraphicsDraw::Draw() {

	//画像データが存在していないならば処理を抜ける
	if (mHandle <= 0) {
		Debug::LogPrintf("[ERORR : (FUNC %s)] Graphic is Not Exist.\nFileName(%s) \n", __func__, this->mFileName);
		return;
	}

	SetDrawBright(mBright.r, mBright.g, mBright.b);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);
	DxLib::DrawGraph(mPosX, mPosY, mHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBright(255, 255, 255);


}