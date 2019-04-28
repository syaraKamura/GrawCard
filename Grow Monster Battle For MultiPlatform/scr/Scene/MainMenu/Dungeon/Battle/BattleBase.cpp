/*
				ファイル名		:BattleBase.cpp
				作成者			:
				作成日時		:2018/03/15
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "AppData/AppData.h"
#include "AppData/Character/Player/Player.h"
#include "AppData/Character/Skill/SkillMgr.h"

#include "BattleBase.h"
#include "BattleCalculator.h"
#include "BattleAnimation.h"
#include "../DungeonMgr.h"
#include "Common/Script/ScriptBase.h"
#include "Common/Graphics/Button/Button.h"


BattleBase::BattleBase() : TaskBase() {
	mGraphics = new Graphics();
	mCard = new Graphics();
	
	Monster* monster = new Monster();

	mPlayer = new Player();
	
	mEnemy = new MonsterDeck();

	monster->SetName("モンスター1");
	monster->SetLevel(1);
	monster->SetAttack(12);
	monster->SetDeffence(8);
	monster->SetSpeed(5);
	monster->SetHp(120);
	monster->SetHpMax(120);

	SaveData* data = AppData::GetInstance()->GetSaveData();
	Player* player = data->GetPlayer();

	if (player->GetSetMonsterNum() == 0) {
#ifdef  __MY_DEBUG__
		mPlayer->SetMonster(0, MonsterMgr::Instance()->GetMonsterData(0));
		monster->SetName("モンスター2");
		mPlayer->SetMonster(1, MonsterMgr::Instance()->GetMonsterData(1));
		monster->SetName("モンスター3");
		mPlayer->SetMonster(2, MonsterMgr::Instance()->GetMonsterData(2));
		monster->SetName("モンスター4");
		mPlayer->SetMonster(3, MonsterMgr::Instance()->GetMonsterData(3));
		monster->SetName("モンスター5");
		mPlayer->SetMonster(4, MonsterMgr::Instance()->GetMonsterData(4));

		Debug::LogPrintf("プレイヤーデータのデッキにモンスターが設定されていません");

#endif
	}
	else {
		mPlayer = player;
	}

	//mEnemy->SetMonster(0, MonsterMgr::Instance()->getMonsterData(5));
	//mEnemy->Attach(0);
	mEnemy->SetMonster(1, MonsterMgr::Instance()->GetMonsterData(6));
	mEnemy->Attach(1);
	//mEnemy->SetMonster(2, MonsterMgr::Instance()->getMonsterData(7));
	//mEnemy->Attach(2);
	mEnemy->SetMonster(3, MonsterMgr::Instance()->GetMonsterData(8));
	mEnemy->Attach(3);
	//mEnemy->SetMonster(4, MonsterMgr::Instance()->getMonsterData(9));
	//mEnemy->Attach(4);
	
	mMoveData.clear();
	
	mMonsterData.clear();

	// プレイヤーモンスター
	for (int i = 0; i < 5; i++) {
		
		MONSTER_DATA_t add;
		Monster* monster = mPlayer->GetMonster(i);
		if (monster == NULL) continue;
		add.monster = monster;
		add.moveOreder = 0;
		add.type = BattleBase::eDeckType_Player;
		add.isDead = false;
		add.moveType = BattleBase::eMoveType_Manual;
		add.graph = MonsterMgr::Instance()->GetGraphics(monster->GetId());
		add.graph.SetVisible(true);
		int y = 1100;
		if (monster->GetHomePosition() == Monster::eHomePosition_Back) {
			y = 1200;
		}
		add.graph.SetPosition(200 + i * 300, y);
		add.graph.SetBasePosition(200 + i * 300, y);
		//GraphicsDrawMgr::GetInstance()->Add(&add.graph, 0);

		mMonsterData.push_back(add);
	}
	

	// エネミーモンスター
	for (int i = 0; i < 5; i++) {
		MONSTER_DATA_t add;
		Monster* monster = mEnemy->GetMonster(i);
		if (monster == NULL) continue;
		add.monster = monster;
		add.moveOreder = 0;
		add.type = BattleBase::eDeckType_Enemy;
		add.isDead = false;
		add.moveType = BattleBase::eMoveType_Auto;
		add.graph = MonsterMgr::Instance()->GetGraphics(monster->GetId());
		add.graph.SetVisible(true);
		int y = 200;
		if (monster->GetHomePosition() == Monster::eHomePosition_Back) {
			y = 100;
		}
		add.graph.SetPosition(200 + i * 300, y);
		add.graph.SetBasePosition(200 + i * 300, y);
		//GraphicsDrawMgr::GetInstance()->Add(&add.graph, 0);

		mMonsterData.push_back(add);
}

#if false
	for (int i = 0; i < 5; i++) {
		Monster* monster = mPlayer->GetMonster(i);
		if (monster == NULL) continue;
		mPlayerCard[i] = MonsterMgr::Instance()->GetGraphics(monster->GetId());
		mPlayerCard[i].SetVisible(true);
		mPlayerCard[i].SetPosition(200 + i * 300, 1100);
		mPlayerCard[i].SetBasePosition(200 + i * 300, 1100);
		GraphicsDrawMgr::GetInstance()->Add(&mPlayerCard[i],0);
	}


	for (int i = 0; i < 5; i++) {
		Monster* monster = mEnemy->GetMonster(i);
		if (monster == NULL) continue;
		mEnemyCard[i] = MonsterMgr::Instance()->GetGraphics(monster->GetId());
	}
#endif

	mBattleAnimation = new BattleAnimation();
	TaskMgr::getInstance().Add(mBattleAnimation);
	
	

}

BattleBase::BattleBase(Player* player) : TaskBase() {
	mGraphics = new Graphics();
	mCard = new Graphics();

	mPlayer = player;

	mEnemy = new MonsterDeck();


	//mEnemy->SetMonster(0, MonsterMgr::Instance()->getMonsterData(5));
	//mEnemy->Attach(0);
	mEnemy->SetMonster(1, MonsterMgr::Instance()->GetMonsterData(6));
	mEnemy->Attach(1);
	//mEnemy->SetMonster(2, MonsterMgr::Instance()->getMonsterData(7));
	//mEnemy->Attach(2);
	mEnemy->SetMonster(3, MonsterMgr::Instance()->GetMonsterData(8));
	mEnemy->Attach(3);
	//mEnemy->SetMonster(4, MonsterMgr::Instance()->getMonsterData(9));
	//mEnemy->Attach(4);

	mMoveData.clear();

	mMonsterData.clear();



	if (mPlayer->GetMonsterDeck().IsEmpty() == true) {

#ifdef __MY_DEBUG__

		Monster* monster = new Monster();

		monster->SetName("モンスター1");
		monster->SetLevel(1);
		monster->SetAttack(12);
		monster->SetDeffence(8);
		monster->SetSpeed(5);
		monster->SetHp(120);
		monster->SetHpMax(120);

		mPlayer->SetMonster(0, MonsterMgr::Instance()->GetMonsterData(0));
		monster->SetName("モンスター2");
		mPlayer->SetMonster(1, MonsterMgr::Instance()->GetMonsterData(1));
		monster->SetName("モンスター3");
		mPlayer->SetMonster(2, MonsterMgr::Instance()->GetMonsterData(2));
		monster->SetName("モンスター4");
		mPlayer->SetMonster(3, MonsterMgr::Instance()->GetMonsterData(3));
		monster->SetName("モンスター5");
		mPlayer->SetMonster(4, MonsterMgr::Instance()->GetMonsterData(4));

		Debug::LogPrintf("プレイヤーデータのデッキにモンスターが設定されていません");

#endif//__MY_DEBUG__
	}
	
	// プレイヤーモンスター
	for (int i = 0; i < 5; i++) {

		MONSTER_DATA_t add;
		Monster* monster = mPlayer->GetMonster(i);
		if (monster == nullptr) continue;
		add.monster = monster;
		add.moveOreder = 0;
		add.type = BattleBase::eDeckType_Player;
		add.isDead = false;
		add.moveType = BattleBase::eMoveType_Manual;
		add.graph = MonsterMgr::Instance()->GetGraphics(monster->GetId());
		add.graph.SetVisible(true);
		int y = 1100;
		if (monster->GetHomePosition() == Monster::eHomePosition_Back) {
			y = 1200;
		}
		add.graph.SetPosition(200 + i * 300, y);
		add.graph.SetBasePosition(200 + i * 300, y);
		//GraphicsDrawMgr::GetInstance()->Add(&add.graph, 0);

		mMonsterData.push_back(add);
	}
	

	// エネミーモンスター
	for (int i = 0; i < 5; i++) {
		MONSTER_DATA_t add;
		Monster* monster = mEnemy->GetMonster(i);
		if (monster == NULL) continue;
		add.monster = monster;
		add.moveOreder = 0;
		add.type = BattleBase::eDeckType_Enemy;
		add.isDead = false;
		add.moveType = BattleBase::eMoveType_Auto;
		add.graph = MonsterMgr::Instance()->GetGraphics(monster->GetId());
		add.graph.SetVisible(true);
		int y = 200;
		if (monster->GetHomePosition() == Monster::eHomePosition_Back) {
			y = 100;
		}
		add.graph.SetPosition(200 + i * 300, y);
		add.graph.SetBasePosition(200 + i * 300, y);
		//GraphicsDrawMgr::GetInstance()->Add(&add.graph, 0);

		mMonsterData.push_back(add);
	}

#if false

	for (int i = 0; i < 5; i++) {
		Monster* monster = mPlayer->GetMonster(i);
		if (monster == NULL) continue;
		mPlayerCard[i] = MonsterMgr::Instance()->GetGraphics(monster->GetId());
		mPlayerCard[i].SetVisible(true);
		mPlayerCard[i].SetPosition(200 + i * 300, 1100);
		mPlayerCard[i].SetBasePosition(200 + i * 300, 1100);
		GraphicsDrawMgr::GetInstance()->Add(&mPlayerCard[i], 0);
	}

	for (int i = 0; i < 5; i++) {
		Monster* monster = mEnemy->GetMonster(i);
		if (monster == NULL) continue;
		mEnemyCard[i] = MonsterMgr::Instance()->GetGraphics(monster->GetId());
	}
#endif

	mBattleAnimation = new BattleAnimation();
	TaskMgr::getInstance().Add(mBattleAnimation);
}

bool BattleBase::Initialize() {

	if (mGraphics->Load("Resources/Graphics/BG/image.png") == false) {
		Debug::ErorrMessage("画像データがありませんでした.");
		return false;
	}
	
	GraphicsDrawMgr::GetInstance()->Add(mGraphics, -1);
	mGraphics->SetVisible(true);

	nowPlaySkillEffect = nullptr;

#ifndef __MY_DEBUG__
	SaveData* save = AppData::GetInstance()->GetSaveData();

	if (!save->Exists()) {
		Debug::ErorrMessage("セーブデータが存在していません.");
		return false;
	}

	mPlayer = save->GetPlayer();

	if (mPlayer == NULL) {
		Debug::ErorrMessage("プレイヤーデータが存在していません.");
		return false;
	}
#endif

	mActionCommand = BattleBase::eCommand_CehcekActionType;
	mAnimPlayMonsterNum = 0;
	mStartAnimCount = 0;

	mIsAutoAction = false;

	mNowStep = eBattleStep_Fade;
	mMainStep = eBattleMainStep_MoveOrder;

	mButtons[BattleBase::eButtonType_Auto] = new Button(1700, 900, 200, 100, "Auto");
	mButtons[BattleBase::eButtonType_Auto]->SetOnListener(this);

	mButtons[BattleBase::eButtonType_Attack] = new Button(0, 0, 100, 40, "Attack");
	mButtons[BattleBase::eButtonType_Attack]->SetOnListener(this);

	mButtons[BattleBase::eButtonType_Skill] = new Button(0, 0, 100, 40, "Skill");
	mButtons[BattleBase::eButtonType_Skill]->SetOnListener(this);
	
	mButtons[BattleBase::eButtonType_Item] = new Button(0, 0, 100, 40, "Item");
	mButtons[BattleBase::eButtonType_Item]->SetOnListener(this);

	NexetStepRequest(eBattleStep_Initialize, eFadeType_In);

	return true;
}

void BattleBase::Finalize() {
	mGraphics->ReleseRequest();
	//Delete(mGraphics);
	Delete(mCard);
	mMoveData.clear();

	TaskMgr::getInstance().RequestKill(mBattleAnimation->GetTaskId());
	mBattleAnimation = NULL;

}

void BattleBase::PreviousUpdate() {

}

bool BattleBase::Updata() {

	switch (mNowStep) {
	case eBattleStep_Fade:
		if (Fade::GetInstance()->IsFadeEnd() == true) {
			mNowStep = mNextStep;
			mNextStep = eBattleStep_None;
		}
		break;
	case eBattleStep_Initialize:
		NexetStepRequest(eBattleStep_BattleStart);
		break;
	case eBattleStep_BattleStart:
		BattleStartAnimation();
		break;
	case eBattleStep_Main:
	{

		BattleBase::eBattleStep step =  BattleMainUpdate();
		if (step != BattleBase::eBattleStep_None) {
			NexetStepRequest(step, BattleBase::eFadeType_In);
		}
	}	
		break;
	case eBattleStep_Result:

		break;
	default: 
#ifdef __MY_DEBUG__
		Debug::ErorrMessage("設定されているステップが無効です.\n");		
#endif
		break;
	}

	return true;
}

void BattleBase::Draw() {

	//if (mNowStep < eBattleStep_Initialize) return;

	//mGraphics->Draw(0, 0, 255, 0.0, 1.0);

#if true

	for (unsigned int i = 0; i < mMonsterData.size(); i++) {
		MONSTER_DATA_t data = mMonsterData[i];
		Monster* monster = data.monster;
		if (monster == NULL) continue;
		int x = data.graph.GetPositionX();
		int y = data.graph.GetPositionY();

		if(monster->GetHp() < 0){
			if (data.type == BattleBase::eDeckType_Enemy) {
				data.graph.SetVisible(false);
				continue;
			}
			data.graph.SetAlpha(100);
		}

		data.graph.Draw();	//味方
		if (monster->GetHp() > 0) {
			int drawY = y - 35;
			DrawBox(x, drawY, x + 100 * ((float)monster->GetHp() / (float)monster->GetHpMax()), drawY + 20, GetColor(0, 255, 255), TRUE);
		}
#ifdef __MY_DEBUG__ 
		DxLib::DrawString(x, y += 20, monster->GetName(), GetColor(0, 255, 0));
		DxLib::DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Lvele   :%d", monster->GetLevel());
		DxLib::DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Type    :%d", monster->GetType());
		DxLib::DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Cost    :%d", monster->GetCost());
		DxLib::DrawFormatString(x, y += 20, GetColor(0, 255, 0), "HP      :%d/%d", monster->GetHp(), monster->GetHpMax());
		DxLib::DrawFormatString(x, y += 20, GetColor(0, 255, 0), "MP      :%d/%d", monster->GetMp(), monster->GetMpMax());
		DxLib::DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Attack  :%d", monster->GetAttack());
		DxLib::DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Deffence:%d", monster->GetDeffence());
		DxLib::DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Speed   :%d", monster->GetSpeed());
		DxLib::DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Exp     :%d", monster->GetExp());
		DxLib::DrawFormatString(x, y += 20, GetColor(0, 255, 0), "HomePos :%d", monster->GetHomePosition());
		DxLib::DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Pos X :%d Y :%d", mPlayerCard[i].GetPositionX(), mPlayerCard[i].GetPositionY());
#endif // __MY_DEBUG__

	}
	
	mButtons[BattleBase::eButtonType_Auto]->Draw();


#ifdef __MY_DEBUG__
	// 行動順番
	for (unsigned int i = 0; i < mMonsterData.size(); i++) {
		MONSTER_DATA_t data = mMonsterData[i];
		Monster* monster = data.monster;
		if (monster == NULL) continue;

		int x = 1600;
		int y = 60 + i * 20;
		static const char* moveType[2] = { "プレイヤー","エネミー" };
		DxLib::DrawFormatString(x, y, GetColor(0, 255, 0), "Oreder:%d %s %s ", data.moveOreder, monster->GetName(), moveType[data.type]);
	}
#endif // __MY_DEBUG__


#else
	for (int i = 0; i < 5; i++) {
		Monster* monster = mEnemy->GetMonster(i);
		if (monster == NULL) continue;
		//Graphics graph = MonsterMgr::Instance()->GetGraphics(monster->GetId());
		Graphics graph = mEnemyCard[i];
		int alpha = monster->GetHp() <= 0 ? 123 : 255;
		int y = 100;
		graph.Draw(200 + i * 300, y, alpha, 0.0, 1.0);	//敵
		if (monster->GetHp() > 0) {
			DrawBox(200 + i * 300, y, 200 + i * 300 + 75 * ((float)monster->GetHp() / (float)monster->GetHpMax()), y + 20, GetColor(0, 255, 255), TRUE);
		}
		DrawString(200 + i * 300, y += 20, monster->GetName(), GetColor(0, 255, 0));
		DrawFormatString(200 + i * 300, y += 20, GetColor(0, 255, 0), "Lvele   :%d", monster->GetLevel());
		DrawFormatString(200 + i * 300, y += 20, GetColor(0, 255, 0), "Type    :%d", monster->GetType());
		DrawFormatString(200 + i * 300, y += 20, GetColor(0, 255, 0), "Cost    :%d", monster->GetCost());
		DrawFormatString(200 + i * 300, y += 20, GetColor(0, 255, 0), "HP      :%d/%d", monster->GetHp(), monster->GetHpMax());
		DrawFormatString(200 + i * 300, y += 20, GetColor(0, 255, 0), "MP      :%d/%d", monster->GetMp(), monster->GetMpMax());
		DrawFormatString(200 + i * 300, y += 20, GetColor(0, 255, 0), "Attack  :%d", monster->GetAttack());
		DrawFormatString(200 + i * 300, y += 20, GetColor(0, 255, 0), "Deffence:%d", monster->GetDeffence());
		DrawFormatString(200 + i * 300, y += 20, GetColor(0, 255, 0), "Speed   :%d", monster->GetSpeed());
		DrawFormatString(200 + i * 300, y += 20, GetColor(0, 255, 0), "Exp     :%d", monster->GetExp());
		DrawFormatString(200 + i * 300, y += 20, GetColor(0, 255, 0), "HomePos :%d", monster->GetHomePosition());
	}

	for (int i = 0; i < 5; i++) {
		Monster* monster = mPlayer->GetMonster(i);
		if (monster == NULL) continue;
		// Graphics* graph = ComRes::Instance()->GetGraphicHandle((ComRes::eComResName)(ComRes::eComResName_Monster_00001 + i));
		//Graphics graph = MonsterMgr::Instance()->GetGraphics(monster->GetId());
		//Graphics graph = mPlayerCard[i];
		int y = 100;
		//graph.Draw(200 + i * 300, y, 255, 0.0, 1.0);	//敵
		y = 750;
		mPlayerCard[i].Draw();	//味方
		if (monster->GetHp() > 0) {
			DrawBox(200 + i * 300, y, 200 + i * 300 + 75 * ((float)monster->GetHp() / (float)monster->GetHpMax()), y + 20, GetColor(0, 255, 255), TRUE);
		}
		DrawString(200 + i * 300, y+=20, monster->GetName(), GetColor(0, 255, 0));
		DrawFormatString(200 + i * 300, y+=20, GetColor(0, 255, 0), "Lvele   :%d", monster->GetLevel());
		DrawFormatString(200 + i * 300, y+=20, GetColor(0, 255, 0), "Type    :%d", monster->GetType());
		DrawFormatString(200 + i * 300, y+=20, GetColor(0, 255, 0), "Cost    :%d", monster->GetCost());
		DrawFormatString(200 + i * 300, y+=20, GetColor(0, 255, 0), "HP      :%d/%d", monster->GetHp(), monster->GetHpMax());
		DrawFormatString(200 + i * 300, y+=20, GetColor(0, 255, 0), "MP      :%d/%d", monster->GetMp(), monster->GetMpMax());
		DrawFormatString(200 + i * 300, y+=20, GetColor(0, 255, 0), "Attack  :%d", monster->GetAttack());
		DrawFormatString(200 + i * 300, y+=20, GetColor(0, 255, 0), "Deffence:%d", monster->GetDeffence());
		DrawFormatString(200 + i * 300, y+=20, GetColor(0, 255, 0), "Speed   :%d", monster->GetSpeed());
		DrawFormatString(200 + i * 300, y+=20, GetColor(0, 255, 0), "Exp     :%d", monster->GetExp());
		DrawFormatString(200 + i * 300, y+=20, GetColor(0, 255, 0), "HomePos :%d", monster->GetHomePosition());
		DrawFormatString(200 + i * 300, y += 20, GetColor(0, 255, 0), "Pos X :%d Y :%d", mPlayerCard[i].GetPositionX(),mPlayerCard[i].GetPositionY());
	}
#endif

	switch (mNowStep) {
	case eBattleStep_BattleStart:
		
		break;
	case eBattleStep_Main:
		//バトルメイン処理
		BattleMainDraw();
		break;
	case eBattleStep_Result:

#ifdef __ANDROID__
		if (ClickInput::GetInstance()->Press(0)) {
			TaskMgr::getInstance().RequestKill(this->mTaskId);
		}
#endif


		break;
	}


#ifdef __MY_DEBUG__
		DxLib::DrawFormatString(0, 40, GetColor(255, 0, 0), "Now Step:%s", dbg_STEP_TITLE[mNowStep]);
		DxLib::DrawFormatString(20, 60, GetColor(255, 0, 0), "Now Main Step:%s", dbg_MAIN_STEP_TITLE[mMainStep]);
#endif

}

void BattleBase::PostUpdate() {
	
#ifdef __MY_DEBUG__
#ifdef __WINDOWS__
	
	if (Keyboard_Press(KEY_INPUT_X)) {
		TaskMgr::getInstance().RequestKill(this->mTaskId);
	}

#endif
#endif

}


/*
次のステップを設定する
eBattleStep nextStep	:次のステップ登録
eFadeType fadeType		:フェードタイプ
*/
void BattleBase::NexetStepRequest(eBattleStep nextStep, eFadeType fadeType/* = eFadeType_None*/) {

#ifdef __MY_DEBUG__
	if (nextStep < eBattleStep_None || nextStep > eBattleStep_Result) {
		Debug::ErorrMessage("設定されているステップが無効です.\n");
	}
#endif

	mNowStep = eBattleStep_Fade;
	mNextStep = nextStep;

	if (fadeType == eFadeType_In) {
		Fade::GetInstance()->FadeIn();
	}
	else if (fadeType == eFadeType_Out) {
		Fade::GetInstance()->FadeOut();
	}

}

