/*
		ファイル名		:DebugList.cpp
		作成者			:
		作成日時		:2018/02/28
		ソース説明		:


		備考



!*/

#include "Common/GameCommon.h"
#include "DebugList.h"


DebugList::DebugList() {
	mListSelect = 0;
}

DebugList::~DebugList() {
	mList.clear();
}

void DebugList::DrawDebugList() {

	if (mList.size() <= 0) {
		DrawString(5, 60, "デバッグ項目なし", GetColor(255, 255, 255));
		return;
	}

	DrawString(5, 60 + mListSelect * 20, "■", GetColor(255, 255, 255));

	int n = 0;
	for (auto it = mList.begin(); it != mList.end(); it++)
	{
		DrawString(40, 60 + n * 20, (*it)->mDebugName, GetColor(255, 255, 255));
		n++;
	}

}

void DebugList::Update() {

#ifdef __WINDOWS__
	if (Keyboard_Press(KEY_INPUT_UP)) {
		mListSelect++;
		if (mListSelect >= mList.size()) {
			mListSelect = mList.size() - 1;
			if (mListSelect < 0) {
				mListSelect = 0;
			}
		}
	}
	else if(Keyboard_Press(KEY_INPUT_DOWN)) {
		mListSelect--;
		if (mListSelect < 0) {
			mListSelect = 0;
		}
	}
	if (Keyboard_Press(KEY_INPUT_Z)) {
		Execute();
	}
#endif

}

/*
	デバッグリスを設定する
	DEBUG_LIST_t* list		:
	const char* debugName	:デバッグ項目名
	eDebugType type			:デバッグ種類
	bool isActive			:実行しているか？
*/
void DebugList::SetList(DEBUG_LIST_t* list, const char* debugName, eDebugType type, bool isActive) {
	strcpyDx(list->mDebugName, debugName);
	list->mType = type;
	list->mIsActive = isActive;
}


void DebugList::AddList(int id,const char* debugName, eDebugType type, bool isActive) {
	DEBUG_LIST_t* add = new DEBUG_LIST_t();
	strcpyDx(add->mDebugName, debugName);
	add->id = id; 
	add->mType = type;
	add->mIsActive = isActive;
	mList.push_back(add);
}