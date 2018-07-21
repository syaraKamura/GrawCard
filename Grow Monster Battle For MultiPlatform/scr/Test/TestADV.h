/*
				ファイル名		:TestADV.h
				作成者			:
				作成日時		:2018/06/14
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __TEST_ADV_H__
#define __TEST_ADV_H__

#ifdef __MY_DEBUG__

#include "Scene/SceneBase.h"

class TestADV : public SceneBase {

private:

	int mTaskId;	//タスクID

public :

	TestADV(ISceneBase* changer);
	
	bool Initialize() override;
	void Finalize() override;
	void PreviousUpdate()override;
	bool Updata()override;
	void Draw() override;
	void PostUpdate() override;


};

#endif //__MY_DEBUG__

#endif // __TEST_ADV_H__