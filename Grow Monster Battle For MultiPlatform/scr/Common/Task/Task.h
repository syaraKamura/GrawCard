/*
				�t�@�C����		:Task.h
				�쐬��			:
				�쐬����		:2017/12/05
				�\�[�X����		:�^�X�N�N���X

				
				
				���l
					
				
				
!*/

#ifndef __TASK_H__
#define __TASK_H__

class Task{

public :

	virtual ~Task(){};

	//������
	virtual bool Initialize() { return true; };
	
	//�O�@�X�V����
	virtual void PreviousUpdate() = 0;
	
	//���͍X�V����
	virtual void InputUpdate() {};
	
	//�X�V����
	virtual bool Updata() = 0;

	//�`��
	virtual void Draw() = 0;

	//�� �X�V����
	virtual void PostUpdate() = 0;

	//�I������
	virtual void Finalize() {};

	
};

#endif