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
#include<string>
#include "Common/GameCommon.h"
#include "GraphicsBase.h"


class Graphics : public GraphicsBase{

private:

protected:

	int LoadResource(std::string fileName) override;
	void DestoryResource(int handle) override;

public:

	Graphics();
	~Graphics();

	/*
		初期化
		std::string tag	:画像取得タグ

	*/
	bool Initialize(std::string tag);

	bool Load(const char* path) override;
	
	void Relese() override;

	void Draw(int posX, int posY, int alpha, double angle, double scale) override;
	void Draw();

	bool IsTouch() override;
	/*
		押されている
	*/
	bool IsTouchPush();
	

};





#endif // __GRAPHICS_H__