/*
				ファイル名		:BattleEffect.cpp
				作成者			:
				作成日時		:2019/05/13
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "BattleEffect.inc"
#include "BattleEffect.h"


namespace battle {
namespace effect {

	struct LoadData {
		const char* filePath;
		int width;
		int height;
	};

	const LoadData LOAD_DATA[] = {
		{"Resources/Effect/Test/Test03.png", 240, 240},	// 炎爪
		{"Resources/Effect/Test/Test04.png", 240, 240},	// 牙
	};

	BattleEffect::BattleEffect() {
		
		mEffectHandle.clear();

		for (int i = 0; i < ArrySize(LOAD_DATA); i++) {
			LoadData data = LOAD_DATA[i];
			mEffectHandle.push_back(Effect::EffectMgr::GetInstance()->Load(data.filePath, data.width, data.height));
		}

		Effect::EffectMgr::GetInstance()->LoadSE("Resources/Sound/SE/Test00.mp3", mEffectHandle[0]);

	}

	BattleEffect::~BattleEffect() {

		for (int i = 0; i < mEffectHandle.size(); i++) {
			Effect::EffectMgr::GetInstance()->Release(mEffectHandle[i]);
		}
		mEffectHandle.clear();

	}

	Effect::EffectPlayData* BattleEffect::Play(int idx, int posX, int posY) {

		if (idx <= eBattleEffect_None || idx >= eBattleEffect_Max) {
			return nullptr;
		}

		int handle = mEffectHandle[idx];
		Effect::EffectPlayData* data = Effect::EffectMgr::GetInstance()->Play(handle);
		if (data != nullptr) {
			data->posX = posX;
			data->posY = posY;
		}
		return data;
	}
}//effect
}//battle

