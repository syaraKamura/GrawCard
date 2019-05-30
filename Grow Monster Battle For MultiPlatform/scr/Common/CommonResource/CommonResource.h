/*
				ファイル名		:CommonResource.h
				作成者			:
				作成日時		:2018/02/13
				ソース説明		:
				
					汎用リソース
				
				備考
				
				
				
!*/

#ifndef __COMMON_RESOURCE_H__
#define __COMMON_RESOURCE_H__


namespace story {
	class StoryData;
}

namespace AdvScript {
	class ScriptBase;
}

class Graphics;

#if 0
enum class eEffect : int{
	
	TestEffect1,
	TestEffect2,

	BATTLE_EFFECT_START = 1000,


	BATTLE_EFFECT_END,

};
#endif

class ComRes {

public :
	
	enum eComResName {
		eComResName_MainMenuBG,			//メインメニュー背景
		eComResName_CommonBG,			//汎用背景
		eComResName_MsgBox,				//メッセージボックス
		eComResName_BMFont,				//フォント画像
		eComResName_MapIcon,			// マップアイコン
		eComResName_StoryButtion,		// ストーリボタン
		eComResname_CommonBGM,			// 汎用BGM
		eComResname_CommonBGM2,			// 汎用BGM2
		eComResname_CommonBGM3,			// 汎用BGM3
		eComResName_PlayerStatusBar,	// プレイヤーステータスバー
		//eComResName_Monster_00001,			//モンスターカード
		//eComResName_Monster_00002,			//モンスターカード
		//eComResName_Monster_00003,			//モンスターカード
		//eComResName_Monster_00004,			//モンスターカード
		//eComResName_Monster_00005,			//モンスターカード
		//eComResName_Monster_00006,			//モンスターカード
		//eComResName_Monster_00007,			//モンスターカード
		//eComResName_Monster_00008,			//モンスターカード
		//eComResName_Monster_00009,			//モンスターカード
		//eComResName_Monster_00010,			//モンスターカード
		//eComResName_Monster_00011,			//モンスターカード
		//eComResName_Monster_00012,			//モンスターカード
		//eComResName_Monster_00013,			//モンスターカード
		//eComResName_Monster_00014,			//モンスターカード
		//eComResName_Monster_00015,			//モンスターカード
		//eComResName_Monster_00016,			//モンスターカード
		//eComResName_Monster_00017,			//モンスターカード
		//eComResName_Monster_00018,			//モンスターカード
		//eComResName_Monster_00019,			//モンスターカード
		//eComResName_Monster_00020,			//モンスターカード
		//eComResName_Monster_00021,			//モンスターカード
		//eComResName_Monster_00022,			//モンスターカード

		eComResName_Num,
	};

private:


	enum eComResKind {
		eComResKind_Graphic,
		eComResKind_SoundBgm,
		eComResKind_Num,
	};

	typedef struct {
		eComResKind kind;
		char* fileName;
		int tagNum;
		Graphics* Graphic;
	}COMMON_RES_t;

	COMMON_RES_t mComRes[eComResName_Num];

#ifdef __MY_DEBUG__
	
	bool mIsError;

#endif


protected:
	
	static ComRes* mInstance;
	story::StoryData* mStoryData;
	int mLoadCnt;
	ComRes();
	
public :

	static void Create();
	static void Destory();
	static ComRes* Instance();
	
	bool Load();
	void Relese();

#ifdef __MY_DEBUG__
	bool IsError();
#endif

	Graphics* GetGraphicHandle(eComResName name) const;
	AdvScript::ScriptBase* StartAdvScript(int idx);

};

#endif // __COMMON_RESOURCE_H__