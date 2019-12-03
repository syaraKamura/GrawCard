/*
				�t�@�C����		:Fade.h
				�쐬��			:
				�쐬����		:2017/12/05
				�\�[�X����		:�t�F�[�h�N���X

				
				
				���l
					�Q�[���N�����ɐ������Q�[���I�����ɔj��������
				
				
!*/

#ifndef __FADE_H__
#define __FADE_H__

#include "Common/Task/TaskBase.h"

const float FADE_VALUE_MAX = 255.0f;

class Fade:public TaskBase{

private:

	unsigned int mColor;	//�F
	bool mIsFadeIn;			//�t�F�[�h�t���O true:�t�F�[�h�� false:�t�F�[�h���ł͂Ȃ�
	bool mIsFadeOut;		//�t�F�[�h�t���O true:�t�F�[�h�� false:�t�F�[�h���ł͂Ȃ�
	bool mIsFadeEnd;		//�t�F�[�h�I���t���O

	float mFadeValue;		//�t�F�[�h�̒l
	float mThrowTime;			//�t�F�[�h�o�ߎ���

	float mFadeTime;			//�t�F�[�h�ɂ����鎞��(�b)

private:

	Fade();

public :

	static Fade* GetInstance(){
		static Fade* inst = NULL;
		if(inst == NULL){
			inst = new Fade();
		}
		return inst;
	}

	
	~Fade();

	//�F��ݒ肷��
	void SetFadeColor(unsigned int red,unsigned int green,unsigned int blue);
		
	void FadeIn(float fadeTime = 1.0f);
	void FadeOut(float fadeTime = 1.0f);

	bool IsFadeEnd();

	bool Initialize() override;
	void Finalize() override;
	bool Updata() override;
	void Draw() override;

};


#endif	//__FADE_H__