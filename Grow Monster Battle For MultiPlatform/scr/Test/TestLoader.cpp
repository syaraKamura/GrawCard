/*
				ファイル名		:TestLoader.cpp
				作成者			:
				作成日時		:2019/02/14
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"

#ifdef __MY_DEBUG__

#include "Scene/ISceneBase.h"
#include "Common/FileLoader/TblLoader/TblLoader.h"
#include "Common/FileLoader/TblLoader/TblLoaderMgr.h"
#include "TestLoader.h"

#include <vector>

struct SKILL_DATA{
	int id;
	char name[64];
	int effectId;
	short attackKind;
	short elementType;
	int hp;
	int mp;
	int attack;
	int deffence;
	int spped;
};



TestLoader::TestLoader(ISceneBase* changer) : SceneBase(changer) {

	mLoader = loader::TblLoaderMgr::GetInstance()->LoadRequest("Resources/Data/Table/Test/TestData.dtl");
}

TestLoader::~TestLoader() {  

}

bool TestLoader::Initialize() {

	return true;
}

void TestLoader::Finalize() {

}

void TestLoader::PreviousUpdate() {

}

bool TestLoader::Updata() {
	
	if (mLoader->IsLoadEnd()) {
		loader::TblLoader::TblData& tblData = mLoader->GetTableData();
		int size = tblData.data[0].dataSize / sizeof(SKILL_DATA);
		SKILL_DATA* skillData = new SKILL_DATA[size];
		memcpy(skillData, tblData.data[0].buffer, tblData.data[0].dataSize);

		for (int i = 0; i < size; i++) {
			auto data = *(skillData + i);
			Debug::LogPrintf("%d %s %d %d %d %d %d %d %d %d\n",
				data.id, data.name, data.effectId, data.attackKind, data.elementType,
				data.hp, data.mp, data.attack, data.deffence, data.spped);
		}
	}


#ifdef __WINDOWS__
	if (Keyboard_Press(KEY_INPUT_X)) {
		dbg_ChangeScene_TestMenu();
	}
#endif	// __WINDOWS__

	return true;
}

void TestLoader::PostUpdate() {

}

void TestLoader::Draw() {

}

#endif	//__MY_DEBUG__