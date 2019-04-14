
#include "Common/GameCommon.h"


#ifdef __MY_DEBUG__
#include "Scene/ISceneBase.h"
#include "Test/AITest.h"

#include "Common/Input/Joypad.h"
#include "Common/Input/Touch.h"

#include "Common/Graphics/Window/WindowGraph.h"
#include "Common/Graphics/GraphicsMulti.h"
#include "Common/Graphics/Graphics.h"
#include "Common/Graphics/Button/ButtonGraph.h"
#include "Common/Graphics/Button/Button.h"
#include "AppData/SaveData/SaveData.h"
#include "Common/String/StringBase.h"
#include "Common/FileIO/WriteBynary.h"
#include "Common/FileIO/ReadBynary.h"
#include "Common/XML/XmlPurser.h"

#include "Common/Animation/Animation.h"

#include "Common/String/FontMgr/BMFont.h"

#include "Common/Sound/Sound.h"

#include "Scene/MainMenu/Dungeon/Map/Map.h"

#ifdef __ANDROID__
#include "android/Networking/Networking.h"
#endif	//__ANDROID__

const int MAP_WIDTH = 41;
const int MAP_HEIGHT= 37;
const int MAP_CHIP_SIZE = 20;

//敵種類
const int ENEMY_KIND_NUM = 4;


enum eDirection{
	eDirection_Up,
	eDirection_Left,
	eDirection_Right,
	eDirection_Down,
};

const unsigned int EnemyColor[ENEMY_KIND_NUM] = 
{
	GetColor(255,255,0),	//黄色
	GetColor(255,0,0),		//赤
	GetColor(0,255,0),		//緑
	GetColor(0,0,255),		//青
};

static int MapData[MAP_HEIGHT][MAP_WIDTH];

typedef struct{
	int posX;			//座標
	int posY;
	int direction;		//向き
	int kind;			//種類
	int counter;		//カウンター
	int moveStartTime;	//移動開始時間
}Enemy_t;

static Enemy_t enemy[ENEMY_KIND_NUM];

static Graphics* mGraphics;

static GraphicsMulti* mGraphicsMulti;
static GraphicsMulti* mGraphicsMulti2;

static SaveData* mData;
static StringBase* mString;
static WriteBynary* mFile;
static ReadBynary* mReadFile;
static XmlPurser* mXml;
static Animation* mAnimation;

static WindowGraph* mWindowGraph;

static int posX = 0;
static int vecX = 4;

static BMFont* mBMFont;

static Sound* mSound;

static Map* mMap;

#ifdef ENABLE_EFFEKSEER
static EffekseerEffect::EffectPlayData mEftData;
static EffekseerEffect::EffectManual* mEftManual;
#endif	// ENABLE_EFFEKSEER

