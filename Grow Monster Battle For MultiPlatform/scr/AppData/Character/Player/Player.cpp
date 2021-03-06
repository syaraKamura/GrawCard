﻿/*
		ファイル名		:Plauer.cpp
		作成者			:
		作成日時		:2018/01/04
		ソース説明		:プレイヤー


		備考



!*/

#include "Common/GameCommon.h"
#include "Player.h"

Player::Player() : CharacterBase() {
	SetCost(10);
	SetName("あゆみ");
	SetGender(eGender_Female);

	mMonsterDeck.Clear();

}

Player::~Player() {

}

void Player::SetGender(eGender gender) {
	mGender = gender;
}

int Player::GetGender() {
	return mGender;
}

/*
	モンスターを設定する
	return	true	:設定に成功
			false	:設定に失敗
*/
bool Player::SetMonster(int idx, Monster* monster) {

	if (mMonsterDeck.IsSetMonster(idx) == true) return false;
	mMonsterDeck.SetMonster(idx, monster);
	mMonsterDeck.Attach(idx);
	return true;
}


/*
	モンスターをデッキから除外する
*/
void Player::RemoveMonster(int idx) {
	if (mMonsterDeck.IsSetMonster(idx) == false) return ;
	mMonsterDeck.SetMonster(idx, NULL);
	mMonsterDeck.Detach(idx);
}

Monster* Player::GetMonster(int idx) {
	return mMonsterDeck.GetMonster(idx);
}

/*
デッキに設定しているモンスターの数
*/
int Player::GetSetMonsterNum() {
	return mMonsterDeck.GetSetNum();
}

/*
		モンスターデッキを取得する
*/
MonsterDeck Player::GetMonsterDeck() const {
	return mMonsterDeck;
}