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

#ifdef __MY_DEBUG__
#include "Common/Debug/Debug.h"
#endif

#include <list>

class TaskMgr {

public:

	/*
		優先順位



	*/
	enum ePriorty {
		ePriorty_Graphics,
		ePriorty_0,
		ePriorty_1,
		ePriorty_2,
		ePriorty_3,
		ePriorty_4,
		ePriorty_5,
		ePriorty_6,
		ePriorty_7,
		ePriorty_Defaul,
		ePriorty_9,
		ePriorty_10,
		ePriorty_11,
		ePriorty_12,
		ePriorty_13,
		ePriorty_Fade,
	};

private:

	unsigned int mOrder;
	std::list<TaskBase*> mList;
	std::list<int> mKillOrderList;


public:
	~TaskMgr();


	static TaskMgr& getInstance() {
		static TaskMgr inst;
		return inst;
	}

	bool Initialize();
	void Finalize();

	void InputUpdate();
	void PreviousUpdate();

	//通常更新
	bool Updata();

	//描画
	void Draw();


	//あと更新
	void LateUpdata();

	//すべてを削除する
	void DeleteAll();

	int Add(TaskBase* task, int priolty = 0);
	int Add(pointer_func updata, pointer_func draw, pointer_func destroy, int priolty);

	//削除を依頼する
	void RequestKill(int taskId);

	//指定のタスクを返却する
	TaskBase* GetTask(int taskId) const;

private:

	TaskMgr();


	//削除依頼があったタスクを消す
	void KillTaskProc();


};

#endif //__TASK_MGR_H__