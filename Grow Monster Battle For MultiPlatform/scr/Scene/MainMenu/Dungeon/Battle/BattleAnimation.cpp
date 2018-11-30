/*
				ファイル名		:BattleAnimation.cpp
				作成者			:
				作成日時		:2018/10/24
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Common/Animation/Animation.h"
#include "BattleAnimation.h"


// 下からカードを画面内へ移動させる(前衛設定)
static ANIMATION_DATA_t BTL_ANIM_CARD_INSIDE_00[] =
{
	// keyframe	positionX	positionY				angle	scale	alpha	easing
	{ 0 ,		0,			WINDOW_HEIGHT,			0.0f,	1.0f,	0.0f									},
	{ 20,		0,			WINDOW_HEIGHT - 350,	0.0f,	1.0f,	255.0f	,Easing::eEasingType_InCubic	},
};

// 下からカードを画面内へ移動させる(後衛設定)
static ANIMATION_DATA_t BTL_ANIM_CARD_INSIDE_02[] =
{
	// keyframe	positionX	positionY				angle	scale	alpha	easing
	{ 0 ,		0,			WINDOW_HEIGHT,			0.0f,	1.0f,	0.0f },
	{ 20,		0,			WINDOW_HEIGHT - 250,	0.0f,	1.0f,	255.0f	,Easing::eEasingType_InCubic },
};


// 上からカードを画面内へ移動させる
static ANIMATION_DATA_t BTL_ANIM_CARD_INSIDE_01[] =
{
	// keyframe	positionX	positionY	angle	scale	alpha	easing
	{ 0 ,		0,			0,			0.0f,	1.0f,	0.0f			},
	{ 20,		0,			350,		0.0f,	1.0f,	255.0f			},
};

// 拡縮を行う
static ANIMATION_DATA_t BTL_ANIM_CARD_TRANSRATE_SCALE[]{
	// keyframe	positionX	positionY	angle	scale	alpha	easing
	{ 0 ,		0,			0,			0.0f,	1.0f,	255.0f ,Easing::eEasingType_InCubic },
	{ 30 ,		0,			0,			0.0f,	1.5f,	255.0f ,Easing::eEasingType_InCubic	},
	{ 35 ,		0,			0,			0.0f,	1.0f,	255.0f								},
};

// 通常攻撃_00
static ANIMATION_DATA_t BTL_ANIM_CARD_ATTACK_00[]{
	// keyframe	positionX	positionY	angle	scale	alpha	easing
	{ 0 ,		0,			0,			0.0f,	1.0f,	255.0f ,Easing::eEasingType_InCubic },
	{ 30 ,		0,			-50,			0.0f,	1.0f,	255.0f ,Easing::eEasingType_InCubic },
	{ 35 ,		0,			0,		0.0f,	1.0f,	255.0f },
};

// 通常攻撃_01
static ANIMATION_DATA_t BTL_ANIM_CARD_ATTACK_01[]{
	// keyframe	positionX	positionY	angle	scale	alpha	easing
	{ 0 ,		0,			0,			0.0f,	1.0f,	255.0f ,Easing::eEasingType_InCubic },
	{ 30 ,		0,			-50,		0.0f,	1.4f,	255.0f ,Easing::eEasingType_InCubic },
	{ 35 ,		0,			0,			0.0f,	1.0f,	255.0f },
};

// 拡大をする
static ANIMATION_DATA_t BTL_ANIM_CARD_TRANSRATE_SCALE_01[]{
	// keyframe	positionX	positionY	angle	scale	alpha	easing
	{ 0 ,		0,			0,			0.0f,	0.0f,	0.0f ,Easing::eEasingType_InCubic },
	{ 30 ,		0,			20,			0.0f,	1.0f,	255.0f},
};

// 縮小をする
static ANIMATION_DATA_t BTL_ANIM_CARD_TRANSRATE_SCALE_02[]{
	// keyframe	positionX	positionY	angle	scale	alpha	easing
	{ 0 ,		0,			0,			0.0f,	1.0f,	255.0f ,Easing::eEasingType_InCubic },
	{ 30 ,		0,			-20,		0.0f,	0.0f,	0.0f },
};


BattleAnimation::ANIMATION_LIST_t BattleAnimation::ANIMATION_LIST_TBL[BattleAnimation::eAnimationNo_Num] =
{
	{ "下から画面内へ移動する（前衛）" ,ArrySize(BTL_ANIM_CARD_INSIDE_00),BTL_ANIM_CARD_INSIDE_00},
	{ "上から画面内へ移動する" ,ArrySize(BTL_ANIM_CARD_INSIDE_01),BTL_ANIM_CARD_INSIDE_01 },
	{ "下から画面内へ移動する（後衛）" ,ArrySize(BTL_ANIM_CARD_INSIDE_01),BTL_ANIM_CARD_INSIDE_02 },
	{"拡大縮小を行う",ArrySize(BTL_ANIM_CARD_TRANSRATE_SCALE),BTL_ANIM_CARD_TRANSRATE_SCALE },
	{"通常攻撃_00",ArrySize(BTL_ANIM_CARD_ATTACK_00 ),BTL_ANIM_CARD_ATTACK_00 },
	{ "通常攻撃_01",ArrySize(BTL_ANIM_CARD_ATTACK_01),BTL_ANIM_CARD_ATTACK_01 },
	{ "拡大を行う",ArrySize(BTL_ANIM_CARD_TRANSRATE_SCALE_01),BTL_ANIM_CARD_TRANSRATE_SCALE_01 },
	{ "縮小を行う",ArrySize(BTL_ANIM_CARD_TRANSRATE_SCALE_02),BTL_ANIM_CARD_TRANSRATE_SCALE_02 },
};

BattleAnimation::BattleAnimation() : TaskBase(){

}

/*
	int idx				:アニメーション番号
	GraphicsDraw* graph	:グラフィックス
	return	NULL以外	: リクエスト成功
			NULL		: リスエスト失敗
*/
Animation* BattleAnimation::RequestAnim(int animNo, GraphicsDraw* graph, bool isNowPositionBase /*= false*/) {

	
	if (animNo < 0 || animNo >= BattleAnimation::eAnimationNo_Num) {
		Debug::ErorrMessage("指定されたバトルアニメーションは無効です\n");
		return NULL;
	}

	if (graph == NULL) {
		Debug::ErorrMessage("GraphicsDrawがNULLです\n");
		return NULL;
	}

	BATTLE_ANIMATION_DATA_t add;
	add.mOrderId = 0;
	add.mAnim = new Animation();
	
	ANIMATION_LIST_t data = ANIMATION_LIST_TBL[animNo];

	for (int i = 0; i < data.mSize; i++) {
		add.mAnim->AddAnimationData(data.mData[i]);
	}

	int timeLength = data.mData[data.mSize - 1].keyframe;
	add.mAnim->SetAnimationTime(timeLength);
	add.mGraph = graph;

	add.mIsNowPositionBase = isNowPositionBase;

	mAnimData.push_back(add);
	
	// 再生開始
	add.mAnim->Play();
	

	return add.mAnim;
}

