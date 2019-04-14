/*
				ファイル名		:MapField.h
				作成者			:
				作成日時		:2018/12/22
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __MAP_FIELD_H__
#define __MAP_FIELD_H__

#include "Common/Task/TaskBase.h"
#include "Common/Graphics/Button/Button.h"
#include "Map.h"
#include <vector>

namespace loader {
	class TblLoader;
}

//class Map;

class MapField : public TaskBase{

private:
	
	enum eState {
		eState_Wait,
		eState_Read,
		eState_Fade,
		eState_Main,
		eState_Story,
		eState_Battle,
		eState_Exit,
	};

	eState mState;
	Graphics* mMapImageHandle;
	std::vector<Map*> mMapIcons;

	Map::StoryData* mStoryData;

	loader::TblLoader* mLoader;
	int mStoryTask;
	int mBatlleTask;

	bool UpdateStory(int storyNo);
	bool UpdataBattle(int battleNo);

public :

	MapField();
	
	MapField(int stageNum);

	~MapField();

	bool Initialize()override;
	void Finalize()override;

	void PreviousUpdate()override;
	void InputUpdate() override;
	bool Updata()override;
	void PostUpdate() override;
	void Draw()override;

	

	Map::StoryData* GetStoryData() const {
		return mStoryData;
	}



};


#endif // __MAP_FIELD_H__