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

class Graphcics;

class MonsterMgr {

private:
	
	typedef struct MonsterGraph_t{
		int id;
		Graphics* graph;
	}MonsterGraph_t;

private :

	static MonsterMgr* mInstance;

	std::list<Monster> mList;
	std::list<MonsterGraph_t> mGraphList;

	MonsterMgr();
	~MonsterMgr();

public :

	static void Create();
	static void Destory();

	static MonsterMgr* Instance();

	int GetMonsterNum();
	Monster* GetMonsterData(int number) const;
	Graphics GetGraphics(int number);

};


#endif // __MONSTER_MGR_H__