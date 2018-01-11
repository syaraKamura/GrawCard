/*
				ファイル名		:GraphicsMulti.cpp
				作成者			:
				作成日時		:2017/12/25
				ソース説明		:

					複数の画像で一枚の画像として扱う

				備考



!*/

#include "Common/GameCommon.h"
#include "GraphicsMulti.h"

GraphicsMulti::GraphicsMulti() : GraphicsBase() {};

bool GraphicsMulti::Load(const char* path){
	
	return true;
};

bool GraphicsMulti::Load(const char* path, int scrX, int scrY) {
	int handle = DxLib::LoadGraph(path);
	if (handle == eGraphicsResult_ERROR) {
		Debug::LogPrintf("[ERORR: FUNC %s] Graphic Load ERROR.(%s)",__func__, path);
		return false;
	}
	return Add(handle, scrX, scrY);
}

void GraphicsMulti::Relese() {

	if (mHandleList.empty() == true || mHandleList.size() <= 0) return;

	for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {
		if ((*it).handle > eGraphicsResult_NONE) {
			DxLib::DeleteGraph((*it).handle);
		}
	}

}

bool GraphicsMulti::Add(int handle, int scrX, int scrY) {

	if (handle > eGraphicsResult_NONE) {
		GRAPHICS_MULTI_t multiGraphics = { handle,scrX,scrY };
		mHandleList.push_back(multiGraphics);
		return true;
	}
	else {
		Debug::LogPrintf("[ERORR : FUNC %s] This Graphic Data is Not Exits.",__func__);
		return false;
	}
}

/*
	描画
*/
void GraphicsMulti::Draw(int posX, int posY, int alpha, double angle, double scale){

	if (mHandleList.empty() == true || mHandleList.size() <= 0) return;

	SetPosition(posX, posY);
	SetAlpha(alpha);
	SetAngleRadian(angle);
	SetScale(scale);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);
	for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {

		if ((*it).handle <= eGraphicsResult_NONE) {
			
			continue;
		}

		int drawPosX = (*it).posX + mPosX;
		int drawPosY = (*it).posY + mPosY;

		DxLib::DrawRotaGraph(mPosX, mPosY, mScale, mAngle, (*it).handle, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
