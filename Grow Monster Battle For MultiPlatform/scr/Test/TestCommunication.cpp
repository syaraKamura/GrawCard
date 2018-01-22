/*
				ファイル名		:TestCommunication.cpp
				作成者			:
				作成日時		:2018/01/22
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"


#ifdef __MY_DEBUG__

#include "Scene/ISceneBase.h"
#include "TestCommunication.h"

TestCommunication::TestCommunication(ISceneBase* changer) :SceneBase(changer) {

}

void TestCommunication::Initialize() {

	//送信用ソケットの作成
	//127.0.0.1
	mSendUDP.MakeSocket(127, 0, 0, 1);

	//受信用のソケットの作成
	mReceiveUDP.MakeSocket();

}

void TestCommunication::Finalize() {

	//送信用ソケットの削除
	mSendUDP.DeleteSocket();

	//受信用ソケットの削除
	mReceiveUDP.DeleteSocket();

}

bool TestCommunication::Updata() {

#ifdef __MY_DEBUG__
#ifdef __WINDOWS__
	if (Keyboard_Press(KEY_INPUT_X)) {
		mNextScene->SceneChange(ISceneBase::eScene_TestMenu);
	}
#endif	//__WINDOWS__
#endif//__MY_DEBUG__

	return true;
}

void TestCommunication::Draw() {

}


#endif	//__MY_DEBUG__