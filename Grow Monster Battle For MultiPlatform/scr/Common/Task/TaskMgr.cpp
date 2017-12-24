/*
				ファイル名		:TaskMgr.cpp
				作成者			:
				作成日時		:2017/12/06
				ソース説明		:タスクマネージャークラス

				
				
				備考
					
				
				
!*/

#include "Common/GameCommon.h"
#include "TaskBase.h"
#include "TaskMgr.h"

void TaskMgr::Initialize(){
	mOrder = 0;
	mList = std::list<TaskBase*>();
	mKillOrderList = std::list<int>();
	DeleteAll();
}

//通常更新
void TaskMgr::Updata(){
	for(auto itr = mList.begin();itr != mList.end();itr++){
		if((*itr)->isInitialize() == false){
			(*itr)->Initialize();
		}else{
			(*itr)->Updata();
		}
	}
}

//描画
void TaskMgr::Draw(){
		
	for(auto itr = mList.begin();itr != mList.end();itr++){
		bool isSkip = false;
		//削除依頼が来ていないか確認する
		for(auto reqKillOrder = mKillOrderList.begin(); reqKillOrder != mKillOrderList.end();reqKillOrder++){
			if((*itr)->GetTaskId() == *reqKillOrder){
				isSkip = true;
				break;
			}
		}
		//初期化が終わっていないまたは削除依頼がされているなら描画をしない
		if((*itr)->isInitialize() == false|| isSkip == true) continue;
			
		(*itr)->Draw();

	}
}


//あと更新
void TaskMgr::LateUpdata(){
	KillTaskProc();
}

//すべてを削除する
void TaskMgr::DeleteAll(){
	mList.clear();
	mKillOrderList.clear();
}

//ソート用関数
static bool sort_priorty(TaskBase* a,TaskBase* b){
	return a->GetPriorty() < b->GetPriorty();
}

int TaskMgr::Add(TaskBase* task,int priorty){
	
	if(priorty < 0){
		priorty = 0;
	}

	task->SetTaskId(++mOrder);
	task->SetPriorty(priorty);
	mList.push_back(task);

	mList.sort(sort_priorty);

	return (mOrder);
}

int TaskMgr::Add(pointer_func updata,pointer_func draw,pointer_func destroy,int priolty){
	TaskBase* task = new TaskBase();
	task->SetFunction(updata,draw,destroy);
	return Add(task,priolty);	
}

/*
	指定のタスクを返却する
	int taskId	:タスク番号
	return	NULL以外: 指定のタスクを返却する
			NULL	: 存在しないタスク番号
*/
TaskBase* TaskMgr::GetTask(int taskId){
	for(auto itr = mList.begin();itr != mList.end();itr++){
		if((*itr)->GetTaskId() == taskId){
			return (*itr);
		}
	}
	return NULL;
}


//削除を依頼する
void TaskMgr::RequestKill(int taskId ){

	bool isReqest = false;

	if(mKillOrderList.size() == 0){
		isReqest = true;
	}else{
		for(auto reqKillOrder = mKillOrderList.begin(); reqKillOrder != mKillOrderList.end();reqKillOrder++){
			if(taskId == *reqKillOrder){
				isReqest = false;
				break;
			}else{
				isReqest = true;
			}
		}
	}

	if(isReqest == true){
		mKillOrderList.push_back(taskId);
	}
}


TaskMgr::TaskMgr(){
	mOrder = 0;
	DeleteAll();
}
TaskMgr::~TaskMgr(){DeleteAll();}

//削除依頼があったタスクを消す
void TaskMgr::KillTaskProc(){

	if(mKillOrderList.size() == 0) return ;

	//指定のリストを削除する
	for(auto reqKillOrder = mKillOrderList.begin(); reqKillOrder != mKillOrderList.end();reqKillOrder++){
		bool isKill = false;	//削除フラグ true:削除 false:削除できなかった
		bool isFind = false;	//削除依頼のタスク番号発見フラグ true:発見	false:見つけられなかった
		for(auto itr = mList.begin();itr != mList.end();itr++){
			if((*itr)->GetTaskId() == *reqKillOrder){
					
				(*itr)->Finalize();						//削除
				delete (*itr);							//メモリから削除
				mList.erase(itr);						//リストから削除
				mKillOrderList.erase(reqKillOrder);		//削除依頼リストからタスク番号を削除
				isKill = true;							//削除した
				isFind = true;							//発見した
				break;
			}
		}

		//削除依頼されたが、見つからなかった
		if(isFind == false){
			//削除依頼リストから削除
			mKillOrderList.erase(reqKillOrder);
		}

		//削除できたまたは　削除依頼リストのサイズが0になった
		if(isKill == true || mKillOrderList.size() == 0){
			break;
		}
	}
		
}