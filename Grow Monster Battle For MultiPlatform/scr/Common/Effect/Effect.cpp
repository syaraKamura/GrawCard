/*
				ファイル名		:Effect.cpp
				作成者			:
				作成日時		:2018/01/16
				ソース説明		:
				
				
				備考
				
				
				
!*/


#include "Effect.h"

#ifdef ENABLE_EFFEKSEER

#include "EffekseerForDXLib.h"
#include "Common/GameCommon.h"

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

#else

#include "Common/GameCommon.h"

namespace Effect{

	EffectMgr*	EffectMgr::mInstance = nullptr;

	int EffectLoader::LoadResource(std::string fileName) {

		char path[2048];
		//ファイル名取得
		strcpyDx(path, fileName.c_str());

#ifdef __WINDOWS__ 
#ifdef  __MY_DEBUG__

		RESORCES_PATH(path);

#endif	
#endif

		int check = FileRead_open(path);
		if (check == 0) {
			return -1;
		}
		FileRead_close(check);

		int handle = LoadGraph(path);
		if (handle == -1) {
			return 0;
		}

		return handle;
	}

	void EffectLoader::DestoryResource(int handle) {
		DeleteGraph(handle);
	}

	//===========================================
	//	EffectPlayer
	//===========================================

	EffectPlayer::~EffectPlayer() {
		Delete(mPlayData);
	}

	void EffectPlayer::Init(EffectData eft, bool IsPlayManual /*= false*/, int startPosX/* = 0*/, int startPosY/* = 0*/) {

		if (mPlayData == nullptr) {
			mPlayData = new EffectPlayData();
		}
		mHandle = eft.mHandle;
		mIsPlayManual = IsPlayManual;
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

		if (eft.sound.se != nullptr) {
			mPlayData->SEPlayTime = eft.sound.delayTime;
			mSE = new Sound(*eft.sound.se);
		}

	}

	void EffectPlayer::Play() {
		mPlayData->isPlay = true;
	}

	void EffectPlayer::Stop() {
		mPlayData->isPlay = false;
		mPlayData->playTime = 0;
	}

	void EffectPlayer::LoopOn() {
		mPlayData->isLoop = true;
	}

	void EffectPlayer::LoopOff() {
		mPlayData->isLoop = false;
	}

	int EffectPlayer::Length() {
		return mPlayData->length;
	}

	bool EffectPlayer::IsPlayManual() {
		return mIsPlayManual;
	}

	void EffectPlayer::Update() {

		if (mPlayData->isPlay == false) return;
		if (mPlayData->length > mPlayData->playTime) {

			if (mSE != nullptr) {
				if (mPlayData->SEPlayTime == mPlayData->playTime) {
					mSE->Play(Sound::ePlayType_BackGround);
				}
			}

			mPlayData->playTime++;
		}
		else {
			
			Stop();
			if (mPlayData->isLoop == true) {
				Play();
			}
		}

	}

	void EffectPlayer::Draw() {

		if (mPlayData->isPlay == false) return;
		EffectPlayData::RECT rect = {};
		if (mPlayData->rectList.size() > mPlayData->playTime ) {
			rect = mPlayData->rectList[mPlayData->playTime];
		}

#ifdef __WINDOWS__
		DxLib::DrawRectGraph(mPlayData->posX,mPlayData->posY,rect.posX, rect.posY, rect.width, rect.heigth, mHandle, TRUE);
#elif __ANDROID__
		DxLib::DrawRectGraph(mPlayData->posX, mPlayData->posY, rect.posX, rect.posY, rect.width, rect.heigth, mHandle, TRUE, FALSE);
#endif
		
	}

	//==================================
	// EffectMgr
	//==================================

	EffectData EffectMgr::_GetEffectData(int handle) {
		EffectData data = {};
		for (int i = 0; i < GetEffectDataNum(); i++) {
			GetEffectData(i, &data);
			if (data.id == handle) {
				return data;
			}
		}
		return data;
	}

	EffectMgr::EffectMgr() {
		mList.clear();
		mManualList.clear();
		mEffectGraphList.clear();
		mLoadOrder = 0;
	}

	EffectMgr::~EffectMgr() {

		AllRelease();
		mEffectGraphList.clear();
		mList.clear();
		mManualList.clear();
	}

	void EffectMgr::Create() {
		if (mInstance == nullptr) {
			mInstance = new EffectMgr();
		}
	}

	void EffectMgr::Destroy() {
		Delete(mInstance);
	}
	
	EffectPlayData* EffectMgr::Play(int handle) {
		return Play(handle, 0, 0);
	}

