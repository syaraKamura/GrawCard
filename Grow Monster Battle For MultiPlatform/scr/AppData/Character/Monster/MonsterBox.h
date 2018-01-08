﻿/*
				ファイル名		:MonsterBox.h
				作成者			:
				作成日時		:2018/01/07
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __MONSTER_BOX_H__
#define __MONSTER_BOX_H__


#include "Monster.h"


class MonsterBox {

private:

	static const int MONSTER_MAX = 1000;


public:
	
	enum eUseState {
		eUseState_None = -1,	//エラー
		eUseState_UnUse,		//使用していない
		eUseState_Use,			//使用中
	};

private:

	typedef struct {
		int id;
		Monster monster;
		eUseState useState;
	}Monster_t;


private:

	//std::list<Monster_t> mList;

	Monster_t mMonsterData[MONSTER_MAX];
	int mMonsterCount;

private:

	bool Exits();

public :

	MonsterBox();
	~MonsterBox();

	bool Add(Monster monster);
	void Relese(int idx);
	void AllDelete();

	int Count();
	
	/*
	使用状態を確認する
	return	 0	:使用していない
			 1	:使用中
			-1	:エラー
	*/
	eUseState UseState(int idx);

	/*
		使用状態を変更する
	*/
	void ChangeUseState(int idx,eUseState useState);


	Monster GetMonster(int idx);
	void SetMonster(int idx,Monster monster);

};

#endif // __MONSTER_BOX_H__