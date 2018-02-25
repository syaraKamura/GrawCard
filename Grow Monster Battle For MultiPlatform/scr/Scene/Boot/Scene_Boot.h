/*
				ファイル名		:Boot.h
				作成者			:
				作成日時		:2017/12/07
				ソース説明		:初期起動

				
				
				備考
					
				
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