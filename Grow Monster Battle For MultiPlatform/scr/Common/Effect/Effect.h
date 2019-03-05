/*
				ファイル名		:Effect.h
				作成者			:
				作成日時		:2018/01/16
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __EFFECT_H__
#define __EFFECT_H__

#ifdef ENABLE_EFFEKSEER

#include <map>
#include <string>

#include "Common/Graphics/GraphicsBase.h"
namespace EffekseerEffect {

	struct EFFECT_DATA {
		int handle;
		std::string fileName;
	};

	class EffectLoader {

	private:


		std::map<int, EFFECT_DATA> mLoaderList;

		static EffectLoader* mInstance;

		EffectLoader();
		~EffectLoader();

	public :

		static void Create();
		static void Destroy();

		static EffectLoader* Instance();

		/*
			読み込み
			int key					: 識別番号
			std::string fileName	: ファイル名
			return	true	: 成功
					false	: 失敗
		*/
		bool Load(int key ,std::string fileName);

		/*
			削除
			int key	: 識別番号
		*/
		void Release(int key);
		void ReleaseAll();

		/*
			取得
		*/
		int Get(int key);

	};

	enum class ePlayMode {
		Play2D,
		Play3D,
		Default = Play2D,
	};

	struct EffectPlayData {

		ePlayMode playMode;
		int playHandle;
		int effecthandle;

	};

	class EffectManual;
	class Effect : public GraphicsBase {

	private:

		static int mOrder;
		static Effect* mInstance;

		Effect();
		~Effect();

	public:

		static void Create();
		static void Destroy();

		static Effect* Instance();

		bool Load(const char* fileName) override;

		void Draw(int posX, int posY, int alpha, double angle, double scale) override ;
		void Draw() override ;
		void Relese() override ;

		void Play(EffectPlayData* src, int handle,ePlayMode mode = ePlayMode::Default);

		EffectManual* Manual_Play(int handle, ePlayMode mode = ePlayMode::Default);
		void Manual_Play(EffectManual* effect);
		void Manual_Stop(EffectManual* effect);

		void Stop(const EffectPlayData& src);
		void StopAll();

		void SetPosition(const EffectPlayData& src, float x, float y, float z);
		void SetRotation(const EffectPlayData& src, float x, float y, float z);
		void SetScale(const EffectPlayData& src, float x, float y, float z);

	};

	/*
		任意の描画タイミングでエフェクトを再生する
	*/
	class EffectManual : public GraphicsBase {

	private :

		EffectPlayData mSrc;

	protected:

		EffectManual() : GraphicsBase(){};
		

	public :
		
		~EffectManual() {};

		friend class Effect;

		bool Load(const char* fileName) override { return true; };

		void Draw(int posX, int posY, int alpha, double angle, double scale) override {};
		void Draw() override;
		void Relese() override;

		EffectPlayData GetEffectPlayData() { return mSrc; }
		void SetEffectPlayData(EffectPlayData data) { mSrc = data; }

	};


};

#endif	// ENABLE_EFFEKSEER

#endif // __EFFECT_H__