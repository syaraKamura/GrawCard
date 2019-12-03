/*
				ファイル名		:
				作成者			:
				作成日時		:
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "Common/Graphics/Button/Button.h"
#include "../../BattleMgr.h"
#include "BattleOptionUI.h"


namespace battle {
namespace ui {

	BattleOptionUI::BattleOptionUI() {

		mPauseButton = new Button(1800,20,100,100,"ポーズ");
		mGameModeButton = new Button(1800, 900,100,60,"ゲームモード");

		mPauseButton->SetOnListener(this);
		mGameModeButton->SetOnListener(this);

		mOldPlayMode = BtlGetInfo().GetPlayMode();

	}

	BattleOptionUI::~BattleOptionUI() {

		Delete(mPauseButton);
		Delete(mGameModeButton);

	}

	void BattleOptionUI::Draw() {

		//ポーズ
		mPauseButton->Draw();

		// バトルモード
		mGameModeButton->Draw();

		if( BtlGetInfo().GetPlayMode() == ePlayMode_Input)
		{
			// モンスター情報
			for (int i = 0; i < BtlGetInfo().GetPlayerMonsterList().size(); i++) {
				auto& mon = BtlGetInfo().GetPlayerMonsterList()[i];
				if (mTouchCount[i] > 20) {
					int x = mon->GetGraphics().GetPositionX();
					int y = mon->GetGraphics().GetPositionY();
					TextObj_DrawText(x, y, COLOR::Magenta(), "カード情報");
				}
			}
		}

	}

	void BattleOptionUI::Update() {

		//ポーズ
		mPauseButton->Update();

		if (BtlGetInfo().CheckPlayMode(ePlayMode_Pause)) {
			return ;
		}
		// バトルモード
		mGameModeButton->Update();
		
		if (BtlGetInfo().GetPlayMode() == ePlayMode_Input)
		{
			// モンスター情報
			for (int i = 0; i < BtlGetInfo().GetPlayerMonsterList().size(); i++) {
				auto& mon = BtlGetInfo().GetPlayerMonsterList()[i];
				if (mon->GetGraphics().IsTouch()) {
					mTouchCount[i] = 0;
				}
				else if (mon->GetGraphics().IsTouchPush()) {
					mTouchCount[i]++;
				}
			}
		}
	}


	void BattleOptionUI::OnClick(View* view) {
		if (view == mPauseButton) {
			if (BtlGetInfo().GetPlayMode() == ePlayMode_Pause) {
				BtlGetInfo().SetPlayMode(mOldPlayMode);
			}
			else {
				mOldPlayMode = BtlGetInfo().GetPlayMode();
				BtlGetInfo().SetPlayMode(ePlayMode_Pause);
			}
		}
		else if (view == mGameModeButton) {
			BtlGetInfo().ChangePlayMode();
		}
	}

}	
}