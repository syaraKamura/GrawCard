#include "Common/GameCommon.h"
#include "Scene/ISCeneBase.h"
#include "Test/TestMenu.h"


#ifdef __MY_DEBUG__

#define STRING_LENTGH (6 * 10)

typedef struct{
	ISceneBase::eScene scene;
	char sceneName[STRING_LENTGH];
}SCENE_LIST;

static const SCENE_LIST s_cSceneListTbl[] = {
	{ISceneBase::eScene_Opning,"オープニング"},
	{ISceneBase::eScene_Title,"タイトル"},
	{ISceneBase::eScene_MainMenu,"メインメニュー"},
	{ISceneBase::eScene_AITest,"AIテスト"},
	{ISceneBase::eScene_TestComunication,"通信テスト"},
};

//シーンリスト数
static const int s_cSceneListNum = sizeof(s_cSceneListTbl)/sizeof(s_cSceneListTbl[0]);

TestMenu::TestMenu(ISceneBase* changer) : SceneBase(changer){

}

void TestMenu::Initialize(){

	mCursorY = 0;

}

void TestMenu::Finalize(){
	
}

bool TestMenu::Updata(){

#ifdef __WINDOWS__
	if(Keyboard_Repeat(KEY_INPUT_UP)){
		mCursorY = (mCursorY + (s_cSceneListNum - 1)) % s_cSceneListNum;
	}else if(Keyboard_Repeat(KEY_INPUT_DOWN)){
		mCursorY = (mCursorY + 1) % s_cSceneListNum ;
	}


	if(Keyboard_Press(KEY_INPUT_Z) == 1){
		mNextScene->SceneChange(s_cSceneListTbl[mCursorY].scene);
	}
#endif
	return true;
}

void TestMenu::Draw(){

	DxLib::DrawString(20,20,"デバッグメニュー！",GetColor(255,255,255));

	//選択カーソル
	DxLib::DrawString(20,60 + mCursorY * 20,"◆",GetColor(255,255,255));

	for(int i = 0;i < s_cSceneListNum;i++){
		DxLib::DrawString(40,60 + i * 20,s_cSceneListTbl[i].sceneName,GetColor(255,255,255));
	}

}


#endif