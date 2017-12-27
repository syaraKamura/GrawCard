/*
				ファイル名		:GraphicsDrawMgr.cpp
				作成者			:
				作成日時		:2017/12/25
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "GraphicsDrawMgr.h"
#include "GraphicsDraw.h"

//ソート用関数
static bool sort_priorty(GraphicsDraw* a, GraphicsDraw* b) {
	return a->GetPriorty() < b->GetPriorty();
}

GraphicsDrawMgr::GraphicsDrawMgr() { 
	mList = new std::list<GraphicsDraw*>(); 
	mIsInitalize = true;
};
GraphicsDrawMgr::~GraphicsDrawMgr() { 	
	
};

void GraphicsDrawMgr::Add(GraphicsBase* graphics,int prio) {
	((GraphicsDraw*)(graphics))->SetPriorty(prio);
	mList->push_back((GraphicsDraw*)graphics);
	mList->sort(sort_priorty);
}

void GraphicsDrawMgr::Initialize() {

}
void GraphicsDrawMgr::Finalize() {
	
	for (auto it = mList->begin(); it != mList->end(); it++) {
		(*it)->Relese();
		Delete((*it));
	}

}

bool GraphicsDrawMgr::Updata()  { 
	return true; 
}

void GraphicsDrawMgr::Draw()  {

	if (mList->size() <= 0) return;

	for (auto it = mList->begin(); it != mList->end();) {

		int posX = (*it)->GetPositionX();
		int posY = (*it)->GetPositionY();
		int alpha = (*it)->GetAlpah();

		if ((*it)->IsVisible() == true && (*it)->IsRelese() == false) {
			(*it)->Draw(posX, posY, alpha);
		}
		else if ((*it)->IsRelese() == true) {
			(*it)->Relese();
			delete (*it);
			mList->erase(it);
			if (mList->size() <= 0) {
				break;
			}
			else {
				it = mList->begin();
				continue;
			}
		}

		it++;
	}

}