int mTargetIdx = 0;
int mMoveChrIdx = 0;

BattleBase::eBattleStep BattleBase::BattleMainUpdate() {

	BattleBase::eBattleStep step = BattleBase::eBattleStep_None;
	
	/*
	
		コマンド選択
			選択した行動をスタック
		行動フェーズ
		経験値取得フェーズ

	*/

	mButtons[BattleBase::eButtonType_Auto]->Update();

	switch (mMainStep) {
	case BattleBase::eBattleMainStep_MoveOrder:

		// 行動順番を設定
		for (unsigned int i = 0; i < mMonsterData.size(); i++) {
			for (unsigned int j = 0; j < mMonsterData.size(); j++) {
				Monster* mon1 = mMonsterData[i].monster;
				Monster* mon2 = mMonsterData[j].monster;
				if (mon1->GetSpeed() > mon2->GetSpeed()) {
					auto tmp = mMonsterData[i];
					mMonsterData[i] = mMonsterData[j];
					mMonsterData[j] = tmp;
				}

			}
		}

		for (unsigned int i = 0; i < mMonsterData.size(); i++) {
			mMonsterData[i].moveOreder = i;
		}

		mMoveOrderMonsterNum = 0;

		mMainStep = BattleBase::eBattleMainStep_Command;
		break;
	case BattleBase::eBattleMainStep_Command:

		SelectCommandUpdate();
		
	break;
	case BattleBase::eBattleMainStep_Battle:

#if true

	{

		/*
			ダメージ計算結果を保持
			攻撃/回復/スキル/アイテム アニメーション開始
			アニメーション終了待ち
			ダメージ計算結果を対象のモンスターに設定
			ゲージ変動アニメーション開始

			すべてのモンスターの行動終了判断
				すべてのモンスターが行動を終了している　→　バトル終了判断
				すべてのモンスターが行動を終了していない　→　ダメージ計算結果を保持　

		*/

		mTargetList.clear();

		for (auto itr = mMoveData.begin(); itr != mMoveData.end();) {

			BattleBase::MOVE_DATA_t move = *itr;
			BattleBase::DAMAGE_MONSTER_t dmgMonster;

			Monster* moveMonster = move.moveMonster;
			Monster* targetMonster = move.targetMonster;
					
			BattleBase::eActiveType type = move.activeType;

			BattleAnimation::eAnimationNo orderAnim = BattleAnimation::eAnimationNo_Attack_00;

			Graphics* graph = &mMonsterData[mMoveOrderMonsterNum].graph;
			graph->SetBasePosition(graph->GetPositionX(), graph->GetPositionY());
			if (move.moveDeckType == BattleBase::eDeckType_Enemy) {
				orderAnim = BattleAnimation::eAnimationNo_Attack_01;
			}

			if (type == BattleBase::eActiveType::eActiveType_Skill) {
				float x = move.targetPosition.posX;
				float y = move.targetPosition.posY;
				nowPlaySkillEffect = SkillMgr::GetInstance()->Play(move.skillId,x,y);
			}
			// 行動するモンスターの体力が0より大きいか判断する
			if (moveMonster->GetHp() > 0) {

				if (targetMonster->GetHp() <= 0) {
					targetMonster = BattleBase::GetLiveMonster(move.targetDeckType);
				}

				if (targetMonster != NULL) {

					int damageResult = 0;

					switch (type) {
					case BattleBase::eActiveType_Attack:
						damageResult = BattleCalculator::NormalDamage(*moveMonster, *targetMonster);
						break;
					case BattleBase::eActiveType_Recovery:
						damageResult = -20;
						break;
					case BattleBase::eActiveType_Skill:
						damageResult = BattleCalculator::SkillDamage(*moveMonster, *targetMonster);
						break;
					}

					dmgMonster.monster = targetMonster;
					dmgMonster.damage = targetMonster->GetHp() - damageResult;
					
					mTargetList.push_back(dmgMonster);

					Debug::LogPrintf("Atk:%s => Def:%s Dmg:%d\n",
						moveMonster->GetName(),
						targetMonster->GetName(),
						damageResult);
				}

				mAnim = mBattleAnimation->RequestAnim(orderAnim, graph, true);

			}


			mMoveData.erase(itr);
			if (mMoveData.size() == 0) {
				break;
			}
			else {
				itr = mMoveData.begin();
			}
		}
#endif	// false

		mMoveOrderMonsterNum++;
		mMainStep = eBattleMainStep_BattleAnim;
	}
		break;
	case BattleBase::eBattleMainStep_BattleAnim:

		if (mAnim == NULL || mAnim->IsPlay() == false && (nowPlaySkillEffect == nullptr || nowPlaySkillEffect->IsPlay() == false)) {
			mMainStep = eBattleMainStep_Judgement;

			for (unsigned int i = 0; i < mTargetList.size(); i++) {
				mTargetList[i].monster->SetHp(mTargetList[i].damage);
			}
			nowPlaySkillEffect = nullptr;
		}

		break;
	case BattleBase::eBattleMainStep_Judgement:

		// 死亡チェック
	
		bool isDead = CheckAllDead(BattleBase::eDeckType_Enemy);
		if (isDead) {
			step = BattleBase::eBattleStep_Result;
		}

		isDead = CheckAllDead(BattleBase::eDeckType_Player);
		if (isDead) {
			step = BattleBase::eBattleStep_Result;
		}

		for (unsigned int i = 0; i < mMonsterData.size(); i++) {
			if (mMonsterData[i].monster->GetHp() < 0) {
				mMonsterData[i].isDead = true;
			}
			else {
				mMonsterData[i].isDead = false;
			}
		}

		//if (Keyboard_Press(KEY_INPUT_Z)) 
		{
			if ((unsigned int)mMoveOrderMonsterNum >= mMonsterData.size()) {
				mMainStep = eBattleMainStep_MoveOrder;
			}
			else {
				mMainStep = eBattleMainStep_Command;
			}
		}
#if false
		if (Keyboard_Press(KEY_INPUT_A)) {
			step = BattleBase::eBattleStep_Result;
		}
#endif
		break;
	}




	return step;
}

