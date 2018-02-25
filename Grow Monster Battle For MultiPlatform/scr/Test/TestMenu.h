#ifndef __TEST_MENU_H__
#define __TEST_MENU_H__

#ifdef __MY_DEBUG__

#include "Scene/SceneBase.h"

class TestMenu : public SceneBase{

private:
	int mCursorY;
public:
	TestMenu(ISceneBase* chager);
	bool Initialize() override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;

};

#endif	//__MY_DEBUG__
#endif	//__TEST_MUNU_H__