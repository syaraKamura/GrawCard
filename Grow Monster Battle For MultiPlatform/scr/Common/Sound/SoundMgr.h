/*
				ファイル名		:SoundMgr.h
				作成者			:
				作成日時		:2018/11/17
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __SOUND_MGR_H__
#define __SOUND_MGR_H__

#include <map>
#include  "Sound.h";

class SoundMgr{

public :

	enum ePlayType{
		ePlayType_BackGround,
		ePlayType_Loop,
	};

private:

	static SoundMgr* mInstance;

	std::map<std::string, Sound*> mSoundData;

	std::string mNowSoundId;	// 現在再生しているサウンド識別用ID
	std::string mNextSoundId;	// 次に再生するサウンド識別用ID
	int mCrossFadeTime;			// crossフェードにかかる時間
	int mCrossFadeCount;		// crossフェード用のカウンタ
	bool mIsCrossFade;			// クロスフェードを行うか

	int mNowSoundVolume;
	int mNextSoundVolume;

	ePlayType mPlayType;		// 再生方法

private:

	SoundMgr();
	~SoundMgr();

	/*
		サウンドデータを探す
		return NULL	:サウンドデータがない
	*/
	Sound* SarchSoundData(std::string soundId) const ;

	/*
		サウンドタイプを返却する
	*/
	Sound::ePlayType PlayType(SoundMgr::ePlayType playType);

public:

	/*
		生成
	*/
	static void Create();

	/*
		削除
	*/
	static void Destroy();

	/*
	サウンドを追加
	std::string soundId		: サウンド識別用ID（固有でなければならない）
	std::string soundPath	: サウンドデータパス
	int volume = 255		: 再生時の音量
	return	true	:追加に成功
	false	:追加に失敗
	*/
	bool Add(std::string soundId, std::string soundPath, int volume = 255);

	/*
		サウンドデータを削除
		std::string soundId		: サウンド識別用ID
	*/
	bool Remove(std::string soundId);

	/*
		再生
		std::string soundId							: サウンド識別用ID
		ePlayType playType = ePlayType_BackGround	: 再生方法
	*/
	void Play(std::string soundId,ePlayType playType = ePlayType_BackGround);

	/*
		ワンショット再生
		std::string soundId							: サウンド識別用ID
	*/
	void PlayOnShot(std::string soundId);

	/*
		停止
		std::string soundId		: サウンド識別用ID
	*/
	void Stop(std::string soundId);
	/*
		現在再生中のサウンドを停止する
	*/
	void Stop();

	/*
		黒フェードしながら再生を始める
		std::string nextSoundId						: 次に再生するサウンド識別ID
		int frameTiem								: クロスフェードにかかる時間
		ePlayType playType = ePlayType_BackGround	: 再生方法
	*/
	void CroosFadePlay(std::string nextSoundId,int frameTiem, ePlayType playType = ePlayType_BackGround);

	/*
		現在再生しているサウンド識別IDを返却する
	*/
	std::string& GetPlaySoundId();

	/*
		更新
	*/
	bool Updata();

	/*
		インスタンスを返却する
	*/
	static SoundMgr* GetInstance();

};

#endif // __SOUND_MGR_H__