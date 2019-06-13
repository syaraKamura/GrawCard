/*
				ファイル名		:BattleAnimation.h
				作成者			:
				作成日時		:2018/10/24
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BATTLE_ANIMATION_H__
#define __BATTLE_ANIMATION_H__

class Animation;
class GraphicsDraw;

#include <list>
#include "Common/Task/TaskBase.h"
#include "Common/Animation/Animation.h"

namespace battle {
namespace anim {

	class BattleAnimation : public TaskBase {

	public:

		enum eAnimationNo {
			eAnimationNo_None = -1,
			eAnimationNo_InSide_00,
			eAnimationNo_InSide_01,
			eAnimationNo_InSide_02,
			eAnimationNo_Transrate_Scale,
			eAnimationNo_Attack_00,
			eAnimationNo_Attack_01,
			eAnimationNo_Transrate_Scale_01,
			eAnimationNo_Transrate_Scale_02,
			eAnimationNo_Num,
		};

		typedef struct {
			int mOrderId;
			Animation* mAnim;
			GraphicsDraw* mGraph;
			bool mIsNowPositionBase;	// 画像の現在の座標を基準とするか
		}BATTLE_ANIMATION_DATA_t;

		typedef struct {
			char mAnimName[128];
			int mSize;
			ANIMATION_DATA_t* mData;
		}ANIMATION_LIST_t;


	private:

		std::list <BATTLE_ANIMATION_DATA_t> mAnimData;

		static ANIMATION_LIST_t ANIMATION_LIST_TBL[BattleAnimation::eAnimationNo_Num];

	public:

		BattleAnimation();

		/*
			int idx				:アニメーション番号
			GraphicsDraw* graph	:グラフィックス
			return	NULL以外	: リクエスト成功
					NULL		: リスエスト失敗
		*/
		Animation* RequestAnim(int animNo, GraphicsDraw* graph, bool isNowPositionBase = false);

		Animation* RequestAnim(ANIMATION_DATA_t* animData, int animDataSize, GraphicsDraw* graph, bool isNowPositionBase = false);

		//初期化
		bool Initialize() override;

		//前　更新処理
		void PreviousUpdate() override;

		//入力更新処理
		void InputUpdate() override;

		//更新処理
		bool Updata() override;

		//描画
		void Draw() override;

		//後 更新処理
		void PostUpdate()override;

		//終了処理
		void Finalize() override;

		/*
			再生中か判断する
			return	true	: 再生中
					false	: 再生中ではない
		*/
		bool IsPlay();

	};

	class DamageNum {

		enum eType {
			eType_None,
			eType_Damage,
			eType_Recavery,
		};

	private:

		int mBasePosX;
		int mBasePosY;
		int mPosX;
		int mPosY;
		int mDamage;
		int mLifeTime;
		int mCounter;
		float mAlpha;

		eType mDamageType;
		unsigned int mColor;

	public :

		DamageNum();

		void Set(int posX, int posY, int damage, int lifeTime = 20) {
			mBasePosX = posX;
			mBasePosY = posY;
			mDamage = damage;
			mLifeTime = lifeTime;

			if (mDamage < 0) {
				mDamageType = eType_Recavery;
			}

			mDamage *= -1;

		}

		void Draw();
		void Update();


		bool IsPlay() {
			return mLifeTime >= mCounter;
		}
	};


}
}
#endif // __BATTLE_ANIMATION_H__