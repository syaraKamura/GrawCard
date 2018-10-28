/*
				ファイル名		:Animation.cpp
				作成者			:
				作成日時		:2018/03/22
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "./Easing/Easing.h"
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

	mBasePositionX = 0.0f;
	mBasePositionY = 0.0f;
	

	memset(&mAnimationValue, 0, sizeof(ANIMATION_DATA_t));
}

Animation::~Animation() {
	DeleteAnimationData();
}


/*
アニメーションデータを追加する
*/
void Animation::AddAnimationData(ANIMATION_DATA_t animationData) {
	mAnimationDataList.push_back(animationData);
	mAnimationDataList.sort(SortKeyframe);
}

/*
アニメーションデータを削除する
*/
void Animation::DeleteAnimationData(){
	mAnimationDataList.clear();
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

#if 1

	ANIMATION_DATA_t prevKeyframe = {};
	ANIMATION_DATA_t nextKeyframe = {};

	bool isSet = false;

	for (int i = 0; i < mAnimationDataList.size(); i++) {
		ANIMATION_DATA_t  now = *std::next(mAnimationDataList.begin(), i);
		if (mCounter < now.keyframe) {

			int prev = i - 1;
			if (prev < 0) {
				prev = 0;
			}

			prevKeyframe = *std::next(mAnimationDataList.begin(), prev);
			nextKeyframe = now;
			isSet = true;
			break;
		}
	}

	if (isSet == true) {

		float frame = nextKeyframe.keyframe - prevKeyframe.keyframe;

		float posX = nextKeyframe.positionX - prevKeyframe.positionX;
		float posY = nextKeyframe.positionY - prevKeyframe.positionY;
		float alpha = nextKeyframe.alpha - prevKeyframe.alpha;
		float angle = nextKeyframe.angle - prevKeyframe.angle;
		float scale = nextKeyframe.scale - prevKeyframe.scale;

		float deltaFrame = (mCounter + 1) - prevKeyframe.keyframe;

#if false
		//現在の時間の割合
 		float rate = deltaFrame / frame;


float X = prevKeyframe.positionX + posX * rate;
float Y = prevKeyframe.positionY + posY * rate;
float ALPHA = prevKeyframe.alpha + alpha * rate;
float ANGLE = prevKeyframe.angle + angle * rate;
float SCALE = prevKeyframe.scale + scale * rate;
#endif

Easing::eEasingType type = Easing::eEasingType_InOutQuad;

float X = Easing::EasingValue(type, deltaFrame, frame, prevKeyframe.positionX, nextKeyframe.positionX);
float Y = Easing::EasingValue(type, deltaFrame, frame, prevKeyframe.positionY, nextKeyframe.positionY);
float ALPHA = Easing::EasingValue(type, deltaFrame, frame, prevKeyframe.alpha, nextKeyframe.alpha);
float ANGLE = Easing::EasingValue(type, deltaFrame, frame, prevKeyframe.angle, nextKeyframe.angle);
float SCALE = Easing::EasingValue(type, deltaFrame, frame, prevKeyframe.scale, nextKeyframe.scale);

if (mCounter == nextKeyframe.keyframe) {
	if (X != nextKeyframe.positionX) X = nextKeyframe.positionX;
	if (Y != nextKeyframe.positionY) Y = nextKeyframe.positionY;
	if (ALPHA != nextKeyframe.alpha) ALPHA = nextKeyframe.alpha;
	if (ANGLE != nextKeyframe.angle) ANGLE = nextKeyframe.angle;
	if (SCALE != nextKeyframe.scale) SCALE = nextKeyframe.scale;
}

mAnimationValue.positionX = X;
mAnimationValue.positionY = Y;
mAnimationValue.alpha = ALPHA;
mAnimationValue.angle = ANGLE;
mAnimationValue.scale = SCALE;




	}

	if (mCounter >= mTimeLength) {

		this->Stop();
		if (mIsLoop == true) {
			this->Play();
		}
		return true;
	}

	mCounter++;


#else
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
		//memset(&mAnimationValue, 0, sizeof(ANIMATION_DATA_t));
	}

	if (mCounter > nowKeyframe.keyframe) {
		if (mNowFrame + 1 < mAnimationDataList.size()) {
			nextKeyframe = *std::next(mAnimationDataList.begin(), mNowFrame + 1);
			mAnimationValue = GetAnimationDataValue(nowKeyframe, nextKeyframe, &mValue);
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

#endif
return true;
}

void Animation::AnimationAttach(GraphicsDraw* graph, bool isNowBasePos/* = false*/) {
	//if (mIsPlay) {
#if 1
	float posX = 0.0f;
	float posY = 0.0f;
	if (isNowBasePos) {
		if (mBasePositionX == 0.0f) {
			//mBasePositionX = graph->GetPositionX() - mAnimationValue.positionX;
			mBasePositionX = graph->GetBasePositionX() - mAnimationValue.positionX;
		}

		if (mBasePositionY == 0.0f) {
			//mBasePositionY =  graph->GetPositionY() - mAnimationValue.positionY;
			mBasePositionY = graph->GetBasePositionY() -mAnimationValue.positionY;
		}
	
  		posX = mBasePositionX;
		posY = mBasePositionY;
	}
	graph->SetPosition(posX + mAnimationValue.positionX, posY + mAnimationValue.positionY);
	graph->SetAlpha(mAnimationValue.alpha);
	graph->SetScale(mAnimationValue.scale);
	graph->SetAngleRadian(mAnimationValue.angle);
#else
//		CheckVeluesZero();
		if (mCounter == 0) {
			graph->SetPosition(mAnimationValue.positionX, mAnimationValue.positionY);
			//graph->SetAlpha(mAnimationValue.alpha);
			//graph->SetScale(mAnimationValue.scale);
			//graph->SetAngleRadian(mAnimationValue.angle);
		}
		else {
			graph->SetPosition(mAnimationValue.positionX, mAnimationValue.positionY);
			//graph->SetPosition(graph->GetPositionX() + mAnimationValue.positionX, graph->GetPositionY() + mAnimationValue.positionY);
			//graph->SetAlpha((float)graph->GetAlpah() + mAnimationValue.alpha);
			//graph->SetScale(graph->GetScale() + mAnimationValue.scale);
			//graph->SetAngleRadian(graph->GetAngleRadian() + mAnimationValue.angle);
		}
#endif
	//}
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

/*
再生中か?
*/
bool Animation::IsPlay() {

	return mIsPlay;

}

/*
	停止中か
*/
bool Animation::IsStop() {

	//ポーズ中は停止として扱わない
	if (mIsPause) return false;
	return mIsStop;
}

/*
一時中か
*/
bool Animation::IsPause() {
	//停止中はポーズとして扱わない
	if (mIsStop) return false;
	return mIsPause;
}