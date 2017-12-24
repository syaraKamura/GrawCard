/*
				�t�@�C����		:TaskMgr.h
				�쐬��			:
				�쐬����		:2017/12/06
				�\�[�X����		:�^�X�N�}�l�[�W���[�N���X

				
				
				���l
					
				
				
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

	//�ʏ�X�V
	void Updata();

	//�`��
	void Draw();


	//���ƍX�V
	void LateUpdata();

	//���ׂĂ��폜����
	void DeleteAll();

	int Add(TaskBase* task,int priolty = 0);
	int Add(pointer_func updata,pointer_func draw,pointer_func destroy,int priolty);

	//�폜���˗�����
	void RequestKill(int taskId );

	//�w��̃^�X�N��ԋp����
	TaskBase* GetTask(int taskId);


private :

	TaskMgr();
	

	//�폜�˗����������^�X�N������
	void KillTaskProc();


};

#endif //__TASK_MGR_H__