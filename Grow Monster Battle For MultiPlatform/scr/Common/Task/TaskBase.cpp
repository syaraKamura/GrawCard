/*
				�t�@�C����		:TaskBase.cpp
				�쐬��			:
				�쐬����		:2017/12/05
				�\�[�X����		:�^�X�N�}�l�[�W���[�N���X

				
				
				���l
					
				
				
!*/

#include "Common/GameCommon.h"
#include "TaskBase.h"

void TaskBase::SetFunction(pointer_func updata,pointer_func draw,pointer_func destroy){
	m_pUpdata = updata;
	m_pDraw = draw;
	m_pDestroy = destroy;
	mIsInitalize = true;
}

bool TaskBase::Initialize() { return true; }

void TaskBase::Finalize(){
	if(m_pDestroy != NULL){
		m_pDestroy();
	}
}

void TaskBase::PreviousUpdate() {

}

void TaskBase::InputUpdate() {

}

bool TaskBase::Updata(){
	if(m_pUpdata != NULL){
		m_pUpdata();
	}
	return true;
}

void TaskBase::Draw(){
	if(m_pDraw != NULL){
		m_pDraw();
	}
}

void TaskBase::PostUpdate() {

}

//�D�揇�ʂ̐ݒ�
void TaskBase::SetPriorty(int priorty){
	mPriorty = priorty;
}

const char* TaskBase::GetTaskName() const throw(){
#ifdef __WINDOWS__
	const char* name = typeid(*this).name();
	return name;
#else
	return "";
#endif
}