void Map_Initialize(){

	//マップの下地を作成
	for(int y = 0;y < MAP_HEIGHT;y++){
		for(int x = 0;x < MAP_WIDTH;x++){
			
			if(y == 0 || y == MAP_HEIGHT - 1 || 
				x == 0 || x == MAP_WIDTH - 1){
					MapData[y][x] = 1;
			}else if(y % 2 == 0 && x % 2 == 0){
				MapData[y][x] = 1;
			}else{
				MapData[y][x] = 0;
			}
		}
	}

	//迷路を生成
	for(int y = 2;y < MAP_HEIGHT - 2;y++){
		for(int x = 1;x < MAP_WIDTH - 2;x++){
			
			if(MapData[y][x] == 1){
				int dir = GetRand(3);
				int cnt = 0;
				bool flg = false;
				while(flg == false && cnt < 3){
					dir = GetRand(3);
					switch(dir){
						case eDirection_Up:
							if(MapData[y - 1][x] == 0){
								flg = true;
							}
							break;
						case eDirection_Left:
							if(MapData[y][x - 1] == 0){
								flg = true;
							}
							break;
						case eDirection_Right:
							if(MapData[y][x + 1] == 0){
								flg = true;
							}
							break;
						case eDirection_Down:
							if(MapData[y + 1][x] == 0){
								flg = true;
							}
							break;
					}
					cnt++;
				}
				
				if(flg == false){
					continue;
				}

				switch(dir){
				case eDirection_Up:
					MapData[y - 1][x] = 99;
					break;
				case eDirection_Left:
					MapData[y][x - 1] = 99;
					break;
				case eDirection_Right:
					MapData[y][x + 1] = 99;
					break;
				case eDirection_Down:
					MapData[y + 1][x] = 99;
				}
			}
		}
	}

	//通行判定が取れるように値を修正
	for(int y = 0;y < MAP_HEIGHT;y++){
		for(int x = 0;x < MAP_WIDTH;x++){
			if(MapData[y][x] == 99){
				MapData[y][x] = 1;
			}
		}
	}

	//通行可能マスの四方が通行不可能なら、通行可能マスをランダムな方向に生成
	for(int y = 2;y < MAP_HEIGHT - 2;y++){
		for(int x = 2;x < MAP_WIDTH - 2;x++){
			
			if(MapData[y - 1][x] == 1 &&MapData[y][x - 1] == 1 &&
			   MapData[y][x + 1] == 1 && MapData[y + 1][x] == 1){
				   int dir = GetRand(3);
					switch(dir){
				case eDirection_Up:
					MapData[y - 1][x] = 0;
					break;
				case eDirection_Left:
					MapData[y][x - 1] = 0;
					break;
				case eDirection_Right:
					MapData[y][x + 1] = 0;
					break;
				case eDirection_Down:
					MapData[y + 1][x] = 0;
				}
			}
		}
	}

	mGraphics = new Graphics();
#ifdef __ANDROID__
	mGraphics->Load("Resources/Graphics/BG/menu_ui_re.png");
#else
	mGraphics->Load("Resources/Data/Graph000.xml");
#endif
	mGraphics->SetAlpha(200);

	mGraphicsMulti = new GraphicsMulti();
	//mGraphicsMulti->Load("Resources/Graphics/UI/start.png", 0, 0);
	//mGraphicsMulti->Load("Resources/Graphics/UI/start.png", 0, 100);
	//mGraphicsMulti->Load("Resources/Graphics/UI/start.png", 0, 50);
	//mGraphicsMulti->Load("Resources/Graphics/UI/start.png", -200, 0);

	mGraphicsMulti->Load("Resources/Data/Graph100.xml");

	mData = new SaveData();

	GraphicsDrawMgr::GetInstance()->Add(mGraphics, 0);
	GraphicsDrawMgr::GetInstance()->Add(mGraphicsMulti,1);

}

/*
	マップ描画
*/
static void Map_Draw(){

	//マップの描画
	for(int y = 0;y < MAP_HEIGHT;y++){
		for(int x = 0;x < MAP_WIDTH;x++){

			int X1 = x * MAP_CHIP_SIZE;
			int Y1 = y * MAP_CHIP_SIZE;
			int X2 = X1 + MAP_CHIP_SIZE;
			int Y2 = Y1 + MAP_CHIP_SIZE;

			if(MapData[y][x] == 1){
				DrawBox(X1,Y1,X2,Y2,GetColor(255,255,255),TRUE);
			}

		}
	}

}

/*
	敵初期化
*/
static void Enemy_Initialize(){

	for(int i = 0;i < ENEMY_KIND_NUM;i++){
		enemy[i].posX = GetRand(MAP_WIDTH);
		enemy[i].posY = GetRand(MAP_HEIGHT);

		//通行可能な場所に設定されるまで設定しなおす
		while(MapData[enemy[i].posY][ enemy[i].posX] == 1){
			enemy[i].posX = GetRand(MAP_WIDTH);
			enemy[i].posY = GetRand(MAP_HEIGHT);
		}

		enemy[i].counter = 0;
		enemy[i].moveStartTime = GetRand(60);

		enemy[i].kind = i;
		enemy[i].direction = 0;
	}
}

/*
	移動可能か確認する
	return	true	:移動可能
			false	:移動不可能
*/
static bool isMoveCheck(Enemy_t enemy){

	int posX = enemy.posX;
	int posY = enemy.posY;
	int dir = enemy.direction;

	bool flg = false;


	switch(dir){
	case eDirection_Up:
		if(MapData[posY - 1][posX] == 0){
			flg = true;
		}
		break;
	case eDirection_Left:
		if(MapData[posY][posX - 1] == 0){
			flg = true;
		}
		break;
	case eDirection_Right:
		if(MapData[posY][posX + 1] == 0){
			flg = true;
		}
		break;
	case eDirection_Down:
		if(MapData[posY + 1][posX] == 0){
			flg = true;
		}
		break;

	}

	return flg;
}

