/*
				ファイル名		:Particle.cpp
				作成者			:
				作成日時		:2019/05/10
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "../Effect.h"
#include "Particle.h"

namespace Effect {
namespace Particle {

	/*
		度数を弧度法にする
	*/
	float _RagAngle( float angle ) {
		const double PI = 3.14159265359;
		return  angle * PI / 180.0f;
	}

	//==========================
	// パーティクル
	//==========================
	EffectParticle::EffectParticle() {
		mAngle = 0;
	}

	EffectParticle::~EffectParticle() {

	}

	void EffectParticle::Init(int emitPosX, int emitPosY, ParticleGenerateData data) {
		
		data.start.posX += emitPosX;
		data.start.posY += emitPosY;
		data.end.posY += emitPosY;
		data.end.posX += emitPosX;

		mData = data;
		
		mAngle = _RagAngle(data.startAngle + 90.0f);
		
		mPositionX = data.start.posX;
		mPositionY = data.start.posY;
		mLifeTime = data.limitTime;
		mPlayTime = 0;
	}

	void EffectParticle::Play() {

	}

	void EffectParticle::Stop() {

	}

	bool EffectParticle::IsPlay() {
		return (mLifeTime > mPlayTime);
	}

	void EffectParticle::LoopOn() {

	}

	void EffectParticle::LoopOff() {

	}

	void EffectParticle::Updata() {

		if (mLifeTime <= mPlayTime) {
			return;
		}
		// 移動処理などを行う
		//float value =  Easing::EasingValue(mData.easingType, 0, 60  + mLifeTime, mData.start.posX, mData.end.posY);
		
		//mPositionX = Easing::EasingValue(mData.easingType, mPlayTime, mLifeTime, mData.start.posX, mData.end.posX);
		//mPositionY = Easing::EasingValue(mData.easingType, mPlayTime, mLifeTime, mData.start.posY, mData.end.posY);
		float speed = mData.startSpeed;
		mPositionX += sin(mAngle) * speed;
		mPositionY += cos(mAngle) * speed;
		mBaseColor.red = Easing::EasingValue(mData.easingType, mPlayTime, mLifeTime, mData.start.baseColor.red, mData.end.baseColor.red);
		mBaseColor.green = Easing::EasingValue(mData.easingType, mPlayTime, mLifeTime, mData.start.baseColor.green, mData.end.baseColor.green);
		mBaseColor.blue = Easing::EasingValue(mData.easingType, mPlayTime, mLifeTime, mData.start.baseColor.blue, mData.end.baseColor.blue);
		mBaseColor.alpha = Easing::EasingValue(mData.easingType, mPlayTime, mLifeTime, mData.start.baseColor.alpha, mData.end.baseColor.alpha);
		mSize = Easing::EasingValue(mData.easingType, mPlayTime, mLifeTime, mData.start.mSize, mData.end.mSize);
		
		mPlayTime++;
	}

	void EffectParticle::Draw() {

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mBaseColor.alpha);
		switch (mData.type) {
		case eFigureType_Circle:
			DrawCircle(mPositionX, mPositionY, mSize, GetColor(mBaseColor.red, mBaseColor.green, mBaseColor.blue), TRUE);
			break;
		case eFigureType_Box:
			
			break;
		case eFigureType_Triangle:

			break;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}

	//==========================
	// エミッター
	//==========================
	ParticleEmmiter::ParticleEmmiter() : mPlayTime(0) {
		
	}
	ParticleEmmiter::~ParticleEmmiter() {
	}

	void ParticleEmmiter::Init(int posX, int posY, ParticleGenerateData data) {
		mPositionX = posX;
		mPositionY = posY;
		mParticle = data;
		isPlay = false;
		mPrio = 0;
		mAngle = 0;
		Play();
	}

	void ParticleEmmiter::Play() {
		isPlay = true;
	}

	void ParticleEmmiter::Stop() {
		isPlay = false;
		mPlayTime = 0;
	}

	void ParticleEmmiter::SetPosition(int posX, int posY) {
		mPositionX = posX;
		mPositionY = posY;
	}

	void ParticleEmmiter::Updata() {

		if (isPlay == false) {
			return;
		}

		if (mPlayTime >= mParticle.genTime) {
			int t = mPlayTime - mParticle.genTime;
			if (t % mParticle.spanGenTime == 0) {
#if 0
				ParticleDrawer* drawer = new ParticleDrawer();
				float addAngle = mParticle.startAngle;
				//パーティクル生成
				EffectParticle* particle = new EffectParticle();
				if (mAngle != 0.0f) {
					if (mAngle < mParticle.angleRangeMin || mAngle > mParticle.angleRangeMax) {
						mAngle = mParticle.angleRangeMin;
					}
					mParticle.startAngle = mAngle;
				}
				mAngle += addAngle;
				particle->Init(mPositionX, mPositionY, mParticle);
				particle->Play();
				drawer->Add(particle);
#else
				ParticleDrawer* drawer = new ParticleDrawer();
				float addAngle = mParticle.startAngle;
				for (int i = 0; i < mParticle.num; i++) {
					//パーティクル生成
					EffectParticle* particle = new EffectParticle();
					if (mAngle != 0.0f) {					
						if (mAngle < mParticle.angleRangeMin || mAngle > mParticle.angleRangeMax) {
							mAngle = mParticle.angleRangeMin;
						}
						mParticle.startAngle = mAngle;
					}
					mAngle += addAngle;
					particle->Init(mPositionX,mPositionY, mParticle);
					particle->Play();
					drawer->Add(particle);
				}
#endif
				GraphicsDrawMgr::GetInstance()->Add(drawer, mPrio);
				mParticle.startAngle = addAngle;
			}
		}

		mPlayTime++;
	}

	//==========================
	// パーティクル描画
	//==========================
	ParticleDrawer::ParticleDrawer() : GraphicsBase(){
		mList.clear();
	}

	ParticleDrawer::~ParticleDrawer() {
		mList.clear();
	}

	void ParticleDrawer::Add(EffectParticle* data) {
		if (data == nullptr) {
			return;
		}
		mList.push_back(data);
	}

	void ParticleDrawer::Draw() {

		int nowPlayCnt = mList.size();
		for (int i = 0; i < mList.size(); i++) {
			//全てのパーティクルの生存時間が終わっていたら削除依頼
			if (mList[i]->IsPlay() == false) {
				nowPlayCnt -- ;
				continue;
			}
			mList[i]->Updata();
			mList[i]->Draw();
		}
		
		if (nowPlayCnt <= 0) {
			ReleseRequest();
		}
	}

}	//Particle 
}	//Effect


