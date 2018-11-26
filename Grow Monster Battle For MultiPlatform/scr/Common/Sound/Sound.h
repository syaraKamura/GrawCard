/*
				ファイル名		:Sound.h
				作成者			:
				作成日時		:2018/11/16
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __SOUND_H__
#define __SOUND_H__

#include "Common/ResourceLoader/ResourceLoader.h"

class Sound : public ResourceLoader{

public :

	enum ePlayType {
		ePlayType_BackGround,
		ePlayType_Loop,
	};

private:

	enum eResult {
		eResult_Error = -1,	// 読み込みエラー
		eResult_None,		// データなし
	};


private:

	int mHandle;
	int mVolume;

	char mFilePath[1024];

protected:

	int LoadResource(std::string fileName) override;
	void DestoryResource(int handle) override;

public :

	Sound();
	~Sound();

	/*
		リソースの読み込み
		return	true	:読み込み成功
				false	:読み込み失敗
	*/
	bool Load(const char* filePath,int volume = 255);

	/*
		サウンドデータの削除を行う
	*/
	void Release();

	/*
		再生する
		ePlayType playType	: 再生方法
	*/
	void Play(ePlayType playType);

	/*
		停止する
	*/
	void Stop();

	/*
		音量を変更する
	*/
	void ChangeVolume(int mVolume);

	/*
		現在の音量を取得する
	*/
	int GetVolume() const;

};

#endif // __SOUND_H__