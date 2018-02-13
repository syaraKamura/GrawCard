/*
				ファイル名		:CommonResource.cpp
				作成者			:
				作成日時		:2018/02/13
				ソース説明		:
				
					汎用リソース
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Common/Graphics/Graphics.h"
#include "CommonResource.h"

ComRes* ComRes::mInstance = NULL;

ComRes::ComRes() {

	COMMON_RES_t COM_RES_TBL[eComResName_Num] = {
		// リソースの種類　　	ファイルパス
		{eComResKind_Graphic,	"Resources/Graphics/BG/menu_ui_re.png"	},
	};

	for (int i = 0; i < eComResName_Num; i++) {
		mComRes[i] = COM_RES_TBL[i];
	}

}

void ComRes::Create() {
	if (mInstance == NULL) {
		mInstance = new ComRes();
	}
}
void ComRes::Destory() {
	Delete(mInstance);
}

ComRes* ComRes::Instance() {
	return mInstance;
}

/*
	リソース読み込み
*/
bool ComRes::Load() {

	for (int i = 0; i < eComResName_Num; i++) {
		if (mComRes[i].kind != eComResKind_Graphic) continue;
		mComRes[i].Graphic = new Graphics();
		if (mComRes[i].Graphic->Load(mComRes[i].fileName) == false) {
			Debug::LogPrintf("画像の読み込みに失敗しました.(%s)", mComRes[i].fileName);
			return false;
		}
	}

	return true;
}

/*
	リソースを削除する
*/
void ComRes::Relese() {

	for (int i = 0; i < eComResName_Num; i++) {
		if (mComRes[i].kind != eComResKind_Graphic) continue;
		Delete(mComRes[i].Graphic);
	}

}

Graphics* ComRes::GetGraphicHandle(ComRes::eComResName name) {
	
	const COMMON_RES_t* result = &mComRes[name];

	if (result->Graphic == NULL) {
		Debug::LogPrintf("指定したグラフィックは存在していません.");
		return NULL;
	}
	Graphics* graph = result->Graphic;

	return graph;
}

