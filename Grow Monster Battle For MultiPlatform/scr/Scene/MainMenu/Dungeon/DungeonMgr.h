/*
				ファイル名		:DungeonMgr.h
				作成者			:
				作成日時		:2018/07/29
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __DUNGEON_MGR_H__
#define __DUNGEON_MGR_H__

class DungeonMgr {

public :

	enum eDungeonType {
		eDungeonType_None = -1,
		eDungeonType_Story,
		eDungeonType_Quest,
		eDungeonType_Dungeon,
	};

private:

	DungeonMgr();
	static DungeonMgr* mInstance;

	int mDungeonType;

public:

	/*
		ダンジョンの種類を設定する
	*/
	void SetDungeonType(int type);

	/*
		ダンジョンの種類を返却する
	*/
	int GetDungeonType();

	static void Create();
	static void Destory();

	static DungeonMgr* GetInstance() {
		if (mInstance == NULL) {
			Create();
		}
		return mInstance;
	}

};


#endif // __DUNGEON_MGR_H__