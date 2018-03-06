
#include "Common/GameCommon.h"
#include "Scene/ISceneBase.h"
#include "Scene_Title.h"
#include "Common/Graphics/Graphics.h"
#include "AppData/AppData.h"

#ifdef __ANDROID__
#include "android/JavaEncoder/InputString/InputString.h"
#endif

#define PI 3.14

enum eImg{
	eImg_Back,		//背景
	eImg_NewGame,	//初めから
	eImg_Continue,	//続きから
	eImg_Rogo,		//タイトルロゴ
	eImg_Num,
};

typedef struct {
	int imgHandle[eImg_Num];
	int selectY;
	bool isLoadSaveData;
	int counter;
}Work;

static Work mWork;

/*
void InitSound();					
int setSound(char* fileName);		
int SoundControl(int kind,int sts);	
void deleteSound();					
*/


Scene_Title::Scene_Title(ISceneBase* changer) :SceneBase(changer){ 
	for (int i = 0; i < eImg_Num; i++) {
		mGraphic[i] = new Graphics;
	}
}

bool Scene_Title::Initialize(){

	//mFade->SetFadeColor(255,255,255);
	//mFade->FadeIn(180);

	//InitSound();	//サウンドの初期化
	//SetUseASyncLoadFlag(TRUE);


	//setSound(0,"data/system/sound/bgm/瑠璃の森.mp3");	//BGM読み込み
	//効果音読み込み
	//setSound(1,"data/system/sound/se/セレクト.mp3");	
	//setSound(2,"data/system/sound/se/決定.mp3");
	//setSound(3,"data/system/sound/se/キャンセル.mp3");

	//mWork.imgHandle[eImg_Back] = LoadGraph("Resources/Graphics/BG/Title.png");
	//RogoImg = LoadGraph("data/System/img/TitleRogo1.png");

	//mWork.imgHandle[eImg_NewGame] = LoadGraph("Resources/Graphics/UI/start.png");
	//mWork.imgHandle[eImg_Continue] = LoadGraph("Resources/Graphics/UI/continue.png");
	
	
	mGraphic[eImg_Back]->Load("Resources/Graphics/BG/Title.png");
	mGraphic[eImg_NewGame]->Load("Resources/Graphics/UI/start.png");
	mGraphic[eImg_Continue]->Load("Resources/Graphics/UI/continue.png");

	GraphicsDrawMgr::GetInstance()->Add((GraphicsBase*)mGraphic[eImg_Back], 0);
	GraphicsDrawMgr::GetInstance()->Add((GraphicsBase*)mGraphic[eImg_NewGame], 1);
	GraphicsDrawMgr::GetInstance()->Add((GraphicsBase*)mGraphic[eImg_Continue], 1);
	
	
	mGraphic[eImg_Back]->SetVisible(false);
	mGraphic[eImg_Back]->SetPosition(0, 0);
	
	int sizeX = 0;
	mGraphic[eImg_NewGame]->GetSize(&sizeX, NULL);
	mGraphic[eImg_NewGame]->SetPosition((WINDOW_WIDTH - sizeX ) / 2,420);
	mGraphic[eImg_NewGame]->SetVisible(false);

	mGraphic[eImg_Continue]->GetSize(&sizeX, NULL);
	mGraphic[eImg_Continue]->SetPosition((WINDOW_WIDTH - sizeX) / 2, 500);
	mGraphic[eImg_Continue]->SetVisible(false);

	//SetUseASyncLoadFlag(FALSE);

	mWork.isLoadSaveData = false;

	if (AppData::GetInstance().Exits() == true) {
		mWork.isLoadSaveData = true;
	}

	//MonsterData_Initalize();	//初期化

	//memset(&Player,0,sizeof(Player_g));		//Playerの初期化
	//for(int i = 0;Player.Item[0][i] != 0;i++){
	//	Player.Item[0][i] = 0;
	//}

	
	//MonsterData_Input(LmD);	//MonsterData_Input

	//InputDungeondata();	//ダンジョンに関するデータの読み込み

	//セーブデータの読み込み
	//SaveData読み込み
	if (AppData::GetInstance().Exits() == true) {
		mWork.isLoadSaveData = true;
	}
	
	mWork.counter = 0;
	mWork.selectY = 0;

	mState = eState_Initialize;

#ifdef __ANDROID__
	InputString_Initialize();
#endif

	return true;
}
void Scene_Title::Finalize(){

	for(int i = 0;i < eImg_Num;i++){
		DeleteGraph(mWork.imgHandle[i]);
	}

	mGraphic[eImg_Back]->ReleseRequest();
	mGraphic[eImg_NewGame]->ReleseRequest();
	mGraphic[eImg_Continue]->ReleseRequest();
	
	//deleteSound(0);
}

