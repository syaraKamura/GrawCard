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

	}

	BattleUIMgr::~BattleUIMgr() {

	}

	void BattleUIMgr::Update() {

	}

	void BattleUIMgr::Draw() {
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

	}


};	// ui
};	// battle

