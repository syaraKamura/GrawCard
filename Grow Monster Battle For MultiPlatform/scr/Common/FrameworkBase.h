/*
				ファイル名		:FrameworkBase.h
				作成者			:
				作成日時		:2017/12/07
				ソース説明		:フレームワーク基底クラス


				
				備考
					
					1.初期化、終了処理、更新、描画
					2.デバッグ用機能関係
						メモリ管理
						デバッグ用メニュー

					3.マルチプラットホームとして使用することができる
					4.拡張することができる

				
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

	void Initialize();	//初期化
	void Finalize();	//終了処理

	bool Run();			//実行
	
private:


};

#endif