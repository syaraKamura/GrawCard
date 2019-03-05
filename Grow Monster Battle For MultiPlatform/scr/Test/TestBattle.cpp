/*
				ファイル名		:TestBase.cpp
				作成者			:
				作成日時		:2018/03/15
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Scene/ISceneBase.h"
#include "TestBattle.h"
#include "Scene/MainMenu/Dungeon/Battle/BattleBase.h"
#include "AppData/AppData.h"
#include "Common/String/StringClick.h"

#ifdef __MY_DEBUG__


const TestBattle::SELECT_DATA_s TestBattle::SELECT_DATA_TBL[TestBattle::eState_BattleStart] = {
	{"デッキ作成",TestBattle::eState_DeckEdit},
	{ "モンスター一覧",TestBattle::eState_MonsterList },
	{ "バトル開始",TestBattle::eState_BattleStart },
};

TestBattle::TestBattle(ISceneBase* changer) : SceneBase(changer) {
	
}

TestBattle::~TestBattle() {
	
}

bool TestBattle::Initialize() {

	mState = TestBattle::eState_SelectMenu;
	mDeckEditState = TestBattle::eDeckEditState_DeckSelect;
	mSelectMenu = 0;
	mSelectMonster = 0;
	mSelectDeckNum = 0;

	mPlayer = new Player();

	mBattle = nullptr;

	AppData::GetInstance()->Load();
	SoundMgr::GetInstance()->Play("Title");
	return true;
}

void TestBattle::Finalize() {
	if (mBattle != nullptr) {
		TaskMgr::getInstance().RequestKill(mBattle->GetTaskId());
		mBattle = nullptr;
	}
	SoundMgr::GetInstance()->Stop();
}

void TestBattle::PreviousUpdate() {
	
}

bool TestBattle::Updata() {

	// TODO : テスト用項目の追加
	// モンスターデッキの設定ができるようにする
	// 実装中の全モンスターの一覧
	// デッキに設定されているモンスター一覧
	// モンスターの画像とステータスの表示
#ifdef __WINDOWS__
	switch (mState) {
	case TestBattle::eState_SelectMenu:

		if (Keyboard_Press(KEY_INPUT_UP)) {
			mSelectMenu = (mSelectMenu + TestBattle::eState_MonsterList) % TestBattle::eState_BattleStart;
		}
		else if (Keyboard_Press(KEY_INPUT_DOWN)) {
			mSelectMenu = (mSelectMenu + 1) % TestBattle::eState_BattleStart;
		}

		if (Keyboard_Press(KEY_INPUT_Z)) {
			mState = SELECT_DATA_TBL[mSelectMenu].state;
		}

		break;
	case TestBattle::eState_DeckEdit:

		switch (mDeckEditState) {

		case TestBattle::eDeckEditState_DeckSelect:
			if (Keyboard_Press(KEY_INPUT_UP)) {
				mSelectDeckNum = (mSelectDeckNum + 4) % 5;
			}
			else if (Keyboard_Press(KEY_INPUT_DOWN)) {
				mSelectDeckNum = (mSelectDeckNum + 1) % 5;
			}
			else if (Keyboard_Press(KEY_INPUT_Z)) {
				mDeckEditState = TestBattle::eDeckEditState_MonsterSelect;
			}
			else if (Keyboard_Press(KEY_INPUT_X)) {
				mState = TestBattle::eState_SelectMenu;
			}
			else if (Keyboard_Press(KEY_INPUT_C)) {
				mPlayer->RemoveMonster(mSelectDeckNum);
			}

			break;
		case TestBattle::eDeckEditState_MonsterSelect:

			if (Keyboard_Press(KEY_INPUT_UP)) {
				mSelectMonster = (mSelectMonster + (MonsterMgr::Instance()->GetMonsterNum() - 1)) % MonsterMgr::Instance()->GetMonsterNum();
			}
			else if (Keyboard_Press(KEY_INPUT_DOWN)) {
				mSelectMonster = (mSelectMonster + 1) % MonsterMgr::Instance()->GetMonsterNum();
			}
			else if (Keyboard_Press(KEY_INPUT_Z)) {
				mPlayer->RemoveMonster(mSelectDeckNum);
				mPlayer->SetMonster(mSelectDeckNum, MonsterMgr::Instance()->GetMonsterData(mSelectMonster));
			}
			else if (Keyboard_Press(KEY_INPUT_X)) {
				mDeckEditState = TestBattle::eDeckEditState_DeckSelect;
			}

			break;
		}

		break;
	case TestBattle::eState_MonsterList:


		if (Keyboard_Press(KEY_INPUT_UP)) {
			mSelectMonster = (mSelectMonster + (MonsterMgr::Instance()->GetMonsterNum() - 1)) % MonsterMgr::Instance()->GetMonsterNum();
		}
		else if (Keyboard_Press(KEY_INPUT_DOWN)) {
			mSelectMonster = (mSelectMonster + 1) % MonsterMgr::Instance()->GetMonsterNum();
		}
		
		if (Keyboard_Press(KEY_INPUT_X)) {
			mState = TestBattle::eState_SelectMenu;
		}


		break;
	case TestBattle::eState_BattleStart:
		SoundMgr::GetInstance()->CroosFadePlay("Battle_1", 60 * 3,SoundMgr::ePlayType_Loop);
		
		mBattle = new BattleBase(mPlayer);
		TaskMgr::getInstance().Add(mBattle);
		mState = TestBattle::eState_BattleEnd;
		break;
	case TestBattle::eState_BattleEnd:

		if (mBattle == NULL) {
			mState = TestBattle::eState_SelectMenu;
		}

		break;
	}

#ifdef __WINDOWS__
	if (Keyboard_Press(KEY_INPUT_Q)) {
		dbg_ChangeScene_TestMenu();
	}

	if (Keyboard_Press(KEY_INPUT_A)) {
		SoundMgr::GetInstance()->CroosFadePlay("Battle_1", 60 * 10,SoundMgr::ePlayType_Loop);
	}

#endif
#endif
	return true;
}

void TestBattle::Draw() {
	

	switch (mState) {
	case TestBattle::eState_SelectMenu:

		for (int i = 0; i < TestBattle::eState_BattleStart; i++) {
			if (mSelectMenu == i) {
				StringClick::SetColor(GetColor(255, 0, 0));
			}
			else {
				StringClick::SetColor(GetColor(255, 255, 255));
			}
			StringClick::SetString(SELECT_DATA_TBL[i].menuName);
			StringClick::Draw(0, i * 20 + 60);
		}

		break;
	case TestBattle::eState_DeckEdit:
	{

		for (int i = 0; i < 5; i++) {
			Monster* monster = mPlayer->GetMonster(i);
			
			if (mSelectDeckNum == i) {
				StringClick::SetColor(GetColor(255, 0, 0));
			}
			else {
				StringClick::SetColor(GetColor(255, 255, 255));
			}

			if (monster == NULL) {
				StringClick::SetString("-------empty-------");
			}
			else {
				StringClick::SetString(monster->GetName());
			}
			StringClick::Draw(0, i * 20 + 60);
		}

		if (mDeckEditState == TestBattle::eDeckEditState_MonsterSelect) {
			for (int i = 0; i < MonsterMgr::Instance()->GetMonsterNum(); i++) {
				if (mSelectMonster == i) {
					StringClick::SetColor(GetColor(255, 0, 0));
				}
				else {
					StringClick::SetColor(GetColor(255, 255, 255));
				}
				StringClick::SetString(MonsterMgr::Instance()->GetMonsterData(i)->GetName());
				StringClick::Draw(300, i * 20 + 60);
			}

			Monster *data = MonsterMgr::Instance()->GetMonsterData(mSelectMonster);
			if (data == nullptr) {
				return;
			}
			Graphics monster = MonsterMgr::Instance()->GetGraphics(mSelectMonster);

			monster.SetPosition(800, 300);
			monster.Draw();

			int y = 600;
			DrawFormatString(700, y += 20, GetColor(0, 255, 0), "Lvele   :%d", data->GetLevel());
			DrawFormatString(700, y += 20, GetColor(0, 255, 0), "Type    :%d", data->GetType());
			DrawFormatString(700, y += 20, GetColor(0, 255, 0), "Cost    :%d", data->GetCost());
			DrawFormatString(700, y += 20, GetColor(0, 255, 0), "HP      :%d/%d", data->GetHp(), data->GetHpMax());
			DrawFormatString(700, y += 20, GetColor(0, 255, 0), "MP      :%d/%d", data->GetMp(), data->GetMpMax());
			DrawFormatString(700, y += 20, GetColor(0, 255, 0), "Attack  :%d", data->GetAttack());
			DrawFormatString(700, y += 20, GetColor(0, 255, 0), "Deffence:%d", data->GetDeffence());
			DrawFormatString(700, y += 20, GetColor(0, 255, 0), "Speed   :%d", data->GetSpeed());
			DrawFormatString(700, y += 20, GetColor(0, 255, 0), "Exp     :%d", data->GetExp());
			DrawFormatString(700, y += 20, GetColor(0, 255, 0), "HomePos :%d", data->GetHomePosition());

		}

	}
		break;
	case TestBattle::eState_MonsterList:
	{
		for (int i = 0; i < MonsterMgr::Instance()->GetMonsterNum(); i++) {
			if (mSelectMonster == i) {
				StringClick::SetColor(GetColor(255, 0, 0));
			}
			else {
				StringClick::SetColor(GetColor(255, 255, 255));
			}
			StringClick::SetString(MonsterMgr::Instance()->GetMonsterData(i)->GetName());
			StringClick::Draw(0, i * 20 + 60);
		}

		Monster* data = MonsterMgr::Instance()->GetMonsterData(mSelectMonster);
		Graphics monster = MonsterMgr::Instance()->GetGraphics(mSelectMonster);

		monster.SetPosition(800, 300);
		monster.Draw();

		int y = 600;
		DrawFormatString(700, y += 20, GetColor(0, 255, 0), "Lvele   :%d", data->GetLevel());
		DrawFormatString(700, y += 20, GetColor(0, 255, 0), "Type    :%d", data->GetType());
		DrawFormatString(700, y += 20, GetColor(0, 255, 0), "Cost    :%d", data->GetCost());
		DrawFormatString(700, y += 20, GetColor(0, 255, 0), "HP      :%d/%d", data->GetHp(), data->GetHpMax());
		DrawFormatString(700, y += 20, GetColor(0, 255, 0), "MP      :%d/%d", data->GetMp(), data->GetMpMax());
		DrawFormatString(700, y += 20, GetColor(0, 255, 0), "Attack  :%d", data->GetAttack());
		DrawFormatString(700, y += 20, GetColor(0, 255, 0), "Deffence:%d", data->GetDeffence());
		DrawFormatString(700, y += 20, GetColor(0, 255, 0), "Speed   :%d", data->GetSpeed());
		DrawFormatString(700, y += 20, GetColor(0, 255, 0), "Exp     :%d", data->GetExp());
		DrawFormatString(700, y += 20, GetColor(0, 255, 0), "HomePos :%d", data->GetHomePosition());

	}
		break;
	case TestBattle::eState_BattleStart:

		break;
	case TestBattle::eState_BattleEnd:

		break;
	}

}

void TestBattle::PostUpdate() {
	
}

#endif //__MY_DEBUG__