/*
	敵の移動
*/
static void EnemyMove(Enemy_t* enemy){

	int dir = enemy->direction;

	switch(dir){
	case eDirection_Up:
		enemy->posY --;
		break;
	case eDirection_Left:
		enemy->posX --;
		break;
	case eDirection_Right:
		enemy->posX ++;
		break;
	case eDirection_Down:
		enemy->posY ++;
		break;

	}

}

/*
	敵更更新処理
*/
static void Enemy_Updata(){
	
	for(int i = 0;i < ENEMY_KIND_NUM;i++){
		
		enemy[i].counter++;

		//行動開始時間になったか？
		if(enemy[i].counter >= enemy[i].moveStartTime){

			//移動方向の決定
			enemy[i].direction = GetRand(3);	//0 ~ 3

			//移動方向へ移動できるか確認
			if(isMoveCheck(enemy[i]) == true){
				//移動開始
				EnemyMove(&enemy[i]);
			}


			//次の移動開始時間を設定
			enemy[i].moveStartTime = GetRand(60);
			//カウンター初期化
			enemy[i].counter = 0;
		}

	}

}

/*
	敵の描画
*/
static void Enemy_Draw(){
	
	for(int i = 0;i < ENEMY_KIND_NUM;i++){

		int X1 = enemy[i].posX * MAP_CHIP_SIZE;
		int Y1 = enemy[i].posY * MAP_CHIP_SIZE;
		int X2 = X1 + MAP_CHIP_SIZE;
		int Y2 = Y1 + MAP_CHIP_SIZE;

		int kind = enemy[i].kind;
		
		DrawBox(X1,Y1,X2,Y2,EnemyColor[kind],TRUE);
		DrawFormatString(X1,Y1-MAP_CHIP_SIZE,GetColor(0,255,255),"T:%d",enemy[i].counter);

	}
}


AITest::AITest(ISceneBase* changer) : SceneBase(changer){
	SRand(GetNowCount());
}

