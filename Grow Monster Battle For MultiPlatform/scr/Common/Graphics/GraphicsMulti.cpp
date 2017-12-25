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
	if (handle < 0) return false;
	return Add(handle, scrX, scrY);
}

void GraphicsMulti::Relese() {

	if (mHandleList.empty() == true || mHandleList.size() <= 0) return;

	for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {
		if ((*it).handle > 0) {
			DxLib::DeleteGraph((*it).handle);
		}
	}

}

bool GraphicsMulti::Add(int handle, int scrX, int scrY) {

	if (handle > 0) {
		GRAPHICS_MULTI_t multiGraphics = { handle,scrX,scrY };
		mHandleList.push_back(multiGraphics);
		return true;
	}
	return false;
}

/*
描画
*/
void GraphicsMulti::Draw(int posX, int posY, int alpha){

	if (mHandleList.empty() == true || mHandleList.size() <= 0) return;

	SetPosition(posX, posY);
	SetAlpha(alpha);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);
	for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {

		int drawPosX = (*it).posX + mPosX;
		int drawPosY = (*it).posY + mPosY;

		DxLib::DrawGraph(drawPosX, drawPosY, (*it).handle, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
