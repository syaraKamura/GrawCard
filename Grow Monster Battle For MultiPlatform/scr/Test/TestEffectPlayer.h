/*
				ファイル名		:TestEffectPlayer.h
				作成者			:
				作成日時		:2019/05/08
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __TEST_EFFECT_PLAYER_H__
#define __TEST_EFFECT_PLAYER_H__

#ifdef __MY_DEBUG__

#include "Scene/SceneBase.h"
#include <vector>

namespace Effect {
namespace Particle {
	class ParticleEmmiter;
}
}

class TestEffectPlayer : public SceneBase {

private:

	std::vector<int> mHandle;
	int mSelectY;
	Effect::Particle::ParticleEmmiter* mEmitter;

	int mPosX;
	int mMoveX;

public :

	TestEffectPlayer(ISceneBase* changer);
	~TestEffectPlayer();

	virtual bool Initialize() override;
	virtual void Finalize() override;
	void PreviousUpdate()override;
	bool Updata()override;
	void Draw() override;
	void PostUpdate() override;
	
};

#endif// __MY_DEBUG__

#endif // __TEST_EFFECT_PLAYER_H__