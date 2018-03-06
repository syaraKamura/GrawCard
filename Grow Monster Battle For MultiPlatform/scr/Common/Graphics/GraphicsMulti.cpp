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

bool GraphicsMulti::Load(const char* path) {

	if (path == NULL) {
		Debug::ErorrMessage("画像ファイルの名前にNULLが渡されました.");
		return false;
	}

	char graphPath[1024];

	int len = strlenDx(path);
	//最後の3文字を取得する
	char extensionString[4] = { *(path + (len - 3)),*(path + (len - 2)),*(path + (len - 1)) };

	if (extensionString[0] == '\0' ||
		strcmpDx(extensionString, "xml") != 0) {
		Debug::ErorrMessage("xmlファイルではないので読み込みを中止しました.");
		return false;
	}

	XmlPurser* xml = new XmlPurser(path);

	int num = xml->GetInt("DATA_NUM");

	for (int i = 0; i < num; i++) {
		
		std::string dataNumStr = my_std::to_string(i);

		std::string filePath = xml->GetString("FILE_NAME" + dataNumStr);

		strcpyDx(graphPath, filePath.c_str());

		int drawX = xml->GetChildInt("POSITION"+ dataNumStr, "DRAW_X");
		int drawY = xml->GetChildInt("POSITION"+ dataNumStr, "DRAW_Y");
		int handle = LoadGraph(graphPath);

		if (handle == eGraphicsResult_ERROR) {
			Debug::LogPrintf("[ERORR: FUNC %s] Graphic Load ERROR.(%s)\n", __func__, path);
			delete xml;
			return false;
		}

		this->Add(handle, drawX, drawY);

	}

	

	delete xml;



	return true;
}

bool GraphicsMulti::Load(const char* path, int scrX, int scrY) {
	int handle = DxLib::LoadGraph(path);
	if (handle == eGraphicsResult_ERROR) {
		Debug::LogPrintf("[ERORR: FUNC %s] Graphic Load ERROR.(%s)\n",__func__, path);
		return false;
	}
	SetFileName(path);
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
		int width;
		int height;
		GetGraphSize(handle, &width, &height);
		GRAPHICS_MULTI_t multiGraphics = { handle,scrX,scrY ,width ,height};
		mHandleList.push_back(multiGraphics);
		return true;
	}
	else {
		Debug::LogPrintf("[ERORR : FUNC %s] This Graphic Data is Not Exits.\n",__func__);
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

		DxLib::DrawRotaGraph(drawPosX, drawPosY, mScale, mAngle, (*it).handle, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


/*
	タッチした画像番号を返却する
	return	-1		:タッチされていない
			0以上	:画像をタッチした
*/
int GraphicsMulti::TouchNumber() {

	int result = -1;

#ifdef __ANDROID__
	if (mHandleList.size() <= 0) return result;

	const TOUCH_DATA* data = Touch_GetParamData(0);
	
	if (Touch_Relese(0)) {

		int number = 0;
		for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {
			GRAPHICS_MULTI_t graph = (*it);


			if (((graph.posX <= data->posX && graph.posX + graph.width >= data->posX) &&
				(graph.posY <= data->posY && graph.posY + graph.height >= data->posY))) {
				result = number;
			}
			number++;
		}

	}
#endif

	return result;
}