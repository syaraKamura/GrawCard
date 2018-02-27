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

public :

	typedef struct {
		int order;
		GraphicsDraw* graph;
	}GRAPHICS_DRAW_ORDER_t;

private:
	std::list<GRAPHICS_DRAW_ORDER_t>* mList;
	std::list<GRAPHICS_DRAW_ORDER_t>* mKillList;	//削除用リスト
	unsigned int mOrder;
private:

	GraphicsDrawMgr();
	
	void DeleteExecute();

public:

	~GraphicsDrawMgr();

	static GraphicsDrawMgr* GetInstance() {
		static GraphicsDrawMgr* inst = new GraphicsDrawMgr();
		return inst;
	}
	
	int Add(GraphicsBase* graphics,int prio);
	/*
		指定の番号の画像データを取得する
		return	NULL以外	:Graphicsクラスを返却する
				NULL		:データがない
	*/
	GraphicsBase* Get(int order);
	/*
		指定の番号の画像データの削除依頼をする
		return	true	:成功
				false	:失敗
	*/
	bool ReleseRequest(int order);

	/*
		指定の番号の画像データをリストから除外する
		return	true	:成功
				false	:失敗
	*/
	bool Remove(int order);

	bool Initialize()override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;
};

#endif // __GRAPHICS_DRAW_MGR_H__