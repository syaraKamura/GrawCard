/*
				ファイル名		:ScriptAnimation.cpp
				作成者			:
				作成日時		:2018/07/15
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Common/Script/ScriptAnimation.h"
// #include "Common/Animation/ScriptAnim.inc"


//右側から画面内へ
static ANIMATION_DATA_t s_FadeIn_RigthToLeft_DATA[] = {
	//int keyframe, float positionX,float positionY,float angle,float scale,float alpha
	{ 0,WINDOW_WIDTH,0,1.0f,1.0f,0.0f },
	//{ 40,WINDOW_WIDTH - 400,0 + 100,1.0f,1.0f,123.0f },
	//{ 0,WINDOW_WIDTH,WINDOW_HEIGHT - 200,1.0f,1.0f,0.0f },
	{ 60, WINDOW_WIDTH - 200,0,1.0f,1.0f,255.0f },
};

//左側から画面内へ
static ANIMATION_DATA_t s_FadeIn_LeftToRigth_DATA[] = {
	//int keyframe, float positionX,float positionY,float angle,float scale,float alpha
	{ 0,-WINDOW_WIDTH,0,1.0f,1.0f,0.0f },
	//{ 40,WINDOW_WIDTH - 400,0 + 100,1.0f,1.0f,123.0f },
	//{ 0,WINDOW_WIDTH,WINDOW_HEIGHT - 200,1.0f,1.0f,0.0f },
	{ 60, 200,0,1.0f,1.0f,255.0f },
};

//フラッシュ
static ANIMATION_DATA_t s_FLASH_DATA[] = {
	{ 0,0,0,1.0f,1.0f,255.0f },
	{ 2,0,0,1.0f,1.0f,0.0f },
	{ 4,0,0,1.0f,1.0f,255.0f },
	{ 6,0,0,1.0f,1.0f,0.0f },
	{ 8,0,0,1.0f,1.0f,255.0f },
	{ 10,0,0,1.0f,1.0f,0.0f },
	{ 12,0,0,1.0f,1.0f,255.0f },
};

//フェードイン
static ANIMATION_DATA_t s_FADE_IN_DATA[] = {
	{ 0,0,0,1.0f,1.0f,0.0f },
	{ 30,0,0,1.0f,1.0f,255.0f },
};

ScriptAnimation::ScriptAnimation() : TaskBase() {

	
	this->ANIMATION_DATA_TBL[ScriptAnimation::eAnimationNo_FadeIn_Rigth_To_Left].Add(ScriptAnimation::eAnimationNo_FadeIn_Rigth_To_Left, s_FadeIn_RigthToLeft_DATA, ArrySize(s_FadeIn_RigthToLeft_DATA));
	this->ANIMATION_DATA_TBL[ScriptAnimation::eAnimationNo_FadeIn_Left_To_Rigth].Add(ScriptAnimation::eAnimationNo_FadeIn_Left_To_Rigth, s_FadeIn_LeftToRigth_DATA, ArrySize(s_FadeIn_LeftToRigth_DATA));
	this->ANIMATION_DATA_TBL[ScriptAnimation::eAnimationNo_Flash].Add(ScriptAnimation::eAnimationNo_Flash, s_FLASH_DATA, ArrySize(s_FLASH_DATA));
	this->ANIMATION_DATA_TBL[ScriptAnimation::eAnimationNo_FadeIn].Add(ScriptAnimation::eAnimationNo_FadeIn, s_FADE_IN_DATA, ArrySize(s_FADE_IN_DATA));

}

ScriptAnimation::~ScriptAnimation() {

}


/*
	アニメーションを行うGraphicsDrawクラスをアタッチする
	return	1以上	:	管理IDを返却する
			-1		:	エラー	
*/
unsigned int ScriptAnimation::AttachGraphics(GraphicsDraw* graph, int animNo, bool isLoop/* = false*/, bool isNowBasePos /*= false*/) {


	if (graph == NULL) {
		Debug::ErorrMessage("GraphicsDrawの値がNULLです.(%s)",__func__);
		return -1;
	}

	ScriptAnimation::GRAPHICS_ANIM_DATA_t add;
	add.mGraphics = graph;
	add.mIsLoop = isLoop;
	add.mIsNowPosBase = isNowBasePos;
	add.mOrderAnimNo = animNo;
	add.mOrderId = ++mOrderCount;

	add.mAnimation = Animation();

	int animationTime = 60;
	bool find = false;
	for (int i = 0; i < ScriptAnimation::eAnimationNo_Num; i++) {
		const ScriptAnimation::ANIMATION_DATA_INOF_t data = this->ANIMATION_DATA_TBL[i];
		if (animNo == data.mAnimNo) {
			int length = data.mAnimDataSize;
			animationTime = (int)data.mAnimationData[length - 1].keyframe;
			for (int j = 0; j < length; j++) {
				add.mAnimation.AddAnimationData(data.mAnimationData[j]);
			}
			find = true;
		}
		if (find == true) break;
	}

	if (find == false) {
		Debug::ErorrMessage("アニメーションのアタッチに失敗しました(%s)",__func__);
		return -1;
	}

	if (add.mIsLoop) {
		add.mAnimation.Loop();
	}

	add.mAnimation.SetAnimationTime(animationTime);
	add.mAnimation.Play();
	this->mAnimData.push_back(add);

	return mOrderCount;
}

void ScriptAnimation::DetachGraphics(int orderId) {


	int length = this->mAnimData.size();

	for (int i = 0; i < length; i++) {
		if (this->mAnimData[i].mOrderId == orderId) {
			auto itr = mAnimData.begin() + i;
			itr->mGraphics = NULL;
			this->mAnimData.erase(itr);
			return;
		}
	}

}

//初期化
bool ScriptAnimation::Initialize() {
	return true;
}

//前　更新処理
void ScriptAnimation::PreviousUpdate() {

}

//入力更新処理
void ScriptAnimation::InputUpdate() {

}

//更新処理
bool ScriptAnimation::Updata() {
	int length = this->mAnimData.size();

	for (int i = 0; i < length; i++) {
		Animation* anim = &this->mAnimData[i].mAnimation;
		if (anim->IsPlay() == false) continue;
		GraphicsDraw* graph = this->mAnimData[i].mGraphics;
		anim->AnimationAttach(graph,this->mAnimData[i].mIsNowPosBase);
		anim->Update();
	}
	return true;
}

//描画
void ScriptAnimation::Draw() {

}

//後 更新処理
void ScriptAnimation::PostUpdate() {

#if 0
	int length = this->mAnimData.size();
	for (int i = 0; i < length; i++) {
		Animation* anim = &this->mAnimData[i].mAnimation;
		if (anim->IsStop() == true) {
			int id = this->mAnimData[i].mOrderId;
			DetachGraphics(id);
		}
	}
#endif

}

//終了処理
void ScriptAnimation::Finalize() {

	int length = this->mAnimData.size();

	for (int i = 0; i < length; i++) {
		//if (this->mAnimData[i].mOrderId == orderId) {
			//auto itr = mAnimData.begin() + i;
			auto itr = mAnimData.begin();
			itr->mGraphics = NULL;
			this->mAnimData.erase(itr);
			//i--;
			//return;
		//}
	}


}


/*
	再生中か
*/
bool ScriptAnimation::IsPlay(int orderId) {
	int length = this->mAnimData.size();
	for (int i = 0; i < length; i++) {
		if (orderId == this->mAnimData[i].mOrderId) {
			Animation* anim = &this->mAnimData[i].mAnimation;
			return anim->IsPlay();
		}
	}
	return false;
}