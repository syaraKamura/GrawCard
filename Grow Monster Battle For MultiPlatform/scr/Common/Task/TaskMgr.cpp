/*
				�t�@�C����		:TaskMgr.cpp
				�쐬��			:
				�쐬����		:2017/12/06
				�\�[�X����		:�^�X�N�}�l�[�W���[�N���X

				
				
				���l
					
				
				
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

//�ʏ�X�V
void TaskMgr::Updata(){
	for(auto itr = mList.begin();itr != mList.end();itr++){
		if((*itr)->isInitialize() == false){
			(*itr)->Initialize();
		}else{
			(*itr)->Updata();
		}
	}
}

//�`��
void TaskMgr::Draw(){
		
	for(auto itr = mList.begin();itr != mList.end();itr++){
		bool isSkip = false;
		//�폜�˗������Ă��Ȃ����m�F����
		for(auto reqKillOrder = mKillOrderList.begin(); reqKillOrder != mKillOrderList.end();reqKillOrder++){
			if((*itr)->GetTaskId() == *reqKillOrder){
				isSkip = true;
				break;
			}
		}
		//���������I����Ă��Ȃ��܂��͍폜�˗�������Ă���Ȃ�`������Ȃ�
		if((*itr)->isInitialize() == false|| isSkip == true) continue;
			
		(*itr)->Draw();

	}
}


//���ƍX�V
void TaskMgr::LateUpdata(){
	KillTaskProc();
}

//���ׂĂ��폜����
void TaskMgr::DeleteAll(){
	mList.clear();
	mKillOrderList.clear();
}

//�\�[�g�p�֐�
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
	�w��̃^�X�N��ԋp����
	int taskId	:�^�X�N�ԍ�
	return	NULL�ȊO: �w��̃^�X�N��ԋp����
			NULL	: ���݂��Ȃ��^�X�N�ԍ�
*/
TaskBase* TaskMgr::GetTask(int taskId){
	for(auto itr = mList.begin();itr != mList.end();itr++){
		if((*itr)->GetTaskId() == taskId){
			return (*itr);
		}
	}
	return NULL;
}


//�폜���˗�����
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

//�폜�˗����������^�X�N������
void TaskMgr::KillTaskProc(){

	if(mKillOrderList.size() == 0) return ;

	//�w��̃��X�g���폜����
	for(auto reqKillOrder = mKillOrderList.begin(); reqKillOrder != mKillOrderList.end();reqKillOrder++){
		bool isKill = false;	//�폜�t���O true:�폜 false:�폜�ł��Ȃ�����
		bool isFind = false;	//�폜�˗��̃^�X�N�ԍ������t���O true:����	false:�������Ȃ�����
		for(auto itr = mList.begin();itr != mList.end();itr++){
			if((*itr)->GetTaskId() == *reqKillOrder){
					
				(*itr)->Finalize();						//�폜
				delete (*itr);							//����������폜
				mList.erase(itr);						//���X�g����폜
				mKillOrderList.erase(reqKillOrder);		//�폜�˗����X�g����^�X�N�ԍ����폜
				isKill = true;							//�폜����
				isFind = true;							//��������
				break;
			}
		}

		//�폜�˗����ꂽ���A������Ȃ�����
		if(isFind == false){
			//�폜�˗����X�g����폜
			mKillOrderList.erase(reqKillOrder);
		}

		//�폜�ł����܂��́@�폜�˗����X�g�̃T�C�Y��0�ɂȂ���
		if(isKill == true || mKillOrderList.size() == 0){
			break;
		}
	}
		
}