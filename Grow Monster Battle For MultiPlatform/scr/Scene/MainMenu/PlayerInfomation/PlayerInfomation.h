/*
				ファイル名		:PlayerInfomation.h
				作成者			:
				作成日時		:2018/10/30
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __PLAYER_INFOMATION_H__
#define __PLAYER_INFOMATION_H__

#include <vector>
#include "Common/Task/TaskBase.h"
#include "Common/Graphics/Button/Button.h"


class Button;
class Player;

class PlayerInfomation : public TaskBase {

public :

	class CMDButton : public OnListener {

	private :

		std::vector<Button*> mList;
		PlayerInfomation* mPlayerInfo;
	public :
		CMDButton():mPlayerInfo(nullptr){}
		CMDButton(PlayerInfomation* pThis):mPlayerInfo(pThis){}
		
		~CMDButton() {
			for (int i = 0; i < mList.size(); i++) {
				Delete(mList[i]);
			}
			mList.clear();
		}

		void Updata() {
			for (int i = 0; i < mList.size(); i++) {
				mList[i]->Update();
			}
		}
		void Draw() {
			for (int i = 0; i < mList.size(); i++) {
				mList[i]->Draw();
			}
		}

		void AddButton(const char* filePath, int posX, int posY, const char* text) {
			Button* add = new Button(filePath, posX, posY, text);
			add->SetOnListener(this);
			mList.push_back(add);
		}

		void OnClick(View* view) override {
			for (int i = 0; i < mList.size(); i++) {
				if (view == mList[i]) {
					mPlayerInfo->Exit();
				}
			}
		}

	};

public:

	enum eState {

		eState_None,
		eState_Select,
		eState_Exit,
		eState_ExitDone,

	};

private :

	int mOrderBackGraph;

	eState mNowState;

	GraphicsMulti* mButtons;
	Player* mPlayer;
	Graphics* mGraph;
	CMDButton* mCMD;

public :

	PlayerInfomation();

	//初期化
	bool Initialize() override;

	//前　更新処理
	void PreviousUpdate() override;

	//入力更新処理
	void InputUpdate() override;

	//更新処理
	bool Updata() override;

	//描画
	void Draw() override;

	//後 更新処理
	void PostUpdate() override;

	//終了処理
	void Finalize() override;

	void Exit() {
		mNowState = PlayerInfomation::eState_Exit;
	}

};



#endif // __PLAYER_INFOMATION_H__