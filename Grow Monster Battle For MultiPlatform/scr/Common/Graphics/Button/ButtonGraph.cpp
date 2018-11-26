/*
				ファイル名		:ButtonGraph.cpp
				作成者			:
				作成日時		:2018/11/05
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Button.h"
#include "ButtonGraph.h"

ButtonGraph::ButtonGraph() : GraphicsBase() {

}

void ButtonGraph::AddButton(Button* button) {
	mButton.push_back(button);
}

void ButtonGraph::Draw() {

	for (auto itr = mButton.begin(); itr != mButton.end(); itr++) {
		(*itr)->Update();
	}
	for (auto itr = mButton.begin(); itr != mButton.end(); itr++) {
		(*itr)->Draw();
	}
}


void ButtonGraph::Relese() {

	for (auto itr = mButton.begin(); itr != mButton.end();itr++) {
		Delete((*itr));
	}

	mButton.clear();

}
