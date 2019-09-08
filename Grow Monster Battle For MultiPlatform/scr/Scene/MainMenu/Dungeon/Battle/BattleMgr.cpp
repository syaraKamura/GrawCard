/*
				ファイル名		:BattleMgr.cpp
				作成者			:
				作成日時		:2019/06/30
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"

#include "BattlePhase/BtlPhaseStart.h"
#include "BattlePhase/BtlPhaseMain.h"
#include "BattlePhase/BtlPhaseResult.h"

#include "BattleMgr.h"


namespace battle {

	BattleMgr* BattleMgr::mInstance = nullptr;

	BattleMgr::BattleMgr() : mStatus(eBattlePhase_Fade),TaskBase() {
		
	}

	BattleMgr::~BattleMgr() {
		mInstance = nullptr;
	}

	TaskBase* BattleMgr::New() {
		if (mInstance == nullptr) {
			mInstance = new BattleMgr();
		}
		return mInstance;
	}
	
	BattleMgr* BattleMgr::getInstance() {
		if (mInstance == nullptr) {
			Debug::ErorrMessage("BattleMgrインスタンスが作成されえていません.");
			New();
		}
		return mInstance;
	}

	bool BattleMgr::Initialize() {
		return true;
	}

	void BattleMgr::Finalize() {
		
	}

	void BattleMgr::PreviousUpdate() {
		
	}

	void BattleMgr::InputUpdate() {
		
	}

	bool BattleMgr::Updata() {

		_BtlPhaseUpdate();
		
		this->mAnim.Updata();

		return true;
	}

	void BattleMgr::PostUpdate() {

	}

	void BattleMgr::Draw() {

#ifdef __MY_DEBUG__

		const char* phaseName[eBattlePhase_Num] = {
			"フェード",
			"初期化",
			"バトルスタート",
			"メイン",
			"リザルト",
		};

		DrawFormatString(0, 40, GetColor(255, 0, 0), "%s", phaseName[mStatus.GetState()]);
#endif

		// 初期化が終わるまでは描画を行わない
		if (mStatus.GetState() <= eBattlePhase_Initialize) { return; }

		this->mAnim.Draw();

		for (auto& monster : BtlGetInfo().GetMonsterList()) {
			if (monster->IsDead()) {
				monster->GetGraphics().SetAlpha(100);
			}

			monster->GetGraphics().Draw();
		}


	}

//==========================================================
//	バトルフェーズ
//==========================================================

	// バトルタスクを追加する
	int _BtlAddTask(BtlTaskBase* addTask) {
		return TaskMgr::getInstance().Add(addTask);
	}

	void BattleMgr::_BtlPhaseUpdate() {

#ifdef __MY_DEBUG__
#ifdef __WINDOWS__
		if (Keyboard_Press(KEY_INPUT_Z)) {
			TaskMgr::getInstance().RequestKill(mTaskId);
			mStatus.SetState(eBattlePhase_End);
		}
#endif //__WINDOWS__
#endif	// __MY_DEBUG__

		mStatus.Update();
		eBattlePhase state = (eBattlePhase)mStatus.GetState();
		switch (state) {
		case eBattlePhase_Fade			:	_BtlPhaseFade();	break;
		case eBattlePhase_Initialize	:	_BtlPhaseInit();	break;
		case eBattlePhase_BattleStart	:	_BtlPhaseStart();	break;
		case eBattlePhase_Main			:	_BtlPhaseMain();	break;
		case eBattlePhase_Result		:	_BtlPhaseResult(); 	break;
		default:
			break;
		}

		//  バトル終了
		if (mStatus.IsEnd( eBattlePhase_End ) ) {
			RequestKill();
		}
	}

	// フェード処理
	void BattleMgr::_BtlPhaseFade() {
		if (mStatus.IsFirstState()) {
			
		}
		if (Fade::GetInstance()->IsFadeEnd() == true) {
			if ((eBattlePhase)mStatus.GetOldState() == eBattlePhase_Result) {
				mStatus.SetState(eBattlePhase_End);
			}
			else {
				mStatus.SetState(eBattlePhase_Initialize);
			}
		}
	}

	// バトル開始初期化
	void BattleMgr::_BtlPhaseInit() {
		if (mStatus.IsFirstState()) {

#ifndef __MY_DEBUG__			
			if (AppData::GetInstance()->Exits()) 
			{
				//デッキセット
				SaveData* pSave = AppData::GetInstance()->GetSaveData();
				MonsterDeck deck = pSave->GetPlayer()->GetMonsterDeck();
				for (int i = 0; i < 5; i++) {
					if (deck.IsSetMonster(i)) {
						MonsterUnit mon(deck.GetMonster(i), eSide_Player);
						BtlGetInfo().AddMonster( mon );
					}
				}
			}
			else {
				// セーブデータが存在していないので終了
				mStatus.SetState(eBattlePhase_End);
				return;

			}
#else
			//デバッグ時はデバッグデッキを適応する
			Monster* deck[5] = {
				MonsterMgr::Instance()->GetMonsterData(0),
				MonsterMgr::Instance()->GetMonsterData(1),
				MonsterMgr::Instance()->GetMonsterData(2),
				MonsterMgr::Instance()->GetMonsterData(3),
				MonsterMgr::Instance()->GetMonsterData(4),
			};

			Monster* deck2[5] = {
				MonsterMgr::Instance()->GetMonsterData(5),
				MonsterMgr::Instance()->GetMonsterData(6),
				MonsterMgr::Instance()->GetMonsterData(7),
				MonsterMgr::Instance()->GetMonsterData(8),
				MonsterMgr::Instance()->GetMonsterData(9),
			};

			for (int i = 0; i < 5; i++) {
				MonsterUnit* mon = new MonsterUnit(deck[i], eSide_Player);
				BtlGetInfo().AddMonster(mon);
				Graphics& graph = mon->GetGraphics();
				graph.SetBasePosition(200 + i * 200, WINDOW_HEIGHT);
				graph.SetVisible(false);
			}

			for (int i = 0; i < 5; i++) {
				MonsterUnit* mon = new MonsterUnit(deck2[i], eSide_Enemy);
				BtlGetInfo().AddMonster(mon);
				Graphics& graph = mon->GetGraphics();
				graph.SetBasePosition(200 + i * 200, 200);
				graph.SetPosition(200 + i * 200, 200);
				graph.SetVisible(false);
			}


#endif//  __MY_DEBUG__			
		}
		mStatus.SetState(eBattlePhase_BattleStart);
	}

	// バトル開始演出
	void BattleMgr::_BtlPhaseStart() {
		if (mStatus.IsFirstState()) {
			mTaskId = _BtlAddTask(new BtlPhaseStart());
		}
		
		if (_CheckTaskEnd(mTaskId)) {
			mStatus.SetState(eBattlePhase_Main);
		}
	}

	// バトルメイン
	void BattleMgr::_BtlPhaseMain() {
		if (mStatus.IsFirstState()) {
			mTaskId = _BtlAddTask(new BtlPhaseMain());
		}

		if (_CheckTaskEnd(mTaskId)) {
			mStatus.SetState(eBattlePhase_Result);
		}

	}

	// バトル結果
	void BattleMgr::_BtlPhaseResult() {
		if (mStatus.IsFirstState()) {

		}

#ifdef __WINDOWS__
		if (Keyboard_Press(KEY_INPUT_Z)) {
			mStatus.SetState(eBattlePhase_Fade);
			Fade::GetInstance()->FadeIn();
		}
#endif // __WINDOWS__

	}


}//battle