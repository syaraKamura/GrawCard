/*
				ファイル名		:WindowGraph.cpp
				作成者			:
				作成日時		:2018/10/30
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Common/String/StringBase.h"
#include "WindowGraph.h"

WindowGraph::WindowGraph() : GraphicsBase() {

	mGraphics = new Graphics();
	
	mGraphics->Load("Resources/Graphics/UI/msgBox.png");
	
	mString = new StringBase();

	SetStrLength(30);

}

WindowGraph::~WindowGraph() {
	
	this->Relese();

	Delete(mString);
	Delete(mGraphics);
}


void WindowGraph::Draw(int posX, int posY, int alpha, double angle, double scale) {

	int width = 0;
	int height = 0;

	// 画像サイズを取得
	mGraphics->GetSize(&width,&height);
	if (width == 0 || height == 0) {
		DxLib::GetGraphSize(mGraphics->GetHandle(), &width, &height);
	}

	int drawPosX = (posX + (posX + width)) / 2;
	int drawPosY = (posY + GetFontSize());

	int strLength = width / GetFontSize();
	int strLengthWidht = strLength / GetFontSize();

	drawPosX = (drawPosX + strLengthWidht) / 2;

	mString->Update(strLength);

	mGraphics->Draw(posX, posY, alpha, angle, scale);
	mString->DrawString(drawPosX,drawPosY);


}

void WindowGraph::Draw() {
	int width = 0;
	int height = 0;

	// 画像サイズを取得
	mGraphics->GetSize(&width, &height);
	if (width == 0 || height == 0) {
		DxLib::GetGraphSize(mGraphics->GetHandle(), &width, &height);
	}

	int fontSize = GetFontSize();
	int drawPosX = (mPosX + (mPosX + width)) / 2;
	int drawPosY = (mPosY + fontSize);

	
	drawPosX = (drawPosX + mStrLength) / 2;
	mString->Update(mStrLength);

	mGraphics->Draw(mPosX, mPosY, mAlpha, mAngle, mScale);
	mString->DrawString(drawPosX, drawPosY);
}


void WindowGraph::Relese() {
	mGraphics->Relese();
}

void WindowGraph::SetString(const char* str) {
	mString->SetString(str);
}

void WindowGraph::SetStrLength(int strLength) {
	mStrLength = strLength;
}