bool AITest::Initialize(){
	
	mJoyPad = new Joypad();
	mTouch = new Touch();
	mString = new StringBase();
	mString->FontCreate("Resources/Data/Font/MS_mintyou_UTF_8.dft", 1);

	mFile = new WriteBynary();
	mReadFile = new ReadBynary();

	//ファイル削除
	mFile->Remove("%s.txt", "Test");

	//ファイル書き込み開始
	if (mFile->Open("Test.txt") == true) {

		mFile->WriteInt(2018);
		mFile->WriteBool(false);
		mFile->WriteString("これはテストなのです。");
		mFile->WriteString("aばta毛tあブﾗ!?");
		mFile->WriteChar('b');

		//ファイル書き込み終了
		mFile->Close();
	}

	if (mReadFile->Exist("Test.txt")) {

		if (mReadFile->Open("Test.txt") == true) {

			int num;
			bool flg;
			char str[256];
			char ch;

			mReadFile->ReadInt(&num);
			mReadFile->ReadBool(&flg);
			mReadFile->ReadString(str);
			Debug::LogPrintf("%s\n",str);
			mReadFile->ReadString(str);
			Debug::LogPrintf("%s\n",str);
			mReadFile->ReadChar(&ch);

			mReadFile->Close();
		}
	}
	else {
		Debug::LogPrintf("Test.txtは存在していませんでした");
	}
	


	Map_Initialize();
	Enemy_Initialize();
	
	
	mData->GetMonsterBox()->Add(* new Monster());
	mData->GetMonsterBox()->ChangeUseState(0, MonsterBox::eUseState_UnUse);

	//XMLの書き込み、書き出し
#if true
	mXml = new XmlPurser("Test.xml");
	

		mXml->Set("DOUBLE", 19.0);
		mXml->Set("STR", "Test String!");
		mXml->Set("INT", 25);
		
		
		mXml->SetAttribute("FILE_NAME", "ID", 25);
		mXml->SetAttribute("FILE_NAME", "TYPE", "COMMON");
		mXml->Set("FILE_NAME", "test1");

		mXml->SetChild("POSITION","DRAW_X",250);
		mXml->SetChild("POSITION","DRAW_Y", 400.0);
		mXml->SetChild("POSITION", "DRAW_Z", 450.0);

		
		mXml->SetAttribute("FILE_NAME", "ID", 26);
		mXml->SetAttribute("FILE_NAME", "TYPE", "CHARACTER");
		mXml->Set("FILE_NAME", "test2");

		mXml->SetChild("POSITION", "DRAW_X", 100);
		mXml->SetChild("POSITION", "DRAW_Y", 20.0);
		mXml->SetChild("POSITION", "DRAW_Z", 860.0);

		

		if (mXml->Write()) {
			Debug::LogPrintf("XMLの書き込みに成功");
		}

#ifdef __WINDOWS__
	if (mXml->Read()) {
		Debug::LogPrintf("XMLの読み込みに成功");

		int intValue = mXml->GetInt("INT");
		double doubleValue = mXml->GetDouble("DOUBLE");
		std::string str = mXml->GetString("STR");
		int intValue2 = mXml->GetInt("INT");
		
		std::string str2 = mXml->GetAttributeString("FILE_NAME", "TYPE");
		int intvalue5 = mXml->GetAttributeInt("FILE_NAME", "ID");

		int intvalue3 = mXml->GetChildInt("POSITION","DRAW_X");
		double doubleValue2 = mXml->GetChildDouble("POSITION", "DRAW_Z");
		
		
		str2 = mXml->GetAttributeString("FILE_NAME", "TYPE");
		intvalue5 = mXml->GetAttributeInt("FILE_NAME", "ID");

		int intvalue4 = mXml->GetChildInt("POSITION", "DRAW_X");
		double doubleValue3 = mXml->GetChildDouble("POSITION", "DRAW_Z");

		Debug::LogPrintf("XMLの読み込みに成功 %d %lf %s",intValue,doubleValue,str.c_str());

	}
#endif

	delete mXml;
#endif


	ANIMATION_DATA_t anims[] = {
		//int keyframe float positionX 	float positionY float angle	float scale	float alpha
	{ 0,20.0f,30.0f,1.0f,1.0f,123.0f},
	{ 10,120.0f,80.0f,1.0f,1.0f,163.0f },
	{ 20,20.0f,130.0f,1.0f,1.0f,200.0f },
	{ 40,220.0f,530.0f,1.0f,1.0f,255.0f },
	{ 50,120.0f,30.0f,1.0f,1.0f,255.0f },
	{ 120,1200.0f,1030.0f,1.0f,1.0f,255.0f },
	{ 180,1200.0f,1080.0f,1.0f,1.0f,255.0f },
	};

	ANIMATION_DATA_t anims2[] = {
		//int keyframe float positionX 	float positionY float angle	float scale	float alpha
		{ 0,20.0f,30.0f,1.0f,1.0f,123.0f },
		{ 30,20.0f,60.0f,1.0f,1.0f,255.0f },		
		{ 60,20.0f,30.0f,1.0f,1.0f,200.0f },
		{ 40,20.0f,80.0f,1.0f,1.0f,255.0f },
		{ 80,1020.0f,30.0f,1.0f,1.0f,255.0f },
		{ 90,0.0f,30.0f,1.0f,1.0f,255.0f },
		{ 91,100.0f,30.0f,1.0f,1.0f,255.0f },
		{ 96,1000.0f,1000.0f,1.0f,1.0f,255.0f },
		{ 180,20.0f,30.0f,1.0f,1.0f,255.0f },
	};

	mAnimation = new Animation();

	int length = sizeof(anims2) / sizeof(anims2[0]);
	
	for (int i = 0; i < length; i++) {
		mAnimation->AddAnimationData(anims2[i]);
	}

	mAnimation->SetAnimationTime(180);

#ifdef __ANDROID__
	mAnimation->Play();
	mAnimation->Loop();
#endif

	mGraphicsMulti2 = new GraphicsMulti();

	//mGraphicsMulti2->LoadDiv("Resources/Graphics/BG/image.png", 12, 6, 0, 0);
	//
	GraphicsDrawMgr::GetInstance()->Add(mGraphicsMulti2,0);

	mGraphicsMulti2->SetDivPosition(0, 120, 0);
	mGraphicsMulti2->SetDivPosition(12, 120, 120);

	mGraphicsMulti2->SetAllDivVisible(false);

	mWindowGraph = new WindowGraph();
	mWindowGraph->SetString("これはテストのウィンドウメッセージです。あああああああああああああああああああああああああああああああああああああああああああああああああああああああああああああああああああ");
	mWindowGraph->SetPosition(300, 700);
	GraphicsDrawMgr::GetInstance()->Add(mWindowGraph, 0);

	mButton = new ButtonGraph();
	mPrevButton = new Button(500, 200, 240, 60, "テストメニューへ戻る");
	mPrevButton->SetOnListener(this);

	Button* btn = new Button("Resources/Graphics/UI/batoru-ui.png", 500, 400, "テストなんですよ");
	btn->SetOnListener(this);

	mButton->AddButton(mPrevButton);
	mButton->AddButton(btn);

	GraphicsDrawMgr::GetInstance()->Add(mButton, 0);

	mBMFont = new BMFont();
	mBMFont->SetString("ABCDEFGHIJKLMNOPQRSTUVWXWZ abcdefghijklmnopqrstuvwxyz こんにちは　コンニチハ　日本語");

	mSound = new Sound();
	mSound->Load("Resources/Sound/BGM/BGM_0001.mp3");

	mSound->Play(Sound::ePlayType_Loop);

#if __ANDROID__
	Networking net;
	net.BeginNetwork();
#endif // __ANDROID__

	mMap = new Map(255, 1000,"テストああああ");

#ifdef ENABLE_EFFEKSEER	
	EffekseerEffect::Effect::Instance()->Play(&mEftData, EffekseerEffect::EffectLoader::Instance()->Get((int)eEffect::TestEffect1));
	EffekseerEffect::Effect::Instance()->SetPosition(mEftData, 200.0f, 300.0f, 0.0f);
	EffekseerEffect::Effect::Instance()->SetScale(mEftData, 10.0f, 10.0f, 10.0f);

	mEftManual = EffekseerEffect::Effect::Instance()->Manual_Play(EffekseerEffect::EffectLoader::Instance()->Get((int)eEffect::TestEffect2));
	EffekseerEffect::Effect::Instance()->SetPosition(mEftManual->GetEffectPlayData(), 300.0f, 400.0f, 0.0f);
	EffekseerEffect::Effect::Instance()->SetScale(mEftManual->GetEffectPlayData(), 10.0f, 10.0f, 10.0f);

	GraphicsDrawMgr::GetInstance()->Add(mEftManual, 1);
#endif	// ENABLE_EFFEKSEER
	return true;
}

