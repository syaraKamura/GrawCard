/*
				ファイル名		:AITest.h
				作成者			:
				作成日時		:2017/12/13
				ソース説明		:AIテストクラス

				
				
				備考
					
				
!*/

#ifndef __AI_TEST_H__
#define __AI_TEST_H__

#include "Scene/SceneBase.h"

class Joypad;

class AITest :public SceneBase{

private:

	Joypad* mJoyPad;

public:

	AITest(ISceneBase* changer);

	void Initialize() override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;


};

#endif	//__AI_TEST_H__