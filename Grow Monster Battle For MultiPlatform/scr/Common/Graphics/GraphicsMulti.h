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
		int width;
		int height;
		bool isVisible;
	}GRAPHICS_MULTI_t;
private:

	std::list<GRAPHICS_MULTI_t> mHandleList;

public:


	GraphicsMulti();

	bool Load(const char* path) override;

	bool Load(const char* path, int scrX, int scrY);

	/*
		画像を分割読み込みする
		const char* path	:	ファイルパス
		int divNumX			:	X分割枚数
		int divNumY			:	Y分割枚数
		int scrX			:	X描画座標
		int scrY			:	Y描画座標
		return		true	:	読み込み成功
					false	:	読み込み失敗
	*/
	bool LoadDiv(const char* path,int divNumX,int divNumY ,int scrX, int scrY);

	void Relese() override;

	bool Add(int handle, int scrX, int scrY);

	/*
	描画
	*/
	void Draw(int posX, int posY, int alpha, double angle, double scale) override;


	int TouchNumber() override;

	/*
		画像個々の座標を設定する
	*/
	void SetDivPosition(int divNum, int posX, int posY);
	void GetDivPosition(int divNum, int* posX, int* posY);

	void SetDivVisible(int divNum, bool isVisible);
	bool IsDivVisivle(int divNum);

	void SetAllDivVisible(bool isVisible);

	/*
		登録している画像の数
		return	: 0以上
	*/
	int GetNum();


};

#endif // __GRAPHICS_MULTI_H__