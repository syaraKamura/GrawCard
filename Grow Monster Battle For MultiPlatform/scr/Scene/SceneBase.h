/*
				�t�@�C����		:SceneBase.h
				�쐬��			:
				�쐬����		:2017/12/07
				�\�[�X����		:�V�[�����N���X

				
				
				���l
					
				
				
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
		�e�X�g���j���[�֖߂�
	*/
	void dbg_ChangeScene_TestMenu() {
		mNextScene->SceneChange(ISceneBase::eScene_TestMenu);
	}

#endif
	

};

#endif	//__SCENE_BASE_H__