void AITest::Finalize(){

	mGraphics->ReleseRequest();
	mGraphicsMulti->ReleseRequest();
	mWindowGraph->ReleseRequest();
	mButton->ReleseRequest();
#ifdef ENABLE_EFFEKSEER
	mEftManual->ReleseRequest();
#endif // ENABLE_EFFEKSEER
	mSound->Release();

	Delete(mJoyPad);
	Delete(mTouch);
	Delete(mString);
	Delete(mFile);
	Delete(mReadFile);
	Delete(mBMFont);
	Delete(mSound);
	Delete(mMap);

	mGraphicsMulti2->ReleseRequest();

#ifdef ENABLE_EFFEKSEER
	if (EffekseerEffect::Effect::Instance() != NULL) {
		EffekseerEffect::Effect::Instance()->StopAll();
	}
#endif // ENABLE_EFFEKSEER


	//mGraphics->Relese();
	//mGraphicsMulti->Relese();

	//Delete(mGraphics);
	//Delete(mGraphicsMulti);

}

void AITest::PreviousUpdate() {
	mJoyPad->Update();
	mTouch->Update();
}


static int count = 0;
static int timer = 0;
static int mVisibleNum = 0;

bool AITest::Updata() {

	

#ifdef __WINDOWS__
	//テストメニューへ戻る
	if (Keyboard_Press(KEY_INPUT_X) || mJoyPad->Press(Joypad::eJoypadXInput_X)) {
		mNextScene->SceneChange(ISceneBase::eScene_TestMenu);
		return true;
	}

	if (Keyboard_Press(KEY_INPUT_Z)) {
		mData->Save(*mData);
	}
	if (Keyboard_Press(KEY_INPUT_A)) {
		SaveData* buffer = nullptr;
		mData->Load(buffer);
		if (buffer != NULL) {
			mData = buffer;
		}
	}
	if (Keyboard_Press(KEY_INPUT_Q)) {
		static int num = 0;
		Monster mon;
		mon.SetName("テスト");
		mon.SetLevel(++num);
		mData->GetMonsterBox()->Add(mon);
	}

	if (Keyboard_Press(KEY_INPUT_W)) {
		static int num = 0;
		MonsterBox* monBox = mData->GetMonsterBox();
		if (monBox->UseState(0) == MonsterBox::eUseState_UnUse) {
			monBox->ChangeUseState(0, MonsterBox::eUseState_Use);
			Monster mon = monBox->GetMonster(0);
			
			Player* player = mData->GetPlayer();
			player->SetMonster(0, &mon);

		}
	}


	if (Keyboard_Press(KEY_INPUT_P)) {
		mAnimation->Play();
	}
	if (Keyboard_Press(KEY_INPUT_S)) {
		mAnimation->Stop();
	}
	if (Keyboard_Press(KEY_INPUT_L)) {
		mAnimation->Loop();
	}

	//mGraphics->Draw(20, 100, 255);
	//mGraphics->SetPosition(WINDOW_WIDTH / 2, 200);
	//mGraphicsMulti->Draw(posX, 200, 255);
	mGraphicsMulti->SetPosition(posX, 200);

	timer++;

	if (timer % (72 / 60) == 0) {
		mGraphicsMulti2->SetDivVisible(mVisibleNum, false);
		mVisibleNum = (mVisibleNum + 1) % 72;
		mGraphicsMulti2->SetDivVisible(mVisibleNum, true);
	}
	static int x = 200.0f;
#ifdef ENABLE_EFFEKSEER
	if (timer % 60 == 0) {
		mGraphics->SetPriorty(count % 2 * 10);
		x = 200.0f;
		EffekseerEffect::Effect::Instance()->Play(&mEftData, EffekseerEffect::EffectLoader::Instance()->Get(0), EffekseerEffect::ePlayMode::Play3D);
		EffekseerEffect::Effect::Instance()->SetPosition(mEftData, 200.0f, 300.0f, 1.0f);
		EffekseerEffect::Effect::Instance()->SetScale(mEftData, 10.0f, 10.0f, 10.0f);
		count++;
	}
	EffekseerEffect::Effect::Instance()->SetPosition(mEftData, x, 300.0f, 0.0f);
	x += 10.0f;
#endif // ENABLE_EFFEKSEER
#endif
	Enemy_Updata();

	if (posX < 0 || posX > 700) {
		vecX *= -1;
	}

	//posX += vecX;

	posX += (int)(mJoyPad->GetLeftAnalogAxis(Joypad::eAnalogAxis_Horizontal) * 10.0f);

	mGraphics->SetAngleRadian(mJoyPad->GetLeftAnalogAngleRadian());

	mString->SetColor(GetColor(255, 0, 0));
	mString->SetString("Tこれはテストメッセージです。tが");

	mAnimation->AnimationAttach(mGraphics);
	mAnimation->Update();
	
	
	mMap->Updata();
	
	int mapSelectListNum = mMap->GetIndex();
	if (mapSelectListNum != -1) {
		Debug::LogPrintf("テスト項目 %d", mapSelectListNum);
	}

	return true;
}

