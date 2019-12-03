/*
				ファイル名		:BattleEffect.h
				作成者			:
				作成日時		:2019/05/13
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BATTLE_EFFECT_H__
#define __BATTLE_EFFECT_H__

#include <vector>

#include "Common/Effect/Effect.h"

namespace battle {
namespace effect {
	class BattleEffect {

	private:

		std::vector<int> mEffectHandle;

	public:

		BattleEffect();
		~BattleEffect();

		Effect::EffectPlayData* Play(int idx, int posX, int posY,bool isPlayManual = false);


	};
}//effect
}//battle

#endif // __BATTLE_EFFECT_H__