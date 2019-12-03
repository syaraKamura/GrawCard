/*
				ファイル名		:PlayerInfomation.cpp
				作成者			:
				作成日時		:2018/10/30
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Common/String/StringClick.h"
#include "Common/ResourceTable/GraphTable.h"

#include "AppData/Character/Player/Player.h"

#include "PlayerInfomation.h"


#define PLAYER_STATUS_BAR_POS_X 100
#define PLAYER_STATUS_BAR_POS_Y 60
#define BASE_BUTTON_POS_X 1000
#define BASE_BUTTON_POS_Y 900

PlayerInfomation::PlayerInfomation() :TaskBase() {

}

//初期化
bool PlayerInfomation::Initialize() { 

	if (Fade::GetInstance()->IsFadeEnd() == false) return false;

	Graphics* add = new Graphics();
	add->Initialize(graphicsTable::GetGraphTag(graphicsTable::eGraphTag_CommonBG));

	add->SetPosition(0, 0);
	mOrderBackGraph = GraphicsDrawMgr::GetInstance()->Add(add, 1);

	mCMD = new CMDButton(this);

	mCMD->AddButton("Resources/Graphics/UI/button/button-kaiihuku1.png", BASE_BUTTON_POS_X, BASE_BUTTON_POS_Y, "");
	mCMD->AddButton("Resources/Graphics/UI/button/button-oubu1.png", BASE_BUTTON_POS_X + 250, BASE_BUTTON_POS_Y, "");
	mCMD->AddButton("Resources/Graphics/UI/button/button-growcrystal.png", BASE_BUTTON_POS_X + 500, BASE_BUTTON_POS_Y, "");

	//mButtons = new GraphicsMulti();
	//mButtons->Load("Resources/Graphics/UI/button/button-kaiihuku1.png", BASE_BUTTON_POS_X, BASE_BUTTON_POS_Y);
	//mButtons->Load("Resources/Graphics/UI/button/button-oubu1.png", BASE_BUTTON_POS_X + 250, BASE_BUTTON_POS_Y);
	//mButtons->Load("Resources/Graphics/UI/button/button-growcrystal.png", BASE_BUTTON_POS_X + 450, BASE_BUTTON_POS_Y);
	//GraphicsDrawMgr::GetInstance()->Add(mButtons,1);


	mGraph = new Graphics();
	mGraph->Initialize(graphicsTable::GetGraphTag(graphicsTable::eGraphTag_PlayerStatusBar));
	mGraph->SetPosition(PLAYER_STATUS_BAR_POS_X, PLAYER_STATUS_BAR_POS_Y);


	mPlayer = AppData::GetInstance()->GetSaveData()->GetPlayer();
	
	//フェードイン
	Fade::GetInstance()->FadeIn(0.5f);

	mNowState = PlayerInfomation::eState_Select;

	StringClick::SetString("メインメニューへ");

	return true; 
};

//前　更新処理
void PlayerInfomation::PreviousUpdate() {

}

//入力更新処理
void PlayerInfomation::InputUpdate() {

#ifdef __WINDOWS__
	if (Keyboard_Press(KEY_INPUT_X)) {
		mNowState = PlayerInfomation::eState_Exit;
	}
#endif // __WINDOWS__
#if  0
	if (StringClick::IsInSide(StringClick::eClickType_Relese)) {
		mNowState = PlayerInfomation::eState_Exit;
	}
#endif

}

//更新処理
bool PlayerInfomation::Updata() {

	if (Fade::GetInstance()->IsFadeEnd() == false) { 
		return true; 
	}
	
	switch (mNowState) {
	case PlayerInfomation::eState_Select:

		mCMD->Updata();

		break;
	case PlayerInfomation::eState_Exit:
		Fade::GetInstance()->FadeOut(0.5f);
		mNowState = PlayerInfomation::eState_ExitDone;
		break;
	case PlayerInfomation::eState_ExitDone:
		if (Fade::GetInstance()->IsFadeEnd()) {
			TaskMgr::getInstance().RequestKill(this->GetTaskId());
		}
		break;
	}
	
	

	return true;
}

//描画
void PlayerInfomation::Draw() {

	DrawString(0, 10, "プレイヤー情報画面", GetColor(255, 255, 255));

	StringClick::Draw(0, 40);

	mGraph->Draw();
	
	DrawFormatString(PLAYER_STATUS_BAR_POS_X + 100, PLAYER_STATUS_BAR_POS_Y + 60, GetColor(0, 0, 0), "%s", mPlayer->GetName());								//名前
	DrawFormatString(PLAYER_STATUS_BAR_POS_X + 280, PLAYER_STATUS_BAR_POS_Y + 60, GetColor(0, 0, 0), "%d", mPlayer->GetLevel());							//レベル
	DrawFormatString(PLAYER_STATUS_BAR_POS_X + 390, PLAYER_STATUS_BAR_POS_Y + 60, GetColor(0, 0, 0), "%d", mPlayer->GetCost());								//コスト
	DrawFormatString(PLAYER_STATUS_BAR_POS_X + 300, PLAYER_STATUS_BAR_POS_Y + 100, GetColor(0, 0, 0), "%d/%d", mPlayer->GetExp(), mPlayer->GetNextExp());	//経験値

	mCMD->Draw();

}

//後 更新処理
void PlayerInfomation::PostUpdate() {

}

//終了処理
void PlayerInfomation::Finalize() {

	GraphicsDrawMgr::GetInstance()->Remove(mOrderBackGraph);
	//mButtons->ReleseRequest();
	Delete(mCMD);
}


