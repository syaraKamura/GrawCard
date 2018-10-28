/*
				ファイル名		:DungeonMenu.cpp
				作成者			:
				作成日時		:2018/03/12
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "DungeonMenu.h"
#include "DungeonMgr.h"

#include "Battle/BattleBase.h"
#include "Common/Script/ScriptBase.h"


typedef struct {
	int mQuestNo;
	int mQuestType;
	char mBeforeAdvName[1024];
	char mAfterAdvName[1024];
}QuestDataBase;

typedef struct {
	int mId;
	QuestDataBase mData;
}QuestData_t;

typedef struct {
	int mQuestType;
	int mQuestNo;
	int mIsBattle;
	char mQuestname[1024];
}QuestInfo_t;


#define TEST_QUEST_DATA_NUM 3

static QuestData_t mQuestDataTbl[TEST_QUEST_DATA_NUM] = {
	{0,0,0,"ADV_0001.txt",""},
	{1,0,1,"ADV_0001.txt","" },
	{ 2,0,2,"ADV_0001.txt","" },
};

static QuestInfo_t mQuestInfoTbl[TEST_QUEST_DATA_NUM] = {
	{0,0,0,"はじまりの森"},
	{0,1,0,"出会い" },
	{ 0,2,0,"リーフの家で" },
};

DungeonMenu::DungeonMenu() : TaskBase() {

	
}

DungeonMenu::~DungeonMenu() {

}

bool DungeonMenu::Initialize() {
	
	if (Fade::GetInstance()->IsFadeEnd() == false) return false;
	
	Graphics* add = ComRes::Instance()->GetGraphicHandle(ComRes::eComResName_CommonBG);
	add->SetPosition(0, 0);
	mBackImageOrder = GraphicsDrawMgr::GetInstance()->Add(add, 1);
	
	mSelect = 0;
	mState = eState_SelectMode;
	mNextState = eState_None;
	mOldState = eState_None;

	mStroySelectNum = 0;

	//フェードイン
	Fade::GetInstance()->FadeIn(30);

	return true;
}

void DungeonMenu::Finalize() {
	GraphicsDrawMgr::GetInstance()->Remove(this->mBackImageOrder);
	
}

void DungeonMenu::PreviousUpdate() {

}

bool DungeonMenu::Updata() {
	if (Fade::GetInstance()->IsFadeEnd() == false) return true;

		
	if (mTaskId != -1) {
		ScriptBase* scriptTask = dynamic_cast<ScriptBase*>(TaskMgr::getInstance().GetTask(mTaskId));
		
		if (scriptTask != NULL) {
			if (scriptTask->IsEnd()) {
				TaskMgr::getInstance().RequestKill(mTaskId);
			}
		}

		if (TaskMgr::getInstance().GetTask(mTaskId) == NULL) {
			mTaskId = -1;
		}
		return true;
	}

	switch (mState) {
	case eState_SelectMode:

#ifdef __WINDOWS__
		if (Keyboard_Press(KEY_INPUT_DOWN)) {
			mSelect = (mSelect + 1) % eMenu_Num;
		}
		else if (Keyboard_Press(KEY_INPUT_UP)) {
			mSelect = (mSelect + (eMenu_Num - 1)) % eMenu_Num;
		}
		if (Keyboard_Press(KEY_INPUT_Z)) {
			DungeonMgr::GetInstance()->SetDungeonType(mSelect);
			eState next = (eState)(mSelect + eState_SelectStoryMap);
			ChangeState(next, eFade_Out);
		}

		else if (Keyboard_Press(KEY_INPUT_X)) {
			DungeonMgr::GetInstance()->SetDungeonType(DungeonMgr::eDungeonType_None);
			ChangeState(eState_ExitDone, eFade_Out);

		}

#else

		//とりあえず自身のタスクを削除する
		//if (Touch_Relese(0)) {
		if (ClickInput::GetInstance()->Relese(0)) {
			mState = eState_Fade;
		}

#endif
		break;
	case eState_SelectStoryMap:
		
#ifdef __WINDOWS__
		if (Keyboard_Press(KEY_INPUT_Z)) {
			//mTaskId = TaskMgr::getInstance().Add(new BattleBase(),TaskMgr::ePriorty_0);
			ChangeState(eState_Adventure, eFade_None);
		}

		if (Keyboard_Press(KEY_INPUT_X)) {
			DungeonMgr::GetInstance()->SetDungeonType(DungeonMgr::eDungeonType_None);
			ChangeState(eState_SelectMode, eFade_Out);
		}
#endif // __WINDOWS__

		break;
	case eState_SelectQuestMap:
#ifdef __WINDOWS__
		if (Keyboard_Press(KEY_INPUT_X)) {
			DungeonMgr::GetInstance()->SetDungeonType(DungeonMgr::eDungeonType_None);
			ChangeState(eState_SelectMode, eFade_Out);
		}
#endif // __WINDOWS__
		break;
	case eState_SelectDungeonMap:
#ifdef __WINDOWS__
		if (Keyboard_Press(KEY_INPUT_X)) {
			DungeonMgr::GetInstance()->SetDungeonType(DungeonMgr::eDungeonType_None);
			ChangeState(eState_SelectMode, eFade_Out);
		}
#endif // __WINDOWS__
		break;
	case eState_Adventure:
		mTaskId = TaskMgr::getInstance().Add(new ScriptBase("ADV_0001.txt"), TaskMgr::ePriorty_0);
		ChangeState(eState_SelectStoryMap, eFade_None);
		break;
	case eState_Fade:
		if (Fade::GetInstance()->IsFadeEnd()) {
			mState = mNextState;
			if (mNextState >= eState_SelectMode && mNextState <= eState_SelectDungeonMap) {
				Fade::GetInstance()->FadeIn(30);
				GraphicsBase* graph = GraphicsDrawMgr::GetInstance()->Get(mBackImageOrder);
				if (mNextState != eState_SelectMode) {
					if (graph != NULL) {
						graph->SetVisible(false);
					}
				}
				else {
					if (graph != NULL) {
						graph->SetVisible(true);
					}
				}
			}
		}
		break;
	case eState_Exit:
		if (Fade::GetInstance()->IsFadeEnd()) {
			mState = eState_ExitDone;
		}
		break;
	case eState_ExitDone:
		TaskMgr::getInstance().RequestKill(this->GetTaskId());
		break;
	}


	return true;
}

void DungeonMenu::Draw() {
	
	switch (mState) {
	case eState_SelectMode:
		DrawString(170, 100 + 60 * mSelect, "■", GetColor(255, 0, 0));
		for (int i = 0; i < eMenu_Num; i++) {
			DrawString(200, 100 + 60 * i, NAME_LIST[i], GetColor(255, 0, 0));
		}
		break;
	case eState_SelectStoryMap:
		DrawString(0, 300, "ストーリーマップ選択画面", GetColor(255, 255, 255));
		break;
	case eState_SelectQuestMap:
		DrawString(0, 300, "クエストマップ選択画面", GetColor(255, 255, 255));
		break;
	case eState_SelectDungeonMap:
		DrawString(0, 300, "ダンジョンマップ選択画面", GetColor(255, 255, 255));
		break;
	}

}

void DungeonMenu::PostUpdate() {

}



/*
	ステート切り替え
*/
void DungeonMenu::ChangeState(eState next, eFade fade, int fadeTime/* = 30*/){
	
	if (Fade::GetInstance()->IsFadeEnd()) {
		mOldState = mState;
		mNextState = next;
		if (fade == eFade_In) {
			Fade::GetInstance()->FadeIn(fadeTime);
		}
		else if (fade == eFade_Out) {
			Fade::GetInstance()->FadeOut(fadeTime);
		}
		mState = eState_Fade;
	}
	
}