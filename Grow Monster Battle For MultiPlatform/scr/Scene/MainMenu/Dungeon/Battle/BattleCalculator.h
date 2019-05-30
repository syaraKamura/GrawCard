/*
				ファイル名		:BattleCalculator.h
				作成者			:
				作成日時		:2018/06/03
				ソース説明		:
					
					バトル計算クラス
					
				備考
				
				
				
!*/

#ifndef __BATTLE_CALCULATOR_H__
#define __BATTLE_CALCULATOR_H__

#include "AppData/Character/Monster/Monster.h"
#include "AppData/Character/Skill/SkillMgr.h"

namespace battle {

	class BattleCalculator {

	private:

		/*
			属性相性の倍率を返却する
			Monster::eType owner	:自分
			Monster::eType target	:対象
			return 0.0f以上の相性倍率を返却する
		*/
		static float TypeCompatibilityRate(eElementType owner, eElementType target);

		/*
			ホームポジション相性倍率を返却する
			Monster::eType owner	:自分
			Monster::eType target	:対象
			return 0.0f以上の相性倍率を返却する
		*/
		static float HomePositionCompatibilityRate(Monster::eHomePosition owner, Monster::eHomePosition target);

		/*
			ダメージ量ランダム加算
			Monster atkOwner	:攻撃側
			Monster atkTarget	:攻撃対象
			return ランダムダメージ量
		*/
		static float AddRandomDamage(Monster atkOwner, Monster atkTarget);

	public:

		/*
			通常攻撃ダメージ計算
			Monster atkOwner	:攻撃側
			Monster atkTarget	:攻撃対象
			return	1以上のダメージを返却する
		*/
		static int NormalDamage(Monster atkOwner, Monster atkTarget);

		/*
			スキル攻撃ダメージ計算
			Monster atkOwner	:攻撃側
			Monster atkTarget	:攻撃対象
			SkillData skill		:スキル情報
			return	1以上のダメージを返却する
		*/
		static int SkillDamage(Monster atkOwner, Monster atkTarget,SkillData skill);

	};
}//battle
#endif // __BATTLE_CALCULATOR_H__