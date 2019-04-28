/*
				ファイル名		:MonsterBox.h
				作成者			:
				作成日時		:2018/01/07
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __MONSTER_BOX_H__
#define __MONSTER_BOX_H__


#include "Monster.h"

namespace monsterBox {

	enum eUseState {
		eUseState_None = -1,	//エラー
		eUseState_UnUse,		//使用していない
		eUseState_Use,			//使用中
	};

	typedef struct {
		int id;
		int deckNo;			// デッキ番号
		int deckIndex;		// デッキ配置番号
		Monster* monster;
		eUseState useState;
	}Monster_t;


	class MonsterBox {

	private:

		static const int MONSTER_MAX = 1000;

	private:

		//std::list<Monster_t> mList;

		Monster_t mMonsterData[MONSTER_MAX];
		int mMonsterCount;
		int mIndex;

	private:

		bool Exits();

	public:

		MonsterBox();
		~MonsterBox();

		bool Add(Monster* monster);
		void Relese(int idx);
		void AllDelete();

		int Count();
		/*
			次のモンスターの情報を返却する

		*/
		Monster* Next();

		/*
			前のモンスターの情報を返却する
		*/
		Monster* Prev();

		/*
			インデックス番号を返却する
		*/
		int Index();

		/*
		使用状態を確認する
		return	 0	:使用していない
				 1	:使用中
				-1	:エラー
		*/
		eUseState UseState(int idx);

		/*
			使用状態を変更する
		*/
		void ChangeUseState(int idx, eUseState useState);


		Monster* GetMonster(int idx);
		void SetMonster(int idx, Monster* monster);

		void Draw();

		const Monster_t GetMonsterInfo(int idx);
		/*
			ロードするときに使用する
		*/
		void SetMonsterInfo(int idx,Monster_t& info);
		/*
			ボックスサイズ
		*/	
		unsigned int GetSize();
	};
}
#endif // __MONSTER_BOX_H__