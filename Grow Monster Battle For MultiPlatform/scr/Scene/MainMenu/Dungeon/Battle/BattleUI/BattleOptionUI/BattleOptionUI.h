/*
				ファイル名		:BattleOptionUI.h
				作成者			:
				作成日時		:2019/09/25
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BATTLE_OPTION_UI_H__
#define __BATTLE_OPTION_UI_H__

#include "Common/System/OnListener.h"
#include ".././../BattleUtil/BtlCommon.h"

class Button;

namespace battle {
namespace ui {
	class BattleOptionUI : public OnListener{

	private:

		int mTouchCount[5]{};

		Button* mPauseButton;
		Button* mGameModeButton;

		ePlayMode mOldPlayMode;

	public:

		BattleOptionUI();
		~BattleOptionUI();

		void Draw();
		void Update();

		// ポーズ
			// リタイア
			// 戻る
		// バトルモード

		// カード情報
			// 所持スキル
			// ステータス
			// 状態

		void OnClick(View* view) override;

	};
}
}

#endif // __BATTLE_OPTION_UI_H__