/*
				ファイル名		:WindowGraph.h
				作成者			:
				作成日時		:2018/10/30
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __WINDOW_GRAPH_H__
#define __WINDOW_GRAPH_H__

#include "../GraphicsBase.h"

class Graphics;
class StringBase;

class WindowGraph : public GraphicsBase{

private:

	Graphics* mGraphics;
	StringBase* mString;

	int mStrLength;	// 1行の文字列の長さ

public:

	WindowGraph();
	~WindowGraph() override;

	virtual void Draw(int posX, int posY, int alpha, double angle, double scale) override;
	virtual void Draw();
	virtual void Relese() override;

	void SetString(const char* str);
	void SetStrLength(int strLength);

	bool Load(const char* path) override { return true; };

	bool IsTouch() override { return false; }
	int TouchNumber() override { return 0; }



};


#endif // __WINDOW_GRAPH_H__