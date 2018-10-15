/*
				ファイル名		:BattleBase.h
				作成者			:
				作成日時		:2018/03/15
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BATTLE_BASE_H__
#define __BATTLE_BASE_H__

#include "Common/Task/TaskBase.h"

class AppData;
class Player;

class BattleBase : public TaskBase{

public :

	enum eBattleStep {
		eBattleStep_None = -1,
		eBattleStep_Fade,			//フェード開始
		eBattleStep_Initialize,		//初期化処理
		eBattleStep_BattleStart,	//バトル開始演出
		eBattleStep_Main,			//バトルメイン処理
		eBattleStep_Result,			//リザルト
		
		eBattleStep_Num,
	};

	enum eFadeType {
		eFadeType_None = -1,
		eFadeType_In,
		eFadeType_Out,
	};

	enum eBattleMainStep {
		eBattleMainStep_None = -1,
		eBattleMainStep_Command,
		eBattleMainStep_Battle,

		eBattleMainStep_Judgement,

		eBattleMainStep_Num,
	};

#ifdef __MY_DEBUG__
	const char* dbg_STEP_TITLE[eBattleStep_Num] =
	{
		{"フェード"},
		{ "初期化中" },
		{ "バトル開始演出中" },
		{ "バトルメイン" },
		{ "リザルト" },
	};

	const char* dbg_MAIN_STEP_TITLE[eBattleMainStep_Num] =
	{
		{ "コマンド選択" },
		{ "バトル" },
		{ "判定" },
		
	};

#endif

protected:
	
	Graphics* mGraphics;
	Graphics* mCard;

	Player* mPlayer;


	eBattleStep mNowStep;	//現在のステップ
	eBattleStep mNextStep;	//次のステップ

	eBattleMainStep mMainStep;	// メインステップ


protected:

	/*
		次のステップを設定する
		eBattleStep nextStep	:次のステップ登録
		eFadeType fadeType		:フェードタイプ
	*/
	void NexetStepRequest(eBattleStep nextStep, eFadeType fadeType = eFadeType_None);

public:

	BattleBase();

	bool Initialize()override;
	void Finalize()override;

	void PreviousUpdate()override;
	bool Updata()override;
	void PostUpdate() override;
	void Draw()override;

	eBattleStep BattleMainUpdate();
	void BattleMainDraw();

};

#endif // __BATTLE_BASE_H__