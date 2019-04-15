/*
				ファイル名		:DungeonMenu.h
				作成者			:
				作成日時		:2018/03/12
				ソース説明		:
				 
					ダンジョンメニュー
				
				備考
				
				
				
!*/

#ifndef __DUNGEON_MENU_H__
#define __DUNGEON_MENU_H__

#include "Common/Task/TaskBase.h"
#include "Common/Graphics/Button/Button.h"

#include <vector>

class DungeonMenu : public TaskBase {

	class ReturnButton : public OnListener {

		Button* mBtn;
		DungeonMenu* mMenu;

	public:
		ReturnButton(DungeonMenu* pThis) {
			mBtn = new Button(1920 - 240, 50, 200, 100, "戻る");
			mBtn->SetOnListener(this);
			mMenu = pThis;
		}

		~ReturnButton() {
			Delete(mBtn);
		}

		void Update() { mBtn->Update(); }
		void Draw() {
			mBtn->Draw(); 
		}
		void SetVisible(bool isVisible) { mBtn->SetVisible(isVisible); }

		void OnClick(View* view) override {

			if (view == mBtn) {
				mMenu->RequestKill();
			}

		}
	};

	struct ButtonData {
		int state;
		Button* btn;

		void init(Button* btn, int state) {
			this->btn = btn;
			this->state = state;
		}

	};

	class ButtonList : public OnListener {

	private :

		std::vector<ButtonData*> mList;
		DungeonMenu* mMenu;

	public:

		ButtonList(DungeonMenu* pThis) {
			mMenu = pThis;
		}

		~ButtonList() {
			for (int i = 0; i < mList.size(); i++) {
				Delete(mList[i]->btn);
			}
			mList.clear();
		}

		void Add(ButtonData* data) {

			ButtonData* add = new ButtonData();
			add->btn = data->btn;
			add->state = data->state;
			add->btn->SetOnListener(this);
			mList.push_back(add);
		}

		void Update() {
			for (int i = 0; i < mList.size(); i++) {
				mList[i]->btn->Update();
			}
		}

		void Draw() {
			for (int i = 0; i < mList.size(); i++) {
				mList[i]->btn->Draw();
			}
		}

		void OnClick(View* view) override {

			for (int i = 0; i < mList.size(); i++) {
				const ButtonData* data = mList[i];
				if (data->btn == view) {
					mMenu->ChangeState((eState)data->state, eFade_Out);
				}
			}
		}

	};


private:

	enum eState {
		eState_None = -1,
		eState_SelectMode,
		eState_SelectStoryMap,
		eState_SelectQuestMap,
		eState_SelectDungeonMap,
		eState_Adventure,
		eState_Fade,
		eState_Exit,
		eState_ExitDone,
	};

	enum eMenu {
		eMenu_None = -1,
		eMenu_Story,		//ストーリー
		eMenu_Quest,		//クエスト
		eMenu_Dungeon,		//ダンジョン
		eMenu_Num,
	};

	enum eFade {
		eFade_None,
		eFade_In,
		eFade_Out,
	};

	char NAME_LIST[eMenu_Num][256] = {
		{"ストーリー"},
		{"クエスト"},
		{"ダンジョン"},
	};
	
#if 0
	typedef struct {
		int mID;
		int mQuestType;
		int mQuestNo;
	};

	typedef struct {
		int mMosterTblNo;
		int mBeforeAdvNo;
		int mAfterAdvNo;
	};
#endif 

private:
	
	int mSelect;
	int mBackImageOrder;
	
	int mStroySelectNum;
	
	eState mState;
	eState mNextState;
	eState mOldState;

	int mTaskId;
	TaskBase* mTask;

	ReturnButton* mRetBtn;
	ButtonList* mSelectButton;

	/*
		ステート切り替え
	*/
	void ChangeState(eState next,eFade fade,int fadeTime = 30);

	

public :

	DungeonMenu();
	~DungeonMenu();

	bool Initialize()override;
	void Finalize()override;

	void PreviousUpdate()override;
	bool Updata()override;
	void Draw()override;
	void PostUpdate() override;
	
	void OnClick(View* view) override;

};

#endif // __DUNGEON_MENU_H__