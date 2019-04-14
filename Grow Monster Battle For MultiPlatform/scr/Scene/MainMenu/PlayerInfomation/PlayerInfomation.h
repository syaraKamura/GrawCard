/*
				ファイル名		:PlayerInfomation.h
				作成者			:
				作成日時		:2018/10/30
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __PLAYER_INFOMATION_H__
#define __PLAYER_INFOMATION_H__

#include "Common/Task/TaskBase.h"

class Player;

class PlayerInfomation : public TaskBase {

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


};



#endif // __PLAYER_INFOMATION_H__