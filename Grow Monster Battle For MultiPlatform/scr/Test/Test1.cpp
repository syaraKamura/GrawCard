#include "Common/GameCommon.h"
#include "Test/Test1.h"
#include "Common/Task/TaskMgr.h"


int x = 0;
int ix = 10;
int taskId = -1;
int count = 0;

//-------------------------------------
// �ʏ�֐��^�X�N�o�^�e�X�g
// �ʏ�֐��^�X�N�o�^�̏ꍇ�͏������֐����Ă΂Ȃ��̂�
// Updata�̒��ōs���悤�ɂ��邱��

void TestUpdata(){
	if(x < 0 || x > 700){
		ix = -ix;
		count++;
	}
	x += ix;
	if(count > 10){
		TaskMgr::getInstance().RequestKill(taskId);
	}
	
}
void TestDraw(){
	DrawString(x,0,"����̓e�X�g�ł�",GetColor(255,255,255));
}

void TestDestory(){
	printfDx("������f�[");
}
//----------------------------------------

Test1::Test1(int posX) : TaskBase() , mPosX(posX),mHandle(0){
	mHandle = DxLib::LoadGraph("data/Monster/img/card0.png");
	//mPosX = 0;
	mIsInitalize = true;
	
}

Test1::~Test1(){

}

bool Test1::Initialize(){
	taskId = TaskMgr::getInstance().Add(TestUpdata,TestDraw,TestDestory,0);
	return true;
}

bool Test1::Updata(){
	
	if(CheckHitKey(KEY_INPUT_RIGHT) != 0){
		mPosX ++;
	}

	if(mPosX > 200){
		TaskMgr::getInstance().RequestKill(mTaskId);
	}

	return true;
}

void Test1::Draw() {
	
	

	DrawGraphF((float)mPosX,0.0f,mHandle,TRUE);
	
	DrawString(mPosX,40,"-Hello! -",GetColor(255,255,255));
	
	
}

void Test1::Finalize(){
	DeleteGraph(mHandle);
	//mHandle = 0;
}