//ロゴを表示させるのみ
//フェードアウトとかフェイドインみたいな感じ？
#include"Common/GameCommon.h"
#include "Scene/ISceneBase.h"
#include "Scene_Opning.h"


typedef struct{
	int count;
	int imageHandle;
}Work_t;

static Work_t mWork;

namespace mylib {
	static int LoadGraph(const char* filePath) {

		char path[1024];
		strcpyDx(path, filePath);
#ifdef __WINDOWS__ 
#ifdef  __MY_DEBUG__

		RESORCES_PATH(path);

#endif	
#endif
		return DxLib::LoadGraph(path);
	}
};

Scene_Opning::Scene_Opning(ISceneBase* changer) : SceneBase(changer){
	
}

bool Scene_Opning::Initialize(){

	mWork.imageHandle = mylib::LoadGraph("Resources/Graphics/BG/opning.png");
	mWork.count = 0;
	return true;
}

void Scene_Opning::Finalize(){
	
	DeleteGraph(mWork.imageHandle);
	mWork.count = 0;
}

bool Scene_Opning::Updata() {

#ifdef __WINDOWS__
	if (Keyboard_Press(KEY_INPUT_X)) {
		mNextScene->SceneChange(ISceneBase::eScene_Title);
	}
#else 

	//if (Touch_Press(0)) {
	if (ClickInput::GetInstance()->Press(0)) {
		mNextScene->SceneChange(ISceneBase::eScene_Title);
	}

#endif

	if(mWork.count > 200){
		mNextScene->SceneChange(ISceneBase::eScene_Title);
	}

	mWork.count++;

	return true;

}

void Scene_Opning::Draw(){

	DrawGraph(0,0,mWork.imageHandle,TRUE);

	//DrawString(0,20,"-XキーでTitleへ移動-",GetColor(255,255,255));

}