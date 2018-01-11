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
	mKillList = new std::list<GraphicsDraw*>();

	mIsInitalize = true;
}

GraphicsDrawMgr::~GraphicsDrawMgr() { 	
	Delete(mList);
	Delete(mKillList);
}

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

	DeleteExecute();

	if (mList == NULL) return true;
	else if (mList->size() <= 1) return true;

	mList->sort(sort_priorty);
	return true; 
}

void GraphicsDrawMgr::Draw()  {

	if (mList == NULL) return;
	else if (mList->size() <= 0) return;

	std::list<GraphicsDraw*>* buffer = new std::list<GraphicsDraw*>();

	for (auto it = mList->begin(); it != mList->end();) {

		int posX = (*it)->GetPositionX();
		int posY = (*it)->GetPositionY();
		int alpha = (*it)->GetAlpah();
		double scale = (*it)->GetScale();
		double angle = (*it)->GetAngleRadian();

		if ((*it)->IsVisible() == true && (*it)->IsRelese() == false) {
			(*it)->Draw(posX, posY, alpha,angle,scale);
		}
		else if ((*it)->IsRelese() == true) {
			(*it)->Relese();
			
			bool bExits = false;
			for (auto j = mKillList->begin(); j != mKillList->end();j++) {
				if ((*j) == (*it)) {
					bExits = true;
					break;
				}
			}
			if (bExits == false) {
				mKillList->push_back(*it);
			}
			
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

/*
	削除依頼があったものを削除する
*/
void GraphicsDrawMgr::DeleteExecute() {
	
	if (mKillList == NULL) return;
	else if (mKillList->size() <= 0) return;

	for (auto it = mKillList->begin(); it != mKillList->end();) {
		delete (*it);
		mKillList->erase(it);

		if (mKillList->size() <= 0) {
			break;
		}
		else {
			it = mKillList->begin();
			continue;
		}
		it++;
	}

}

