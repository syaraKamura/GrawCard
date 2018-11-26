/*
		ファイル名		:Player,h
		作成者			:
		作成日時		:2018/01/04
		ソース説明		:プレイヤー


		備考



!*/

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../CharacterBase.h"
#include "../Monster/MonsterDeck.h"

class Player : public CharacterBase {

private:

	static const int MONSTER_DEK_NUM = 5;

private:

public:

	enum eGender {
		eGender_Male,		//男性
		eGender_Female,		//女性
	};

private:

	/*
		アイテムクラス
			アイテム番号
			アイテム名
			アイテムの所持数
			アイテムの効果
		モンスターデッキクラス
	*/

	eGender mGender;	//性別

	MonsterDeck mMonsterDeck;	//モンスターデッキ

public:

	Player();
	~Player();

	void SetGender(eGender gender);
	int GetGender();

	/*
		モンスターを設定する
		return	true	:設定に成功
				false	:設定に失敗
	*/
	bool SetMonster(int idx, Monster* monster);
	Monster* GetMonster(int idx);

	/*
		モンスターをデッキから除外する
	*/
	void RemoveMonster(int idx);

	/*
		デッキに設定しているモンスターの数
	*/
	int GetSetMonsterNum();

};

#endif //__PLAYER_H__