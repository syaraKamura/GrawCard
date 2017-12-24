/*
				ファイル名		:TaskMgr.h
				作成者			:
				作成日時		:2017/12/06
				ソース説明		:タスクマネージャークラス

				
				
				備考
					
				
				
!*/

#ifndef __TASK_MGR_H__
#define __TASK_MGR_H__


#include "TaskBase.h"

#include <list>

class TaskMgr {

private:

	unsigned int mOrder;
	std::list<TaskBase*> mList;
	std::list<int> mKillOrderList;
	
	
public :
	~TaskMgr();
	

	 static TaskMgr& getInstance(){
		 static TaskMgr inst;
		return inst;
	}

	 void Initialize();

	//通常更新
	void Updata();

	//描画
	void Draw();


	//あと更新
	void LateUpdata();

	//すべてを削除する
	void DeleteAll();

	int Add(TaskBase* task,int priolty = 0);
	int Add(pointer_func updata,pointer_func draw,pointer_func destroy,int priolty);

	//削除を依頼する
	void RequestKill(int taskId );

	//指定のタスクを返却する
	TaskBase* GetTask(int taskId);


private :

	TaskMgr();
	

	//削除依頼があったタスクを消す
	void KillTaskProc();


};

#endif //__TASK_MGR_H__