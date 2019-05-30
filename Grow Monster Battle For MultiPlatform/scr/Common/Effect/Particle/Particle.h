/*
				ファイル名		:Particle.h
				作成者			:
				作成日時		:2019/05/10
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Common/Animation/Easing/Easing.h"
#include "Common/Graphics/GraphicsBase.h"

#include <vector>

namespace Effect {
namespace Particle {

	enum eFigureType {
		eFigureType_Circle,		// 円
		eFigureType_Box,		// 四角
		eFigureType_Triangle,	// 三角
	};

	struct particleColor {
		int red;
		int green;
		int blue;
		int alpha;
	};

	struct ParticleData {
		float posX;
		float posY;
		particleColor baseColor;		//色彩 RGBA
		particleColor brightColor;	//輝度 RGB
		float mSize;
		int imageHandle;
	};

	struct ParticleGenerateData {
		int num;						// パーティクルの数
		int genTime;					// 生成する時間
		int spanGenTime;				// 生成する間隔
		eFigureType type;				// 形状種類
		ParticleData start;
		ParticleData end;
		Easing::eEasingType easingType; // 補完
		float angleRangeMin;// 角度範囲(最小)
		float angleRangeMax;// 角度範囲(最大)
		float startAngle;	// 最初の角度
		int limitTime;		// 生存時間
		float startSpeed;		// 最初の移動速度
	};

	/*
		パーティクル
	*/
	class EffectParticle {

	private:

		ParticleData mStart;
		ParticleData mEnd;
		ParticleGenerateData mData;
		int mLifeTime;	//	生存時間
		int mPlayTime;	// 経過時間
		
		
		float mPositionX;	// 座標
		float mPositionY;
		float mAlpha;
		particleColor mBaseColor;
		float mAngle;		// 角度

		float mSize;

		float variationRangeMin;	// 
		float variationRangeMax;

	public:

		EffectParticle();
		~EffectParticle();

		void Init(int emitPosX, int emitPosY, ParticleGenerateData data);

		void Play();
		bool IsPlay();

		void Stop();
		void LoopOn();
		void LoopOff();

		void Updata();
		void Draw();

	};

	/*
		エミッター
	*/
	class ParticleEmmiter {

	private:

		ParticleGenerateData mParticle;

		int mPositionX;
		int mPositionY;
		int mPlayTime;
		bool isPlay;
		int mPrio;
		int mAngle;

	public:

		ParticleEmmiter();
		~ParticleEmmiter();

		void Init(int posX, int posY, ParticleGenerateData data);

		void Play();
		void Stop();

		void SetPosition(int posX, int posY);

		void Updata();

	};


	class ParticleDrawer : public GraphicsBase {

	private:

		std::vector<EffectParticle*> mList;

	public:
		
		ParticleDrawer();
		~ParticleDrawer();
		
		void Add(EffectParticle* data);
		void Draw() override;

		void Draw(int posX, int posY, int alpha, double angle, double scale) override {};
		void Relese() override {};
		bool Load(const char* path) override { return false; }

	};



}	//Effect
}	//Particle


#endif // __PARTICLE_H__