/*
				ファイル名		:GraphicsDrawMgr.h
				作成者			:
				作成日時		:2017/12/25
				ソース説明		:
					画像描画マネージャー

					タスクに登録して使用する
				
				備考
				
				
				
!*/

#ifndef __GRAPHICS_DRAW_MGR_H__
#define __GRAPHICS_DRAW_MGR_H__

#include  <list>
#include "Common/Task/TaskBase.h"


class GraphicsBase;
class GraphicsDraw;

class GraphicsDrawMgr : public TaskBase {

private:
	std::list<GraphicsDraw*>* mList;
	std::list<GraphicsDraw*>* mKillList;	//削除用リスト
private:

	GraphicsDrawMgr();
	
	void DeleteExecute();

public:

	~GraphicsDrawMgr();

	static GraphicsDrawMgr* GetInstance() {
		static GraphicsDrawMgr* inst = new GraphicsDrawMgr();
		return inst;
	}
	
	void Add(GraphicsBase* graphics,int prio);

	void Initialize()override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;
};

#endif // __GRAPHICS_DRAW_MGR_H__