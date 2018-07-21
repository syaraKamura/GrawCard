/*
				ファイル名		:ScriptBase.h
				作成者			:
				作成日時		:2018/04/03
				ソース説明		:
					
					スクリプト基底クラス
				
				備考
				
					基本的な動作を作成していく

					〇スクリプトの解読機能
					〇スクリプトファイル読み込み
				
!*/

#include "Common/Task/TaskBase.h"

#ifndef __SCRIPT_BASE_H__
#define __SCRIPT_BASE_H__

 
#include "Common/String/StringBase.h"
#include <vector>

class ScriptAnimation;

class ScriptBase : public TaskBase {

private:

	const static int MAX_INT_VALUE = 6;
	const static int MAX_FLOAT_VALUE = 6;
	const char* SCRIPT_DATA_PATH = "Resources/Data/AdvScripts/";
	const char* DELIM_STRINGS = " ";
	
	enum eAnalysis {
		eAnalysis_Error = -1,		//エラー
		eAnalysis_Mes,				//メッセージ
		eAnalyis_SetFlag,			//フラグを設定
		eAnalyis_FlagOn,			//フラグをオンにする
		eAnalyis_FlagOff,			//フラグをオフにする
		eAnalyis_If,				//if文	:ONになっているか確認する
		eAnalyis_Ifn,				//ifn文	:OFFになっているか確認する
		eAnalysis_endif,			//if文終了
		eAnalysis_Lable,			//ラベル
		eAnalysis_Goto,				//指定のラベル位置に移動する
		eAnalysis_LoadScript,		//スクリプトの読み込みを行う
		eAnalysis_LoadGraph,		//画像読み込み
		eAnalysis_DrawGraph,		//画像表示
		eAnalysis_HideGraph,		//画像を非表示にする
		eAnalysis_AnimGraph,		//画像をアニメーションさせる
		eAnalysis_End,				//スクリプト終了

	};

	typedef struct {
		int mGraphId;
		Graphics* mGraph;
	}GRAPHICS_DATA_t;

	typedef struct {
		int mFlagID;
		char mFlagName[256];
	}FLAG_DATA_t;

	typedef struct {
		char mMethod[27];
		char mString[1024];
		int mInt[MAX_INT_VALUE];
		float mFloat[MAX_FLOAT_VALUE];
	}ADV_DATA_t;


	char mFileName[256];
	std::list<std::string> mStringDatas;
	int mNowLine;			//現在の行
	int mMaxLine;			//最大行
	bool mIsEnd;			//スクリプト終了判定

	Graphics mMsgGraphics;

	StringBase* mString;
	StringBase::eDrawState mOldStringDrawState;	//文字列描画状態
	StringBase::eDrawState mStringDrawState;	//文字列描画状態
	bool mIsAllDrawString;						//文字をすべて描画するか
	bool mIsDrawNextIcon;						//次へのアイコンを描画するか
	bool mIsWait;								//次の処理を行うのを待つか
	SaveData* mSaveData;

	ADV_DATA_t* mAdvData;
	
	ScriptAnimation* mAnimation;

	std::vector<FLAG_DATA_t> mFlagDatas;
	std::vector<GRAPHICS_DATA_t> mGraphicsDatas;

	std::vector<unsigned int> mAnimOrderIdList;


private :

	void SplitString(char* str, const char* delim, std::list<std::string>* list, char* context = NULL);
	bool SetFlag(const char* flagName, unsigned int flag);
	/*
		スクリプト解析
	*/
	void Analysis();

	bool Load(const char* fileName);
	void CreateFilePath(const char* fileName);

	eAnalysis MethodAnalysis(const char* str);
	

public:

	ScriptBase();
	ScriptBase(const char* scriptName);

	bool Initialize()override;
	void Finalize()override;

	void PreviousUpdate()override;
	void InputUpdate() override;
	bool Updata()override;
	void PostUpdate() override;
	void Draw()override;

	bool IsEnd();

};

#endif // __TEMPLETE_H__