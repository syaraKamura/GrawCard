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

	enum eImg {
		eImg_Back,		//îwåi
		eImg_NewGame,	//èâÇﬂÇ©ÇÁ
		eImg_Continue,	//ë±Ç´Ç©ÇÁ
		eImg_Rogo,		//É^ÉCÉgÉãÉçÉS
		eImg_Num,
	};

private :

	eState mState;
	eState mNextState;

	Graphics* mGraphic[eImg_Num];

private:

	void NexetState( eState nextState, eFadeType type = eFadeType_None,float fadeFrame = 1.0f);
	bool UpdataProc();

public :

	Scene_Title(ISceneBase* changer);
	bool Initialize() override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;

};

#endif