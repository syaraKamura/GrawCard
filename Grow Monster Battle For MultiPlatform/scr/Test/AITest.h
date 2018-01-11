/*
				�t�@�C����		:AITest.h
				�쐬��			:
				�쐬����		:2017/12/13
				�\�[�X����		:AI�e�X�g�N���X

				
				
				���l
					
				
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