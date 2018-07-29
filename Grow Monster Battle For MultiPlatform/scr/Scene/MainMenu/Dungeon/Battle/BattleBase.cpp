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
#include "../DungeonMgr.h"
#include "Common/Script/ScriptBase.h"


BattleBase::BattleBase() : TaskBase() {
	mGraphics = new Graphics();
	mCard = new Graphics();
	
	Monster* monster = new Monster();

	mPlayer = new Player();

	monster->SetName("モンスター1");
	monster->SetLevel(1);
	monster->SetAttack(12);
	monster->SetDeffence(8);
	monster->SetSpeed(5);
	monster->SetHp(120);
	monster->SetHpMax(120);

	
	mPlayer->SetMonster(0, MonsterMgr::Instance()->getMonsterData(0));
	monster->SetName("モンスター2");
	mPlayer->SetMonster(1, MonsterMgr::Instance()->getMonsterData(1));
	monster->SetName("モンスター3");
	mPlayer->SetMonster(2, MonsterMgr::Instance()->getMonsterData(2));
	monster->SetName("モンスター4");
	mPlayer->SetMonster(3, MonsterMgr::Instance()->getMonsterData(3));
	monster->SetName("モンスター5");
	mPlayer->SetMonster(4, MonsterMgr::Instance()->getMonsterData(4));
	
	

}

bool BattleBase::Initialize() {

	if (mGraphics->Load("Resources/Graphics/BG/image.png") == false) {
		Debug::ErorrMessage("画像データがありませんでした.");
		return false;
	}

#if 0
	if (mCard->Load("Resources/Graphics/Monster/Test.png") == false) {
		Debug::ErorrMessage("画像データがありませんでした.");
		return false;
	}
#endif

	mCard = ComRes::Instance()->GetGraphicHandle(ComRes::eComResName_Monster_00001);


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

	mNowStep = eBattleStep_Fade;
	NexetStepRequest(eBattleStep_Initialize, eFadeType_In);

	return true;
}

void BattleBase::Finalize() {
	Delete(mGraphics);
	//Delete(mCard);
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
		NexetStepRequest(eBattleStep_Main);
		break;
	case eBattleStep_Main:

		//Debug::LogPrintf("ダメージ %d\n", BattleCalculator::NormalDamage(*mPlayer->GetMonster(0), *mPlayer->GetMonster(0)));

		NexetStepRequest(eBattleStep_Result,BattleBase::eFadeType_In);
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

	for (int i = 0; i < 5; i++) {
		Monster* monster = mPlayer->GetMonster(i);
		if (monster == NULL) continue;
		Graphics* graph = ComRes::Instance()->GetGraphicHandle((ComRes::eComResName)(ComRes::eComResName_Monster_00001 + i));
		graph->Draw(200 + i * 300, 100, 255, 0.0, 1.0);	//敵
		graph->Draw(200 + i * 300, 750, 255, 0.0, 1.0);	//味方
		DrawString(200 + i * 300, 750, monster->GetName(), GetColor(0, 255, 0));
	}


	switch (mNowStep) {
	case eBattleStep_BattleStart:
		
		break;
	case eBattleStep_Main:
		//バトルメイン処理
		break;
	case eBattleStep_Result:

		break;
	}


#ifdef __MY_DEBUG__
		DrawFormatString(0, 40, GetColor(255, 0, 0), "Now Step:%s", dbg_STEP_TITLE[mNowStep]);
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