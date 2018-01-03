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

	if (mHandle == eGraphicsResult_ERROR) {
		Debug::LogPrintf("[ERORR : FUNC %s] Graphic Load ERROR.(%s)",__func__,path);
		return false;
	}
	DxLib::GetGraphSize(mHandle, &mWidth, &mHeight);

	return true;
};

void Graphics::Relese() {
	if (mHandle > eGraphicsResult_NONE) {
		DxLib::DeleteGraph(mHandle);
		mHandle = eGraphicsResult_NONE;
	}
}

void Graphics::Draw(int posX, int posY, int alpha){

	//画像データが存在していないならば処理を抜ける
	if (mHandle <= eGraphicsResult_NONE) {
		Debug::LogPrintf("[ERORR : (FUNC %s)] Graphic is Not Exist.",__func__);
		return;
	}

	SetPosition(posX, posY);
	SetAlpha(alpha);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);
	DxLib::DrawGraph(mPosX, mPosY, mHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}


