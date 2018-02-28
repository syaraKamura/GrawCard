/*
				ファイル名		:SceneMgr.h
				作成者			:
				作成日時		:2017/12/11
				ソース説明		:ゲーム管理クラス

				
				
				備考
					
				
!*/


#ifndef __GAME_MGR_H__
#define __GAME_MGR_H__

class SceneMgr;
class FPS;
#ifdef __MY_DEBUG__
class Debug;
#endif 

class GameMgr{

private:

	SceneMgr* mSceneMgr;
	FPS* mFPS;

#ifdef __MY_DEBUG__
	Debug* mDebug;
#endif

public :

	GameMgr();
	~GameMgr();

	void Initialize();
	void Finalize();
	bool Updata();
	void Draw();

#ifndef __MY_DEBUG__

	//デバッグ用


#endif

private:
	
#ifndef __MY_DEBUG__

	//デバッグ用

#endif

};

#endif	//__GAME_MGR_H__