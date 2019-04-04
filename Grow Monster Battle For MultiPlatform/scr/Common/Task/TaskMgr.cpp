﻿/*
				ファイル名		:TaskMgr.cpp
				作成者			:
				作成日時		:2017/12/06
				ソース説明		:タスクマネージャークラス

				
				
				備考
					
				
				
!*/

#include "Common/GameCommon.h"
#include "TaskBase.h"
#include "TaskMgr.h"

bool TaskMgr::Initialize(){
	mOrder = 0;
	mList = std::list<TaskBase*>();
	mKillOrderList = std::list<int>();
	DeleteAll();
	return true;
}

/*
	終了処理
*/
void TaskMgr::Finalize() {
	DeleteAll();
}

void TaskMgr::InputUpdate(){
	for (auto itr = mList.begin(); itr != mList.end(); itr++) {
		if ((*itr)->isInitialize() == true) {
			(*itr)->InputUpdate();
		}

	}
}

void TaskMgr::PreviousUpdate() {

	for (auto itr = mList.begin(); itr != mList.end(); itr++) {
		if ((*itr)->isInitialize() == false) {
			bool ret = (*itr)->Initialize();
			(*itr)->SetInitialize(ret);
		}
 
		if ((*itr)->isInitialize() == true) {
			(*itr)->PreviousUpdate();
		}

	}
	
}

//通常更新
bool TaskMgr::Updata(){
	bool result = true;
	for(auto itr = mList.begin();itr != mList.end();itr++){
		if((*itr)->isInitialize() == true){
			result = (*itr)->Updata();
		}
	}
	return result;
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

	for (auto itr = mList.begin(); itr != mList.end(); itr++) {
		if ((*itr)->isInitialize() == true) {
			(*itr)->PostUpdate();
		}
	}

	KillTaskProc();
}

//すべてを削除する
void TaskMgr::DeleteAll(){
	mList.clear();
	mKillOrderList.clear();
	mSarchList.clear();
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

	// 検索用データを設定
	mSarchList.insert(std::make_pair(mOrder, task));

	
#ifdef __MY_DEBUG__

	Debug::LogPrintf("=====       登録Task       ===== \n");
	Debug::LogPrintf("TaskId : %d TaskName : %s\n", task->GetTaskId(), task->GetTaskName());
	Debug::LogPrintf("================================ \n\n\n");

	Debug::LogPrintf("=====        Taskソート    ===== \n");
	for (auto itr = mList.begin(); itr != mList.end(); itr++) {
		Debug::LogPrintf("TaskId : %d TaskName : %s Prio : %d\n", (*itr)->GetTaskId(), (*itr)->GetTaskName(), (*itr)->GetPriorty());
	}
	Debug::LogPrintf("================================ \n\n\n");
#endif


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
TaskBase* TaskMgr::GetTask(int taskId) const{

#if true
	// C++11以降でのみ使用できる機能.
	try {
		return mSarchList.at(taskId);
	}
	catch (std::out_of_range) {
		return NULL;
	}

#else

	for(auto itr = mList.begin();itr != mList.end();itr++){
		if((*itr)->GetTaskId() == taskId){
			return (*itr);
		}
	}

	return NULL;
#endif

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
		for (auto& task : this->mList) {
			if (task->GetTaskId() == taskId) {
				task->RequestKill();
				break;
			}
		}
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

#if 1
	for (auto itr = mList.begin(); itr != mList.end(); itr++) {
		if ((*itr)->IsRelease()) {
			int taskId = (*itr)->GetTaskId();		//タスク検索用mapデータから削除するタスク番号を設定
			(*itr)->Finalize();						//削除
			Delete(*itr);							//メモリから削除
			mList.erase(itr);						//リストから削除
			mKillOrderList.remove(taskId);			//削除依頼リストからタスク番号を削除
			mSarchList.erase(taskId);				//タスク検索用mapデータからタスク番号を削除
			itr = mList.begin();
		}
	}
#else
	if(mKillOrderList.size() == 0) return ;

	//指定のリストを削除する
	for(auto reqKillOrder = mKillOrderList.begin(); reqKillOrder != mKillOrderList.end();reqKillOrder++){
		bool isKill = false;	//削除フラグ true:削除 false:削除できなかった
		bool isFind = false;	//削除依頼のタスク番号発見フラグ true:発見	false:見つけられなかった
		for(auto itr = mList.begin();itr != mList.end();itr++){
			if((*itr)->GetTaskId() == *reqKillOrder){
				
#ifdef __MY_DEBUG__
				Debug::LogPrintf("=====        削除Task      ===== \n");
				Debug::LogPrintf("TaskId : %d TaskName : %s\n", (*itr)->GetTaskId(), (*itr)->GetTaskName());
				Debug::LogPrintf("================================ \n\n");
#endif

				int taskId = (*itr)->GetTaskId();		//タスク検索用mapデータから削除するタスク番号を設定
				(*itr)->Finalize();						//削除
				Delete (*itr);							//メモリから削除
				mList.erase(itr);						//リストから削除
				mKillOrderList.erase(reqKillOrder);		//削除依頼リストからタスク番号を削除
				mSarchList.erase(taskId);				//タスク検索用mapデータからタスク番号を削除
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
#endif	


#ifdef __MY_DEBUG__
	Debug::LogPrintf("=====      削除後のTask    ===== \n");
	for (auto itr = mList.begin(); itr != mList.end(); itr++) {
		Debug::LogPrintf("TaskId : %d TaskName : %s\n", (*itr)->GetTaskId(), (*itr)->GetTaskName());
	}
	Debug::LogPrintf("================================ \n");
#endif



}