void BattleBase::BattleMainDraw() {

	char str[1024] = { "" };

	switch (mMainStep) {
	case BattleBase::eBattleMainStep_Command:
	
		SelectCommandDraw();
	
		break;
	case BattleBase::eBattleMainStep_Battle:
		strcpyDx(str, "Zキー: 判定へ");
		break;
	case BattleBase::eBattleMainStep_Judgement:
		strcpyDx(str, "Zキー: コマンド選択へ　Aキー: リザルトへ");
		break;
	}

	DrawString(200, 600, str, GetColor(255, 0, 0));

}


/*
生存しているモンスターを返却する
eDeckType type		: 探索するデッキタイプ
*/
Monster* BattleBase::GetLiveMonster(eDeckType type) {
	Monster* ret = NULL;
	if (type == BattleBase::eDeckType_Player) {
		
		for (int i = 0; i < 5; i++) {
			Monster* mon = mPlayer->GetMonster(i);
			if (mon == NULL) continue;
			if (mon->GetHp() > 0) {
				ret = mon;
				break;
			}
		}

	}
	else {
		
		for (int i = 0; i < 5; i++) {
			Monster* mon = mEnemy->GetMonster(i);
			if (mon == NULL) continue;
			if (mon->GetHp() > 0) {
				ret = mon;
				break;
			}
		}

	}
	return ret;
}

