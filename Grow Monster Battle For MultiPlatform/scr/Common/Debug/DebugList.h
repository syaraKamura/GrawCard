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

public:

	enum eDebugType {
		eDebugType_Flag,	//ON,Offの切り替えで実行する
		eDebugType_Func,	//選択されたときのみ実行する
	};


protected:

	int mListSelect;

public:

	typedef struct {
		int id;
		char mDebugName[64];		//デバッグ名
		eDebugType mType;			//
		bool mIsActive;
	}DEBUG_LIST_t;

	std::list<DEBUG_LIST_t*> mList;

public:

	DebugList();
	virtual ~DebugList();
	void DrawDebugList();
	void Update();
	/*
		各デバッグ項目の実行用純仮想関数
	*/
	virtual void Execute() = 0;
	
	void SetList(DEBUG_LIST_t* list, const char* debugName, eDebugType type, bool isActive);

	void AddList(int id,const char* debugName, eDebugType type, bool isActive);


};

#endif //__DEBUG_LIST_H__