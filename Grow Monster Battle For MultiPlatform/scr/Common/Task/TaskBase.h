/*
				ファイル名		:TaskBase.h
				作成者			:
				作成日時		:2017/12/05
				ソース説明		:タスク基底クラス

				
				
				備考
					
				
				
!*/

#ifndef __TASK_BASE_H__
#define __TASK_BASE_H__

#include "Task.h"

#ifdef __MY_DEBUG__
#include "Common/Debug/Debug.h"
#endif 

typedef void(*pointer_func)(void);

class TaskBase : public Task{


private:
	//プライオリティ 数値が小さいほど優先順位が高い
	int mPriorty;
	
	pointer_func m_pUpdata;
	pointer_func m_pDraw;
	pointer_func m_pDestroy;

protected:
	bool mIsInitalize;	//初期化フラグ
	int mTaskId;		//タスク番号	
	
public :

	

	TaskBase(){
		mTaskId = 0;
		mIsInitalize = false;
		mPriorty = 0;
	}

	virtual ~TaskBase(){};

	void SetTaskId(int taskId){mTaskId = taskId;}
	int GetTaskId(){return mTaskId;}

	//優先順位の設定
	void SetPriorty(int priorty);
	const int GetPriorty(){return mPriorty;}

	const char* GetTaskName() const throw();

	//初期化が終了しているか？
	bool isInitialize(){return mIsInitalize;}
	void SetInitialize(bool isInitialize) { mIsInitalize = isInitialize; }
	
	bool Initialize()override ;
	void Finalize()override;

	void PreviousUpdate()override;
	void InputUpdate() override;
	bool Updata()override;
	void PostUpdate() override;
	void Draw()override;
	
	void SetFunction(pointer_func updata,pointer_func draw,pointer_func destroy);

};

#endif