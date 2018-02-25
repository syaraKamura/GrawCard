/*
				�t�@�C����		:Framework.h
				�쐬��			:
				�쐬����		:2017/12/07
				�\�[�X����		:�t���[�����[�N�N���X


				
				���l
					
					1.�������A�I�������A�X�V�A�`��
					2.�f�o�b�O�p�@�\�֌W
						�������Ǘ�
						�f�o�b�O�p���j���[

					3.�}���`�v���b�g�z�[���Ƃ��Ďg�p���邱�Ƃ��ł���
					4.�g�����邱�Ƃ��ł���

				
!*/

#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#include "Common/GameMgr.h"

class Framework {
	
private:
	GameMgr* mGameMgr;
public :

	Framework(GameMgr* game);
	~Framework();

	bool Initialize(int width, int height, const char* titleName = "", bool isWindowMode = true);	//������
	void Finalize();	//�I������

	void Run();			//���s
	
private:


};

#endif