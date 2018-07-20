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

int Monster::GetId() {
	return mId;
}

Monster::eType Monster::GetType() {
	return mType;
}

int Monster::GetHp() {
	return mHp;
}

int Monster::GetHpMax() {
	return mHpMax;
}

int Monster::GetMp() {
	return mMp;
}

int Monster::GetMpMax() {
	return mMpMax;
}

int Monster::GetAttack() {
	return mAttack;
}

int Monster::GetDeffence() {
	return mDeffence;
}

int Monster::GetSpeed() {
	return mSpeed;
}