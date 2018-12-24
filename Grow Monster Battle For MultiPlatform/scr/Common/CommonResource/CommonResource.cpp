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

#ifdef __MY_DEBUG__
static int mStartTime;
static const int TIME_OUT = 6000;	//6秒でタイムアウト
#endif

ComRes::ComRes() {

	COMMON_RES_t COM_RES_TBL[eComResName_Num] = {
		// リソースの種類　　	ファイルパス
		{ eComResKind_Graphic,	"Resources/Graphics/BG/menu_ui_re.png"	},
		{ eComResKind_Graphic,	"Resources/Graphics/BG/deckedit.png"	},
		{ eComResKind_Graphic,	"Resources/Graphics/UI/msgBox.png"		},
		{ eComResKind_Graphic,  "Resources/Data/Font/MS_Gothic_0.png"   },
		{ eComResKind_Graphic,	"Resources/Graphics/Map/MapIcon.png"	},
		{ eComResKind_SoundBgm ,"Resources/Sound/BGM/BGM_0001.mp3","Title"	},
		{ eComResKind_SoundBgm ,"Resources/Sound/BGM/BGM_0002.mp3","Battle_1"	},
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00001.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00002.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00003.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00004.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00005.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00006.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00007.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00008.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00009.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00010.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00011.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00012.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00013.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00014.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00015.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00016.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00017.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00018.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00019.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00020.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00021.png" },
		//{ eComResKind_Graphic,	"Resources/Graphics/Monster/mon_00022.png" },
	};

	for (int i = 0; i < eComResName_Num; i++) {
		mComRes[i] = COM_RES_TBL[i];
	}
#ifdef __MY_DEBUG__
	mStartTime = 0;
	mIsError = false;
#endif

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


#ifdef __MY_DEBUG__

	if (mStartTime == 0) {
		mStartTime = GetNowCount();
	}

	double time = GetNowCount() - mStartTime;

	//タイムアウト時間が来たら抜ける
	if (time >= TIME_OUT) {
		Debug::ErorrMessage("汎用リソースの読み込みに失敗したため\n強制終了します");
		mIsError = true;
	}
	
#endif	// __MY_DEBUG__

	for (int i = 0; i < eComResName_Num; i++) {
		if (mComRes[i].kind != eComResKind_Graphic) continue;
		mComRes[i].Graphic = new Graphics();
		if (mComRes[i].Graphic->Load(mComRes[i].fileName) == false) {
			Debug::LogPrintf("画像の読み込みに失敗しました.(%s)", mComRes[i].fileName);
			return false;
		}
	}

	for (int i = 0; i < eComResName_Num; i++) {
		if (mComRes[i].kind != eComResKind_SoundBgm) continue;
		
		SoundMgr::GetInstance()->Add(mComRes[i].buffer, mComRes[i].fileName);

	}

	return true;
}

/*
	リソースを削除する
*/
void ComRes::Relese() {

	for (int i = 0; i < eComResName_Num; i++) {
		if (mComRes[i].kind != eComResKind_Graphic) continue;
		mComRes[i].Graphic->Relese();
		Delete(mComRes[i].Graphic);
	}

}

Graphics* ComRes::GetGraphicHandle(ComRes::eComResName name) const {
	
	const COMMON_RES_t* result = &mComRes[name];

	if (result->Graphic == NULL) {
		Debug::LogPrintf("指定したグラフィックは存在していません.");
		return NULL;
	}
	Graphics* graph = result->Graphic;

	return graph;
}

#ifdef __MY_DEBUG__
bool ComRes::IsError() {
	return mIsError;
}
#endif