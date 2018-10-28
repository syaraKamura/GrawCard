/*
				ファイル名		:MonsterDeck.cpp
				作成者			:
				作成日時		:2018/01/08
				ソース説明		:モンスターデッキ
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "MonsterDeck.h"

MonsterDeck::MonsterDeck() {
	mSetMonsterCount = 0;

	for (int i = 0; i < MONSTER_DECK_NUM; i++) {
		mMonster[i].isAttach = false;
	}
	

}

MonsterDeck::~MonsterDeck() {

}

void MonsterDeck::SetMonster(int idx, Monster monster) {
	if (idx < 0 || idx >= MONSTER_DECK_NUM) return;
	else if (IsSetMonster(idx) == true) return;

	mMonster[idx].monster = monster;
}

Monster* MonsterDeck::GetMonster(int idx) {
	if (idx < 0 || idx >= MONSTER_DECK_NUM) return NULL;
	if (IsSetMonster(idx) == false) return NULL;
	return &mMonster[idx].monster;
}

/*
	モンスターが設定されているか判断する
	return	true	:設定されている
			false	:設定されていない
*/
bool MonsterDeck::IsSetMonster(int idx) {
	if (idx < 0 || idx >= MONSTER_DECK_NUM) return true;
	return mMonster[idx].isAttach;
}

/*
	設定されている状態にする
*/
void MonsterDeck::Attach(int idx) {
	if (idx < 0 || idx >= MONSTER_DECK_NUM) return;
	mMonster[idx].isAttach = true;
	mSetMonsterCount++;
}

/*
	設定されていない状態にする
*/
void MonsterDeck::Detach(int idx) {
	if (idx < 0 || idx >= MONSTER_DECK_NUM) return;
	mMonster[idx].isAttach = false;
	mSetMonsterCount--;
}

int MonsterDeck::GetSetNum() {
	return mSetMonsterCount;
}