	EffectPlayData* EffectMgr::Play(int handle, float posX, float posY, int prio/* = 1000*/) {
		EffectData data = _GetEffectData(handle);
		EffectPlayer* add = new EffectPlayer();
		add->Init(data, false, posX, posY);
		add->Play();
		GraphicsDrawMgr::GetInstance()->Add(add, prio);
		mList.push_back(add);
		return add->GetPlayData();
	}

	/*
			エフェクトを再生する(描画は手動)
			int handle	:	再生するエフェクトハンドル
			float posX	:	描画座標
			float posY	:
			return		:	エフェクトデータ
		*/
	EffectPlayData* EffectMgr::PlayManual(int handle, float posX, float posY) {
		EffectData data = _GetEffectData(handle);
		EffectPlayer* add = new EffectPlayer();
		add->Init(data, true, posX, posY);
		add->Play();
		mManualList.push_back(add);
		return add->GetPlayData();
	}

	void EffectMgr::ManualUpdate() {

		for (int i = 0; i < mManualList.size(); i++) {
			EffectPlayer* eft = mManualList[i];
			if (eft == nullptr) {
				continue;
			}
			if (eft->GetPlayData()->isPlay == false) {
				eft->ReleseRequest();	//	描画マネージャーから削除
				mManualList.erase(mManualList.begin() + i);
				i--;
				continue;
			}
			eft->Update();
		}
	}

	void EffectMgr::ManualDraw() {
		for (int i = 0; i < mManualList.size(); i++) {
			EffectPlayer* eft = mManualList[i];
			if (eft == nullptr) {
				continue;
			}
			eft->Draw();
		}
	}

	void EffectMgr::Update() {

		for (int i = 0; i < mList.size(); i++) {
			EffectPlayer* eft = mList[i];
			if (eft == nullptr) {
				continue;
			}
			if (eft->GetPlayData()->isPlay == false) {
				eft->ReleseRequest();	//	描画マネージャーから削除
				mList.erase(mList.begin() + i);
				i--;
				continue;
			}
			eft->Update();
		}
		
	}

	void EffectMgr::Draw() {

		for (int i = 0; i < mList.size(); i++) {
			EffectPlayer* eft = mList[i];
			if (eft == nullptr) {
				continue;
			}
			eft->Draw();
		}

	}

	int EffectMgr::Load(std::string fileName, int divWidth, int divHeight) {

		int handle = 0;
		if (mLoader.LoadASync(fileName, &handle) == false) {
			return -1;
		}

		EffectData add = {};
		int width = 0;
		int height = 0;
		handle = mLoader.Get(fileName);
		GetGraphSize(handle, &width, &height);
		add.wdith = width;
		add.height = height;
		add.DivWidth = divWidth;
		add.DivHeight = divHeight;
		strcpyDx(add.path, fileName.c_str());
		add.id = ++mLoadOrder;
		add.mHandle = handle;
		add.divXNum = add.wdith / divWidth;
		add.divYNum = add.height / divHeight;

		mEffectGraphList.push_back(add);

		return add.id;
	}

	bool EffectMgr::LoadSE(std::string fileName, int attachHandle, int delayTime/* = 0*/) {
		EffectData data = {};
		int num = -1;
		for (int i = 0; i < GetEffectDataNum(); i++) {
			GetEffectData(i, &data);
			if (data.id == attachHandle) {
				num = i;
			}
		}
		
		// アタッチ対象がなかった
		if (num == -1) {
			return false;
		}

		EffectData& eft = mEffectGraphList[num];
		eft.sound.se = new Sound();
		Sound& se = *eft.sound.se;
		if (se.Load(fileName.c_str()) == false) {
			return false;
		}
		eft.sound.delayTime = delayTime;
		return true;
	}

	void EffectMgr::Release(int handle) {
		EffectData data = {};
		for (int i = 0; i < GetEffectDataNum(); i++) {
			GetEffectData(i, &data);
			if (data.id == handle) {
				mLoader.Destory(data.path);

				if (data.sound.se != nullptr) {
					data.sound.se->Release();
					Delete(data.sound.se);
				}

				mEffectGraphList.erase(mEffectGraphList.begin() + i);
				break;
			}
		}
	}

	void EffectMgr::AllRelease() {
		for (int i = 0; i < GetEffectDataNum(); i++) {
			if (mEffectGraphList[i].sound.se != nullptr) {
				mEffectGraphList[i].sound.se->Release();
				Delete(mEffectGraphList[i].sound.se);
			}
			mLoader.Destory(mEffectGraphList[i].path);
		}
	}

	int EffectMgr::GetEffectDataNum() {
		return mEffectGraphList.size();
	}

	void EffectMgr::GetEffectData(int idx,EffectData* pOutData) {
		if (idx < 0 || GetEffectDataNum() < idx) {
			return;
		}
		*pOutData = mEffectGraphList[idx];
	}
		

}

#endif	// ENABLE_EFFEKSEER