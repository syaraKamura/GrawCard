/*
				ファイル名		:Task.h
				作成者			:
				作成日時		:2017/12/05
				ソース説明		:タスククラス

				
				
				備考
					
				
				
!*/

#ifndef __TASK_H__
#define __TASK_H__

class Task{

public :

	virtual ~Task(){};

	virtual bool Initialize() { return true; };
	virtual void Finalize(){};
	virtual bool Updata() = 0;
	virtual void Draw() = 0;
	
};

#endif