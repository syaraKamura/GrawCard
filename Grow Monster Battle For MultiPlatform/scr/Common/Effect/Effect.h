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


#else

#include "Common/ResourceLoader/ResourceLoader.h"
#include "Common/Graphics/GraphicsBase.h"
#include <vector>

class Sound;

namespace Effect {

	struct EffectSE {
		Sound* se;
		int delayTime;	// 再生開始時間
	};

	struct EffectData{
		int id;
		int mHandle;
		int wdith;			//画像サイズ
		int height;
		int DivWidth;		//分割サイズ
		int DivHeight;
		int divXNum;		//分割枚数
		int divYNum;
		char path[2048];
		EffectSE sound;
	};

	struct EffectPlayData{
		int id;					//識別ID
		float posX;				//座標
		float posY;
		int length;				//再生の長さ
		int playTime;			//再生時間
		bool isPlay;			//再生中か
		bool isLoop;			// ループするか	
		
		int SEPlayTime;			// 効果音再生時間

		struct RECT {
			int posX;
			int posY;
			int width;
			int heigth;
		};

		std::vector<RECT> rectList;

		void Init() {
			id = 0;
			posX = 0;
			posY = 0;
			length = 60;
			playTime = 0;
			isPlay = false;
			isLoop = false;
		}

	};
		
	class EffectPlayer : public GraphicsBase {
	private:
		
		EffectPlayData* mPlayData;
		Sound* mSE;
		int mHandle;
		bool mIsPlayManual;

	public :

		EffectPlayer() : GraphicsBase(){
			mPlayData = new EffectPlayData();
			mHandle = 0;
			mPlayData->Init();
			mSE = nullptr;
			mIsPlayManual = false;
		};
#if 0
		EffectPlayer(EffectData eft,int startPosX = 0,int startPosY = 0) : GraphicsBase(),mPlayData(new EffectPlayData()), mHandle(eft.mHandle){
			mPlayData->Init();

			mPlayData->posX = startPosX;
			mPlayData->posY = startPosY;

			for (int y = 0; y < eft.divYNum; y++) {
				for (int x = 0; x < eft.divXNum; x++) {
					EffectPlayData::RECT rect;
					rect.posX = x * eft.DivWidth;
					rect.posY = y * eft.DivHeight;
					rect.width = x + eft.DivWidth;
					rect.heigth = y + eft.DivHeight;
					mPlayData->rectList.push_back(rect);
				}
			}

			mPlayData->length = eft.divXNum * eft.divYNum;

		}
#endif
		~EffectPlayer();

		void Init(EffectData eft,bool IsPlayManual = false, int startPosX = 0, int startPosY = 0);

		void Play();
		void Stop();
		void LoopOn();
		void LoopOff();

		int Length();

		void Update();
		void Draw() override;

		bool IsPlayManual();

		/*
			未定義
		*/
		void Draw(int posX, int posY, int alpha, double angle, double scale) override {}
		void Relese() override {}
		bool Load(const char* path) override { return false; }

		EffectPlayData* GetPlayData() const {
			return mPlayData;
		}

	};

	class EffectLoader: public ResourceLoader {

	private:
		
	protected:

		int LoadResource(std::string fileName) override;
		void DestoryResource(int handle) override;

	public:

	};

	class EffectMgr {

	private:

		struct REQUEST {
			int handle;
			std::string path;
			int width;
			int height;
		};

		std::vector<REQUEST> mLoadRequestList;

	private:

		int mLoadOrder;
		EffectLoader mLoader;

		std::vector<EffectData> mEffectGraphList;

		std::vector<EffectPlayer*> mList;

		// マニュアル再生用
		std::vector<EffectPlayer*> mManualList;

		static EffectMgr* mInstance;

		EffectMgr();

		EffectData _GetEffectData(int handle);

	public :

		~EffectMgr();

		/*
			インスタンス作成
		*/
		static void Create();
		/*
			インスタンス削除
		*/
		static void Destroy();
		static EffectMgr* GetInstance() {
			if (mInstance == nullptr) {
				Create();
			}
			return mInstance;
		}

		/*
			int handle	:	再生するエフェクトハンドル
			return		:	エフェクトデータ
		*/
		EffectPlayData* Play(int handle);
		/*
			エフェクトを再生する
			int handle	:	再生するエフェクトハンドル
			float posX	:	描画座標
			float posY	:
			int prio	:	描画優先度
			return		:	エフェクトデータ
		*/
		EffectPlayData* Play(int handle,float posX,float posY,int prio = 1000);

		/*
			エフェクトを再生する(描画は手動)
			int handle	:	再生するエフェクトハンドル
			float posX	:	描画座標
			float posY	:
			return		:	エフェクトデータ
		*/
		EffectPlayData* PlayManual(int handle, float posX, float posY);

		/*
			エフェクト画像読み込み
			std::string fileName	: ファイルパス
			int divWidth			: 分割サイズ
			int divHeight			:
				return -1		: 失敗　
						0以上	: 成功
		*/
		int Load(std::string fileName, int divWidth, int divHeight);
		/*
			SEを読み込む
			std::string fileName	: ファイルパス
			int attachHandle		: アタッチするエフェクト
			int delayTime			: 再生開始時間
			reutrn			true	: 成功
							false	: 失敗
		*/
		bool LoadSE(std::string fileName,int attachHandle,int delayTime = 0);

		/*
			指定のエフェクト画像削除
		*/
		void Release(int handle);
		/*
			すべてのエフェクト画像を削除する
		*/
		void AllRelease();

		void ManualUpdate();
		void ManualDraw();

		void Update();
		void Draw();

		int GetEffectDataNum();
		void GetEffectData(int idx, EffectData* pOutData);

	};


}

#endif	// ENABLE_EFFEKSEER

#endif // __EFFECT_H__