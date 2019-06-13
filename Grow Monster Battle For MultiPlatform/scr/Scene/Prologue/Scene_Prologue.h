/*
				ファイル名		:Scene_Prologue.h
				作成者			:
				作成日時		:201/11/19
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __SCENE_PROLOGUE_H__
#define __SCENE_PROLOGUE_H__

#include "Common/Utility/Status.h"
#include "../SceneBase.h"


namespace AdvScript{
class ScriptBase;
}

class Scene_Prologue : public SceneBase{

private:

	enum eState {
		eState_Prologure,
		eState_SelectCard,
		eState_Exit,
	};

private:
	Utility::Status mState;
	AdvScript::ScriptBase* mPrologue;

private:

public:

	Scene_Prologue(ISceneBase* changer);
#ifdef __MY_DEBUG__
	Scene_Prologue(ISceneBase* changer, Debug* debug);
#endif	//__MY_DEBUG__
	bool Initialize() override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;


};


#endif // __SCENE_PROLOGUE_H__