#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

#include "Scene/SceneBase.h"

class Scene_Title : public SceneBase{

private:

	enum eState {
		eState_Initialize,
		eState_Fade,
		eState_Main,
		eState_Exit,
		eState_ExitDone,
		eState_None,
	};

	enum eFadeType {
		eFadeType_In,
		eFadeType_Out,
		eFadeType_None,
	};

	eState mState;
	eState mNextState;

private:

	void NexetState( eState nextState, eFadeType type = eFadeType_None,int fadeFrame = 60);
	bool UpdataProc();

public :

	Scene_Title(ISceneBase* changer);
	void Initialize() override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;

};

#endif