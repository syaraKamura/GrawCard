/*
				ファイル名		:Monster.h
				作成者			:
				作成日時		:2017/12/31
				ソース説明		:モンスタークラス
				
				
				備考
				
				
				
!*/

#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "../CharacterBase.h"

const int SKILL_HAVE_NUM = 2;	//スキル所持数


class Monster : public CharacterBase {

private:

	enum eHomePosition {
		eHomePosition_Front,	//前衛
		eHomePosition_Back,		//後衛
	};

private:

	int SkillIndex[SKILL_HAVE_NUM];
	eHomePosition mHomePosition;	//定位置

public :

};

#endif // __MONSTER_H__