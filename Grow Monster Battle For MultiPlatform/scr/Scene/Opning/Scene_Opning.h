
#ifndef __SCENE_OPNING_H__
#define __SCENE_OPNING_H__

#include "Scene/SceneBase.h"
class Scene_Opning : SceneBase{

public :
	Scene_Opning(ISceneBase* changer);

	bool Initialize() override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;

};

#endif //__SCENE_OPNING_H__