/*
手持ちのモンスターがすべて倒されているか判断する
return	true	:倒されている
false	:倒されていない
*/
bool BattleBase::CheckAllDead(eDeckType type) {

	bool ret = false;
	int deadCount = 0;

	if (type == BattleBase::eDeckType_Player) {

#if true

		for (unsigned int i = 0; i < mMonsterData.size(); i++) {
			MONSTER_DATA_t data = mMonsterData[i];
			if (data.type == type) {
				if (data.monster->GetHp() <= 0) {
					data.isDead = true;
					deadCount++;
				}
			}
		}
#else
		for (int i = 0; i < 5; i++) {
			Monster* mon = mPlayer->GetMonster(i);
			if (mon == NULL) continue;
			if (mon->GetHp() <= 0) {
				deadCount++;
			}
		}
#endif
		if (deadCount == mPlayer->GetSetMonsterNum()) {
			ret = true;
		}


	}
	else {

		for (int i = 0; i < 5; i++) {
			Monster* mon = mEnemy->GetMonster(i);
			if (mon == NULL) continue;
			if (mon->GetHp() <= 0) {
				deadCount++;
			}
		}

		if (deadCount == mEnemy->GetSetNum()) {
			ret = true;
		}

	}
	return ret;

}

void BattleBase::BattleStartAnimation() {
	mStartAnimCount++;

	if (mStartAnimCount % 20 != 0) return ;

	if (mAnimPlayMonsterNum >= 5) {
		NexetStepRequest(eBattleStep_Main);
		mAnimPlayMonsterNum = 0;
		mStartAnimCount = 0;
		return ;
	}

	Monster* monster = mPlayer->GetMonster(mAnimPlayMonsterNum);

	if (monster == NULL) {
		mAnimPlayMonsterNum++;
		mStartAnimCount--;
		return;

	}

	int monsterNum = 0;
	for (unsigned int i = 0; i < mMonsterData.size(); i++) {
		if (mMonsterData[i].monster == monster) {
			monsterNum = i;
		}
	}

	BattleAnimation::eAnimationNo animNo = BattleAnimation::eAnimationNo_InSide_00;
	if (monster->GetHomePosition() == Monster::eHomePosition_Back) {
		animNo = BattleAnimation::eAnimationNo_InSide_02;
	}

	//mBattleAnimation->RequestAnim(animNo, &mPlayerCard[mAnimPlayMonsterNum], true);
	mBattleAnimation->RequestAnim(animNo, &mMonsterData[monsterNum].graph, true);
	mAnimPlayMonsterNum++;
}

