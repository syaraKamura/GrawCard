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

	//初期化
	virtual bool Initialize() { return true; };
	
	//前　更新処理
	virtual void PreviousUpdate() = 0;
	
	//入力更新処理
	virtual void InputUpdate() {};
	
	//更新処理
	virtual bool Updata() = 0;

	//描画
	virtual void Draw() = 0;

	//後 更新処理
	virtual void PostUpdate() = 0;

	//終了処理
	virtual void Finalize() {};

	
};

#endif