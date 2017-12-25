/*
				ファイル名		:Graphics.cpp
				作成者			:
				作成日時		:
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Graphics.h"

Graphics::Graphics() : GraphicsBase() {}

Graphics::~Graphics() {}

bool Graphics::Load(const char* path) {

	mHandle = DxLib::LoadGraph(path);

	if (mHandle == -1) {
		return false;
	}
	DxLib::GetGraphSize(mHandle, &mWidth, &mHeight);

	return true;
};

void Graphics::Relese() {
	if (mHandle > 0) {
		DxLib::DeleteGraph(mHandle);
	}
}

void Graphics::Draw(int posX, int posY, int alpha){

	SetPosition(posX, posY);
	SetAlpha(alpha);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);
	DxLib::DrawGraph(mPosX, mPosY, mHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}


