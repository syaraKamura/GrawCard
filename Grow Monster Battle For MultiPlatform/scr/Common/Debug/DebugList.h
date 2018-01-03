/*
		ファイル名		:DebugList.h
		作成者			:
		作成日時		:2017/12/31
		ソース説明		:


		備考



!*/

#ifndef __DEBUG_LIST_H__
#define __DEBUG_LIST_H__

class DebugList {

private:

	enum eDebugType {
		eDebugType_Flag,	//ON,Offの切り替えで実行する
		eDebugType_Func,	//選択されたときのみ実行する
	};


private:

	char mDebugName[64];		//デバッグ名
	eDebugType mType;			//
	bool mIsActive;				//

public:


	bool UpdateFunc();
	bool UpdateOnFunc();
	bool UpdateOffFunc();
	void DrawFunc();



};

#endif //__DEBUG_LIST_H__