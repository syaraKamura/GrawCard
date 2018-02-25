/*
				ファイル名		:Framework.h
				作成者			:
				作成日時		:2017/12/07
				ソース説明		:フレームワーククラス


				
				備考
					
					1.初期化、終了処理、更新、描画
					2.デバッグ用機能関係
						メモリ管理
						デバッグ用メニュー

					3.マルチプラットホームとして使用することができる
					4.拡張することができる

				
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

	bool Initialize(int width, int height, const char* titleName = "", bool isWindowMode = true);	//初期化
	void Finalize();	//終了処理

	void Run();			//実行
	
private:


};

#endif