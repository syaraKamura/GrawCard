/*
				ファイル名		:GraphTable.h
				作成者			:
				作成日時		:2019/03/21
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __GRAPH_TABLE_H__
#define __GRAPH_TABLE_H__

namespace graphicsTable {

	enum eGraphTag {
		eGraphTag_None = -1,
		eGraphTag_MainMenuBG,
		eGraphTag_CommonBG,
		eGraphTag_MsgBox,
		eGraphTag_BMFont_S,
		eGraphTag_BMFont_M,
		eGraphTag_BMFont_L,
		eGraphTag_MapIcon,
		eGraphTag_StoryButton,
		eGraphTag_PlayerStatusBar,
		eGraphTag_Max,
	};

	/*
		グラフィックスのタグを返却する
		int tag	:タグID eGraphTag
		return タグ名
	*/
	const char* GetGraphTag(int tag);
	
}


#endif // __GRAPH_TABLE_H__