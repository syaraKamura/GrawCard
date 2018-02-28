/*
				ファイル名		:SceneMgr.h
				作成者			:
				作成日時		:2017/12/07
				ソース説明		:シーン管理クラス

				
				
				備考
					
				
				
!*/

#ifndef __SCENE_MGR_H__
#define __SCENE_MGR_H__

#include "ISceneBase.h"

class Debug;

class SceneBase;

class SceneMgr : public ISceneBase,Task{

private:

	bool mIsLoadEnd;	//読み込み終了フラグ
	SceneBase* mScene;
	
	ISceneBase::eScene mPrevScene;	//前回のシーン
	ISceneBase::eScene mNowScene;	//今のシーン
	ISceneBase::eScene mNextScene;	//次のシーン

private:

	//シーン切り替えプロセス
	bool SceneChangeProc();
	void SceneChangeDraw();

public :

	SceneMgr();
	
#ifdef __MY_DEBUG__

	Debug* mDebug;
	SceneMgr(Debug* debug);

#endif

	bool Initialize() override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;

	void SceneChange(eScene nextScene) override;
	
	//前回のシーンに変更する
	void SceneChangePreve();



	// -------------------------------------
	// デバッグ機能

#ifdef __MY_DEBUG__
private:
	char m_DbgNowSceneName[126];		//現在のシーン名

private:

	//シーンの名前の表示
	void dbg_SceneNameDraw();
	void dbg_SetSceneName(const char* name);

#endif//__MY_DEBUG__


};

#endif	//__SCENE_MGR_H__