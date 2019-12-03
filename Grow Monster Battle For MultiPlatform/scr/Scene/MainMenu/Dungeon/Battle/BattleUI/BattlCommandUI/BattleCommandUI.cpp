/*
				ファイル名		:BattleCommandUI.cpp
				作成者			:
				作成日時		:2019/09/24
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Common/Graphics/Button/Button.h"
#include "../../BattleMgr.h"
#include "BattleCommandUI.h"

namespace battle {
namespace ui {
	BattleCommandUI::BattleCommandUI() {
		this->mListener = new CmdButtonUI();
		Close();
	}

	BattleCommandUI::~BattleCommandUI() {
		Delete(mListener);
	}

	void BattleCommandUI::Open(int posX, int posY) {
		mListener->SetPosition(posX,posY);
		mListener->SetVisible(true);
	}

	void BattleCommandUI::Close() {
		mListener->SetVisible(false);
	}

	bool BattleCommandUI::IsVisible() {
		return mListener->IsVisible();
	}

	int BattleCommandUI::GetValue() {
		return mListener->GetRetValue();
	}

	void BattleCommandUI::Update() {
		
		if (BtlGetInfo().CheckPlayMode(ePlayMode_Pause)) {
			return;
		}

		mListener->Update();
		if (mListener->IsClick()) {
			Close();
		}
	}

	void BattleCommandUI::Draw() {
		mListener->Draw();
	}
	
	//====================================================
	// CmdButtonUI クラス
	//====================================================
	
	BattleCommandUI::CmdButtonUI::CmdButtonUI() {

		const char* pStr[(int)eCommand::Max] = { "攻撃","スキル" };

		for (int i = 0; i < (int)eCommand::Max; i++) {
			mCmdButton[i] = new Button(0,0,120,60, pStr[i]);
			mCmdButton[i]->SetOnListener(this);
		}
		mRetValue = -1;
	}

	BattleCommandUI::CmdButtonUI::~CmdButtonUI() {
		for (int i = 0; i < (int)eCommand::Max; i++) {
			Delete(mCmdButton[i]);
		}
	}

	void BattleCommandUI::CmdButtonUI::SetPosition(int posX, int posY) {
		for (int i = 0; i < (int)eCommand::Max; i++) {
			int w = mCmdButton[i]->GetWidth();
			int x = posX + ((i-1) * w) + (i * 20);
			mCmdButton[i]->SetPosition(x,posY);
		}
	}

	void BattleCommandUI::CmdButtonUI::SetVisible(bool isVisible) {
		for (int i = 0; i < (int)eCommand::Max; i++) {
			mCmdButton[i]->SetVisible(isVisible);
		}
		if (isVisible == true) {
			mIsClick = false;
		}
		mIsVisible = isVisible;
	}

	bool BattleCommandUI::CmdButtonUI::IsClick() {
		return mIsClick;
	}

	bool BattleCommandUI::CmdButtonUI::IsVisible() {
		return mIsVisible;
	}

	int BattleCommandUI::CmdButtonUI::GetRetValue() {
		return mRetValue;
	}

	void BattleCommandUI::CmdButtonUI::Update() {

		for (int i = 0; i < (int)eCommand::Max; i++) {
			mCmdButton[i]->Update();
		}

	}

	void BattleCommandUI::CmdButtonUI::Draw() {
		for (int i = 0; i < (int)eCommand::Max; i++) {
			mCmdButton[i]->Draw();
		}
	}

	void BattleCommandUI::CmdButtonUI::OnClick(View* view) {
		mRetValue = -1;
		for (int i = 0; i < (int)eCommand::Max; i++) {
			if (mCmdButton[i] == view) {
				mRetValue = i;
				mIsClick = true;
				break;
			}
		}
	}

}
}

