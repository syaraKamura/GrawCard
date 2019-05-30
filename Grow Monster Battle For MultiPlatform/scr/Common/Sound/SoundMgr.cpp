/*
				ファイル名		:SoundMgr.h
				作成者			:
				作成日時		:2018/11/17
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Sound.h"
#include "SoundMgr.h"

SoundMgr* SoundMgr::mInstance = NULL;

SoundMgr::SoundMgr() {
	mSoundData.clear();
	mIsCrossFade = false;
	mNowSoundId = "";
	mNextSoundId = "";
}

SoundMgr::~SoundMgr() {
	// サウンドデータを削除
	for (auto itr = mSoundData.begin(); itr != mSoundData.end();) {

#ifdef __MY_DEBUG__
		Debug::LogPrintf("==== Sound List Remove ====\n");
		Debug::LogPrintf("%s\n",itr->first.c_str());
#endif // __MY_DEBUG__

		itr->second->Release();
		Delete(itr->second);
		mSoundData.erase(itr);
		itr = mSoundData.begin();
	}
}

/*
	サウンドデータを探す
	return NULL	:サウンドデータがない
*/
Sound* SoundMgr::SarchSoundData(std::string soundId) const {
	// C++11以降でのみ使用できる機能.
	try {
		Sound* ret = mSoundData.at(soundId);
		return (ret ? new Sound(*ret) : nullptr);
	}
	catch (std::out_of_range) {
		return NULL;
	}
}

/*
	サウンドタイプを返却する
*/
Sound::ePlayType SoundMgr::PlayType(SoundMgr::ePlayType playType) {

	Sound::ePlayType type = Sound::ePlayType_BackGround;
	switch (playType) {
	case SoundMgr::ePlayType_Loop:
		type = Sound::ePlayType_Loop;
		break;
	}

	return type;

}

/*
	生成
*/
void SoundMgr::Create() {
	mInstance = new SoundMgr();
}

/*
	削除
*/
void SoundMgr::Destroy() {
	Delete(mInstance);
}

/*
	サウンドを追加
	std::string soundId		: サウンド識別用ID（固有でなければならない）
	std::string soundPath	: サウンドデータパス
	int volume = 255		: 再生時の音量
	return	true	:追加に成功
			false	:追加に失敗
*/
bool SoundMgr::Add(std::string soundId, std::string soundPath,int volume /*= 255*/) {

	Sound* add = new Sound();
	if (add->Load(soundPath.c_str(), volume) == false) {
		Debug::ErorrMessage("登録に失敗しました.\n%s",soundId.c_str());
		return false;
	}
	
	mSoundData.insert(std::make_pair(soundId, add));

#ifdef __MY_DEBUG__

	Debug::LogPrintf("===== Sound List =====\n");

	for (auto itr = mSoundData.begin(); itr != mSoundData.end(); itr++) {
		Debug::LogPrintf("%s\n", itr->first.c_str());
	}


#endif	// __MY_DEBUG__

	return true;
}

/*
	サウンドデータを削除
	std::string soundId		: サウンド識別用ID
*/
bool SoundMgr::Remove(std::string soundId) {
	Sound* sound  = SarchSoundData(soundId);
	if (sound == nullptr) return false;
	sound->Release();
	mSoundData.erase(soundId);

	if (mNowSoundId == soundId) {
		mNowSoundId = "";
	}

#ifdef __MY_DEBUG__

	Debug::LogPrintf("===== Sound List =====\n");

	for (auto itr = mSoundData.begin(); itr != mSoundData.end(); itr++) {
		Debug::LogPrintf("%s\n", itr->first.c_str());
	}

#endif	// __MY_DEBUG__

	return true;
}

/*
	再生
	std::string soundId							: サウンド識別用ID
	ePlayType playType = ePlayType_BackGround	: 再生方法
*/
void SoundMgr::Play(std::string soundId, ePlayType playType/* = ePlayType_BackGround*/) {

	// 次に再生しようとしているサウンド または 現在再生中のサウンドなら設定をしない
	if (mNextSoundId == soundId || mNowSoundId == soundId) return;

	mPlayType = playType;
	mNextSoundId = soundId;
	mIsCrossFade = false;
}

