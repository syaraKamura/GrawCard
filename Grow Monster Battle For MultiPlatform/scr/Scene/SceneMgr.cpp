/*
				ファイル名		:SceneMgr.cpp
				作成者			:
				作成日時		:2017/12/07
				ソース説明		:シーン管理クラス

				
				
				備考
					
				
!*/

#include "Common/GameCommon.h"
#include "SceneMgr.h"
#include "SceneBase.h"
#include "Boot/Scene_Boot.h"
#include "Opning/Scene_Opning.h"
#include "Title/Scene_Title.h"
#include "MainMenu/Scene_MainMenu.h"

#ifdef __MY_DEBUG__
	#include "Test/TestMenu.h"
	#include "Test/AITest.h"
	#include "Test/TestCommunication.h"
#endif

typedef struct {
	SceneBase* scene;
	char name[123];
}SCENE_LIST_t;


SceneMgr::SceneMgr(){
	mNextScene = ISceneBase::eScene_None;
	mPrevScene = ISceneBase::eScene_None;
	mScene = (SceneBase*) new Scene_Boot(this);	//ブートシーンを設定

#ifdef __MY_DEBUG__
	dbg_SetSceneName("");
#endif	//__MY_DEBUG__

}

#ifdef __MY_DEBUG__

SceneMgr::SceneMgr(Debug* debug){
	mNextScene = ISceneBase::eScene_None;
	mPrevScene = ISceneBase::eScene_None;
	mScene = (SceneBase*) new Scene_Boot(this);	//ブートシーンを設定
	mDebug = debug;
}

#endif

bool SceneMgr::Initialize(){
	if(mScene == NULL) return false;
	mScene->Initialize();
	return true;
}

void SceneMgr::Finalize(){
	if(mScene == NULL) return ;
	mScene->Finalize();
}

void SceneMgr::PreviousUpdate() {
	if (mScene == NULL) return;

	if (SceneChangeProc() == false) return;

	mScene->PreviousUpdate();
}

bool SceneMgr::Updata(){
	if(mScene == NULL) return false;
	else if (mIsLoadEnd == false) return false;

	return mScene->Updata();
}

void SceneMgr::Draw(){
	if(mScene == NULL) return ;

	if(mIsLoadEnd == false){
		SceneChangeDraw();
	}else{
		mScene->Draw();
	}

#ifdef __MY_DEBUG__
	dbg_SceneNameDraw();
#endif	//__MY_DEBUG__

}

void SceneMgr::PostUpdate() {
	if (mScene == NULL) return;
	
	mScene->PostUpdate();

}

//シーン切り替え
void SceneMgr::SceneChange(eScene nextScene){
	mNextScene = nextScene;
}

//前回のシーンに変更する
void SceneMgr::SceneChangePreve(){
	if(mPrevScene != ISceneBase::eScene_None){
		SceneChange(mPrevScene);
	}
}

bool SceneMgr::SceneChangeProc(){

#ifdef __MY_DEBUG__
	//シーンリスト
	const SCENE_LIST_t SCENE_LIST[ISceneBase::eScene_Num] = {
		//シーンクラス							シーン名
	{ (SceneBase*)new Scene_Boot(this),		"Scene_Boot" },
	{ (SceneBase*)new Scene_Opning(this),	"Scene_Opning" },
	{ (SceneBase*)new Scene_Title(this),		"Scene_Title" },
	{ (SceneBase*)new Scene_MainMenu(this,mDebug),	"Scene_MainMenu" },

#ifdef __MY_DEBUG__
	{ (SceneBase*)new TestMenu(this),		"Scene_TestMenu" },
	{ (SceneBase*)new AITest(this),			"Scene_AITest" },
	{ (SceneBase*)new TestCommunication(this),"Scene_TestCommunication" },
#endif

	};
#else
	//シーンリスト
	const SCENE_LIST_t SCENE_LIST[ISceneBase::eScene_Num] = {
		//シーンクラス							シーン名
		{(SceneBase*)new Scene_Boot(this),		"Scene_Boot"},
		{(SceneBase*)new Scene_Opning(this),	"Scene_Opning" },
		{(SceneBase*)new Scene_Title(this),		"Scene_Title" },
		{(SceneBase*)new Scene_MainMenu(this),	"Scene_MainMenu"},

	};
#endif
	if(mNextScene != ISceneBase::eScene_None){
		
		mScene->Finalize();
		Delete(mScene);


		mPrevScene = mNowScene;
		mNowScene = mNextScene;		
		mScene = (SceneBase*)SCENE_LIST[mNextScene].scene;

#ifdef __MY_DEBUG__
		dbg_SetSceneName( SCENE_LIST[mNextScene].name);
#endif // !__MY_DEBUG__

		mNextScene = ISceneBase::eScene_None;
		
		if(mScene != NULL){	
			mScene->Initialize();
		}
	}

	if(mScene == NULL){
		mIsLoadEnd = false;
	}else{
		mIsLoadEnd = (GetASyncLoadNum() == 0);
	}

	return mIsLoadEnd;
}

void SceneMgr::SceneChangeDraw(){
	DrawString(0,0,"Now Loading...",GetColor(255,255,255));
}

//---------------------------------------------
// デバッグ機能

#ifdef __MY_DEBUG__

//現在のシーン名を描画する
void SceneMgr::dbg_SceneNameDraw() {
	if (m_DbgNowSceneName == "") return;

	DrawStringF(0, 0, m_DbgNowSceneName, GetColor(0, 255, 0));
}

/*

*/
void SceneMgr::dbg_SetSceneName(const char* name) {
#ifdef __WINDOWS__
	strcpy_s(m_DbgNowSceneName, name);
#else
	strcpyDx(m_DbgNowSceneName, name);
#endif	//__WINDOWS__
}

#endif//__MY_DEBUG__