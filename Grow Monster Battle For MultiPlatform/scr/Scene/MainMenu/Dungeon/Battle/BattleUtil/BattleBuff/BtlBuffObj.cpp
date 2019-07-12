/*
				ファイル名		:BtlBuffObj.cpp
				作成者			:
				作成日時		:2019/07/06
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "../../BattleMgr.h"
#include "BtlBuffObj.h"

namespace battle {

	/*
		バフの状態を更新
	*/
	void BuffObj::Update() {
		
		for (int i = 0; i < mBuff.size();i++) {
			auto& buff = mBuff[i];
			int throwTurn = BtlGetInfo().GetNowTurn() - buff.mEffectActiveTrun;
			if (throwTurn > buff.mEffectiveTurn ) {
				mBuff.erase(mBuff.begin() + i);
				i--;
			}
		}

	}

	/*
		全てのバフを削除する
	*/
	void BuffObj::Clear() {
		mBuff.clear();
	}

	/*
		バフを追加する
	*/
	void BuffObj::Add(StatusRate buff) {

		if (CheckExists(buff.mBuffType)) {
			return;
		}
		mBuff.push_back(buff);
	}


	/*
		指定タイプのバフを持っているか？
	*/
	bool BuffObj::CheckExists(eBuffType buffType) {
		for (auto buff : mBuff) {
			if (buff.mBuffType == buffType) {
				return true;
			}
		}
		return false;
	}
	bool BuffObj::CheckExists(eBuffType buffType) const {
		for (auto buff : mBuff) {
			if (buff.mBuffType == buffType) {
				return true;
			}
		}
		return false;
	}

	/*
		指定バフの効果値を取得する
	*/
	float BuffObj::GetValue(eBuffType buffType) {
		for (auto buff : mBuff) {
			if (buff.mBuffType == buffType) {
				return buff.mValue;
			}
		}
		return 0.0f;
	}
	float BuffObj::GetValue(eBuffType buffType) const {
		for (auto buff : mBuff) {
			if (buff.mBuffType == buffType) {
				return buff.mValue;
			}
		}
		return 0.0f;
	}

	StatusRate& BuffObj::GetBuff(eBuffType buffType) {
		for (auto buff : mBuff) {
			if (buff.mBuffType == buffType) {
				return buff;
			}
		}
		return *(StatusRate*)nullptr;
	}

	StatusRate& BuffObj::GetBuff(eBuffType buffType) const {
		for (auto buff : mBuff) {
			if (buff.mBuffType == buffType) {
				return buff;
			}
		}
		return *(StatusRate*)nullptr;
	}


}// battle


