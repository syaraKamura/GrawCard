/*
				ファイル名		:TestCommunication.h
				作成者			:
				作成日時		:2018/01/22
				ソース説明		:
				
					通信テスト
				
				備考
				
				
				
!*/

#ifdef __MY_DEBUG__

#ifndef __TEST_COMMUNICATION_H__
#define __TEST_COMMUNICATION_H__

#include "Scene/SceneBase.h"
#include "Common/Communication/SendUDP.h"
#include "Common/Communication/ReceiveUDP.h"

class TestCommunication : public SceneBase {

private:

	enum eStep {
		eStep_Select,
		eStep_Send,		//送信
		eStep_Receive,	//受信
		eStep_Chat,		//チャット開始
	};


	SendUDP mSendUDP;
	ReceiveUDP mReceiveUDP;

	int mSelect;

private:



public :

	TestCommunication(ISceneBase* changer);

	void Initialize() override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;


};

#endif // __TEST_COMMUNICATION_H__

#endif //__MY_DEBUG__