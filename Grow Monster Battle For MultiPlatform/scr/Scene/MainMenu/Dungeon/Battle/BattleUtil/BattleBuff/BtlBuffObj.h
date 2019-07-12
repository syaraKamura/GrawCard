/*
				ファイル名		:BtlBuffObj.h
				作成者			:
				作成日時		:2019/07/06
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BTL_BUFF_OBJ_H__
#define __BTL_BUFF_OBJ_H__

#include "../BtlCommon.h"
#include <vector>

namespace battle {


	struct StatusRate {
		eBuffType mBuffType;		// 効果の種類
		float mValue;
		int mEffectiveTurn;		// 効果継続期間
		int mEffectActiveTrun;	// 効果が付与されたターン
	};


	/*
		バフ/デバフ管理クラス
	*/
	class BuffObj {

	private:

		std::vector<StatusRate> mBuff;

	public:

		/*
			バフの状態を更新
		*/
		void Update();

		/*
			全てのバフを削除する
		*/
		void Clear();
		/*
			バフを追加する
		*/
		void Add(StatusRate buff);

		/*
			指定タイプのバフを持っているか？
		*/
		bool CheckExists(eBuffType buffType);
		bool CheckExists(eBuffType buffType) const ;

		/*
			指定バフの効果値を取得する
		*/
		float GetValue(eBuffType buffType);
		float GetValue(eBuffType buffType) const ;

		StatusRate& GetBuff(eBuffType buffType);
		StatusRate& GetBuff(eBuffType buffType) const;


	};

};


#endif // __TEMPLETE_H__