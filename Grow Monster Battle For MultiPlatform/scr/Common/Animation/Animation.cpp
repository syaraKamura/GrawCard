/*
				ファイル名		:Animation.cpp
				作成者			:
				作成日時		:2018/03/22
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Animation.h"

/*
	
*/
ANIMATION_DATA_t GetAnimationDataValue(ANIMATION_DATA_t now, ANIMATION_DATA_t next, ANIMATION_DATA_t* changeValue) {
	
	ANIMATION_DATA_t value = {};

	value.keyframe = next.keyframe - now.keyframe;
	value.positionX = next.positionX - now.positionX;
	value.positionY = next.positionY - now.positionY;
	value.alpha = next.alpha - now.alpha;
	value.scale = next.scale - now.scale;
	value.angle = next.angle - now.angle;

	changeValue->positionX = fabsf(value.positionX);
	changeValue->positionY = fabsf(value.positionY);
	changeValue->alpha = fabsf(value.alpha);
	changeValue->scale = fabsf(value.scale);
	changeValue->angle = fabsf(value.angle);

	value.positionX /= value.keyframe;
	value.positionY /= value.keyframe;
	value.alpha /= value.keyframe;
	value.scale /= value.keyframe;
	value.angle /= value.keyframe;

	return value;
}

static bool SortKeyframe(ANIMATION_DATA_t a, ANIMATION_DATA_t b) {

	if (a.keyframe < b.keyframe) {
		return true;
	}

	return false;
}

Animation::Animation() {
	mAnimationDataList.clear();
	mCounter = 0;
	mTimeLength = 60;
	mIsLoop = false;
	mIsPlay = false;
	mIsStop = true;
	mIsPause = false;
	mNowFrame = 0;
	memset(&mAnimationValue, 0, sizeof(ANIMATION_DATA_t));
}

Animation::~Animation() {
	mAnimationDataList.clear();
}


/*
アニメーションデータを追加する
*/
void Animation::AddAnimationData(ANIMATION_DATA_t animationData) {
	mAnimationDataList.push_back(animationData);
	mAnimationDataList.sort(SortKeyframe);
}

/*
アニメーションの再生時間を設定する
*/
void Animation::SetAnimationTime(int timeLength) {
	mTimeLength = timeLength;
}

/*
再生
*/
void Animation::Play() {
	mIsPlay = true;
	mIsPause = false;
	mIsStop = false;
}

/*
停止
*/
void Animation::Stop() {
	mIsPlay = false;
	mIsPause = false;
	mIsStop = true;
	mCounter = 0;
	mNowFrame = 0;
	memset(&mAnimationValue, 0, sizeof(ANIMATION_DATA_t));
}

/*
一時停止
*/
void Animation::Pause() {
	mIsPlay = false;
	mIsPause = true;
}

/*
ループ再生
*/
void Animation::Loop() {
	mIsLoop = !mIsLoop;
}

/*
更新
*/
bool Animation::Update() {

	if (mIsStop == true) return true;
	else if (mIsPause == true) return true;
	else if (mAnimationDataList.size() <= 0) return false;

	if (mIsPlay) {

		ANIMATION_DATA_t nowKeyframe = {};
		ANIMATION_DATA_t nextKeyframe = {};
		//ANIMATION_DATA_t value = {};

		if (mNowFrame < mAnimationDataList.size()) {
			nowKeyframe = *std::next(mAnimationDataList.begin(), mNowFrame);
		}
		else {
			memset(&mAnimationValue, 0, sizeof(ANIMATION_DATA_t));
		}

		if (mCounter == nowKeyframe.keyframe) {
			if (mNowFrame + 1 < mAnimationDataList.size()) {
				nextKeyframe = *std::next(mAnimationDataList.begin(), mNowFrame + 1);
				mAnimationValue = GetAnimationDataValue(nowKeyframe, nextKeyframe ,&mValue);
			}
			mNowFrame++;
		}
		

		if (mCounter >= mTimeLength) {

			this->Stop();
			if (mIsLoop == true) {	
				this->Play();
			}
			return true;
		}
		mCounter++;
	}


	return true;
}

void Animation::AnimationAttach(GraphicsDraw* graph) {
	if (mIsPlay) {
		CheckVeluesZero();
		if (mCounter == 0) {
			graph->SetPosition(mAnimationValue.positionX, mAnimationValue.positionY);
			graph->SetAlpha(mAnimationValue.alpha);
			graph->SetScale(mAnimationValue.scale);
			graph->SetAngleRadian(mAnimationValue.angle);
		}
		else {
			graph->SetPosition(graph->GetPositionX() + mAnimationValue.positionX, graph->GetPositionY() + mAnimationValue.positionY);
			graph->SetAlpha((float)graph->GetAlpah() + mAnimationValue.alpha);
			graph->SetScale(graph->GetScale() + mAnimationValue.scale);
			graph->SetAngleRadian(graph->GetAngleRadian() + mAnimationValue.angle);
		}
	}
}

void Animation::AnimationAttach(float* posX, float* posY, float*alpha, float*angle/* = NULL*/, float*scale/* = NULL*/) {
	if (mIsPlay) {
		if (mCounter == 0) {
			if (posX != NULL) {
				*posX = mAnimationValue.positionX;
			}
			if (posY != NULL) {
				*posY = mAnimationValue.positionY;
			}
			if (alpha != NULL) {
				*alpha = mAnimationValue.alpha;
			}
			if (scale != NULL) {
				*scale = mAnimationValue.scale;
			}
			if (angle != NULL) {
				*angle = mAnimationValue.angle;
			}
		}
		else {
			if (posX != NULL) {
				*posX = *posX + mAnimationValue.positionX;
			}
			if (posY != NULL) {
				*posY = *posY + mAnimationValue.positionY;
			}
			if (alpha != NULL) {
				*alpha = *alpha + mAnimationValue.alpha;
			}
			if (scale != NULL) {
				*scale = *scale + mAnimationValue.scale;
			}
			if (angle != NULL) {
				*angle = *angle+ mAnimationValue.angle;
			}
		}
		
	}
}

/*
		値が0になっているか判断する
		return	true	:0になっている
				false	:なっていない
*/
bool Animation::CheckVeluesZero() {

	int ret = 0;

	mValue.positionX -= fabsf(mAnimationValue.positionX);
	if (mValue.positionX <= 0.0f) {
		mAnimationValue.positionX = 0.0f;
		ret++;
	}

	mValue.positionY -= fabsf(mAnimationValue.positionY);
	if (mValue.positionY <= 0.0f) {
		mAnimationValue.positionY = 0.0f;
		ret++;
	}
	
	mValue.alpha -= fabsf(mAnimationValue.alpha);
	if (mValue.alpha <= 0.0f) {
		mAnimationValue.alpha = 0.0f;
		ret++;
	}
	mValue.scale -= fabsf(mAnimationValue.scale);
	if (mValue.scale <= 0.0f) {
		mAnimationValue.scale = 0.0f;
		ret++;
	}

	mValue.angle -= fabsf(mAnimationValue.angle);
	if (mValue.angle <= 0.0f) {
		mAnimationValue.angle = 0.0f;
		ret++;
	}

	return (ret == 5);
}