void BattleBase::SelectCommandUpdate() {

	MONSTER_DATA_t data = mMonsterData[mMoveOrderMonsterNum];

	if (data.isDead == true || data.monster->GetHp() <= 0) {
		mMoveOrderMonsterNum++;
		return;
	}

	switch (mActionCommand) {
	case BattleBase::eCommand_CehcekActionType:

		if (data.type == BattleBase::eDeckType_Player) {

			if (data.moveType == BattleBase::eMoveType_Manual) {
				mActionCommand = BattleBase::eCommand_Select;
			}
			else if (data.moveType == BattleBase::eMoveType_Auto) {
				// 自動攻撃(通常攻撃)
				// 攻撃対象は体力が最も少ないモンスターへ行う
				mOrderMoveData.moveDeckType = data.type;
				mOrderMoveData.moveMonster = data.monster;
				mOrderMoveData.activeType = BattleBase::eActiveType_Attack;
				mOrderMoveData.skillId = -1;

				for (unsigned int i = 0; i < mMonsterData.size(); i++) {
					if (mMonsterData[i].type == BattleBase::eDeckType_Enemy) {
						if (mMonsterData[i].isDead == true) continue;
						mOrderMoveData.targetDeckType = BattleBase::eDeckType_Enemy;
						mOrderMoveData.targetMonster = mMonsterData[i].monster;
						mOrderMoveData.targetPosition.posX = mMonsterData[i].graph.GetPositionX();
						mOrderMoveData.targetPosition.posY = mMonsterData[i].graph.GetPositionY();
						mMoveData.push_back(mOrderMoveData);
						break;
					}
				}

				mMainStep = BattleBase::eBattleMainStep_Battle;
			}
		}
		else { // エネミーの行動
			   // 自動攻撃
			   // 攻撃対象はとりあえずランダム
			mOrderMoveData.moveDeckType = data.type;
			mOrderMoveData.moveMonster = data.monster;
			mOrderMoveData.activeType = BattleBase::eActiveType_Attack;
			for (unsigned int i = 0; i < mMonsterData.size(); i++) {
				if (mMonsterData[i].type == BattleBase::eDeckType_Player) {
					if (mMonsterData[i].isDead == true) continue;
					mOrderMoveData.targetDeckType = BattleBase::eDeckType_Player;
					mOrderMoveData.targetMonster = mMonsterData[i].monster;
					mOrderMoveData.targetPosition.posX = mMonsterData[i].graph.GetPositionX();
					mOrderMoveData.targetPosition.posY = mMonsterData[i].graph.GetPositionY();
					mMoveData.push_back(mOrderMoveData);
					break;
				}
			}

			mMainStep = BattleBase::eBattleMainStep_Battle;
		}

		mOrderMoveData.moveDeckType = data.type;

		break;
	case BattleBase::eCommand_Select:

	{
		int x = data.graph.GetPositionX() - 120;
		int y = data.graph.GetPositionY() - 100;
		for (int i = BattleBase::eButtonType_Attack; i < BattleBase::eButtonType_Num; i++) {
			mButtons[i]->SetVisible(true);
			mButtons[i]->SetPosition(x, y);
			mButtons[i]->Update();
			x += 110;
		}

	}

	break;
	case BattleBase::eCommand_SelectTarget:

		// スキル選択
		// 　回復系
		//   補助系
		//   復活系
		//アイテム選択
		// 　回復系
		// 　復活系
		// プレイヤーデッキの選択もする

		for (unsigned int i = 0; i < mMonsterData.size(); i++) {
			MONSTER_DATA_t  data = mMonsterData[i];
			if (data.type == BattleBase::eDeckType_Enemy) {
				if (data.isDead) continue;
				if (data.graph.IsTouch()) {
					mOrderMoveData.targetDeckType = data.type;
					mOrderMoveData.targetMonster = data.monster;
					mOrderMoveData.targetPosition.posX = data.graph.GetPositionX();
					mOrderMoveData.targetPosition.posY = data.graph.GetPositionY();
					mActionCommand = BattleBase::eCommand_Decision;
					break;
				}
			}
		}

		break;
	case BattleBase::eCommand_Decision:
		// 行動データに設定
		mOrderMoveData.moveMonster = data.monster;
		mOrderMoveData.skillId = data.monster->GetSkillNumber();
		mMoveData.push_back(mOrderMoveData);
		mActionCommand = BattleBase::eCommand_CehcekActionType;
		mMainStep = BattleBase::eBattleMainStep_Battle;

		for (int i = BattleBase::eButtonType_Attack; i < BattleBase::eButtonType_Num; i++) {
			mButtons[i]->SetVisible(false);
		}

		break;
	}


}

