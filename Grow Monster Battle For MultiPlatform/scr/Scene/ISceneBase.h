/*
				�t�@�C����		:ISceneBase.h
				�쐬��			:
				�쐬����		:2017/12/07
				�\�[�X����		:�V�[�����N���X�C���^�[�t�F�[�X

				
				
				���l
					
				
				
!*/

#ifndef __ISCENE_BASE_H__
#define __ISCENE_BASE_H__

#include "Common/Task/Task.h"

class ISceneBase{

private:

public :

	enum eScene {

		eScene_None = -1,
		eScene_Boot,				//�N��
		eScene_Opning,				//�I�[�v�j���O
		eScene_Title,				//�^�C�g��
		eScene_MainMenu,			//���C�����j���[

#ifdef __MY_DEBUG__
		eScene_TestMenu,			//�e�X�g���j���[
		eScene_AITest,				//AI�e�X�g
		eScene_TestComunication,	//�ʐM�e�X�g
		eScene_TestBattle,			//�o�g���e�X�g
		eScene_TestADV,				//�A�h�x���`���[�e�X�g
#endif

		eScene_Num,
	};

public :


	virtual ~ISceneBase() = 0;
	virtual void SceneChange(eScene nextScene) = 0;
};

#endif	//__ISCENE_BASE_H__