/*
				ファイル名		:BattleUIMgr.h
				作成者			:
				作成日時		:2019/09/18
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BATTLE_UI_MGR_H__
#define __BATTLE_UI_MGR_H__

#include "Common/Graphics/GraphicsBase.h"
#include "BattlCommandUI/BattleCommandUI.h"
#include "BattleOptionUI/BattleOptionUI.h"

namespace battle {
namespace ui {
	class BattleUIMgr : public GraphicsBase{

	private:

		// ここにUIクラス変数を宣言する

		BattleCommandUI mCmdUI;
		BattleOptionUI mOptionUI;

	public:

		BattleUIMgr();
		~BattleUIMgr();

		void Update();
		void Draw() override;
		void Draw(int posX, int posY, int alpha, double angle, double scale) {};
		void Relese() {};
		bool Load(const char* path) override { return true; };

		bool IsTouch() override { return false; }
		int TouchNumber() override { return 0; }

		BattleCommandUI& GetCmdUI();
		BattleOptionUI& GetOptionUI();

		Graphics* mBack;

	};

};	// ui
};	// battle

#endif // __BATTLE_UI_MGR_H__