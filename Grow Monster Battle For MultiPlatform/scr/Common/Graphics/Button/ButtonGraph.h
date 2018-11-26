/*
				ファイル名		:ButtonGraph.h
				作成者			:
				作成日時		:2018/11/05
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __BUTTON_GRAPH_H__
#define __BUTTON_GRAPH_H__

#include "../GraphicsBase.h"
#include <list>

class Button;

class ButtonGraph :public GraphicsBase {

private:

	std::list<Button*> mButton;

public :

	ButtonGraph();

	bool Load(const char* path) override { return true; };
	void Draw(int posX, int posY, int alpha, double angle, double scale) override {};
	void Relese() override;
	void Draw() override;
	bool IsTouch() override { return false; }
	int TouchNumber() override { return 0; }

	void AddButton(Button* button);

};


#endif // __BUTTON_GRAPH_H__