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
class BattleAnimation;

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

	enum eActiveType {
		eActiveType_Attack,		// 攻撃
		eActiveType_Recovery,	// 回復
		eActiveType_Skill		// スキル
	};

	enum eDeckType {
		eDeckType_Player,		// プレイヤー　
		eDeckType_Enemy,		// エネミー
	};

	typedef struct MOVE_DATA_t{
		eDeckType moveDeckType;
		int moveId;
		eDeckType targetDeckType;
		int targetId;
		eActiveType activeType;
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
	MonsterDeck* mEnemy;	// 敵モンスター

	eBattleStep mNowStep;	//現在のステップ
	eBattleStep mNextStep;	//次のステップ

	eBattleMainStep mMainStep;	// メインステップ

	std::list<MOVE_DATA_t> mMoveData;

	Graphics mPlayerCard[5];
	Graphics mEnemyCard[5];

	BattleAnimation* mBattleAnimation;

protected:

	/*
		次のステップを設定する
		eBattleStep nextStep	:次のステップ登録
		eFadeType fadeType		:フェードタイプ
	*/
	void NexetStepRequest(eBattleStep nextStep, eFadeType fadeType = eFadeType_None);

	/*
		生存しているモンスターを返却する
		eDeckType type		: 探索するデッキタイプ
	*/
	Monster* GetLiveMonster(eDeckType type);

	/*
		手持ちのモンスターがすべて倒されているか判断する
		return	true	:倒されている
				false	:倒されていない
	*/
	bool CheckAllDead(eDeckType type);

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