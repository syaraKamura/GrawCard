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
#include "Prologue/Scene_Prologue.h"
#include "MainMenu/Scene_MainMenu.h"

#ifdef __MY_DEBUG__
	#include "Test/TestMenu.h"
	#include "Test/AITest.h"
	#include "Test/TestCommunication.h"
	#include "Test/TestBattle.h"
	#include "Test/TestADV.h"
	#include "Test/TestMapField.h"
	#include "Test/TestLoader.h"
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
	memset(m_DbgNowSceneName, 0, sizeof(char) * 126);
#endif	//__MY_DEBUG__

}

#ifdef __MY_DEBUG__

SceneMgr::SceneMgr(Debug* debug){
	mNextScene = ISceneBase::eScene_None;
	mPrevScene = ISceneBase::eScene_None;
	mScene = (SceneBase*) new Scene_Boot(this);	//ブートシーンを設定
	mDebug = debug;
	memset(m_DbgNowSceneName, 0, sizeof(char) * 126);
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
	if (mScene == NULL) {
#ifdef __MY_DEBUG__
		Debug::ErorrMessage("シーンデータがNULLです\nTestMenuへ戻ります.");
		mScene = (SceneBase*)new TestMenu(this);
		mNextScene = ISceneBase::eScene_None;
		mPrevScene = ISceneBase::eScene_None;
#endif
		return;
	}
	
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

#if false	// コンテナメソッドを作成したためコメントアウト
#ifdef __MY_DEBUG__
	//シーンリスト
	const SCENE_LIST_t SCENE_LIST[ISceneBase::eScene_Num] = {
		//シーンクラス							シーン名
	{ (SceneBase*)new Scene_Boot(this),				"Scene_Boot"				},
	{ (SceneBase*)new Scene_Opning(this),			"Scene_Opning"				},
	{ (SceneBase*)new Scene_Title(this),			"Scene_Title"				},
	{ (SceneBase*)new Scene_MainMenu(this,mDebug),	"Scene_MainMenu"			},

#ifdef __MY_DEBUG__
	{ (SceneBase*)new TestMenu(this),				"Scene_TestMenu"			},
	{ (SceneBase*)new AITest(this),					"Scene_AITest"				},
	{ (SceneBase*)new TestCommunication(this),		"Scene_TestCommunication"	},
	{ (SceneBase*)new TestBattle(this),				"Scene_TestBattle"			},
	{ (SceneBase*)new TestADV(this),				"Scene_TestADV"				},
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
#endif
	if(mNextScene != ISceneBase::eScene_None){
		
		mScene->Finalize();
		Delete(mScene);


		mPrevScene = mNowScene;
		mNowScene = mNextScene;		

#if true 
		mScene = CreateNextScene(mNextScene);
#else
		mScene = (SceneBase*)SCENE_LIST[mNextScene].scene;

#ifdef __MY_DEBUG__
		dbg_SetSceneName( SCENE_LIST[mNextScene].name);
#endif // !__MY_DEBUG__
#endif // true

		mNextScene = ISceneBase::eScene_None;
		
		if(mScene != NULL){	
			mIsLoadEnd = mScene->Initialize();
			if (mIsLoadEnd == false) {
				return false;
			}
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


SceneBase* SceneMgr::CreateNextScene(ISceneBase::eScene next) {

#if false	// とりあえず元のものは残しておく
#ifdef __MY_DEBUG__
	//シーンリスト
	const SCENE_LIST_t SCENE_LIST[ISceneBase::eScene_Num] = {
		//シーンクラス							シーン名
		{ (SceneBase*)new Scene_Boot(this),				"Scene_Boot" },
	{ (SceneBase*)new Scene_Opning(this),			"Scene_Opning" },
	{ (SceneBase*)new Scene_Title(this),			"Scene_Title" },
	{ (SceneBase*)new Scene_MainMenu(this,mDebug),	"Scene_MainMenu" },

#ifdef __MY_DEBUG__
	{ (SceneBase*)new TestMenu(this),				"Scene_TestMenu" },
	{ (SceneBase*)new AITest(this),					"Scene_AITest" },
	{ (SceneBase*)new TestCommunication(this),		"Scene_TestCommunication" },
	{ (SceneBase*)new TestBattle(this),				"Scene_TestBattle" },
	{ (SceneBase*)new TestADV(this),				"Scene_TestADV" },
#endif // __MY_DEBUG__

	};
#else
	//シーンリスト
	const SCENE_LIST_t SCENE_LIST[ISceneBase::eScene_Num] = {
		//シーンクラス							シーン名
		{ (SceneBase*)new Scene_Boot(this),		"Scene_Boot" },
	{ (SceneBase*)new Scene_Opning(this),	"Scene_Opning" },
	{ (SceneBase*)new Scene_Title(this),		"Scene_Title" },
	{ (SceneBase*)new Scene_MainMenu(this),	"Scene_MainMenu" },

	};
#endif // __MY_DEBUG__
#endif // false
	SceneBase* scene = NULL;
	char sceneName[124];

	switch (next) {
			case ISceneBase::eScene_Boot:
				scene = (SceneBase*)new Scene_Boot(this);
				strcpyDx(sceneName, "Scene_Boot");
				break;
			case ISceneBase::eScene_Opning:
				scene = (SceneBase*)new Scene_Opning(this);
				strcpyDx(sceneName, "Scene_Opning");
				break;
			case ISceneBase::eScene_Title:
				scene = (SceneBase*)new Scene_Title(this);
				strcpyDx(sceneName, "Scene_Title");
				break;
			case ISceneBase::eScene_Prologue:
				scene = (SceneBase*)new Scene_Prologue(this);
				strcpyDx(sceneName, "Scene_Prologue");
				break;
			case ISceneBase::eScene_MainMenu:
				scene = (SceneBase*)new Scene_MainMenu(this);
				strcpyDx(sceneName, "Scene_MainMenu");
				break;

#ifdef __MY_DEBUG__
			case ISceneBase::eScene_TestMenu:
				scene = (SceneBase*)new TestMenu(this);
				strcpyDx(sceneName, "Scene_TestMenu");
				break;
			case ISceneBase::eScene_AITest:
				scene = (SceneBase*)new AITest(this);
				strcpyDx(sceneName, "Scene_AITest");
				break;
			case ISceneBase::eScene_TestComunication:
				scene = (SceneBase*)new TestCommunication(this);
				strcpyDx(sceneName, "Scene_TestCommunication");
				break;
			case ISceneBase::eScene_TestBattle:
				scene = (SceneBase*)new TestBattle(this);
				strcpyDx(sceneName, "Scene_TestBattle");
				break;
			case ISceneBase::eScene_TestADV:
				scene = (SceneBase*)new TestADV(this);
				strcpyDx(sceneName, "Scene_TestADV");
				break;
			case ISceneBase::eScene_TestMapField:
				scene = (SceneBase*)new TestMapField(this);
				strcpyDx(sceneName, "Scene_TestMapField");
				break;
			case ISceneBase::eScene_TestLoader:
				scene = (SceneBase*)new TestLoader(this);
				strcpyDx(sceneName, "Scene_TestLader");
				break;
#endif // __MY_DEBUG__
	}

#ifdef __MY_DEBUG__
	//dbg_SetSceneName(SCENE_LIST[next].name);
	dbg_SetSceneName(sceneName);
#endif // !__MY_DEBUG__

	return scene;
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