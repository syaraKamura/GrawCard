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

	if (path == NULL) {
		Debug::ErorrMessage("画像ファイルの名前にNULLが渡されました.");
		return false;
	}
	
	char graphPath[1024];

	int len = strlenDx(path);
	//最後の3文字を取得する
	char extensionString[4] = { *(path + (len - 3)),*(path + (len - 2)),*(path + (len - 1)) };

	if (extensionString[0] != '\0' &&
		(strcmpDx(extensionString, "xml") == 0 || strcmpDx(extensionString, "XML") == 0)) {

		XmlPurser* xml = new XmlPurser(path);

		std::string filePath = xml->GetString("FILE_NAME");

		strcpyDx(graphPath,filePath.c_str());

		int drawX = xml->GetChildInt("POSITION", "DRAW_X");
		int drawY = xml->GetChildInt("POSITION", "DRAW_Y");
		int alpha = xml->GetChildInt("OPTION", "ALPHA");
		double scale = xml->GetChildDouble("OPTION", "SCALE");
		
		//スケールが0以下の時は1.0にする
		if (scale <= 0.0) {
			scale = 1.0;
		}

		SetPosition(drawX, drawY);
		SetAlpha(alpha);
		SetScale(scale);

		delete xml;
	}
	else {
		strcpyDx(graphPath,path);
	}
	
	mHandle = DxLib::LoadGraph(graphPath);

	if (mHandle == eGraphicsResult_ERROR) {
		Debug::LogPrintf("[ERORR : FUNC %s] Graphic Load ERROR.(%s)\n", __func__, path);
		return false;
	}
	DxLib::GetGraphSize(mHandle, &mWidth, &mHeight);
	SetFileName(graphPath);

	
	return true;
};

void Graphics::Relese() {
	if (mHandle > eGraphicsResult_NONE) {
		DxLib::DeleteGraph(mHandle);
		mHandle = eGraphicsResult_NONE;
	}
}

void Graphics::Draw(int posX, int posY, int alpha, double angle, double scale){

	//画像データが存在していないならば処理を抜ける
	if (mHandle <= eGraphicsResult_NONE) {
		Debug::LogPrintf("[ERORR : (FUNC %s)] Graphic is Not Exist.\n",__func__);
		return;
	}

	SetPosition(posX, posY);
	SetAlpha(alpha);
	SetAngleRadian(angle);
	SetScale(scale);
   
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);
	DxLib::DrawGraph(mPosX, mPosY, mHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}


bool Graphics::IsTouch() {

	bool result = false;

	int posX = 0;
	int posY = 0;

#ifdef __ANDROID__
	const TOUCH_DATA* data = Touch_GetParamData(0);
	posX = data->posX;
	posY = data->posY;
	if (Touch_Relese(0)) 
#else
	Mouse_GetPosition(&posX, &posY);
	if(Mouse_Relese(Mouse::eInputType_Left))
#endif		
	{
		if (((this->mPosX <= posX && this->mPosX + this->mWidth >= posX) &&
			(this->mPosY <= posY && this->mPosY + this->mHeight >= posY))) {
			result = true;
		}
	}


	return result;
}