/*
				ファイル名		:ISceneBase.h
				作成者			:
				作成日時		:2017/12/07
				ソース説明		:シーン基底クラスインターフェース

				
				
				備考
					
				
				
!*/

#ifndef __ISCENE_BASE_H__
#define __ISCENE_BASE_H__

#include "Common/Task/Task.h"

class ISceneBase{

private:

public :

	enum eScene {

		eScene_None = -1,
		eScene_Boot,				//起動
		eScene_Opning,				//オープニング
		eScene_Title,				//タイトル
		eScene_MainMenu,			//メインメニュー

#ifdef __MY_DEBUG__
		eScene_TestMenu,			//テストメニュー
		eScene_AITest,				//AIテスト
		eScene_TestComunication,	//通信テスト
		eScene_TestBattle,			//バトルテスト
		eScene_TestADV,				//アドベンチャーテスト
#endif

		eScene_Num,
	};

public :


	virtual ~ISceneBase() = 0;
	virtual void SceneChange(eScene nextScene) = 0;
};

#endif	//__ISCENE_BASE_H__