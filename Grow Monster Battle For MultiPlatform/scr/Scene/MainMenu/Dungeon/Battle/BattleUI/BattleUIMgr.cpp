/*
				ファイル名		:BattleUIMgr.cpp
				作成者			:
				作成日時		:2019/09/18
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "../BattleMgr.h"
#include "BattleUIMgr.h"

namespace battle {
namespace ui {

	BattleUIMgr::BattleUIMgr() :GraphicsBase(){
		mBack = new Graphics();
		mBack->Load("Resources/Graphics/BG/sindennai.png");
	}

	BattleUIMgr::~BattleUIMgr() {
		Delete(mBack);
	}

	void BattleUIMgr::Update() {

		GetCmdUI().Update();
		GetOptionUI().Update();

	}

	void BattleUIMgr::Draw() {

		mBack->Draw();

		TextObj_DrawFormatText(20, 20, COLOR::Cyan(), eFontSize::M, "ターン:%d", BtlGetInfo().GetNowTurn());

		for (auto& monster : BtlGetInfo().GetMonsterList()) {
			if (monster->IsDead()) {
				monster->GetGraphics().SetAlpha(100);
			}

			monster->GetGraphics().Draw();
			int x = monster->GetGraphics().GetPositionX();
			int y = monster->GetGraphics().GetPositionY();

			StringBase str;
			char buf[1024];
			sprintfDx(buf, "HP:%d", monster->GetHp());
			str.SetString(buf);
			str.Update();
			str.DrawString(x, y);

		}

		GetCmdUI().Draw();
		GetOptionUI().Draw();
	}

	BattleCommandUI& BattleUIMgr::GetCmdUI() {
		return mCmdUI;
	}

	BattleOptionUI& BattleUIMgr::GetOptionUI() {
		return mOptionUI;
	}

};	// ui
};	// battle

