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
		const char* SeFilePath;
	};

	const LoadData LOAD_DATA[] = {
		{"Resources/Effect/Test/Test03.png", 240, 240,"Resources/Sound/SE/Test00.mp3"	},	// 炎爪
		{"Resources/Effect/Test/Test04.png", 240, 240,nullptr							},	// 牙
	};

	BattleEffect::BattleEffect() {
		
		mEffectHandle.clear();

		for (int i = 0; i < ArrySize(LOAD_DATA); i++) {
			LoadData data = LOAD_DATA[i];
			int handle = Effect::EffectMgr::GetInstance()->Load(data.filePath, data.width, data.height);
			mEffectHandle.push_back(handle);
			if (data.SeFilePath != nullptr) {
				Effect::EffectMgr::GetInstance()->LoadSE(data.SeFilePath, handle);
			}
		}

		

	}

	BattleEffect::~BattleEffect() {

		for (int i = 0; i < mEffectHandle.size(); i++) {
			Effect::EffectMgr::GetInstance()->Release(mEffectHandle[i]);
		}
		mEffectHandle.clear();

	}

	Effect::EffectPlayData* BattleEffect::Play(int idx, int posX, int posY, bool isPlayManual /*= false*/) {

		if (idx <= eBattleEffect_None || idx >= eBattleEffect_Max) {
			return nullptr;
		}

		int handle = mEffectHandle[idx];
		Effect::EffectPlayData* data = nullptr;
		if (isPlayManual == true) {
			data = Effect::EffectMgr::GetInstance()->PlayManual(handle,posX,posY);
		}
		else {
			data = Effect::EffectMgr::GetInstance()->Play(handle, posX, posY);
		}
		if (data != nullptr) {
			data->posX = posX;
			data->posY = posY;
		}
		return data;
	}
}//effect
}//battle

