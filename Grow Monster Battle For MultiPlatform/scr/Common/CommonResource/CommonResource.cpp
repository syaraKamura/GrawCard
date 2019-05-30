/*
				ファイル名		:CommonResource.cpp
				作成者			:
				作成日時		:2018/02/13
				ソース説明		:
				
					汎用リソース
				
				備考
				
				
				
!*/

#include "AppData/StoryData/StoryData.h"
#include "Common/ResourceTable/GraphTable.h"

#include "Common/GameCommon.h"
#include "Common/Graphics/Graphics.h"
#include "CommonResource.h"

enum eSoundTag {
	eSoundTag_Title,
	eSoundTag_Batlle_1,
	eSoundTag_MainMenu,
	eSoundTag_Max,
};

static const char* smSOUND_TAG_TABLE[eSoundTag_Max] = {
	"Title",
	"Battle_1",
	"MainMenu",
};

ComRes* ComRes::mInstance = nullptr;

#ifdef __MY_DEBUG__
static int mStartTime;
static const int TIME_OUT = 60000;	//60秒でタイムアウト
#endif

ComRes::ComRes() {

	COMMON_RES_t COM_RES_TBL[eComResName_Num] = {
		// リソースの種類　　	ファイルパス
		{ eComResKind_Graphic,	"Resources/Graphics/BG/menu_ui_re.png"	,	graphicsTable::eGraphTag_MainMenuBG	},
		{ eComResKind_Graphic,	"Resources/Graphics/BG/deckedit.png"	,	graphicsTable::eGraphTag_CommonBG	},
		{ eComResKind_Graphic,	"Resources/Graphics/UI/msgBox.png"		,	graphicsTable::eGraphTag_MsgBox		},
		{ eComResKind_Graphic,  "Resources/Data/Font/MS_Gothic_0.png"	,	graphicsTable::eGraphTag_BMFont		},
		{ eComResKind_Graphic,	"Resources/Graphics/Map/MapIcon.png"	,	graphicsTable::eGraphTag_MapIcon	},
		{ eComResKind_Graphic,	"Resources/Graphics/UI/story_button.png",	graphicsTable::eGraphTag_StoryButton},
		{ eComResKind_Graphic,	"Resources/Graphics/UI/PlayerBar.png"	,	graphicsTable::eGraphTag_PlayerStatusBar,			},

		{ eComResKind_SoundBgm ,"Resources/Sound/BGM/BGM_0001.ogg"		,	eSoundTag_Title					},
		{ eComResKind_SoundBgm ,"Resources/Sound/BGM/BGM_0002.ogg"		,	eSoundTag_Batlle_1				},
		{ eComResKind_SoundBgm ,"Resources/Sound/BGM/BGM_0003.ogg"		,	eSoundTag_MainMenu				}

	};

	for (int i = 0; i < eComResName_Num; i++) {
		mComRes[i] = COM_RES_TBL[i];
	}

	mStoryData = new story::StoryData();

#ifdef __MY_DEBUG__
	mStartTime = 0;
	mIsError = false;
#endif

	mLoadCnt = 0;

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

	bool ret = false;

	if (mLoadCnt == 0) {
		for (int i = 0; i < eComResName_Num; i++) {
			if (mComRes[i].kind != eComResKind_Graphic) continue;
			mComRes[i].Graphic = new Graphics();
			const char* tag = graphicsTable::GetGraphTag(mComRes[i].tagNum);
			if (tag == nullptr) {
				Debug::ErorrMessage("タグが設定されていません.(%s)",mComRes[i].fileName);
				continue;
			}
			graphics::LoadGraphics::GetInstance()->Load(mComRes[i].fileName, tag);
			//if (mComRes[i].Graphic->Load(mComRes[i].fileName) == false) {
			//	Debug::LogPrintf("画像の読み込みに失敗しました.(%s)", mComRes[i].fileName);
			//	return false;
			//}
		}
		mLoadCnt++;
	}
	else if (mLoadCnt == 1) {
		for (int i = 0; i < eComResName_Num; i++) {
			if (mComRes[i].kind != eComResKind_SoundBgm) continue;
			const char* tag = smSOUND_TAG_TABLE[mComRes[i].tagNum];
			SoundMgr::GetInstance()->Add(tag, mComRes[i].fileName);

		}
		mLoadCnt++;
	}
	else if (mLoadCnt == 2) {

		if (mStoryData->IsLoadEnd()) {
			mStoryData->LoadData();
			mLoadCnt++;
		}
		
	}
	else {
#ifdef ENABLE_EFFEKSEER
		EffekseerEffect::EffectLoader::Instance()->Load((int)eEffect::TestEffect1, "Resources/Effect/sword.efk");
		EffekseerEffect::EffectLoader::Instance()->Load((int)eEffect::TestEffect2, "Resources/Effect/aura.efk");
#endif // ENABLE_EFFEKSEER
		mLoadCnt++;
		ret = true;
	}

	return ret;
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

AdvScript::ScriptBase* ComRes::StartAdvScript(int idx) {
	return mStoryData->RequestADV(idx);
}


#ifdef __MY_DEBUG__
bool ComRes::IsError() {
	return mIsError;
}
#endif