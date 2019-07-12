/*
				ファイル名		:BattleMgr.h
				作成者			:
				作成日時		:2019/06/30
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BATTLE_MGR_H__
#define __BATTLE_MGR_H__

#include "Common/Task/TaskBase.h"
#include "Common/Utility/Status.h"
#include "BattleBase.h"
#include "BattleAnimation.h"
#include "BattleEffect.h"
#include "BattleUtil/BattleInfo/BtlInfo.h"
#include "BattlePhase/BtlTaskBase.h"

namespace battle {

	using namespace anim;
	using namespace effect;

	class BattleMgr : public TaskBase {

	private:


		static BattleMgr* mInstance;

		Utility::Status mStatus;

		BattleAnimation mAnim;
		BattleEffect mEffect;

		BtlInfo mBtlInfo;

		int mTaskId;

		BattleMgr();


	public:

		~BattleMgr();

		static TaskBase* New();
		static BattleMgr* getInstance();
		
		bool Initialize()override;
		void Finalize()override;

		void PreviousUpdate()override;
		void InputUpdate() override;
		bool Updata()override;
		void PostUpdate() override;
		void Draw()override;
				
		BattleAnimation& GetAnim() {
			return mAnim;
		}

		BattleEffect& GetEffect() {
			return mEffect;
		}

		BtlInfo& GetBtlInfo() {
			return mBtlInfo;
		}

	private:

		// フェーズ更新
		void _BtlPhaseUpdate();
		// フェード
		void _BtlPhaseFade();
		// バトル初期化
		void _BtlPhaseInit();
		// バトル開始演出
		void _BtlPhaseStart();
		// バトルメイン
		void _BtlPhaseMain();
		// バトル結果
		void _BtlPhaseResult();

	};

	inline BattleMgr* BtlGetMgr() {
		return BattleMgr::getInstance();
	}
	inline BattleAnimation& BtlGetAnim() {
		return BtlGetMgr()->GetAnim();
	}
	inline BattleEffect& BtlGetEffect() {
		return BtlGetMgr()->GetEffect();
	}
	inline BtlInfo& BtlGetInfo() {
		return BtlGetMgr()->GetBtlInfo();
	}

	class BtlTaskBase;
	int _BtlAddTask(BtlTaskBase* addTask);

	//タスクが終了しているか確認する
	inline bool _CheckTaskEnd(int taskId) {
		return (TaskMgr::getInstance().GetTask(taskId) == nullptr);
	}

}//battle

#endif // __BATTLE_MGR_H__
