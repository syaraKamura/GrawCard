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
class Touch;
class ButtonGraph;
class Button;

class AITest :public SceneBase{

private:

	Joypad* mJoyPad;
	Touch* mTouch;

	ButtonGraph* mButton;
	Button* mPrevButton;

public:

	AITest(ISceneBase* changer);

	bool Initialize() override;
	void Finalize() override;
	void PreviousUpdate() override;
	bool Updata() override;
	void Draw() override;

	void OnClick(View* view) override;


};

#endif	//__AI_TEST_H__