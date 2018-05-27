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

MonsterMgr* MonsterMgr::mInstance = NULL;


MonsterMgr::MonsterMgr() {

	std::ifstream file(MONSTER_DATA_PATH);

	if (file.is_open() == false) {
		Debug::ErorrMessage("モンスターデータの読み込みに失敗しました.");
	}


	file.close();
	
}

MonsterMgr::~MonsterMgr() {

}

void MonsterMgr::Create() {
	if (mInstance == NULL) {
		mInstance = new MonsterMgr();
	}
}

void MonsterMgr::Destory() {
	Delete(mInstance);
}

MonsterMgr* MonsterMgr::Instance() {

#ifdef __MY_DEBUG__
	Debug::ErorrMessage("MonsterMgrシングルトンがNULです.");
#endif

	return mInstance;
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


