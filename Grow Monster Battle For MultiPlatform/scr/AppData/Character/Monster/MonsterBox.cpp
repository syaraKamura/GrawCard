/*
				ファイル名		:MonsterBox.cpp
				作成者			:
				作成日時		:2018/01/07
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include <list>
#include "Common/GameCommon.h"
#include "MonsterBox.h"


MonsterBox::MonsterBox() {

	mMonsterCount = 0;
	mIndex = 0;
}

MonsterBox::~MonsterBox() {

}


bool MonsterBox::Add(Monster monster) {
	
	if (Count() >= MONSTER_MAX) {
		Debug::LogPrintf("ボックスのモンスター登録限度を超えています。\n");
		return false;
	}

	Monster_t _monster = { mMonsterCount, monster,eUseState_UnUse};
	
	mMonsterData[mMonsterCount] = _monster;

	mMonsterCount++;
	return true;
}

void MonsterBox::Relese(int idx) {

	if (Exits() == false) return;
	else if (idx < 0 || mMonsterCount > idx) return;
	
	ChangeUseState(idx, eUseState_None);
	mMonsterData[idx].id = -1;
	mMonsterData[idx].monster = Monster();

}

void MonsterBox::AllDelete(){
	
}

int MonsterBox::Count() {
	if (Exits() == false) return 0;
	return mMonsterCount;
}

Monster MonsterBox::GetMonster(int idx) {
	Monster monster;
	if (Exits() == false) return monster;
	else if (idx < 0 || mMonsterCount < idx) return monster;

	monster = mMonsterData[idx].monster;

	return monster;
}

void MonsterBox::SetMonster(int idx,Monster monster) {

	if (Exits() == false) return;
	else if (idx < 0 || mMonsterCount > idx) return;

	mMonsterData[idx].monster = monster;
}

/*
	使用状態を確認する
	return	0	:使用していない
			1	:使用中
			-1	:エラー
*/
MonsterBox::eUseState MonsterBox::UseState(int idx) {
	if (Exits() == false) return eUseState_None;
	else if (idx < 0 || mMonsterCount < idx) return eUseState_None;

	return mMonsterData[idx].useState;
}

/*
	使用状態を変更する
*/
void MonsterBox::ChangeUseState(int idx, eUseState useState) {
	
	if (Exits() == false) return;
	else if (idx < 0 || mMonsterCount < idx) return;
	else if (useState < eUseState_UnUse || useState > eUseState_Use) {
		Debug::LogPrintf("設定された値が無効です。(%d)\n", useState);
		return;
	}
	
	mMonsterData[idx].useState = useState;

}

bool MonsterBox::Exits() {
	if (mMonsterCount <= 0)return false;
	else return true;
}

/*
次のモンスターの情報を返却する

*/
Monster* MonsterBox::Next() {

	if (mMonsterCount <= 0) return NULL;
	if (mIndex < mMonsterCount) {
		mIndex++;
	}
	return &mMonsterData[mIndex].monster;
}

/*
	前のモンスターの情報を返却する
*/
Monster* MonsterBox::Prev() {
	if (mMonsterCount <= 0) return NULL;
	if (mIndex > 0) {
		mIndex--;
	}
	return &mMonsterData[mIndex].monster;
}

int MonsterBox::Index() {
	return mIndex;
}