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

	int mLoadingPosX;

private:

	//シーン切り替えプロセス
	bool SceneChangeProc();
	void SceneChangeDraw();

	SceneBase* CreateNextScene(ISceneBase::eScene next);


public :

	SceneMgr();
	
#ifdef __MY_DEBUG__

	Debug* mDebug;
	SceneMgr(Debug* debug);

#endif

	bool Initialize() override;
	void Finalize() override;
	void PreviousUpdate()override;
	bool Updata()override;
	void Draw() override;
	void PostUpdate() override;

	void SceneChange(eScene nextScene) override;
	
	//前回のシーンに変更する
	void SceneChangePreve();



	// -------------------------------------
	// デバッグ機能.

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