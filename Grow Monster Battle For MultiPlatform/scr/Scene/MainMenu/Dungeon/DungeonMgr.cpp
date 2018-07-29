/*
				ファイル名		:DungeonMgr.cpp
				作成者			:
				作成日時		:2018/07/29
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "DungeonMgr.h"

DungeonMgr* DungeonMgr::mInstance = NULL;

DungeonMgr::DungeonMgr() {
	mDungeonType = DungeonMgr::eDungeonType_None;
}

void DungeonMgr::Create() {
	if (mInstance == NULL) {
		mInstance = new DungeonMgr();
	}
}

void DungeonMgr::Destory() {
	Delete(mInstance);
}


/*
ダンジョンの種類を設定する
*/
void DungeonMgr::SetDungeonType(int type){
	mDungeonType = type;
}

/*
ダンジョンの種類を返却する
*/
int DungeonMgr::GetDungeonType() {
	return mDungeonType;
}
