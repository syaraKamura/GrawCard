﻿/*
				ファイル名		:MonsterUnit.cpp
				作成者			:
				作成日時		:2019/0706
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "MonsterUnit.h"

namespace battle {

	MonsterUnit::MonsterUnit(Monster* mon, eSide side) :
		mMonster( mon ), 
		mSide( side ),
		mImg( nullptr )
	{
		if (mon != nullptr) {
			mImg = new Graphics(MonsterMgr::Instance()->GetGraphics(mon->GetId()));
		}
	}
	
	MonsterUnit::~MonsterUnit() {
		Delete(mImg);
	}


	int MonsterUnit::GetId() const {
		return mMonster->GetId();
	}

	eElementType MonsterUnit::GetType()const {
		return mMonster->GetType();
	}

	const char* MonsterUnit::GetTypeString() const {
		return mMonster->GetTypeString();
	}

	Monster::eHomePosition MonsterUnit::GetHomePosition()const {
		return mMonster->GetHomePosition();
	}

	int MonsterUnit::GetHp()const {
		return mMonster->GetHp();
	}

	int MonsterUnit::GetHpMax()const {
		return mMonster->GetHpMax();
	}

	int MonsterUnit::GetMp()const {
		return mMonster->GetMp();
	}

	int MonsterUnit::GetMpMax() const {
		return mMonster->GetMpMax();
	}

	int MonsterUnit::GetAttack()const {

		if (GetBuff().CheckExists(eBuffType_AddPower)) {
			float value = GetBuff().GetValue(eBuffType_AddPower);
			return mMonster->GetAttack() * value;
		}

		return mMonster->GetAttack();
	}

	int MonsterUnit::GetDeffence()const {
		return mMonster->GetDeffence();
	}

	int MonsterUnit::GetSpeed()const {
		return mMonster->GetSpeed();
	}

	int MonsterUnit::GetSkillNumber()const {
		return mMonster->GetSkillNumber();
	}

	bool MonsterUnit::IsDead() const {
		return this->GetHp() <= 0;
	}

}


