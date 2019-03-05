/*
				ファイル名		:StoryData.h
				作成者			:
				作成日時		:2019/03/02
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __SCRIPT_DATA_H__
#define __SCRIPT_DATA_H__

#include "Common/Script/ScriptBase.h"

namespace loader {
	class TblLoader;
}

namespace story {

	struct STORY_DATA {
		int id;
		char title[64];
		int beforStoryNo;
		int afterStoryNo;
		int existBattle;
		int battleDataNo;
	};

	class StoryData {

	private:

		bool mIsLoadEnd;
		loader::TblLoader* mLoad;

		std::vector<STORY_DATA> mStoryData;

	public:

		StoryData();
		~StoryData();

		void Update();

		void LoadData();
		bool IsLoadEnd();

		AdvScript::ScriptBase* RequestADV(int idx);


	};
}

#endif // __SCRIPT_DATA_H__