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
		GraphicsDrawMgr::GetInstance()->Add(&add.graph, 0);

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
		int y = 1100;
		if (monster->GetHomePosition() == Monster::eHomePosition_Back) {
			y = 1200;
		}
		add.graph.SetPosition(200 + i * 300, y);
		add.graph.SetBasePosition(200 + i * 300, y);
		GraphicsDrawMgr::GetInstance()->Add(&add.graph, 0);

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
		GraphicsDrawMgr::GetInstance()->Add(&add.graph, 0);

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
		GraphicsDrawMgr::GetInstance()->Add(&add.graph, 0);

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
	
#ifndef __MY_DEBUG__
	SaveData* save = AppData::GetInstance().GetSaveData();

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
	mGraphics->Relese();
	Delete(mGraphics);
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

#if true
	{
		mStartAnimCount++;

		if (mStartAnimCount % 20 != 0) break;

		if (mAnimPlayMonsterNum >= 5) {
			NexetStepRequest(eBattleStep_Main);
			mAnimPlayMonsterNum = 0;
			mStartAnimCount = 0;
			break;
		}

		Monster* monster = mPlayer->GetMonster(mAnimPlayMonsterNum);

		if (monster == NULL) {
			mAnimPlayMonsterNum++;
			mStartAnimCount--;
			break;

		}

		int monsterNum = 0;
		for (int i = 0; i < mMonsterData.size(); i++) {
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
#else
		for (int i = 0; i < 5; i++) {
			if(mPlayer->GetMonster(i) == NULL) continue;
			mBattleAnimation->RequestAnim(BattleAnimation::eAnimationNo_InSide_00, &mPlayerCard[i], true);
		}
		
		NexetStepRequest(eBattleStep_Main);
#endif
		break;
	case eBattleStep_Main:
	{
		//Debug::LogPrintf("ダメージ %d\n", BattleCalculator::NormalDamage(*mPlayer->GetMonster(0), *mPlayer->GetMonster(4)));


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

	mGraphics->Draw(0, 0, 255, 0.0, 1.0);

#if true

	for (int i = 0; i < mMonsterData.size(); i++) {
		MONSTER_DATA_t data = mMonsterData[i];
		Monster* monster = data.monster;
		if (monster == NULL) continue;
		int x = data.graph.GetPositionX();
		int y = data.graph.GetPositionY();
		data.graph.Draw();	//味方
		if (monster->GetHp() > 0 || data.isDead) {
			int drawY = y - 35;
			DrawBox(x, drawY, x + 100 * ((float)monster->GetHp() / (float)monster->GetHpMax()), drawY + 20, GetColor(0, 255, 255), TRUE);
		}
#ifdef __MY_DEBUG__
		DrawString(x, y += 20, monster->GetName(), GetColor(0, 255, 0));
		DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Lvele   :%d", monster->GetLevel());
		DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Type    :%d", monster->GetType());
		DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Cost    :%d", monster->GetCost());
		DrawFormatString(x, y += 20, GetColor(0, 255, 0), "HP      :%d/%d", monster->GetHp(), monster->GetHpMax());
		DrawFormatString(x, y += 20, GetColor(0, 255, 0), "MP      :%d/%d", monster->GetMp(), monster->GetMpMax());
		DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Attack  :%d", monster->GetAttack());
		DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Deffence:%d", monster->GetDeffence());
		DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Speed   :%d", monster->GetSpeed());
		DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Exp     :%d", monster->GetExp());
		DrawFormatString(x, y += 20, GetColor(0, 255, 0), "HomePos :%d", monster->GetHomePosition());
		DrawFormatString(x, y += 20, GetColor(0, 255, 0), "Pos X :%d Y :%d", mPlayerCard[i].GetPositionX(), mPlayerCard[i].GetPositionY());
#endif // __MY_DEBUG__

	}

	mButtons[BattleBase::eButtonType_Auto]->Draw();


#ifdef __MY_DEBUG__
	// 行動順番
	for (int i = 0; i < mMonsterData.size(); i++) {
		MONSTER_DATA_t data = mMonsterData[i];
		Monster* monster = data.monster;
		if (monster == NULL) continue;

		int x = 1600;
		int y = 60 + i * 20;
		static const char* moveType[2] = { "プレイヤー","エネミー" };
		DrawFormatString(x, y, GetColor(0, 255, 0), "Oreder:%d %s %s ", data.moveOreder, monster->GetName(), moveType[data.type]);
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

		break;
	}


#ifdef __MY_DEBUG__
		DrawFormatString(0, 40, GetColor(255, 0, 0), "Now Step:%s", dbg_STEP_TITLE[mNowStep]);
		DrawFormatString(20, 60, GetColor(255, 0, 0), "Now Main Step:%s", dbg_MAIN_STEP_TITLE[mMainStep]);
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
#if false
	for (int i = 0; i < 5; i++) {
		Monster* monster = mPlayer->GetMonster(i);
		if (monster == NULL) continue;
		if (monster->GetHp() <= 0) continue;
		if (mPlayerCard[i].IsTouch()) {
			//該当のモンスターの行動タイプをスキルに設定する
			for (auto itr = mMoveData.begin(); itr != mMoveData.end(); itr++) {
				if (itr->moveId == monster->GetId()) {
					itr->activeType = BattleBase::eActiveType_Skill;
					Debug::LogPrintf("スキル発動 %s\n",monster->GetName());
				}
			}
		}
	}
#endif


	switch (mMainStep) {
	case BattleBase::eBattleMainStep_MoveOrder:

		// 行動順番を設定
		for (int i = 0; i < mMonsterData.size(); i++) {
			for (int j = 0; j < mMonsterData.size(); j++) {
				Monster* mon1 = mMonsterData[i].monster;
				Monster* mon2 = mMonsterData[j].monster;
				if (mon1->GetSpeed() > mon2->GetSpeed()) {
					auto tmp = mMonsterData[i];
					mMonsterData[i] = mMonsterData[j];
					mMonsterData[j] = tmp;
				}

			}
		}

		for (int i = 0; i < mMonsterData.size(); i++) {
			mMonsterData[i].moveOreder = i;
		}

		mMoveOrderMonsterNum = 0;

		mMainStep = BattleBase::eBattleMainStep_Command;
		break;
	case BattleBase::eBattleMainStep_Command:

	{
		MONSTER_DATA_t data = mMonsterData[mMoveOrderMonsterNum];

		if (data.isDead == true || data.monster->GetHp() <= 0) {
			mMoveOrderMonsterNum++;
			break;
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
					mOrderMoveData.moveMonster = data.monster;
					mOrderMoveData.activeType = BattleBase::eActiveType_Attack;

					for (int i = 0; i < mMonsterData.size(); i++) {
						if (mMonsterData[i].type == BattleBase::eDeckType_Enemy) {
							if (mMonsterData[i].isDead == true) continue;
							mOrderMoveData.targetDeckType = BattleBase::eDeckType_Enemy;
							mOrderMoveData.targetMonster = mMonsterData[i].monster;
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
				mOrderMoveData.moveMonster = data.monster;
				mOrderMoveData.activeType = BattleBase::eActiveType_Attack;
				for (int i = 0; i < mMonsterData.size(); i++) {
					if (mMonsterData[i].type == BattleBase::eDeckType_Player) {
						if (mMonsterData[i].isDead == true) continue;
						mOrderMoveData.targetDeckType = BattleBase::eDeckType_Player;
						mOrderMoveData.targetMonster = mMonsterData[i].monster;
						mMoveData.push_back(mOrderMoveData);
						break;
					}
				}

				mMainStep = BattleBase::eBattleMainStep_Battle;
			}

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

			for (int i = 0; i < mMonsterData.size(); i++) {
				MONSTER_DATA_t  data = mMonsterData[i];
				if (data.type == BattleBase::eDeckType_Enemy) {
					if (data.graph.IsTouch()) {
						mOrderMoveData.targetDeckType = data.type;
						mOrderMoveData.targetMonster = data.monster;
						mActionCommand = BattleBase::eCommand_Decision;
						break;
					}
				}
			}

			break;
		case BattleBase::eCommand_Decision:
			// 行動データに設定
			mOrderMoveData.moveMonster = data.monster;
			mMoveData.push_back(mOrderMoveData);
			mActionCommand = BattleBase::eCommand_CehcekActionType;
			mMainStep = BattleBase::eBattleMainStep_Battle;

			for (int i = BattleBase::eButtonType_Attack; i < BattleBase::eButtonType_Num; i++) {
				mButtons[i]->SetVisible(false);
			}

			break;
		}


	}


#if false
#ifdef __WINDOWS__

	if (Keyboard_Press(KEY_INPUT_Z)) {
		mMainStep = eBattleMainStep_Battle;

		for (int i = 0; i < 5; i++) {

			Monster* moveMonster = mPlayer->GetMonster(mMoveChrIdx);
			Monster* targetMonster = mEnemy->GetMonster(mTargetIdx);

			if (moveMonster == NULL) continue;

			if (moveMonster->GetHp() <= 0) {
				continue;
			}

			while (targetMonster == NULL || targetMonster->GetHp() <= 0) {
				mTargetIdx = (mTargetIdx + 1) % 5;
				targetMonster = mEnemy->GetMonster(mTargetIdx);
			}

			BattleBase::MOVE_DATA_t add = {
				BattleBase::eDeckType_Player,
				mMoveChrIdx,
				BattleBase::eDeckType_Enemy,
				mTargetIdx,
				BattleBase::eActiveType_Attack,
			};
			mMoveData.push_back(add);
			mMoveChrIdx = (mMoveChrIdx + 1) % 5;
			mTargetIdx = (mTargetIdx + 1) % 5;
		}

		for (int i = 0; i < 5; i++) {

			Monster* moveMonster = mEnemy->GetMonster(mMoveChrIdx);
			Monster* targetMonster = mPlayer->GetMonster(mTargetIdx);

			if (moveMonster == NULL || moveMonster->GetHp() <= 0) {
				continue;
			}

			while (targetMonster == NULL || targetMonster->GetHp() <= 0) {
				mTargetIdx = (mTargetIdx + 1) % 5;
				targetMonster = mPlayer->GetMonster(mTargetIdx);
			}

			BattleBase::MOVE_DATA_t add = {
				BattleBase::eDeckType_Enemy,
				mMoveChrIdx,
				BattleBase::eDeckType_Player,
				mTargetIdx,
				BattleBase::eActiveType_Attack,
			};
			mMoveData.push_back(add);
			mMoveChrIdx = (mMoveChrIdx + 1) % 5;
			mTargetIdx = (mTargetIdx + 1) % 5;
		}

	}
#endif
#endif
	/*
		誰が
		誰を対象に
		どのような行動をするのか　行動タイプ


	*/

	break;
	case BattleBase::eBattleMainStep_Battle:

#if true


		//if (Keyboard_Press(KEY_INPUT_Z)) 
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
			if (move.moveDeckType == BattleBase::eDeckType_Player) {
				Graphics* graph = &mMonsterData[mMoveOrderMonsterNum].graph;
				//moveMonster = mPlayer->GetMonster(moveId);
				//mPlayerCard[moveId].SetBasePosition(mPlayerCard[moveId].GetPositionX(), mPlayerCard[moveId].GetPositionY());
				graph->SetBasePosition(graph->GetPositionX(), graph->GetPositionY());
				mAnim = mBattleAnimation->RequestAnim(BattleAnimation::eAnimationNo_Transrate_Scale, graph, true);

			}
			else {
				Graphics* graph = &mMonsterData[mMoveOrderMonsterNum].graph;
				//moveMonster = mPlayer->GetMonster(moveId);
				//mPlayerCard[moveId].SetBasePosition(mPlayerCard[moveId].GetPositionX(), mPlayerCard[moveId].GetPositionY());
				graph->SetBasePosition(graph->GetPositionX(), graph->GetPositionY());
				mAnim = mBattleAnimation->RequestAnim(BattleAnimation::eAnimationNo_Transrate_Scale, graph, true);
			}

			// 行動するモンスターの体力が0より大きいか判断する
			if (moveMonster->GetHp() > 0) {


#if false
				if (move.targetDeckType == BattleBase::eDeckType_Player) {
					targetMonster = mPlayer->GetMonster(targetId);
				}
				else {
					targetMonster = mEnemy->GetMonster(targetId);
				}
#endif

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
					//int damage = targetMonster->GetHp() - damageResult;
					dmgMonster.damage = targetMonster->GetHp() - damageResult;

					/*
						ここから攻撃アニメ―ション開始
					*/

					//targetMonster->SetHp(damage);

					mTargetList.push_back(dmgMonster);

					Debug::LogPrintf("Atk:%s => Def:%s Dmg:%d\n",
						moveMonster->GetName(),
						targetMonster->GetName(),
						damageResult);
				}
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
#if false
		int ret = BattleCalculator::NormalDamage(*mPlayer->GetMonster(mMoveChrIdx), *mEnemy->GetMonster(mTargetIdx));
		mEnemy->GetMonster(mTargetIdx)->SetHp(mEnemy->GetMonster(mTargetIdx)->GetHp() - ret);

		Debug::LogPrintf("Atk:%s => Def:%s Dmg:%d\n",
			mPlayer->GetMonster(mMoveChrIdx)->GetName(),
			mEnemy->GetMonster(mTargetIdx)->GetName(),
			ret);

		ret = BattleCalculator::NormalDamage(*mEnemy->GetMonster(0), *mPlayer->GetMonster(1));
		mPlayer->GetMonster(1)->SetHp(mPlayer->GetMonster(1)->GetHp() - ret);
#endif
		mMoveOrderMonsterNum++;
		mMainStep = eBattleMainStep_BattleAnim;
	}
		break;
	case BattleBase::eBattleMainStep_BattleAnim:

		if (mAnim == NULL || mAnim->IsPlay() == false) {
			mMainStep = eBattleMainStep_Judgement;

			for (int i = 0; i < mTargetList.size(); i++) {
				mTargetList[i].monster->SetHp(mTargetList[i].damage);
			}

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

		//if (Keyboard_Press(KEY_INPUT_Z)) 
		{
			if (mMoveOrderMonsterNum >= mMonsterData.size()) {
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
	{
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


		strcpyDx(str, "Zキー: バトルへ");
	}
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

		for (int i = 0; i < mMonsterData.size(); i++) {
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

void BattleBase::OnClick(View* view) {
	
	if (view == mButtons[BattleBase::eButtonType_Auto]) {
		
		mIsAutoAction = !mIsAutoAction;
		
		BattleBase::eMoveType type = BattleBase::eMoveType_Manual;
		if (mIsAutoAction) {
			type = BattleBase::eMoveType_Auto;
		}

		for (int i = 0; i < mMonsterData.size(); i++) {
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