bool Scene_Title::Updata(){

#ifdef __ANDROID__
	InputString_Update();
#endif

	switch ((int)mState) {
	case eState_Initialize:
		NexetState(eState_Main,eFadeType_In,180);
		mGraphic[eImg_NewGame]->SetVisible(true);
		mGraphic[eImg_Back]->SetVisible(true);
		if (mWork.isLoadSaveData == true) {
			mGraphic[eImg_Continue]->SetVisible(true);
		}

		break;
	case eState_Fade:
		if (Fade::GetInstance()->IsFadeEnd() == false) return true;
		
		mState = mNextState;
		mNextState = eState_None;

		break;
	case eState_Main:
		UpdataProc();
		break;
	case eState_Exit:
		mNextScene->SceneChange(ISceneBase::eScene_MainMenu);
		break;
	case eState_ExitDone:
		break;
	}
	
	return true;
}

void Scene_Title::Draw(){

	//if(mFade->IsFadeEnd() == false) return;
	if(GetASyncLoadNum() != 0){
		DxLib::DrawString(700,580,"Now Loading...",GetColor(255,255,255));
		return ;
	}

	//DxLib::DrawGraph(0,0,mWork.imgHandle[eImg_Back],TRUE);	//背景

	//DrawGraph(100,50,RogoImg,TRUE);	//タイトルロゴ

#if false
	if(mWork.isLoadSaveData == true){
		for(int i = 0;i < 2;i++){
			if(mWork.selectY == i){
				DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA,sin(PI*2/255*mWork.counter)*255 + 10);
				DxLib::DrawGraph(Menu[i].x,Menu[i].y,mWork.imgHandle[i+eImg_NewGame],TRUE);
				DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
				//DrawString(Menu[i].x,Menu[i].y,Menu[i].name,GetColor(255,0,0));
			}else{
				DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				DxLib::DrawGraph(Menu[i].x,Menu[i].y,mWork.imgHandle[i+eImg_NewGame],TRUE);
				DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
				//DrawString(Menu[i].x,Menu[i].y,Menu[i].name,GetColor(255,255,255));
			}
		}
	}else{
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA,sin(PI*2/255*mWork.counter)*255);
		DxLib::DrawGraph(Menu[0].x,Menu[0].y,mWork.imgHandle[eImg_NewGame],TRUE);
		DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		//DrawString(Menu[0].x,Menu[0].y,Menu[0].name,GetColor(255,0,0));
	}
#endif
}



bool Scene_Title::UpdataProc() {

#ifdef __WINDOWS__
	if (mWork.isLoadSaveData == 1) {
		if (Keyboard_Press(KEY_INPUT_UP)) {
			mWork.selectY = (mWork.selectY + 1) % 2;
			//SoundControl(1,1);
			mWork.counter = 0;
		}

		if (Keyboard_Press(KEY_INPUT_DOWN)) {
			mWork.selectY = (mWork.selectY + 1) % 2;
			//SoundControl(1,1);
			mWork.counter = 0;
		}
	}

	if (Keyboard_Press(KEY_INPUT_Z)) {
		if (mWork.selectY == 0) {
			//SoundControl(2,1);

			//mNextScene->SceneChange(ISceneBase::e_Scecne_SelectPlayer);
			NexetState(eState_Exit, eFadeType_Out);
		}
		else {
			mNextScene->SceneChange(ISceneBase::eScene_MainMenu);
			//LoadDataInputFlag = 1;
		}
	}

#ifdef __MY_DEBUG__

	//タイトルメニューへ戻る
	if (Keyboard_Press(KEY_INPUT_X)) {
		dbg_ChangeScene_TestMenu();
	}

#endif	// __MY__DEBUG_

#else

	//Android用操作処理

	//int touchNum = Touch_GetTouchNum();

	if (Touch_Press(0)) {
		if (mWork.selectY == 0) {
			//SoundControl(2,1);

			//ChangeNextScene(SelectPlayer);
			NexetState(eState_Exit, eFadeType_Out);
		}
		else {
			//mNextScene->SceneChange(ISceneBase::eScene_MainMenu);
			//LoadDataInputFlag = 1;
		}
	}


#endif	//	__WINDOWS__

	if (mWork.isLoadSaveData == true) {
		for (int i = 0; i < 2; i++) {
			if (mWork.selectY == i) {
				float alpha = (1.0f + sin(PI / 2.0f / 20.0f * mWork.counter) / 2.0f) * 255.0f;
				mGraphic[i + eImg_NewGame]->SetAlpha(alpha);
				
			}
			else {
				mGraphic[i + eImg_NewGame]->SetAlpha(255);
				
			}
		}
	}
	else {
		float alpha = (1.0f+sin(PI / 2.0f / 30.0f * mWork.counter)/2.0f) * 255.0f;
		mGraphic[eImg_NewGame]->SetAlpha(alpha);
	}

	mWork.counter++;
	return true;
}

void Scene_Title::NexetState(eState nextState,eFadeType type, int fadeFrame) {
	
	mState = eState_Fade;
	mNextState = nextState;

	if (type == eFadeType_In) {
		Fade::GetInstance()->FadeIn(fadeFrame);
	}
	else if (type == eFadeType_Out) {
		Fade::GetInstance()->FadeOut(fadeFrame);
	}

}