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

	
	mPlayer->SetMonster(0, MonsterMgr::Instance()->getMonsterData(0));
	monster->SetName("モンスター2");
	mPlayer->SetMonster(1, MonsterMgr::Instance()->getMonsterData(1));
	monster->SetName("モンスター3");
	mPlayer->SetMonster(2, MonsterMgr::Instance()->getMonsterData(2));
	monster->SetName("モンスター4");
	mPlayer->SetMonster(3, MonsterMgr::Instance()->getMonsterData(3));
	monster->SetName("モンスター5");
	mPlayer->SetMonster(4, MonsterMgr::Instance()->getMonsterData(4));
	
	//mEnemy->SetMonster(0, MonsterMgr::Instance()->getMonsterData(5));
	//mEnemy->Attach(0);
	mEnemy->SetMonster(1, MonsterMgr::Instance()->getMonsterData(6));
	mEnemy->Attach(1);
	//mEnemy->SetMonster(2, MonsterMgr::Instance()->getMonsterData(7));
	//mEnemy->Attach(2);
	mEnemy->SetMonster(3, MonsterMgr::Instance()->getMonsterData(8));
	mEnemy->Attach(3);
	//mEnemy->SetMonster(4, MonsterMgr::Instance()->getMonsterData(9));
	//mEnemy->Attach(4);
	
	mMoveData.clear();
	
	for (int i = 0; i < 5; i++) {
		Monster* monster = mPlayer->GetMonster(i);
		if (monster == NULL) continue;
		mPlayerCard[i] = MonsterMgr::Instance()->GetGraphics(monster->GetId());
		mPlayerCard[i].SetVisible(true);
		mPlayerCard[i].SetPosition(200 + i * 300, 750);
		mPlayerCard[i].SetBasePosition(200 + i * 300, 750);
		GraphicsDrawMgr::GetInstance()->Add(&mPlayerCard[i],0);
	}

	for (int i = 0; i < 5; i++) {
		Monster* monster = mEnemy->GetMonster(i);
		if (monster == NULL) continue;
		mEnemyCard[i] = MonsterMgr::Instance()->GetGraphics(monster->GetId());
	}

	mBattleAnimation = new BattleAnimation();
	TaskMgr::getInstance().Add(mBattleAnimation);
	
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

	//mCard = ComRes::Instance()->GetGraphicHandle(ComRes::eComResName_Monster_00001);


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
	mMainStep = eBattleMainStep_Command;

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

		for (int i = 0; i < 5; i++) {
			if(mPlayer->GetMonster(i) == NULL) continue;
			mBattleAnimation->RequestAnim(BattleAnimation::eAnimationNo_InSide_00, &mPlayerCard[i], true);
		}
		
		NexetStepRequest(eBattleStep_Main);
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
		//mPlayerCard[i].Draw(200 + i * 300, y, 255, 0.0, 1.0);	//味方
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


	switch (mMainStep) {
	case BattleBase::eBattleMainStep_Command:
#ifdef __WINDOWS__

		if (Keyboard_Press(KEY_INPUT_Z)) {
			mMainStep = eBattleMainStep_Battle;
			
			for (int i = 0; i < 5; i++) {

				Monster* moveMonster = mPlayer->GetMonster(mMoveChrIdx);
				Monster* targetMonster = mEnemy->GetMonster(mTargetIdx);

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

				if(moveMonster == NULL || moveMonster->GetHp() <= 0) {
					continue;
				}

				while (targetMonster == NULL  || targetMonster->GetHp() <= 0) {
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

		/*
			誰が
			誰を対象に
			どのような行動をするのか　行動タイプ


		*/

		break;
	case BattleBase::eBattleMainStep_Battle:
#ifdef __WINDOWS__

		if (Keyboard_Press(KEY_INPUT_Z)) {

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


			for (auto itr = mMoveData.begin(); itr != mMoveData.end();) {

				BattleBase::MOVE_DATA_t move = *itr;

				Monster* moveMonster = NULL;
				Monster* targetMonster = NULL;
				int moveId = move.moveId;
				int targetId = move.targetId;
				BattleBase::eActiveType type = BattleBase::eActiveType_Attack;
				if (move.moveDeckType == BattleBase::eDeckType_Player) {
					moveMonster = mPlayer->GetMonster(moveId);

					mBattleAnimation->RequestAnim(BattleAnimation::eAnimationNo_InSide_00, &mPlayerCard[moveId], true);

				}
				else {
					moveMonster = mEnemy->GetMonster(moveId);
				}
				
				// 行動するモンスターの体力が0より大きいか判断する
				if (moveMonster->GetHp() > 0) {

					

					if (move.targetDeckType == BattleBase::eDeckType_Player) {
						targetMonster = mPlayer->GetMonster(targetId);
					}
					else {
						targetMonster = mEnemy->GetMonster(targetId);
					}

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

							break;
						case BattleBase::eActiveType_Skill:
							damageResult = BattleCalculator::SkillDamage(*moveMonster, *targetMonster);
							break;
						}

						int damage = targetMonster->GetHp() - damageResult;

						/*
							ここから攻撃アニメ―ション開始
						*/

						targetMonster->SetHp(damage);

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
			mMainStep = eBattleMainStep_Judgement;
		}
#endif
		
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

#ifdef __WINDOWS__

		if (Keyboard_Press(KEY_INPUT_Z)) {
			mMainStep = eBattleMainStep_Command;
		}
		if (Keyboard_Press(KEY_INPUT_A)) {
			step = BattleBase::eBattleStep_Result;
		}
#endif
		break;
	}




	return step;
}

void BattleBase::BattleMainDraw() {

	char str[1024];

	switch (mMainStep) {
	case BattleBase::eBattleMainStep_Command:
		strcpyDx(str, "Zキー: バトルへ");
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

		for (int i = 0; i < 5; i++) {
			Monster* mon = mPlayer->GetMonster(i);
			if (mon == NULL) continue;
			if (mon->GetHp() <= 0) {
				deadCount++;
			}
		}

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