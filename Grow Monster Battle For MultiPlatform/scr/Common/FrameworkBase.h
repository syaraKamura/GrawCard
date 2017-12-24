/*
				�t�@�C����		:FrameworkBase.h
				�쐬��			:
				�쐬����		:2017/12/07
				�\�[�X����		:�t���[�����[�N���N���X


				
				���l
					
					1.�������A�I�������A�X�V�A�`��
					2.�f�o�b�O�p�@�\�֌W
						�������Ǘ�
						�f�o�b�O�p���j���[

					3.�}���`�v���b�g�z�[���Ƃ��Ďg�p���邱�Ƃ��ł���
					4.�g�����邱�Ƃ��ł���

				
!*/

#ifndef __FRAMEWORK_BASE_H__
#define __FRAMEWORK_BASE_H__

class GameMgr;

class FrameworkBase{
	
private:
	GameMgr* mGameMgr;
	
public :

	FrameworkBase(GameMgr* game);
	~FrameworkBase();


	void Setup(int width,int height,const char* titleName = "",BOOL isWindowMode = true);

	void Initialize();	//������
	void Finalize();	//�I������

	bool Run();			//���s
	
private:


};

#endif