/*
				ファイル名		:MonsterMgr.cpp
				作成者			:
				作成日時		:2018/05/27
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "MonsterMgr.h"

#define MONSTER_DATA_PATH "Resources/Data/Monster/MonsterData.dat"

#ifdef __MY_DEBUG__

#define SIZE(X) (sizeof(X)/sizeof(X[0]))
//#define __TEST_DATA__	//テストデータ読み込み用

typedef struct MonsterData_t{

	Monster::eType mType;

	int mId;		//管理番号
	int mHp;
	int mHpMax;
	int mMp;
	int mMpMax;

	int mAttack;
	int mDeffence;
	int mSpeed;

};


MonsterData_t MONSTER_DATA_TBL[] =
{
	{ Monster::eType_Fire,0,20,20,10,10,6,5,2 },
	{ Monster::eType_Fire,1,200,200,10,10,16,15,4 },
	{ Monster::eType_Water,2,20,20,10,10,6,5,2 },
	{ Monster::eType_Water,3,200,200,10,10,16,20,2 },
	{ Monster::eType_Grass,4,20,20,10,10,6,5,2 },
	{ Monster::eType_Grass,5,200,200,10,10,16,21,1 },
};

#endif

MonsterMgr* MonsterMgr::mInstance = NULL;

MonsterMgr::MonsterMgr() {

	std::ifstream file(MONSTER_DATA_PATH);

	if (file.is_open() == false) {
		Debug::ErorrMessage("モンスターデータの読み込みに失敗しました.");
	}

	
#if defined(__MY_DEBUG__) && defined(__TEST_DATA__)

	for (int i = 0; i < SIZE(MONSTER_DATA_TBL); i++) {

		Monster monster;

		monster.SetLevel(1);
		monster.SetCost(1);
		monster.SetId(MONSTER_DATA_TBL[i].mId);
		monster.SetType(MONSTER_DATA_TBL[i].mType);
		monster.SetHomePosition(Monster::eHomePosition_Front);
		monster.SetHp(MONSTER_DATA_TBL[i].mHp);
		monster.SetHpMax(MONSTER_DATA_TBL[i].mId);
		monster.SetMp(MONSTER_DATA_TBL[i].mId);
		monster.SetMpMax(MONSTER_DATA_TBL[i].mId);
		monster.SetAttack(MONSTER_DATA_TBL[i].mId);
		monster.SetDeffence(MONSTER_DATA_TBL[i].mId);
		monster.SetSpeed(MONSTER_DATA_TBL[i].mId);


		mList.push_back(monster);

	}
#else

	



#endif
	

	file.close();
	

}

MonsterMgr::~MonsterMgr() {

}

void MonsterMgr::Create() {
	if (MonsterMgr::mInstance == NULL) {
		MonsterMgr::mInstance = new MonsterMgr();
	}
}

void MonsterMgr::Destory() {
	Delete(MonsterMgr::mInstance);
}

MonsterMgr* MonsterMgr::Instance() {

#ifdef __MY_DEBUG__
	if (MonsterMgr::mInstance == NULL) {
		Debug::ErorrMessage("MonsterMgrシングルトンがNULLです.");
	}
#endif

	return MonsterMgr::mInstance;
}


/*
	モンスターデータを返却する
	int	number		:モンスターID
	return			:モンスターデータ
*/
Monster MonsterMgr::getMonsterData(int number) {

	if (this->mList.size() == 0) return Monster();
	
	Monster ret;

	for (auto itr = this->mList.begin(); itr != this->mList.end(); itr++) {

		if (itr->GetId() == number) {
			ret = *itr;
			break;
		}
	}
	return ret;
}


