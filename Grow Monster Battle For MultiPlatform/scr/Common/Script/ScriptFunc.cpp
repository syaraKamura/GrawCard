/*
				ファイル名		:ScriptBase.cpp
				作成者			:
				作成日時		:2019/01/31
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "ScriptFunc.h"
#include "ScriptAnimation.h"
#include "ScriptBase.h"

namespace AdvScript {

	typedef int(*ScriptFunc)();
	
	ScriptBase* mspScript = NULL;
	//------------------------------------------------------------------
	//プロトタイプ宣言
	//------------------------------------------------------------------
	static int MessageFunc();
	static int TalkFunc();
	static int FlagOnFunc();
	static int FlagOffFunc();
	static int IfFunc();
	static int IfnFunc();
	static int GotoFunc();
	static int LoadScriptFunc();
	static int DrawGraphFunc();
	static int HideGraphFunc();
	static int AnimGraphFunc();
	static int SetGraphAlphaFunc();
	static int PlaySoundFunc();
	static int StopSoundFunc();
	static int EndScriptFunc();
	//------------------------------------------------------------------


	ScriptFunc FunctionTable[] = {
		// nullptr,			//	eAnalysis_Error = -1,		//エラー							
		TalkFunc,			//	eAnalysis_Talk,				//会話									[話者名][文字列]
		MessageFunc,		//	eAnalysis_Mes,				//メッセージ							[文字列]
		nullptr,			//	eAnalysis_SetFlag,			//フラグを設定							[フラグ名][フラグ番号]
		FlagOnFunc,			//	eAnalysis_FlagOn,			//フラグをオンにする					[フラグ名]
		FlagOffFunc,		//	eAnalysis_FlagOff,			//フラグをオフにする					[フラグ名]
		IfFunc,				//	eAnalysis_If,				//if文	:ONになっているか確認する		[フラグ名]
		IfnFunc,			//	eAnalysis_Ifn,				//ifn文	:OFFになっているか確認する		[フラグ名]
		nullptr,			//	eAnalysis_endif,			//if文終了								
		nullptr,			//	eAnalysis_Lable,			//ラベル								[ラベル名]
		GotoFunc,			//	eAnalysis_Goto,				//指定のラベル位置に移動する			[ラベル名]
		LoadScriptFunc,		//	eAnalysis_LoadScript,		//スクリプトの読み込みを行う			[スクリプトファイルパス]
		nullptr,			//	eAnalysis_LoadGraph,		//画像読み込み							[管理番号][画像ファイルパス]
		DrawGraphFunc,		//	eAnalysis_DrawGraph,		//画像表示								[管理番号][X座標][Y座標][フェードインを行うか(0 or 1)]
		HideGraphFunc,		//	eAnalysis_HideGraph,		//画像を非表示にする					[管理番号][非表示までにかかる時間(1以上)]
		AnimGraphFunc,		//	eAnalysis_AnimGraph,		//画像をアニメーションさせる			[管理番号][アニメーション番号][ループ再生か(0 or 1)][今の座標を原点とするか(0 or 1)]
		SetGraphAlphaFunc,	//	eAnalysis_SetGraphAlpha,	//画像のアルファ値を設定する			[管理番号][アルファ値(0 ~ 255)]
		nullptr,			//	eAnalysis_LoadSound,		//サウンドの読み込み					[管理番号][ファイルパス]
		PlaySoundFunc,		//	eAnalysis_PlaySound,		//サウンドの再生						[管理番号]
		StopSoundFunc,		//	eAnalysis_StopSound,		//サウンドの停止						[管理番号]
		EndScriptFunc,		//	eAnalysis_End,				//スクリプト終了
	};

	void ScriptFunc_Initialize(ScriptBase& script) {
		mspScript = &script;
	}
	
	/*
		終了処理
		delete事態はScriptBaseを使用しているクラスが行う
	*/
	void ScriptFunc_Finalize() {
		mspScript = NULL;
	}

	int ScriptFunc_FunctionUpdate() {
		
		if (mspScript == NULL) {
			return ScriptBase::eActType_Error;
		}

		ScriptBase::eAnalysis funcType = mspScript->GetNowActFunction();

		if (funcType == ScriptBase::eAnalysis_Error) {
			return ScriptBase::eActType_Error;
		}

		ScriptFunc func = FunctionTable[funcType];

		if (func == nullptr) {
			return ScriptBase::eActType_None;
		}

		return func();

	}


	/*
		メッセージ表示
	*/
	static int MessageFunc() {

		auto data = mspScript->GetNowActAdvData();

		mspScript->mTalkName->SetString("");			// 話者はいないので文字列をない状態に設定
		mspScript->mString->SetString(data.mString);
		
		return ScriptBase::eActType_InputWait;
	}

	/*
		会話メッセージ
	*/
	static int TalkFunc() {

		auto data = mspScript->GetNowActAdvData();

		mspScript->mString->SetString(data.mString2);
		mspScript->mTalkName->SetString(data.mString);

		return ScriptBase::eActType_InputWait;
	}

	/*
		フラグをOnにする
	*/
	static int FlagOnFunc() {
		auto data = mspScript->GetNowActAdvData();
		mspScript->SetFlag(data.mString, TRUE);
		return ScriptBase::eActType_Next;
	}

	/*
		フラグをOffにする
	*/
	static int FlagOffFunc() {
		auto data = mspScript->GetNowActAdvData();
		mspScript->SetFlag(data.mString, FALSE);
		return ScriptBase::eActType_Next;
	}

	/*
		条件がtrueか判断する
	*/
	static int IfFunc() {

		auto data = mspScript->GetNowActAdvData();

		SaveData::FLAG_DATA_t* mflagData = mspScript->mSaveData->GetFlagData();
		char* name = data.mString;
		int id = -1;

		for (unsigned int i = 0; i < mspScript->mFlagDatas.size(); i++) {
			char* flagName = mspScript->mFlagDatas[i].mFlagName;
			if (strcmpDx(flagName, name) == 0) {
				id = mspScript->mFlagDatas[i].mFlagID;
				break;
			}
		}

		if (id >= 0 && mflagData->mFlags[id]) {
			//mNowLine++;
		}
		else {

			//isNext = false;

#ifdef __MY_DEBUG__
			bool find = false;
#endif	//__MY_DEBUG__
			int ifId = data.mInt[0];
			for (int i = mspScript->mNowLine; i < mspScript->mMaxLine; i++) {
				data = mspScript->mAdvData[i];
				//ret = MethodAnalysis(data.mMethod);
				ScriptBase::eAnalysis ret = data.mMethodId;
				if (ret == ScriptBase::eAnalysis_endif) {
					if (data.mInt[0] != ifId) continue;
					mspScript->mNowLine = i;
#ifdef __MY_DEBUG__
					find = true;
#endif	//__MY_DEBUG__
					break;
				}
			}
#ifdef __MY_DEBUG__
			if (find == false) {
				Debug::ErorrMessage("$endifを見つけることができませんでした.");
			}
#endif	//__MY_DEBUG__
		}

		return ScriptBase::eActType_Next;

	}

	/*
		条件がfalseか判断する
	*/
	static int IfnFunc() {

		auto data = mspScript->GetNowActAdvData();

		SaveData::FLAG_DATA_t* mflagData = mspScript->mSaveData->GetFlagData();
		char* name = data.mString;
		int id = -1;

		for (unsigned int i = 0; i < mspScript->mFlagDatas.size(); i++) {
			char* flagName = mspScript->mFlagDatas[i].mFlagName;
			if (strcmpDx(flagName, name) == 0) {
				id = mspScript->mFlagDatas[i].mFlagID;
				break;
			}
		}

		if (id >= 0 && !mflagData->mFlags[id]) {
			//mNowLine++;
		}
		else {

			//isNext = false;

#ifdef __MY_DEBUG__
			bool find = false;
#endif	//__MY_DEBUG__
			int ifId = data.mInt[0];
			for (int i = mspScript->mNowLine; i < mspScript->mMaxLine; i++) {
				data = mspScript->mAdvData[i];
				//ret = MethodAnalysis(data.mMethod);
				ScriptBase::eAnalysis ret = data.mMethodId;
				if (ret == ScriptBase::eAnalysis_endif) {
					if (data.mInt[0] != ifId) continue;
					mspScript->mNowLine = i;
#ifdef __MY_DEBUG__
					find = true;
#endif	//__MY_DEBUG__
					break;
				}
			}
#ifdef __MY_DEBUG__
			if (find == false) {
				Debug::ErorrMessage("$endifを見つけることができませんでした.");
			}
#endif	//__MY_DEBUG__
		}
		return ScriptBase::eActType_Next;
	}

	/*
		指定のラベルの場所へ移動する(同名ラベルは最初に見つけラベルへ移動する)
	*/
	static int GotoFunc() {

		auto data = mspScript->GetNowActAdvData();

		char labelName[256];
		strcpyDx(labelName, data.mString);

#ifdef __MY_DEBUG__
		bool find = false;
#endif	//__MY_DEBUG__
		for (int i = 0; i < mspScript->mMaxLine; i++) {
			data = mspScript->mAdvData[i];
			//ret = MethodAnalysis(data.mMethod);
			ScriptBase::eAnalysis ret = data.mMethodId;
			if (ret == ScriptBase::eAnalysis_Lable) {
				if (strcmpDx(labelName, data.mString) == 0) {
					mspScript->mNowLine = i;
#ifdef __MY_DEBUG__
					find = true;
#endif	//__MY_DEBUG__
					break;
				}
			}
		}
#ifdef __MY_DEBUG__
		if (find == false) {
			Debug::ErorrMessage("ラベル%sを見つけることができませんでした.", labelName);
		}
#endif	//__MY_DEBUG__

		return ScriptBase::eActType_Next;
	}

	/*
		スクリプトを読み込む
		※先に読み込まれているスクリプトの後ろに追加でスクリプトデータを設定する
	*/
	static int LoadScriptFunc() {
		
		auto data = mspScript->GetNowActAdvData();

		mspScript->CreateFilePath(data.mString);
		if (mspScript->Load(mspScript->mFileName) == false) {
			Debug::ErorrMessage("%sの読み込みに失敗しました.", data.mString);
		}
		return ScriptBase::eActType_Next;
	}

	/*
		画像を描画する
	*/
	static int DrawGraphFunc() {
		auto data = mspScript->GetNowActAdvData();

		Graphics* graph = NULL;
		for (unsigned int i = 0; i < mspScript->mGraphicsDatas.size(); i++) {
			if (mspScript->mGraphicsDatas[i].mGraphId == data.mInt[0]) {
				graph = mspScript->mGraphicsDatas[i].mGraph;
				break;
			}
		}

		if (graph != NULL) {
			int posX = 0;//graph->GetPositionX();
			int posY = 0;//graph->GetPositionY();

			if (data.mInt[1] > -1) {
				posX = data.mInt[1];
			}
			if (data.mInt[2] > -1) {
				posY = data.mInt[2];
			}

			graph->SetPosition(posX, posY);
			graph->SetBasePosition(posX, posY);
			graph->SetVisible(true);

			if (data.mInt[3] > -1) {

				int fade = (data.mInt[3] == 1) ? ScriptAnimation::eAnimationNo_FadeIn : ScriptAnimation::eAnimationNo_None;

				if (fade != ScriptAnimation::eAnimationNo_None) {
					bool isLoop = false;
					bool isNowBasePos = true;
					unsigned int id = mspScript->mAnimation->AttachGraphics(graph, fade, isLoop, isNowBasePos);
					mspScript->mAnimOrderIdList.push_back(id);
				}
			}
		}

		return ScriptBase::eActType_Next;
	}

	/*
		画像を非表示にする
		1以上をの値を設定することで設定されたフレームをかけてフェードする
	*/
	static int HideGraphFunc() {

		auto data = mspScript->GetNowActAdvData();

		Graphics* graph = NULL;
		for (unsigned int i = 0; i < mspScript->mGraphicsDatas.size(); i++) {
			if (mspScript->mGraphicsDatas[i].mGraphId == data.mInt[0]) {
				graph = mspScript->mGraphicsDatas[i].mGraph;
				break;
			}
		}

		if (graph != NULL) {

			float tmp = (float)graph->GetAlpah();
			if (tmp > 0.0f) {
				tmp -= 255.0f / (float)data.mInt[1];
				graph->SetAlpha(tmp);
				//isNext = false;
				//mIsWait = true;
				return ScriptBase::eActType_Wait;
			}
			else {
				graph->SetVisible(false);
			}

		}
		return ScriptBase::eActType_Next;
	}

	/*
		アニメーションを再生する
	*/
	static int AnimGraphFunc(){
	
		auto data = mspScript->GetNowActAdvData();

		Graphics * graph = NULL;
		for (unsigned int i = 0; i < mspScript->mGraphicsDatas.size(); i++) {
			if (mspScript->mGraphicsDatas[i].mGraphId == data.mInt[0]) {
				graph = mspScript->mGraphicsDatas[i].mGraph;
				break;
			}
		}

		if (graph != NULL) {
			bool isLoop = (data.mInt[2] == 1) ? true : false;
			bool isNowBasePos = (data.mInt[3] == 1) ? true : false;
			unsigned int id = mspScript->mAnimation->AttachGraphics(graph, data.mInt[1], isLoop, isNowBasePos);
			mspScript->mAnimOrderIdList.push_back(id);
		}
		return ScriptBase::eActType_Next;
	}

	/*
		指定の画像のアルファ値を設定する
	*/
	static int SetGraphAlphaFunc() {
		
		auto data = mspScript->GetNowActAdvData();
		
		Graphics* graph = NULL;
		for (unsigned int i = 0; i < mspScript->mGraphicsDatas.size(); i++) {
			if (mspScript->mGraphicsDatas[i].mGraphId == data.mInt[0]) {
				graph = mspScript->mGraphicsDatas[i].mGraph;
				break;
			}
		}

		if (graph != NULL) {
			int alpha = data.mInt[1];
			if (alpha < 0) {
				alpha = 0;
			}
			else if (alpha > 255) {
				alpha = 255;
			}
			graph->SetAlpha(alpha);
		}
		return ScriptBase::eActType_Next;
	}

	/*
		サウンドを再生する
	*/
	static int PlaySoundFunc() {
		
		auto data = mspScript->GetNowActAdvData();

		for (unsigned int i = 0; i < mspScript->mSoundDatas.size(); i++) {
			if (mspScript->mSoundDatas[i].mSoundId == data.mInt[0]) {
				SoundMgr::GetInstance()->Play(mspScript->mSoundDatas[i].mSoundStrId);
				break;
			}
		}
		return ScriptBase::eActType_Next;
	}
	
	/*
		サウンドを停止する
	*/
	static int StopSoundFunc() {

		auto data = mspScript->GetNowActAdvData();

		for (unsigned int i = 0; i < mspScript->mSoundDatas.size(); i++) {
			if (mspScript->mSoundDatas[i].mSoundId == data.mInt[0]) {
				SoundMgr::GetInstance()->Stop(mspScript->mSoundDatas[i].mSoundStrId);
				break;
			}
		}

		return ScriptBase::eActType_Next;

	}

	/*
		スクリプトを終了する
	*/
	static int EndScriptFunc() {
		return ScriptBase::eActType_End;
	}

}