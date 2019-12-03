/*
				ファイル名		:BtlCommon.h
				作成者			:
				作成日時		:2019/07/06
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BTL_COMMON_H__
#define __BTL_COMMON_H__

namespace battle {

	enum eSide {
		eSide_Player,
		eSide_Enemy,
		eSide_Max,
	};

	enum ePlayMode {
		ePlayMode_Input,	// 入力操作
		ePlayMode_Auto,		// 自動操作
		ePlayMode_Pause,	// 一時停止
		ePlayMode_Max,
	};

	enum eBuffType {
		eBuffType_None = -1,
		eBuffType_AddPower,	// パワーが上昇する
		eBuffType_Max,
	};

	enum eBattlePhase {
		eBattlePhase_None = -1,
		eBattlePhase_Fade,				//フェード開始
		eBattlePhase_Initialize,		//初期化処理
		eBattlePhase_BattleStart,		//バトル開始演出
		eBattlePhase_Main,				//バトルメイン処理
		eBattlePhase_Result,			//リザルト

		eBattlePhase_End,

		eBattlePhase_Num,
	};

	typedef struct BATTLE_MOVE_DATA_t{
		class MonsterUnit* Attacker;	// 攻撃側
		class MonsterUnit* Deffender;	// 防御側
		int AttackKind;			// 攻撃の種類

		void init() {
			Attacker = nullptr;
			Deffender = nullptr;
			AttackKind = 0;
		}

	}BATTLE_MOVE_DATA;

}// battle


#endif // __BTL_COMMON_H__