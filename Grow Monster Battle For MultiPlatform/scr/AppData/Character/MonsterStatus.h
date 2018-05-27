/*
				ファイル名		:MonsterStatus.h
				作成者			:
				作成日時		:2018/03/20
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __MONSTER_STATUS_H__
#define __MONSTER_STATUS_H__

class MonsterStatus {

private:

	char mName[256];
	int mLv;
	int mExp;
	int mNextExp;
	int mHp;
	int mAttack;
	int mDeffence;
	int mSpeed;
	int mSkill;

public :

	MonsterStatus();
	~MonsterStatus();
	


};

#endif // __MONSTER_STATUS_H__