void AITest::Draw(){

	
	Map_Draw();
	Enemy_Draw();

	mMap->Draw();

	if (mJoyPad->Repeate(Joypad::eJoypadXInput_A) || mTouch->On(Touch::eTouchInput_1)) {
		DrawString(0, 100, "入力されている", GetColor(255, 0, 0));
	}

	DxLib::DrawFormatString(0, 600, GetColor(0, 255, 0), "度数  : %f", mJoyPad->GetLeftAnalogAngleDegree());
	DxLib::DrawFormatString(0, 620, GetColor(0, 255, 0), "弧度法: %f", mJoyPad->GetLeftAnalogAngleRadian());
	DxLib::DrawFormatString(0, 640, GetColor(0, 255, 0), "フリック度数  : %f", mTouch->GetFlickAngleDegree(Touch::eTouchInput_1));
	DxLib::DrawFormatString(0, 660, GetColor(0, 255, 0), "フリック弧度法: %f", mTouch->GetFlickAngleRadian(Touch::eTouchInput_1));

	DxLib::DrawFormatString(600, 220, GetColor(0, 255, 0), "文字数は%dです", mString->DrawString(600, 200));
	
	mBMFont->Draw(20,1040,true);

}

void AITest::OnClick(View* view) {
	
	if (mPrevButton == view) {
		mNextScene->SceneChange(ISceneBase::eScene_TestMenu);
	}

}


#endif