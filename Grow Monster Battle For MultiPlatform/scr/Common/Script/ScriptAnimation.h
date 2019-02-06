/*
				ファイル名		:ScriptAnimation.h
				作成者			:
				作成日時		:2018/07/15
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __SCRIPT_ANIMATION_H__
#define __SCRIPT_ANIMATION_H__

#include <vector>

#include "Common/Task/TaskBase.h"
#include "Common/Graphics/GraphicsDraw.h"
#include "Common/Animation/Animation.h"

class ScriptAnimation : public TaskBase {

public :

	enum eAnimationNo {

		eAnimationNo_None = -1,
		eAnimationNo_FadeIn_Rigth_To_Left,		//右側から画面内へ
		eAnimationNo_FadeIn_Left_To_Rigth,		//左側から画面内へ
		eAnimationNo_Flash,						//点滅させる
		eAnimationNo_FadeIn,					//フェードイン

		eAnimationNo_Num
	};

private :

	typedef struct {
		int mOrderId;				//管理番号
		GraphicsDraw* mGraphics;	//画像描画クラス
		Animation mAnimation;
		int mOrderAnimNo;			//再生を行うアニメーション番号
		bool mIsLoop;				//ループ再生を行うか
		bool mIsNowPosBase;			//現在の座標を基本座標とする
	}GRAPHICS_ANIM_DATA_t;

	typedef struct{
		int mAnimNo;
		int mAnimDataSize;
		ANIMATION_DATA_t* mAnimationData;

		void Add(int animNo, ANIMATION_DATA_t* data, int animDataSize) {
			mAnimNo = animNo;
			mAnimationData = data;
			mAnimDataSize = animDataSize;
		}
	} ANIMATION_DATA_INOF_t;
	
	ANIMATION_DATA_INOF_t ANIMATION_DATA_TBL[eAnimationNo_Num];

private:

	unsigned int mOrderCount;

	std::vector<GRAPHICS_ANIM_DATA_t> mAnimData;
	

public :

	ScriptAnimation();
	~ScriptAnimation();

	/*
		アニメーションを行うGraphicsDrawクラスをアタッチする
		return 管理IDを返却する
	*/
	unsigned int AttachGraphics(GraphicsDraw* graph, int animNo, bool isLoop = false, bool isNowBasePos = false);
	void DetachGraphics(int orderId);

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
		再生中か
	*/
	bool IsPlay(int orderId);

};

#endif // __SCRIPT_ANIMATION_H__