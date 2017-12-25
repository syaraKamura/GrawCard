/*
				ファイル名		:
				作成者			:
				作成日時		:
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <list>
#include "Common/GameCommon.h"
#include "GraphicsBase.h"


class Graphics : public GraphicsBase{

private:

public:

	Graphics();
	~Graphics();
	bool Load(const char* path) override;
	
	void Relese();

	void Draw(int posX, int posY, int alpha) override;

};





#endif // __GRAPHICS_H__