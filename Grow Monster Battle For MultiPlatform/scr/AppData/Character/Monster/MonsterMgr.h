/*
				ファイル名		:MonsterMgr.h
				作成者			:
				作成日時		:2018/05/27
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __MONSTER_MGR_H__
#define __MONSTER_MGR_H__

#include "Monster.h"

class MonsterMgr {

private :

	static MonsterMgr* mInstance;

	std::list<Monster> mList;

	MonsterMgr();
	~MonsterMgr();

public :

	static void Create();
	static void Destory();

	static MonsterMgr* Instance();

	Monster getMonsterData(int number);

};


#endif // __MONSTER_MGR_H__