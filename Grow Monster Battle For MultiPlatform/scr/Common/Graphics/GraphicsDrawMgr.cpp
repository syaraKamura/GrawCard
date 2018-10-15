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
#include <typeinfo>

//ソート用関数
static bool sort_priorty(GraphicsDrawMgr::GRAPHICS_DRAW_ORDER_t a, GraphicsDrawMgr::GRAPHICS_DRAW_ORDER_t b) {
	return a.graph->GetPriorty() < b.graph->GetPriorty();
}

GraphicsDrawMgr::GraphicsDrawMgr() { 
	
	mList = new std::list<GRAPHICS_DRAW_ORDER_t>();
	mKillList = new std::list<GRAPHICS_DRAW_ORDER_t>();
	mOrder = 0;
	mIsInitalize = true;

}

GraphicsDrawMgr::~GraphicsDrawMgr() { 	
	Delete(mList);
	Delete(mKillList);
}

int GraphicsDrawMgr::Add(GraphicsBase* graphics,int prio) {
	
	((GraphicsDraw*)(graphics))->SetPriorty(prio);
	GRAPHICS_DRAW_ORDER_t add = { 0,(GraphicsDraw*)(graphics) };
	add.order = ++mOrder;
	mList->push_back(add);
	mList->sort(sort_priorty);
	return mOrder;
}

/*
	指定の番号の画像データを取得する
	return	NULL以外	:Graphicsクラスを返却する
			NULL		:データがない
*/
GraphicsBase* GraphicsDrawMgr::Get(int order) const {
	for (auto it = mList->begin(); it != mList->end();) {
		if ((*it).order == order) {
			GraphicsMulti* graph = dynamic_cast<GraphicsMulti*>((*it).graph);
			if (graph != NULL) {
				return graph;
			}
			return dynamic_cast<Graphics*>((*it).graph);
		}
		it++;
	}
	return NULL;
}

/*
	指定の番号の画像データの削除依頼をする
	return	true	:成功
			false	:失敗
*/
bool GraphicsDrawMgr::ReleseRequest(int order) {
	for (auto it = mList->begin(); it != mList->end();) {
		if ((*it).order == order) {
			(*it).graph->ReleseRequest();
			return true;
		}
		it++;
	}
	return false;
}


/*
	指定の番号の画像データをリストから除外する
	return	true	:成功
			false	:失敗
*/
bool GraphicsDrawMgr::Remove(int order) {

	for (auto it = mList->begin(); it != mList->end();) {
		if ((*it).order == order) {
			mList->erase(it);
			return true;
		}
		it++;
	}
	return false;
}

bool GraphicsDrawMgr::Initialize() {
	return true;
}
void GraphicsDrawMgr::Finalize() {
	
	for (auto it = mList->begin(); it != mList->end(); it++) {
		(*it).graph->Relese();
		Delete((*it).graph);
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

	//std::list<GraphicsDraw*>* buffer = new std::list<GraphicsDraw*>();

	for (auto it = mList->begin(); it != mList->end();) {

		int posX = (*it).graph->GetPositionX();
		int posY = (*it).graph->GetPositionY();
		int alpha = (*it).graph->GetAlpah();
		double scale = (*it).graph->GetScale();
		double angle = (*it).graph->GetAngleRadian();

		if ((*it).graph->IsVisible() == true && (*it).graph->IsRelese() == false) {
			(*it).graph->Draw(posX, posY, alpha,angle,scale);
		}
		else if ((*it).graph->IsRelese() == true) {
			(*it).graph->Relese();
			
			bool bExits = false;
			for (auto j = mKillList->begin(); j != mKillList->end();j++) {
				if ((*j).graph == (*it).graph) {
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
		delete (*it).graph;
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

