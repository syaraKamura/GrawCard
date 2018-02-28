/*
				�t�@�C����		:SceneMgr.h
				�쐬��			:
				�쐬����		:2017/12/11
				�\�[�X����		:�Q�[���Ǘ��N���X

				
				
				���l
					
				
!*/


#ifndef __GAME_MGR_H__
#define __GAME_MGR_H__

class SceneMgr;
class FPS;
#ifdef __MY_DEBUG__
class Debug;
#endif 

class GameMgr{

private:

	SceneMgr* mSceneMgr;
	FPS* mFPS;

#ifdef __MY_DEBUG__
	Debug* mDebug;
#endif

public :

	GameMgr();
	~GameMgr();

	void Initialize();
	void Finalize();
	bool Updata();
	void Draw();

#ifndef __MY_DEBUG__

	//�f�o�b�O�p


#endif

private:
	
#ifndef __MY_DEBUG__

	//�f�o�b�O�p

#endif

};

#endif	//__GAME_MGR_H__