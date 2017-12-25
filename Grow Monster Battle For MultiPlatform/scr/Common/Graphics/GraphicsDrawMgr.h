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
#include "Common/Task/Task.h"


class GraphicsBase;
class GraphicsDraw;

class GraphicsDrawMgr : public Task {

private:
	std::list<GraphicsDraw*>* mList;
public:

	GraphicsDrawMgr();
	~GraphicsDrawMgr();

	void Add(const GraphicsBase& graphics);

	void Initialize()override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;

};

#endif // __GRAPHICS_DRAW_MGR_H__