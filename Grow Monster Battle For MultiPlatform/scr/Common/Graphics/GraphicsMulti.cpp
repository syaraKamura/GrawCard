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

	char filePath[1024];
	strcpyDx(filePath, path);

#ifdef __WINDOWS__ 
#ifdef  __MY_DEBUG__

	
	RESORCES_PATH(filePath);

#endif	// __MY_DEBUG__
#endif	// __WINDOWS__ 

	int handle = DxLib::LoadGraph(filePath);
	if (handle == eGraphicsResult_ERROR) {
		Debug::LogPrintf("[ERORR: FUNC %s] Graphic Load ERROR.(%s)\n",__func__, filePath);
		return false;
	}
	SetFileName(filePath);
	return Add(handle, scrX, scrY);
}

bool GraphicsMulti::LoadDiv(const char* path, int divNumX, int divNumY, int scrX, int scrY) {

	if (divNumX <= 0 || divNumY <= 0) return false;

	char filePath[1024];
	strcpyDx(filePath, path);

#ifdef __WINDOWS__ 
#ifdef  __MY_DEBUG__


	RESORCES_PATH(filePath);

#endif
#endif


	int tmpHandle = DxLib::LoadGraph(filePath);

	// 一枚絵として読み込み　
	if (tmpHandle == GraphicsMulti::eGraphicsResult_ERROR) {
		return false;
	}

	int sizeX = 0;
	int sizeY = 0;
	DxLib::GetGraphSize(tmpHandle,&sizeX, &sizeY);

	int allNum = divNumX * divNumY;
	int width = sizeX / divNumX;
	int height = sizeY / divNumY;
	int* handle = new int[allNum];

	// 元の画像を削除
	DeleteGraph(tmpHandle);

	int ret = DxLib::LoadDivGraph(filePath,allNum,divNumX,divNumY,width,height,handle);

	if (ret == GraphicsMulti::eGraphicsResult_ERROR) {
		DeleteArry(handle);
		return false;
	}

	
	for (int i = 0; i < allNum; i++) {
		if (this->Add(handle[i], scrX, scrY) == false) {
			return false;
		}
	}

	SetFileName(filePath);
	DeleteArry(handle);
	return true;
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
		GRAPHICS_MULTI_t multiGraphics = { handle,scrX,scrY ,width ,height,true};
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

		if ((*it).isVisible == false) continue;

		int drawPosX = (*it).posX + mPosX;
		int drawPosY = (*it).posY + mPosY;

		//DxLib::DrawRotaGraph(drawPosX, drawPosY, mScale, mAngle, (*it).handle, TRUE);
		DxLib::DrawGraph(drawPosX, drawPosY, (*it).handle, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef __MY_DEBUG__
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 123);
	for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {

		if ((*it).handle <= eGraphicsResult_NONE) {

			continue;
		}

		if ((*it).isVisible == false) continue;

		int drawPosX = (*it).posX + mPosX;
		int drawPosY = (*it).posY + mPosY;
		int drawWidth = drawPosX + (*it).width;
		int drawHeigth = drawPosY + (*it).height;

		DxLib::DrawBox(drawPosX, drawPosY, drawWidth, drawHeigth, GetColor(255, 0, 0), TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#endif	// __MY_DEBUG__

}

void GraphicsMulti::Draw() {

	if (mHandleList.empty() == true || mHandleList.size() <= 0) return;
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);
	for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {

		if ((*it).handle <= eGraphicsResult_NONE) {

			continue;
		}

		if ((*it).isVisible == false) continue;

		int drawPosX = (*it).posX + mPosX;
		int drawPosY = (*it).posY + mPosY;

		//DxLib::DrawRotaGraph(drawPosX, drawPosY, mScale, mAngle, (*it).handle, TRUE);
		DxLib::DrawGraph(drawPosX, drawPosY, (*it).handle, TRUE);
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

	int posX = 0;
	int posY = 0;

	posX = ClickInput::GetInstance()->GetPositionX(0);
	posY = ClickInput::GetInstance()->GetPositionY(0);

	if(ClickInput::GetInstance()->Relese(0))

#ifdef __ANDROID__
	//if (mHandleList.size() <= 0) return result;
	//
	//const TOUCH_DATA* data = Touch_GetParamData(0);
	//posX = data->posX;
	//posY = data->posY;
	//if (Touch_Relese(0))
#else
	//Mouse_GetPosition(&posX, &posY);
	//if (Mouse_Relese(Mouse::eInputType_Left))
#endif
	{
		int number = 0;
		for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {
			GRAPHICS_MULTI_t graph = (*it);


			if (((graph.posX <= posX && graph.posX + graph.width >= posX) &&
				(graph.posY <= posY && graph.posY + graph.height >= posY))) {
				result = number;
				break;
			}
			number++;
		}

	}


	return result;
}


void GraphicsMulti::SetDivPosition(int divNum, int posX, int posY) {

	if (divNum < 0 || divNum >= mHandleList.size()) return;

	int num = 0;
	for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {
		GRAPHICS_MULTI_t* graph = &(*it);

		if (num == divNum) {
			graph->posX = posX;
			graph->posY = posY;
		}
		num++;
	}

}

void GraphicsMulti::GetDivPosition(int divNum, int* posX, int* posY) {

	if (divNum < 0 || divNum >= mHandleList.size()) return;

	int num = 0;
	for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {
		GRAPHICS_MULTI_t graph = (*it);

		if (num == divNum) {
			*posX = graph.posX;
			*posY = graph.posY;
		}
		num++;
	}

}


void GraphicsMulti::SetDivVisible(int divNum, bool isVisible) {
	if (divNum < 0 || divNum >= mHandleList.size()) return;

	int num = 0;
	for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {
		GRAPHICS_MULTI_t* graph = &(*it);

		if (num == divNum) {
			graph->isVisible = isVisible;
		}
		num++;
	}
}

bool GraphicsMulti::IsDivVisivle(int divNum) {
	if (divNum < 0 || divNum >= mHandleList.size()) return false;

	int num = 0;
	for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {
		GRAPHICS_MULTI_t graph = (*it);

		if (num == divNum) {
			return graph.isVisible;
		}
		num++;
	}
}

void GraphicsMulti::SetAllDivVisible(bool isVisible) {
	for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {
		GRAPHICS_MULTI_t* graph = &(*it);
		graph->isVisible = isVisible;
	}
}

int GraphicsMulti::GetNum() {
	return mHandleList.size();
}