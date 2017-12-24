/*
				ファイル名		:SceneBase.h
				作成者			:
				作成日時		:2017/12/07
				ソース説明		:シーン基底クラス

				
				
				備考
					
				
				
!*/
#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include "Common/Task/Task.h"

class ISceneBase;

class SceneBase : public Task{

protected:
	ISceneBase* mNextScene;
public :

	SceneBase(ISceneBase* nextScene){mNextScene = nextScene;};
	virtual ~SceneBase(){};

	virtual void Initialize() override{}
	virtual void Finalize() override{}
	virtual bool Updata() override{return true;}
	virtual void Draw() override{}


protected:
#ifdef __MY_DEBUG__
	/*
		テストメニューへ戻る
	*/
	void dbg_ChangeScene_TestMenu() {
		mNextScene->SceneChange(ISceneBase::eScene_TestMenu);
	}

#endif
	

};

#endif	//__SCENE_BASE_H__