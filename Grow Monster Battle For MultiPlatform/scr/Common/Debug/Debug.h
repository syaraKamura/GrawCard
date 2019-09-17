/*
		ファイル名		:Debug.h
		作成者			:
		作成日時		:2017/12/30
		ソース説明		:デバッグ


		備考



!*/

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <vector>
#include <string>

class DebugList;

class Debug {

private :

	static const int DEBUG_LOG_NUM = 50;

public:

	typedef struct {
		int logType;
		std::string str;
	}DEBUG_LOG_t;

private:

	//基本データ
	/*
		☆メモリーの増減を確認する
			初期起動が終了したときのメモリー量を基準として扱う。
			シーンの切り替わり、オブジェクトが破棄されタイミングでメモリ確保時と異なっていた場合にアサートを出力する

		☆デバッグ画面
			・Nキー、左クリック長押し、３点タッチが行われた場合デバッグリストを出現させる
			・デバッグリストが出現中はゲームの更新はされない
			・デバッグリストの追加について
			・デバッグリスト名ごとにページを作成する
			・デバッグ要綱を並べる
				○Windows版
					・文字列と選択カーソルの描画
				○Android版、マウス版
					・ページ送りボタン、デバッグのON、OFFボタン、実行ボタンとデバッグ名の文字列

		☆デバッグの更新順番
			
			デバッグ更新
			シーン更新
			タスク更新

			シーン描画
			タスク描画
			デバッグ描画

	*/

	
	static int mDebugLogCnt;
	static DEBUG_LOG_t mDebugStrings[DEBUG_LOG_NUM];

	bool mIsActive;	//デバッグ機能起動フラグ
	bool mIsAssert;	//アサートがおきたかフラグ
	static bool mIsVisibleInfoBard;

	size_t mOldAllocSize;
	int mOldAllocNum;

	DebugList* mDebugList;

private:



	/*
		デバッグが起動状態になっているか確認する
		return	true	:起動中
				false	:起動していない
	*/
	bool ChcekActive();

public:

	Debug();
	~Debug();

	void Initialize();
	void Finalize();
	bool Updata();
	void Draw();
	
	void SetDebugList(DebugList* debugList) {
		if (debugList == NULL) return;
		mDebugList = debugList;
	}

	void DeleteList();


public :

	//静的メソッド

	static void LogPrintf(const char* str, ...);
	static void LogPrintfWithInforboard(const char* str, ...);
	static void ErorrMessage(const TCHAR* str, ...);
	
	static void InfoboardOff() {
		mIsVisibleInfoBard = false;
	}
	static void InfoboardOn() {
		mIsVisibleInfoBard = true;
	}
};


#endif //__DEBUG_H__