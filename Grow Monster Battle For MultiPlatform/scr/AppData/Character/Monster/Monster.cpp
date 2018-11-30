/*
				ファイル名		:Monster.cpp
				作成者			:
				作成日時		:2018/01/04
				ソース説明		:モンスターデータ
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Monster.h"

Monster::Monster() : CharacterBase() {

	SetLevel(LEVEL_MIN);
	SetName("None");
	SetType(eType_None);
	SetHomePosition(eHomePosition_Front);
	SetHp(10);
	SetHpMax(GetHp());
	SetMp(10);
	SetMpMax(GetMp());
	SetAttack(12);
	SetDeffence(8);
	SetSpeed(13);
	

}

Monster::~Monster() {

}

void Monster::SetId(int id) {
	mId = id;
}

void Monster::SetType(eType type) {
	mType = type;
}

void Monster::SetHomePosition(Monster::eHomePosition homePosition) {
	mHhomePosition = homePosition;
}

void Monster::SetHp(int hp) {
	mHp = hp;
}

void Monster::SetHpMax(int hpMax) {
	mHpMax = hpMax;
}

void Monster::SetMp(int mp) {
	mMp = mp;
}

void Monster::SetMpMax(int mpMax) {
	mMpMax = mpMax;
}

void Monster::SetAttack(int attack) {
	mAttack = attack;
}

void Monster::SetDeffence(int deffence) {
	mDeffence = deffence;
}

void Monster::SetSpeed(int speed) {
	mSpeed = speed;
}

void Monster::SetSkillNumber(int skill) {
	SkillIndex[0] = skill;
}

int Monster::GetId() const {
	return mId;
}

Monster::eType Monster::GetType() const {
	return mType;
}

Monster::eHomePosition Monster::GetHomePosition() const {
	return mHhomePosition;
}

int Monster::GetHp() const {
	return mHp;
}

int Monster::GetHpMax() const {
	return mHpMax;
}

int Monster::GetMp() const {
	return mMp;
}

int Monster::GetMpMax() const {
	return mMpMax;
}

int Monster::GetAttack() const {
	return mAttack;
}

int Monster::GetDeffence() const {
	return mDeffence;
}

int Monster::GetSpeed() const {
	return mSpeed;
}

int Monster::GetSkillNumber() const {
	return SkillIndex[0];
}