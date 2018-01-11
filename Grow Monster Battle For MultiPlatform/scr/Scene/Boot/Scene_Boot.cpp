/*
				�t�@�C����		:Boot.h
				�쐬��			:
				�쐬����		:2017/12/07
				�\�[�X����		:�����N��

				
				
				���l
					
				
!*/

#include"Common/GameCommon.h"
#include "Scene/ISceneBase.h"
#include "Scene_Boot.h"



Scene_Boot::Scene_Boot(ISceneBase* changer):SceneBase(changer){

}

void Scene_Boot::Initialize(){
	TaskMgr::getInstance().Add(Fade::GetInstance(),TaskMgr::ePriorty_Fade);
	TaskMgr::getInstance().Add(GraphicsDrawMgr::GetInstance(), TaskMgr::ePriorty_Graphics);
}

void Scene_Boot::Finalize(){

}

bool Scene_Boot::Updata(){

#ifdef __MY_DEBUG__ 
#ifdef __WINDOWS__
	//�e�X�g���j���[��
	mNextScene->SceneChange(ISceneBase::eScene_TestMenu);
#else
	//�I�[�v�j���O�V�[���ֈڍs
	mNextScene->SceneChange(ISceneBase::eScene_Opning);
#endif	//__WINDOWS__
#else
	//�I�[�v�j���O�V�[���ֈڍs
	mNextScene->SceneChange(ISceneBase::eScene_Opning);
#endif
	return true;
}

void Scene_Boot::Draw(){

}
