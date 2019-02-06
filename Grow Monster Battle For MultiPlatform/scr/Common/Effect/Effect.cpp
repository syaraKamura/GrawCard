/*
				ファイル名		:Effect.cpp
				作成者			:
				作成日時		:2018/01/16
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "EffekseerForDXLib.h"

#include "Common/GameCommon.h"
#include "Effect.h"

namespace EffekseerEffect {

	//============================================
	// EffectLoaderクラス
	//============================================

	EffectLoader* EffectLoader::mInstance = nullptr;

	EffectLoader::EffectLoader() {

	}

	EffectLoader::~EffectLoader() {
		ReleaseAll();
	}


	void EffectLoader::Create() {
		if (mInstance == nullptr) {
			mInstance = new EffectLoader();
		}
	}

	void EffectLoader::Destroy() {
		Delete(mInstance);
	}

	EffectLoader* EffectLoader::Instance() {
		return mInstance;
	}

	/*
		読み込み
		int key					: 識別番号
		std::string fileName	: ファイル名
		return	true	: 成功
				false	: 失敗
	*/
	bool EffectLoader::Load(int key, std::string fileName) {
		
		if (mLoaderList.count(key) != 0) {
			Debug::LogPrintf("エフェクトの読み込みに失敗しました.(%s)\n", fileName.c_str());
			Debug::LogPrintf("すでに同じキーが設定されています.(%d)\n",key);
			return false;
		}

		int handle = 0;

#ifdef __WINDOWS__ 
#ifdef  __MY_DEBUG__

		char path[1024];

		strcpyDx(path, fileName.c_str());
		RESORCES_PATH(path);

		handle = LoadEffekseerEffect(path);

		fileName = path;

#else
		handle = LoadEffekseerEffect(fileName.c_str());
#endif	
#endif

		if (handle == -1) {
			Debug::LogPrintf("エフェクトの読み込みに失敗しました.(%s)\n", fileName.c_str());
			return false;
		}

		EFFECT_DATA data;
		data.fileName = fileName;
		data.handle = handle;

		mLoaderList.insert(std::pair<int, EFFECT_DATA>(key,data));

		return true;
	}

	/*
		削除
		int key	: 識別番号
	*/
	void EffectLoader::Release(int key) {

		// キーが存在しているか判断する
		if (mLoaderList.count(key) != 0) {
			return ;
		}

		DeleteEffekseerEffect(mLoaderList[key].handle);
		mLoaderList.erase(key);

	}

	void EffectLoader::ReleaseAll() {

		for (auto itr = mLoaderList.begin(); itr != mLoaderList.end(); itr++) {
			DeleteEffekseerEffect(itr->second.handle);
		}

		mLoaderList.clear();

	}

	/*
		取得
	*/
	int EffectLoader::Get(int key) {

		try {
			return mLoaderList.at(key).handle;
		}
		catch (std::out_of_range&) {
			return -1;
		}

		return -1;
	}


	//============================================
	// Effectクラス
	//============================================

	int Effect::mOrder = -1;
	Effect* Effect::mInstance = nullptr;

	Effect::Effect() : GraphicsBase() {

		if (Effkseer_Init(8000) == -1) {
			Debug::ErorrMessage("Effekseerの初期化に失敗しました");
		}

		// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
		// Effekseerを使用する場合は必ず設定する。
		SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

		// DXライブラリのデバイスロストした時のコールバックを設定する。
		// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
		// ただし、DirectX11を使用する場合は実行する必要はない。
		Effekseer_SetGraphicsDeviceLostCallbackFunctions();

		// Effekseerに2D描画の設定をする。
		Effekseer_Set2DSetting(WINDOW_WIDTH, WINDOW_HEIGHT);

		// Zバッファを有効にする。
		// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
		SetUseZBuffer3D(TRUE);

		// Zバッファへの書き込みを有効にする。
		// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
		SetWriteZBuffer3D(TRUE);

		mOrder = GraphicsDrawMgr::GetInstance()->Add(this, 1);
	}
	
	Effect::~Effect() {
		Effkseer_End();
	}


	void Effect::Create() {
		if (mInstance == nullptr) {
			mInstance = new Effect();
		}
	}
	void Effect::Destroy() {
		GraphicsDrawMgr::GetInstance()->Remove(mOrder);
		Delete(mInstance);
	}

	Effect* Effect::Instance() {
		return mInstance;
	}

	bool Effect::Load(const char* fileName) {
		return true;
	}

	void Effect::Draw(int posX, int posY, int alpha, double angle, double scale) {
	
	
	}

	void Effect::Draw(){
		
		// DXライブラリのカメラとEffekseerのカメラを同期する。
		Effekseer_Sync3DSetting();

		UpdateEffekseer2D();
		UpdateEffekseer3D();

		DrawEffekseer2D();
		DrawEffekseer3D();

		RefreshDxLibDirect3DSetting();

	}

	void Effect::Relese() {

	}

	void Effect::Play(EffectPlayData* src, int handle, ePlayMode mode/* = ePlayMode::Default*/) {

		if (src == nullptr) {
			Debug::ErorrMessage("EffectPlayData が「nullptr」です.");
			return;
		}

		EffectPlayData eft;

		eft.playMode = mode;
		eft.effecthandle = handle;

		switch (mode) {
		case ePlayMode::Play2D:
			eft.playHandle = PlayEffekseer2DEffect(handle);
			break;
		case ePlayMode::Play3D:
			eft.playHandle = PlayEffekseer3DEffect(handle);
			break;
		}

		src->effecthandle = eft.effecthandle;
		src->playHandle = eft.playHandle;
		src->playMode = eft.playMode;

	}

	EffectManual* Effect::Manual_Play(int handle, ePlayMode mode/* = ePlayMode::Default*/) {
		EffectManual* effectManual = new EffectManual();
		EffectPlayData data;
		Play(&data, handle, mode);
		effectManual->SetEffectPlayData(data);
		return effectManual;
	}

	void Effect::Manual_Play(EffectManual* effect) {
		EffectPlayData data = effect->GetEffectPlayData();
		Play(&data, data.effecthandle, data.playMode);
	}

	void Effect::Manual_Stop(EffectManual* effect) {
		Stop(effect->GetEffectPlayData());
	}


	void Effect::Stop(const EffectPlayData& src) {

		switch (src.playMode) {
		case ePlayMode::Play2D:
			StopEffekseer2DEffect(src.playHandle);
			break;
		case ePlayMode::Play3D:
			StopEffekseer3DEffect(src.playHandle);
			break;
		}

	}

	void Effect::StopAll() {
		if (GetEffekseer2DManager() == NULL || GetEffekseer3DManager() == NULL) return;
		GetEffekseer2DManager()->StopAllEffects();
		GetEffekseer3DManager()->StopAllEffects();
	}

	void Effect::SetPosition(const EffectPlayData& src, float x, float y, float z) {
		
		switch (src.playMode) {
		case ePlayMode::Play2D:
			SetPosPlayingEffekseer2DEffect(src.playHandle,x,y,z);
			break;
		case ePlayMode::Play3D:
			SetPosPlayingEffekseer3DEffect(src.playHandle, x, y, z);
			break;
		}

	}

	void Effect::SetRotation(const EffectPlayData& src, float x, float y, float z) {

		switch (src.playMode) {
		case ePlayMode::Play2D:
			SetRotationPlayingEffekseer2DEffect(src.playHandle, x, y, z);
			break;
		case ePlayMode::Play3D:
			SetRotationPlayingEffekseer3DEffect(src.playHandle, x, y, z);
			break;
		}

	}

	void Effect::SetScale(const EffectPlayData& src, float x, float y, float z) {

		switch (src.playMode) {
		case ePlayMode::Play2D:
			SetScalePlayingEffekseer2DEffect(src.playHandle, x, y, z);
			break;
		case ePlayMode::Play3D:
			SetScalePlayingEffekseer3DEffect(src.playHandle, x, y, z);
			break;
		}

	}

	//============================================
	// EffectManualクラス
	//============================================
	
	void EffectManual::Draw() {

		if (mSrc.playMode == ePlayMode::Play2D) {
			DrawEffekseer2D_Begin();
			DrawEffekseer2D_Draw(mSrc.playHandle);
			DrawEffekseer2D_End();
		}
		else {
			DrawEffekseer3D_Begin();
			DrawEffekseer3D_Draw(mSrc.playHandle);
			DrawEffekseer3D_End();
		}

	}

	void EffectManual::Relese() {
		Effect::Instance()->Manual_Stop(this);
	}

}