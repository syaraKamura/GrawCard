/*
				ファイル名		:BattleCommandUI.h
				作成者			:
				作成日時		:2019/09/24
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BATTLE_COMMAND_UI_H__
#define __BATTLE_COMMAND_UI_H__

#include "Common/System/OnListener.h"

class Button;

namespace battle {
namespace ui {

	enum class eCommand : int {
		Attack,
		Skill,
		Max,
	};

	class BattleCommandUI {
	private:
		class CmdButtonUI;

		CmdButtonUI* mListener;

	public:
		BattleCommandUI();
		~BattleCommandUI();

		void Open(int posX,int posY);
		void Close();

		bool IsVisible();
		int GetValue();

		void Update();
		void Draw();

	};

	class BattleCommandUI::CmdButtonUI : public OnListener {
	private:
		
		bool mIsVisible;
		bool mIsClick;
		int mRetValue;
		Button* mCmdButton[(int)eCommand::Max];

	public:

		CmdButtonUI();
		~CmdButtonUI();

		void SetPosition(int posX,int posY);
		void SetVisible(bool isVisible);

		bool IsVisible();
		bool IsClick();
		int GetRetValue();

		void Update();
		void Draw();


		virtual void OnClick(View* view) override;

	};

}
}

#endif // __BATTLE_COMMAND_UI_H__