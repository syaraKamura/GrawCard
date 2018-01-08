﻿/*
				ファイル名		:MonsterDeck.h
				作成者			:
				作成日時		:2018/01/07
				ソース説明		:モンスターデッキ
				
				
				備考
				
				
				
!*/

#ifndef __MONSTER_DECK_H__
#define __MONSTER_DECK_H__

#include "Monster.h"

class MonsterDeck {

private:

	static const int MONSTER_DECK_NUM = 5;

private:

	typedef struct {
		Monster monster;	//モンスターデータ
		bool isAttach;			//モンスターが設定されているか？
	}MonsterDeck_t;

private:

	MonsterDeck_t mMonster[MONSTER_DECK_NUM];
	

public :

	MonsterDeck();
	~MonsterDeck();

	/*
		モンスターが設定されているか判断する
		return	true	:設定されている
				false	:設定されていない
	*/
	bool IsSetMonster(int idx);

	/*
		設定されている状態にする
	*/
	void Attach(int idx);

	/*
		設定されていない状態にする
	*/
	void Detach(int idx);

	void SetMonster(int idx,Monster monster);
	Monster* GetMonster(int idx);


};

#endif // __MONSTER_DECK_H__