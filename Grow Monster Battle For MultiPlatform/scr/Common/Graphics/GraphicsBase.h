/*
				ファイル名		:GraphicsBase.h
				作成者			:
				作成日時		:2017/12/25
				ソース説明		:
					
					画像基底クラス
				
				備考
				
				
				
!*/

#ifndef __GRAPHICS_BASE_H__
#define __GRAPHICS_BASE_H__

#include "GraphicsDraw.h"

class GraphicsBase : public GraphicsDraw {

protected:

	int mHandle;

public:

	GraphicsBase() :GraphicsDraw() {}
	
	virtual bool Load(const char* path) = 0;

	int GetHandle() { return mHandle; }



};

#endif // __TEMPLETE_H__