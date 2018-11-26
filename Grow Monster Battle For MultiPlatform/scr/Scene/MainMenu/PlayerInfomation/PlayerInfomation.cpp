/*
				ファイル名		:PlayerInfomation.cpp
				作成者			:
				作成日時		:2018/10/30
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Common/String/StringClick.h"
#include "PlayerInfomation.h"


PlayerInfomation::PlayerInfomation() :TaskBase() {

}

//初期化
bool PlayerInfomation::Initialize() { 

	if (Fade::GetInstance()->IsFadeEnd() == false) return false;

	Graphics* add = ComRes::Instance()->GetGraphicHandle(ComRes::eComResName_CommonBG);
	add->SetPosition(0, 0);
	mOrderBackGraph = GraphicsDrawMgr::GetInstance()->Add(add, 1);



	mButtons = new GraphicsMulti();
	mButtons->Load("Resources/Graphics/UI/button/button-kaiihuku1.png", 500, 300);
	mButtons->Load("Resources/Graphics/UI/button/button-oubu1.png", 750, 300);
	mButtons->Load("Resources/Graphics/UI/button/button-growcrystal.png", 1000, 300);
	GraphicsDrawMgr::GetInstance()->Add(mButtons,1);



	//フェードイン
	Fade::GetInstance()->FadeIn(30);

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

	if (StringClick::IsInSide(StringClick::eClickType_Relese)) {
		mNowState = PlayerInfomation::eState_Exit;
	}


}

//更新処理
bool PlayerInfomation::Updata() {

	
	switch (mNowState) {
	case PlayerInfomation::eState_Select:

		break;
	case PlayerInfomation::eState_Exit:
		Fade::GetInstance()->FadeOut(30);
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

}

//後 更新処理
void PlayerInfomation::PostUpdate() {

}

//終了処理
void PlayerInfomation::Finalize() {

	GraphicsDrawMgr::GetInstance()->Remove(mOrderBackGraph);
	mButtons->ReleseRequest();

}


