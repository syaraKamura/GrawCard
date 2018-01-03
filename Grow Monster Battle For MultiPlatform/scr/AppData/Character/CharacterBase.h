/*
				ファイル名		:CharacterBase.h
				作成者			:
				作成日時		:2017/12/31
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __CHARACTER_BASE_H__
#define __CHARACTER_BASE_H__

class CharacterBase {

protected:

	int mLevel;

	char mName[256];

	int mHp;
	int mHpMax;
	int mMp;
	int mMpMax;

	int mAttack;
	int mDeffence;
	int mSpeed;

public :

	virtual ~CharacterBase();
	CharacterBase();

	void SetLevel(int level);
	void SetHp(int hp);
	void SetHpMax(int hpMax);
	void SetMp(int mp);
	void SetMpMax(int mpMax);

	void SetAttack(int attack);
	void SetDeffence(int deffence);
	void SetSpeed(int speed);



};

#endif // __CHARACTER_BASE_H__