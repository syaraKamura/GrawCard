/*
				ファイル名		:GraphTable.cpp
				作成者			:
				作成日時		:2019/03/21
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "GraphTable.h"

namespace graphicsTable {



	const char* mGRAPH_TAG_TABLE[eGraphTag_Max] = {
		"tag_MainMenuBG",		// eGraphTag_MainMenuBG
		"tag_CommonBG",			// eGraphTag_CommonBG
		"tag_MsgBox",			// eGraphTag_MsgBox
		"tag_BMFont_S",			// eGraphTag_BMFont_S
		"tag_BMFont_M",			// eGraphTag_BMFont_M
		"tag_BMFont_L",			// eGraphTag_BMFont_L
		"tag_MapIcon",			// eGraphTag_MapIcon
		"tag_StoryButton",		// eGraphTag_StoryButton
		"tag_PlayerStatusBar",	// eGraphTag_PlayerStatusBar
	};

	/*
		グラフィックスのタグを返却する
		int tag	:タグID eGraphTag
		return タグ名
	*/
	const char* GetGraphTag(int tag) {
		if (tag == eGraphTag_None || tag >= eGraphTag_Max) return nullptr;
		return (char*)mGRAPH_TAG_TABLE[tag];
	}

}
