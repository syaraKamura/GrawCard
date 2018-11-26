/*
				ファイル名		:Monster.h
				作成者			:
				作成日時		:2017/12/31
				ソース説明		:モンスタークラス
				
				
				備考
				
				
				
!*/

#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "../CharacterBase.h"

static const int SKILL_HAVE_NUM = 1;	//スキル所持数


class Monster : public CharacterBase {

private:

	
public :

	enum eHomePosition {
		eHomePosition_None = -1,//設定なし
		eHomePosition_Front,	//前衛
		eHomePosition_Back,		//後衛
	};


	enum eType {
		eType_None = -1,
		eType_Fire,
		eType_Grass,
		eType_Water,
		eType_Light,
		eType_dark,
	};

private:

	eType mType;
	eHomePosition mHhomePosition;
	
	int mId;		//管理番号
	int mHp;
	int mHpMax;
	int mMp;
	int mMpMax;

	int mAttack;
	int mDeffence;
	int mSpeed;

	int SkillIndex[SKILL_HAVE_NUM];

public :

	Monster();
	~Monster();

	void SetId(int id);
	void SetType(eType type);
	void SetHomePosition(eHomePosition homePosition);
	void SetHp(int hp);
	void SetHpMax(int hpMax);
	void SetMp(int mp);
	void SetMpMax(int mpMax);

	void SetAttack(int attack);
	void SetDeffence(int deffence); 
	void SetSpeed(int speed);

	
	int GetId() const;
	eType GetType()const;
	eHomePosition GetHomePosition()const;

	int GetHp()const;
	int GetHpMax()const;
	int GetMp()const;
	int GetMpMax()const;

	int GetAttack()const;
	int GetDeffence()const;
	int GetSpeed()const;

};

#endif // __MONSTER_H__