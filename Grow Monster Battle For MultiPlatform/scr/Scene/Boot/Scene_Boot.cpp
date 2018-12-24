/*
				ファイル名		:Boot.h
				作成者			:
				作成日時		:2017/12/07
				ソース説明		:初期起動

				
				
				備考
					
				
!*/

#include"Common/GameCommon.h"
#include "Scene/ISceneBase.h"
#include "Scene_Boot.h"



Scene_Boot::Scene_Boot(ISceneBase* changer):SceneBase(changer){

	

}

bool Scene_Boot::Initialize(){

	
	TaskMgr::getInstance().Add(Fade::GetInstance(),TaskMgr::ePriorty_Fade);
	TaskMgr::getInstance().Add(GraphicsDrawMgr::GetInstance(), TaskMgr::ePriorty_Graphics);

	return true;
}

void Scene_Boot::Finalize(){

	

}

bool Scene_Boot::Updata(){

	if (ComRes::Instance()->Load() == false) return false;

#ifdef __MY_DEBUG__ 
#ifdef __WINDOWS__
	//テストメニューへ
	mNextScene->SceneChange(ISceneBase::eScene_TestMenu);
#else
	//オープニングシーンへ移行
	//mNextScene->SceneChange(ISceneBase::eScene_Opning);
	mNextScene->SceneChange(ISceneBase::eScene_AITest);
#endif	//__WINDOWS__
#else
	//オープニングシーンへ移行
	mNextScene->SceneChange(ISceneBase::eScene_Opning);
#endif
	return true;
}

void Scene_Boot::Draw(){

}
