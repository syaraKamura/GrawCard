/*
				�t�@�C����		:TaskBase.h
				�쐬��			:
				�쐬����		:2017/12/05
				�\�[�X����		:�^�X�N���N���X

				
				
				���l
					
				
				
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
	//�v���C�I���e�B ���l���������قǗD�揇�ʂ�����
	int mPriorty;
	
	pointer_func m_pUpdata;
	pointer_func m_pDraw;
	pointer_func m_pDestroy;

protected:
	bool mIsInitalize;	//�������t���O
	int mTaskId;		//�^�X�N�ԍ�	
	
public :

	

	TaskBase(){
		mTaskId = 0;
		mIsInitalize = false;
		mPriorty = 0;
	}

	virtual ~TaskBase(){};

	void SetTaskId(int taskId){mTaskId = taskId;}
	int GetTaskId(){return mTaskId;}

	//�D�揇�ʂ̐ݒ�
	void SetPriorty(int priorty);
	const int GetPriorty(){return mPriorty;}

	const char* GetTaskName() const throw();

	//���������I�����Ă��邩�H
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