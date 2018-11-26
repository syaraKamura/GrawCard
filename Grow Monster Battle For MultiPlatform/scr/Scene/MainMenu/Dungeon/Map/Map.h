/*
				ファイル名		:Map.h
				作成者			:
				作成日時		:2018/11/24
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __MAP_H__
#define __MAP_H__

#include "Common/Task/TaskBase.h"

class Map : public TaskBase {

private:

	// ダンジョンのデータ
	Graphics* mMapIcon; // マップアイコン
	char mDungeonDataFileName[1024];

public :

	Map() {};
	Map(Graphics* mapIcon);

	void Draw() override {};
	void Update() {};
	
};


#endif // __MAP_H__