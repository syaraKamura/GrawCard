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
#include <vector>

class AppData;
class Player;
class BattleAnimation;
class Animation;
class Button;

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
		eBattleMainStep_MoveOrder,		// 行動順番設定
		eBattleMainStep_Command,		// コマンド入力
		eBattleMainStep_Battle,
		eBattleMainStep_BattleAnim,		// バトルアニメーション

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

	enum eMoveType {
		eMoveType_Manual,		// 入力行動
		eMoveType_Auto,			// 自動行動 
		
	};

	enum eCommand {
		eCommand_CehcekActionType,		// 行動の種類を判断する
		eCommand_Select,		// 選択
		eCommand_SelectTarget,	// 対象選択
		eCommand_Decision,		// 確定
	};

	enum eButtonType {
		eButtonType_Auto,
		eButtonType_Attack,
		eButtonType_Skill,
		eButtonType_Item,
		eButtonType_Num,
	};

	typedef struct {
		eDeckType moveDeckType;
		Monster* moveMonster;
		eDeckType targetDeckType;
		Monster* targetMonster;
		eActiveType activeType;
	}MOVE_DATA_t;

	typedef struct {
		Monster* monster;
		eDeckType type;
		Graphics graph;
		int moveOreder;
		bool isDead;
		eMoveType moveType;		// 行動方法
	}MONSTER_DATA_t;

	typedef struct {
		int damage;
		Monster* monster;
	}DAMAGE_MONSTER_t;

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

	std::vector<MONSTER_DATA_t> mMonsterData;
	std::vector<DAMAGE_MONSTER_t> mTargetList;

	MONSTER_DATA_t mNowOrderMonsterData;
	MOVE_DATA_t mOrderMoveData;		// 行動データ

	Graphics mPlayerCard[5];
	Graphics mEnemyCard[5];

	BattleAnimation* mBattleAnimation;
	Animation* mAnim;

	eCommand mActionCommand;

	Button* mButtons[eButtonType_Num];

	int mStartAnimCount;
	int mAnimPlayMonsterNum;

	int mBattleTimeCounter;
	int mBattleTimeBase;

	int mMoveOrderMonsterNum;

	int mDamage;

	bool mIsAutoAction;		// 自動操作

	class ButtonAnim;

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

	void BattleStartAnimation();

	void SelectCommandUpdate();
	void SelectCommandDraw();

public:

	BattleBase();
	BattleBase(Player* player);
	
	bool Initialize()override;
	void Finalize()override;

	void PreviousUpdate()override;
	bool Updata()override;
	void PostUpdate() override;
	void Draw()override;

	eBattleStep BattleMainUpdate();
	void BattleMainDraw();

	void OnClick(View* view) override;

};

class BattleBase::ButtonAnim : public TaskBase {

public :

	enum eAnim{
		eAnim_None,
		eAnim_InSide,
		eAnim_OutSide,
	};

private:


	Button* mButton;
	eAnim mAnim;

	int mBasePosX;
	int mBasePosY;

public:

	ButtonAnim(Button* button);
	~ButtonAnim();

	bool Initialize()override;
	void Finalize()override;

	void PreviousUpdate()override;
	void InputUpdate() override;
	bool Updata()override;
	void PostUpdate() override;
	void Draw()override;

	/*
		ボタンのアニメーションが再生中か
		return	true	: 再生中
				false	: 再生中ではない
	*/
	bool IsPlayAnim();

	/*
		アニメーションの再生
	*/
	void PlayAnim(eAnim anim);

};

#endif // __BATTLE_BASE_H__