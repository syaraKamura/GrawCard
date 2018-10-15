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

#ifdef __MY_DEBUG__
#include "Common/Debug/Debug.h"
#endif

#include <list>

class TaskMgr {

public:

	/*
		�D�揇��



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

	//�ʏ�X�V
	bool Updata();

	//�`��
	void Draw();


	//���ƍX�V
	void LateUpdata();

	//���ׂĂ��폜����
	void DeleteAll();

	int Add(TaskBase* task, int priolty = 0);
	int Add(pointer_func updata, pointer_func draw, pointer_func destroy, int priolty);

	//�폜���˗�����
	void RequestKill(int taskId);

	//�w��̃^�X�N��ԋp����
	TaskBase* GetTask(int taskId) const;

private:

	TaskMgr();


	//�폜�˗����������^�X�N������
	void KillTaskProc();


};

#endif //__TASK_MGR_H__