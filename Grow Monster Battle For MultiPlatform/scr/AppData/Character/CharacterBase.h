/*
				ファイル名		:CharacterBase.h
				作成者			:
				作成日時		:2017/12/31
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __CHARACTER_BASE_H__
#define __CHARACTER_BASE_H__

class CharacterBase {

protected:

	static const int LEVEL_MIN = 1;			//最小レベル
	static const int LEVEL_MAX = 100;		//最大レベル
	static const int COST_MIN = 1;			//最小コスト
	static const int COST_MAX = 999;		//最大コスト

protected:

	int mLevel;			//レベル
	int mExp;			//経験値
	int mNextExp;		//レベルアップに必要な経験値
	
	char mName[256];	//名前
	
	int mCost;			//コスト


public:

	virtual ~CharacterBase();
	CharacterBase();

	void SetName(const char* name);
	void SetLevel(int level);
	void SetExp(int exp);
	void SetNextExp(int nextExp);
	void SetCost(int cost);

	const char* GetName();
	int GetLevel();
	int GetExp();
	int GetNextExp();
	int GetCost();
};

#endif // __CHARACTER_BASE_H__