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
	{ISceneBase::eScene_TestBattle,"バトルテスト" },
	{ISceneBase::eScene_TestADV,"アドベンチャーテスト"},
};

//シーンリスト数
static const int s_cSceneListNum = sizeof(s_cSceneListTbl)/sizeof(s_cSceneListTbl[0]);

TestMenu::TestMenu(ISceneBase* changer) : SceneBase(changer){

}

bool TestMenu::Initialize(){

	mCursorY = 0;

	return true;

}

void TestMenu::Finalize(){
	
}

bool TestMenu::Updata() {

#ifdef __WINDOWS__

	if (Keyboard_Repeat(KEY_INPUT_UP)) {
		mCursorY = (mCursorY + (s_cSceneListNum - 1)) % s_cSceneListNum;
	}
	else if (Keyboard_Repeat(KEY_INPUT_DOWN)) {
		mCursorY = (mCursorY + 1) % s_cSceneListNum;
	}


	if (Keyboard_Press(KEY_INPUT_Z) == true) {
		mNextScene->SceneChange(s_cSceneListTbl[mCursorY].scene);
	}
#endif

	int fontSize = DxLib::GetFontSize();
	int pointX = ClickInput::GetInstance()->GetPositionX(0);
	int pointY = ClickInput::GetInstance()->GetPositionY(0);
	if (ClickInput::GetInstance()->Press(0)) {
		for (int i = 0; i < s_cSceneListNum; i++) {
			int x = 40;
			int y = 60 + i * 20;
			int dx = x + fontSize * 60;
			int dy = y + fontSize;

			if ((x <= pointX && dx >= pointX) && 
				(y <= pointY && dy >= pointY)) {
				mNextScene->SceneChange(s_cSceneListTbl[i].scene);
				break;
			}

		}
	}

	return true;
}

void TestMenu::Draw(){

	DxLib::DrawString(20,20,"デバッグメニュー！",GetColor(255,255,255));

	//選択カーソル
	DxLib::DrawString(20,60 + mCursorY * 20,"◆",GetColor(255,255,255));

	
	for(int i = 0;i < s_cSceneListNum;i++){
		unsigned int strColor = GetColor(255, 255, 255);
		if (s_cSceneListTbl[i].scene == ISceneBase::eScene_None) {
			strColor = GetColor(255, 0, 0);
		}
		else {
			if (i == mCursorY) {
				strColor = GetColor(0, 255, 0);
			}
		}
		DxLib::DrawString(40,60 + i * 20,s_cSceneListTbl[i].sceneName,strColor);
	}

}


#endif