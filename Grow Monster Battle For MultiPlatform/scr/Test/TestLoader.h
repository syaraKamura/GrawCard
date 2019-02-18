/*
				ファイル名		:TestLoader.h
				作成者			:
				作成日時		:2019/02/14
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __TEST_LOADER_H__
#define __TEST_LOADER_H__

#ifdef __MY_DEBUG__

#include "Scene/SceneBase.h"

namespace loader{
	class TblLoader;
}

class TestLoader : public SceneBase {

private:

	loader::TblLoader* mLoader;

public :

	TestLoader(ISceneBase* changer);
	~TestLoader();

	virtual bool Initialize() override;
	virtual void Finalize() override;
	void PreviousUpdate()override;
	bool Updata()override;
	void Draw() override;
	void PostUpdate() override;

};

#endif	// __MY_DEBUG__

#endif // __TEST_LOADER_H__