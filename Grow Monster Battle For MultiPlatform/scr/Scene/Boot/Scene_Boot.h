/*
				�t�@�C����		:Boot.h
				�쐬��			:
				�쐬����		:2017/12/07
				�\�[�X����		:�����N��

				
				
				���l
					
				
!*/

#ifndef __SCENE_BOOT_H__
#define __SCENE_BOOT_H__

#include "Scene/SceneBase.h"

class Scene_Boot :public SceneBase{

private:
	
public :

	Scene_Boot(ISceneBase* changer);

	bool Initialize() override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;

};

#endif	//__SCENE_BOOT_H__