void BattleBase::SelectCommandDraw() {

	MONSTER_DATA_t data = mMonsterData[mMoveOrderMonsterNum];
	switch (mActionCommand) {
	case BattleBase::eCommand_CehcekActionType:

		break;
	case BattleBase::eCommand_Select:
	{
		// 行動選択を表示

		int x = data.graph.GetPositionX();
		int y = data.graph.GetPositionY() - 100;

		for (int i = BattleBase::eButtonType_Attack; i < BattleBase::eButtonType_Num; i++) {
			mButtons[i]->Draw();
		}


		DrawString(200, 620, "攻撃方法選択", GetColor(255, 0, 0));
	}
	break;
	case BattleBase::eCommand_SelectTarget:
		// 対象を設定を表示
		DrawString(200, 620, "アクション対象を選択", GetColor(255, 0, 0));
		break;
	case BattleBase::eCommand_Decision:
		// 行動データに設定
		DrawString(200, 620, "行動決定", GetColor(255, 0, 0));
		break;
	}

#ifdef __MY_DEBUG__
	DrawString(200, 600, "Zキー: バトルへ", GetColor(255, 0, 0));
#endif // __MY_DEBUG__

}

void BattleBase::OnClick(View* view) {
	
	if (view == mButtons[BattleBase::eButtonType_Auto]) {
		
		mIsAutoAction = !mIsAutoAction;
		
		BattleBase::eMoveType type = BattleBase::eMoveType_Manual;
		if (mIsAutoAction) {
			type = BattleBase::eMoveType_Auto;
		}

		for (unsigned int i = 0; i < mMonsterData.size(); i++) {
			if (mMonsterData[i].type == BattleBase::eDeckType_Player) {
				mMonsterData[i].moveType = type;
			}
		}
		mActionCommand = BattleBase::eCommand_CehcekActionType;
	}
	else if (view == mButtons[BattleBase::eButtonType_Attack]) {
		mOrderMoveData.activeType = BattleBase::eActiveType_Attack;
		mActionCommand = BattleBase::eCommand_SelectTarget;
	}
	else if (view == mButtons[BattleBase::eButtonType_Skill]) {
		mOrderMoveData.activeType = BattleBase::eActiveType_Skill;
		mActionCommand = BattleBase::eCommand_SelectTarget;
	}
	else if (view == mButtons[BattleBase::eButtonType_Item]) {
		mOrderMoveData.activeType = BattleBase::eActiveType_Recovery;
		mActionCommand = BattleBase::eCommand_SelectTarget;
	}


}




BattleBase::ButtonAnim::ButtonAnim(Button* button) : TaskBase() , mButton(NULL){

	mButton = button;

}

BattleBase::ButtonAnim::~ButtonAnim() {

}

bool BattleBase::ButtonAnim::Initialize() {
	return true;
}

void BattleBase::ButtonAnim::Finalize() {

}

void BattleBase::ButtonAnim::PreviousUpdate() {

	if (mButton == NULL) return;

}

void BattleBase::ButtonAnim::InputUpdate() {

}

bool BattleBase::ButtonAnim::Updata() {

	if (mButton == NULL) return true;

	switch (mAnim) {
	case BattleBase::ButtonAnim::eAnim_InSide:

		break;
	case BattleBase::ButtonAnim::eAnim_OutSide:

		break;
	}

	return true;
}

void BattleBase::ButtonAnim::PostUpdate() {

	if (mButton == NULL) return;

}

void BattleBase::ButtonAnim::Draw() {

}


bool BattleBase::ButtonAnim::IsPlayAnim() {
	return mAnim != eAnim_None;
}

void BattleBase::ButtonAnim::PlayAnim(eAnim anim) {
	this->mAnim = anim;
}