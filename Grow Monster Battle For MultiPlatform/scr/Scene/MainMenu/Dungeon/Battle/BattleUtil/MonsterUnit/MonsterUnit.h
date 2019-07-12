/*
				ファイル名		:MonsterUnit.h
				作成者			:
				作成日時		:2019/07/06
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __MONSTER_UNIT_H__
#define __MONSTER_UNIT_H__

#include "../BattleBuff/BtlBuffObj.h"
#include "AppData/Character/Monster/Monster.h"

class Graphics;

namespace battle {


	class MonsterUnit {

	private:

		eSide mSide;
		Monster* mMonster;
		BuffObj mBuff;
		Graphics* mImg;

	public:

		MonsterUnit(Monster* mon,eSide side);
		~MonsterUnit();

		Monster* GetMonster() { return mMonster; };
		BuffObj& GetBuff() { return mBuff; }
		const BuffObj& GetBuff() const { return mBuff; }

		int GetId() const;
		eElementType GetType()const;
		const char* GetTypeString() const;
		Monster::eHomePosition GetHomePosition()const;

		int GetHp()const;
		int GetHpMax()const;
		int GetMp()const;
		int GetMpMax()const;

		int GetAttack()const;
		int GetDeffence()const;
		int GetSpeed()const;

		int GetSkillNumber()const;

		/*
			倒されているか？
		*/
		bool IsDead() const ;

		/*
			モンスターを所持していサイド
		*/
		eSide GetSide() {
			return mSide;
		}

		Graphics& GetGraphics() {
			return *mImg;
		}


	};

}


#endif // __MONSTER_UNIT_H__