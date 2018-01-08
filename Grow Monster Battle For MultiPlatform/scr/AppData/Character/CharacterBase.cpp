/*
				ファイル名		:CharacterBase.cpp
				作成者			:
				作成日時		:2017/12/31
				ソース説明		:キャラクター基底クラス
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "CharacterBase.h"



CharacterBase::CharacterBase() {
	SetName("None_Name");
	SetLevel(LEVEL_MIN);
	SetExp(0);
	SetNextExp(10);
	SetCost(COST_MIN);
}

CharacterBase::~CharacterBase() {

}


void CharacterBase::SetName(const char* name) {
	strcpyDx(mName, name);
}

void CharacterBase::SetLevel(int level) {
	mLevel = level;
	if (mLevel <= 0) {
		mLevel = LEVEL_MIN;
	}
	else if (mLevel > LEVEL_MAX) {
		mLevel = LEVEL_MAX;
	}
}

void CharacterBase::SetExp(int exp) {
	mExp = exp;
}

void CharacterBase::SetNextExp(int nextExp) {
	mNextExp = nextExp;
}

void CharacterBase::SetCost(int cost) {
	mCost = cost;
}

const char* CharacterBase::GetName() {
	return mName;
}

int CharacterBase::GetLevel() {
	return mLevel;
}

int CharacterBase::GetExp() {
	return mExp;
}

int CharacterBase::GetNextExp() {
	return mNextExp;
}

int CharacterBase::GetCost() {
	return mCost;
}