Animation* BattleAnimation::RequestAnim(ANIMATION_DATA_t* animData, int animDataSize, GraphicsDraw* graph, bool isNowPositionBase/* = false */) {

	if (animData == NULL) {
		Debug::ErorrMessage("animDataがNULLです\n");
		return  NULL;
	}

	if (graph == NULL) {
		Debug::ErorrMessage("GraphicsDrawがNULLです\n");
		return NULL;
	}

	BATTLE_ANIMATION_DATA_t add;
	add.mOrderId = 0;
	add.mAnim = new Animation();

	for (int i = 0; i < animDataSize; i++) {
		add.mAnim->AddAnimationData(animData[i]);
	}

	int timeLength = animData[animDataSize - 1].keyframe;
	add.mAnim->SetAnimationTime(timeLength);
	add.mGraph = graph;

	add.mIsNowPositionBase = isNowPositionBase;

	mAnimData.push_back(add);

	// 再生開始
	add.mAnim->Play();


	return add.mAnim;

}


//初期化
bool BattleAnimation::Initialize() {

	return true;
}

//前　更新処理
void BattleAnimation::PreviousUpdate() {

}

//入力更新処理
void BattleAnimation::InputUpdate() {

}

//更新処理
bool BattleAnimation::Updata() {

	for (auto itr = mAnimData.begin(); itr != mAnimData.end(); itr++) {
		itr->mAnim->Update();
		if (itr->mAnim->IsPlay()) {
			itr->mAnim->AnimationAttach(itr->mGraph, itr->mIsNowPositionBase);
		}
	}

	return  true;
}

//描画
void BattleAnimation::Draw() {

}

//後 更新処理
void BattleAnimation::PostUpdate(){


	// 再生が終了したものを一覧から削除する
	for (auto itr = mAnimData.begin(); itr != mAnimData.end();) {
		if (itr->mAnim->IsPlay() == false) {
			mAnimData.erase(itr);
			itr = mAnimData.begin();
		}
		else {
			itr++;
		}
	}

}

//終了処理
void BattleAnimation::Finalize() {
	for (auto itr = mAnimData.begin(); itr != mAnimData.end();) {
		itr->mAnim->Stop();
		mAnimData.erase(itr);
		itr = mAnimData.begin();
	}
	mAnimData.clear();
}

/*
再生中か判断する
return	true	: 再生中
false	: 再生中ではない
*/
bool BattleAnimation::IsPlay() {
	
	return false;
}