/*
	ワンショット再生
	std::string soundId							: サウンド識別用ID
*/
void SoundMgr::PlayOnShot(std::string soundId) {
	Sound* sound = SarchSoundData(soundId);
	if (sound == nullptr) {
		Debug::ErorrMessage("サウンドIDが見つかりませんでした.(%s)",soundId.c_str());
		return;
	}
	sound->Play(Sound::ePlayType_BackGround);
}

/*
	停止
	std::string soundId		: サウンド識別用ID
*/
void SoundMgr::Stop(std::string soundId) {
	if (mIsCrossFade == true) return;
	Sound* nowSound = SarchSoundData(soundId);
	if (nowSound == nullptr) return ;
	nowSound->Stop();
	if (soundId == mNowSoundId) {
		mNowSoundId = "";
	}
}

/*
	現在再生中のサウンドを停止する
*/
void SoundMgr::Stop() {
	Sound* nowSound = SarchSoundData(mNowSoundId);
	if (nowSound == nullptr) return;
	nowSound->Stop();
	mNowSoundId = "";

	Sound* nextSound = SarchSoundData(mNextSoundId);
	if (nextSound == nullptr) return;
	nextSound->Stop();
	mNextSoundId = "";
}

/*
	黒フェードしながら再生を始める
	std::string nextSoundId						: 次に再生するサウンド識別ID
	int frameTiem								: クロスフェードにかかる時間
	ePlayType playType = ePlayType_BackGround	: 再生方法
*/
void SoundMgr::CroosFadePlay(std::string nextSoundId, int frameTime, ePlayType playType/* = ePlayType_BackGround*/) {

	if (mNextSoundId.empty() == false) {
		//Debug::LogPrintf("すでに次に再生するサウンドの識別IDが設定されています.\n%s",mNextSoundId.c_str());
		mNowSoundId = mNextSoundId;
		mNextSoundId = "";
		//return;
	}
	else {
		mCrossFadeCount = 0;
	}

	mPlayType = playType;
	mNextSoundId = nextSoundId;
	mCrossFadeTime = frameTime;
	mIsCrossFade = true;
}

/*
	現在再生しているサウンド識別IDを返却する
*/
std::string& SoundMgr::GetPlaySoundId() {
	return mNowSoundId;
}

/*
	更新
*/
bool SoundMgr::Updata() {

	if (mNextSoundId.empty()) return true;

	Sound* nowSound = SarchSoundData(mNowSoundId);
	Sound* nextSound = SarchSoundData(mNextSoundId);
	
	if (nextSound == nullptr) {
		Debug::ErorrMessage("指定されたサウンド識別IDが存在していません%s", mNextSoundId.c_str());
		return true;
	}

	if (mIsCrossFade) {

		float volumRange = (float)mCrossFadeCount / (float)mCrossFadeTime;

		if (mCrossFadeCount == 0) {
			if (nowSound != nullptr) {
				mNowSoundVolume = nowSound->GetVolume();
			}
			mNextSoundVolume = nextSound->GetVolume();
			nextSound->Play(PlayType(mPlayType));
		}

		float volume = (1.0f - volumRange) * (float)mNowSoundVolume;
		
		if (nowSound != nullptr) {
			nowSound->ChangeVolume(volume);
		}

		volume = volumRange * (float)mNextSoundVolume;
		nextSound->ChangeVolume(volume);

		mCrossFadeCount++;
		if (mCrossFadeCount > mCrossFadeTime) {
			mIsCrossFade = false;
			
			if (nowSound != nullptr) {
				nowSound->Stop();
				nowSound->ChangeVolume(mNowSoundVolume);
			}

			mNowSoundId = mNextSoundId;
			mNextSoundId = "";
		}

	}
	else {
		if (nowSound != nullptr) {
			nowSound->Stop();
		}
		
		nextSound->Play(PlayType(mPlayType));
		mNowSoundId = mNextSoundId;
		mNextSoundId = "";
	}



	return true;
}

/*
	インスタンスを返却する
*/
SoundMgr* SoundMgr::GetInstance() {

	if (mInstance == nullptr) {
		Create();
	}
	return mInstance;
}


