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

class GraphicsDraw {

protected:

	bool mIsVisible;	//表示フラグ
	bool mIsKill;		

	int mPosX;
	int mPosY;
	int mAlpha;

	int mWidth;
	int mHeight;

public :
	
	virtual void Draw(int posX, int posY, int alpha) = 0;
	virtual void Relese() = 0;

	int GetPositionX() { return mPosX; }
	int GetPositionY() { return mPosY; }
	int GetAlpah() { return mAlpha; }

	void  SetAlpha(int alpha) { mAlpha = alpha; }
	void SetPosition(int posX, int posY) {
		mPosX = posX;
		mPosY = posY;
	}

};

class GraphicsBase : public GraphicsDraw{

protected:

	int mHandle;

public :

	virtual bool Load(const char* path) = 0;
	
	int GetHandle() { return mHandle; }

	

};

class Graphics : public GraphicsBase{

private:

public:

	Graphics() : GraphicsBase() {}
	~Graphics() {}
	bool Load(const char* path) override { 
		mHandle = DxLib::LoadGraph(path);
		
		if (mHandle == -1) {
			return false;
		}
		DxLib::GetGraphSize(mHandle, &mWidth, &mHeight);
		return true; 
	};
	
	void Relese() {
		if (mHandle > 0) {
			DxLib::DeleteGraph(mHandle);
		}
	}

	void Draw(int posX, int posY, int alpha) override {
	
		SetPosition(posX, posY);
		SetAlpha(alpha);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);
		DxLib::DrawGraph(mPosX, mPosY, mHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
};

/*
	複数の画像で一枚の画像として扱う
*/
class GraphicsMulti : public GraphicsBase {

private:
	typedef struct {
		int handle;
		int posX;		//画像内座標
		int posY;
	}GRAPHICS_MULTI_t;
private:

	std::list<GRAPHICS_MULTI_t> mHandleList;

public :


	GraphicsMulti() : GraphicsBase() {};
	
	bool Load(const char* path) override { return true; };

	bool Load(const char* path,int scrX,int scrY){ 
		int handle = DxLib::LoadGraph(path);
		if (handle < 0) return false;
		return Add(handle, scrX, scrY);
	}

	void Relese() {

		if (mHandleList.empty() == true || mHandleList.size() <= 0) return;

		for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {
			if ((*it).handle > 0) {
				DxLib::DeleteGraph((*it).handle);
			}
		}

	}

	bool Add(int handle, int scrX, int scrY) {

		if (handle > 0) {
			GRAPHICS_MULTI_t multiGraphics = {handle,scrX,scrY};
			mHandleList.push_back(multiGraphics);
			return true;
		}
		return false;
	}

	/*
		描画
	*/
	void Draw(int posX, int posY, int alpha) override {
	
		if (mHandleList.empty() == true || mHandleList.size() <= 0) return;

		SetPosition(posX, posY);
		SetAlpha(alpha);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);
		for (auto it = mHandleList.begin(); it != mHandleList.end(); it++) {
			
			int drawPosX = (*it).posX + mPosX;
			int drawPosY = (*it).posY + mPosY;

			DxLib::DrawGraph(drawPosX, drawPosY, (*it).handle, TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

};

#include "Common/Task/Task.h"

class GraphicsDrawMgr : public Task{

private:
	std::list<GraphicsDraw*> mList;
public :

	GraphicsDrawMgr() {};
	~GraphicsDrawMgr() { mList.clear(); };

	void Add(const GraphicsBase& graphics) {
		mList.push_back((GraphicsDraw*)&graphics);
	}

	void Initialize()override {}
	void Finalize() override {
		for (auto it = mList.begin(); it != mList.end();it++) {
			(*it)->Relese();
		}
			
	}
	bool Updata() override { return true; };
	void Draw() override {
	
		for (auto it = mList.begin(); it != mList.end();) {

			int posX = (*it)->GetPositionX();
			int posY = (*it)->GetPositionY();
			int alpha = (*it)->GetAlpah();

			(*it)->Draw(posX,posY, alpha);

			it++;
		}
	
	}
	

};

#endif // __GRAPHICS_H__