/*
				ファイル名		:GraphicsMulti.h
				作成者			:
				作成日時		:2017/12/25
				ソース説明		:
					
					複数の画像で一枚の画像として扱う
				
				備考
				
				
				
!*/

#ifndef __GRAPHICS_MULTI_H__
#define __GRAPHICS_MULTI_H__

#include <list>
#include "GraphicsBase.h"
class GraphicsMulti : public GraphicsBase {

private:
	typedef struct {
		int handle;
		int posX;		//画像内座標
		int posY;
	}GRAPHICS_MULTI_t;
private:

	std::list<GRAPHICS_MULTI_t> mHandleList;

public:


	GraphicsMulti();

	bool Load(const char* path) override;

	bool Load(const char* path, int scrX, int scrY);

	void Relese() override;

	bool Add(int handle, int scrX, int scrY);

	/*
	描画
	*/
	void Draw(int posX, int posY, int alpha, double angle, double scale) override;

};

#endif // __GRAPHICS_MULTI_H__