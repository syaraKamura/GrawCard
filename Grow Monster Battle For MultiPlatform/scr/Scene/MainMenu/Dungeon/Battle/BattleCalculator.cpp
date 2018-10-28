/*
				ファイル名		:BattleCalculator.cpp
				作成者			:
				作成日時		:2018/06/03
				ソース説明		:
				
					バトル計算クラス
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "BattleCalculator.h"

static const int VOUCH_DAMAGE_VALUE = 1;			//最低限保証するダメージ量
static const int VOUCH_MAX_RANDAM_DAMAGE_VALUE = 10;	//最低限保証するランダムダメージ量最大値

/*
		属性相性の倍率を返却する
		Monster::eType owner	:自分
		Monster::eType target	:対象
		return 0.0f以上の相性倍率を返却する
*/
float BattleCalculator::TypeCompatibilityRate(Monster::eType owner, Monster::eType target) {

	float rate = 1.0f;

	//属性設定がどちらかがなければ等倍で返却
	if (owner == Monster::eType_None || target == Monster::eType_None) return rate;	

	int ret = (owner + 1) % (Monster::eType_Water + 1);

	if (owner == target)	rate *= 1.0f;	//同じ属性
	else if (ret == target)	rate *= 2.0f;	//相手の属性に有利
	else {									

		if (owner == Monster::eType_Light && target == Monster::eType_dark) rate *= 2.0f;
		else if (owner == Monster::eType_dark && target == Monster::eType_Light) rate *= 2.0f;
		else rate *= 0.5f;					//相手の属性に不利

	}

	return rate;
}

/*
	ホームポジション相性倍率を返却する
	Monster::eType owner	:自分
	Monster::eType target	:対象
	return 0.0f以上の相性倍率を返却する
*/
float BattleCalculator::HomePositionCompatibilityRate(Monster::eHomePosition owner, Monster::eHomePosition target) {

	float rat = 1.0f;

	if (owner == Monster::eHomePosition_Front && target == Monster::eHomePosition_Front) rat = 1.0f;
	else if (owner == Monster::eHomePosition_Front && target == Monster::eHomePosition_Back) rat = 0.5f;
	else if (owner == Monster::eHomePosition_Back && target == Monster::eHomePosition_Front) rat = 0.75f;
	else if (owner == Monster::eHomePosition_Back && target == Monster::eHomePosition_Back) rat = 0.25f;
	else {
		Debug::ErorrMessage("不正なホームポジションが設定されています");
	}

	return rat;
}

/*
	ダメージ量ランダム加算
	Monster atkOwner	:攻撃側
	Monster atkTarget	:攻撃対象
	return ランダムダメージ量
*/
float BattleCalculator::AddRandomDamage(Monster atkOwner, Monster atkTarget) {

	int max = atkOwner.GetAttack() - atkTarget.GetDeffence();
	float damage = 0.0f;

	if (max <= 0) {
		max = VOUCH_MAX_RANDAM_DAMAGE_VALUE;
	}

	// -(max/2) ~ (max/2)になるようにする
	damage = (float)DxLib::GetRand(max) - (float)(max / 2.0f);

	return damage;
}

/*
	通常攻撃ダメージ計算
	Monster atkOwner	:攻撃側
	Monster atkTarget	:攻撃対象
	return	1以上のダメージを返却する
*/
int BattleCalculator::NormalDamage(Monster atkOwner, Monster atkTarget) {

	float damage = VOUCH_DAMAGE_VALUE;

	float ownerAtk = (float)atkOwner.GetAttack() * (float)atkOwner.GetLevel();
	float targetDef = (float)atkTarget.GetDeffence() * (float)atkTarget.GetLevel() * 0.5f;

	//タイプ相性分を乗算
	ownerAtk *= TypeCompatibilityRate(atkOwner.GetType(), atkTarget.GetType());

	//ホームポジション相性を乗算
	ownerAtk *= HomePositionCompatibilityRate(atkOwner.GetHomePosition(), atkTarget.GetHomePosition());

	damage = ownerAtk - targetDef;

	damage += AddRandomDamage(atkOwner, atkTarget);

	if (damage <= 0.0f) {
		damage = VOUCH_DAMAGE_VALUE;
	}

	return (int)damage;
}

/*
	スキル攻撃ダメージ計算
	Monster atkOwner	:攻撃側
	Monster atkTarget	:攻撃対象
	return	1以上のダメージを返却する
*/
int BattleCalculator::SkillDamage(Monster atkOwner, Monster atkTarget) {

	//とりあえずこれで計算
	float damage = (float)NormalDamage(atkOwner, atkTarget);

	if (damage <= 0.0f) {
		damage = VOUCH_DAMAGE_VALUE;
	}

	return (int)damage;
}