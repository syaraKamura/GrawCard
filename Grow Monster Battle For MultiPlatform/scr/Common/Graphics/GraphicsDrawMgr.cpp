/*
				ファイル名		:GraphicsDrawMgr.cpp
				作成者			:
				作成日時		:2017/12/25
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "GraphicsDrawMgr.h"
#include "GraphicsDraw.h"

GraphicsDrawMgr::GraphicsDrawMgr() {};
GraphicsDrawMgr::~GraphicsDrawMgr() { 	

	mList = new std::list<GraphicsDraw*>();

	mList->clear();
};

void GraphicsDrawMgr::Add(const GraphicsBase& graphics) {
	mList->push_back((GraphicsDraw*)&graphics);
}

void GraphicsDrawMgr::Initialize() {

}
void GraphicsDrawMgr::Finalize() {
	
	for (auto it = mList->begin(); it != mList->end(); it++) {
		(*it)->Relese();
	}

}

bool GraphicsDrawMgr::Updata()  { 
	return true; 
}

void GraphicsDrawMgr::Draw()  {

	for (auto it = mList->begin(); it != mList->end();) {

		int posX = (*it)->GetPositionX();
		int posY = (*it)->GetPositionY();
		int alpha = (*it)->GetAlpah();

		(*it)->Draw(posX, posY, alpha);

		it++;
	}

}


