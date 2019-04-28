/*
				�t�@�C����		:SceneMgr.h
				�쐬��			:
				�쐬����		:2017/12/07
				�\�[�X����		:�V�[���Ǘ��N���X

				
				
				���l
					
				
				
!*/

#ifndef __SCENE_MGR_H__
#define __SCENE_MGR_H__

#include "ISceneBase.h"

class Debug;

class SceneBase;

class SceneMgr : public ISceneBase,Task{

private:

	bool mIsLoadEnd;	//�ǂݍ��ݏI���t���O
	SceneBase* mScene;
	
	ISceneBase::eScene mPrevScene;	//�O��̃V�[��
	ISceneBase::eScene mNowScene;	//���̃V�[��
	ISceneBase::eScene mNextScene;	//���̃V�[��

	int mLoadingPosX;

private:

	//�V�[���؂�ւ��v���Z�X
	bool SceneChangeProc();
	void SceneChangeDraw();

	SceneBase* CreateNextScene(ISceneBase::eScene next);


public :

	SceneMgr();
	
#ifdef __MY_DEBUG__

	Debug* mDebug;
	SceneMgr(Debug* debug);

#endif

	bool Initialize() override;
	void Finalize() override;
	void PreviousUpdate()override;
	bool Updata()override;
	void Draw() override;
	void PostUpdate() override;

	void SceneChange(eScene nextScene) override;
	
	//�O��̃V�[���ɕύX����
	void SceneChangePreve();



	// -------------------------------------
	// �f�o�b�O�@�\.

#ifdef __MY_DEBUG__
private:
	char m_DbgNowSceneName[126];		//���݂̃V�[����

private:

	//�V�[���̖��O�̕\��
	void dbg_SceneNameDraw();
	void dbg_SetSceneName(const char* name);

#endif//__MY_DEBUG__


};

#endif	//__SCENE_MGR_H__