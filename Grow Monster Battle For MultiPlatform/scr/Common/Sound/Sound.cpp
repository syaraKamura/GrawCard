/*
				ファイル名		:Sound.cpp
				作成者			:
				作成日時		:2018/11/16
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Sound.h"
#include "Common/GameCommon.h"

int Sound::LoadResource(std::string fileName) {

	strcpyDx(mFilePath,fileName.c_str());

#ifdef __MY_DEBUG__
#ifdef __WINDOWS__
	RESORCES_PATH(mFilePath);
#endif // __WINDOWS__
#endif // __MY_DEBUG__

	return DxLib::LoadSoundMem(mFilePath);
}

void Sound::DestoryResource(int handle) {
	if (handle == Sound::eResult_None) return;
	DeleteSoundMem(handle);
}

Sound::Sound() : ResourceLoader(){
	mHandle = Sound::eResult_None;
	mVolume = 255;
}

Sound::~Sound() {

}

bool Sound::Load(const char* filePath, int volume/* = 255*/) {

	if (LoadASync(filePath)) {
		mHandle = Get(filePath);
	}

	if (mHandle == Sound::eResult_Error) {
		Debug::ErorrMessage("サウンドデータの読み込みに失敗しました.\n(%s)",mFilePath);
		return false;
	}

	ChangeVolume(volume);

	return true;
}

void Sound::Release() {
	Stop();
	DestoryResource(mHandle);
	mHandle = Sound::eResult_None;
}

void Sound::Play(ePlayType playType) {

	if (mHandle <= Sound::eResult_None) return;

	unsigned int type = 0;
	switch (playType) {
	case Sound::ePlayType_BackGround:
		type = DX_PLAYTYPE_BACK;
		break;
	case Sound::ePlayType_Loop:
		type = DX_PLAYTYPE_LOOP;
		break;
	}

	PlaySoundMem(mHandle, type);

}

void Sound::Stop() {
	if (mHandle <= Sound::eResult_None) return;
	StopSoundMem(mHandle);
}

void Sound::ChangeVolume(int volume) {
	if (mHandle <= Sound::eResult_None) return;

	if (volume < 0) {
		volume = 0;
	}
	else if (volume > 255) {
		volume = 255;
	}

	mVolume = volume;
	ChangeVolumeSoundMem(mVolume, mHandle);
}

int Sound::GetVolume() const{
	return mVolume;
}