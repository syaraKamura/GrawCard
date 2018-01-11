/*
				ファイル名		:InputBase.h
				作成者			:
				作成日時		:201/018/11
				ソース説明		:
					入力系基底クラス
				
				備考
				
				
				
!*/

#ifndef __INPUT_BASE_H__
#define __INPUT_BASE_H__

class InputBase {

private:

public :

	virtual ~InputBase();

	/*
		押下
	*/
	virtual bool Press(int code) = 0;
	
	/*
		繰り返し
	*/
	virtual bool Repeate(int code) = 0;
	
	/*
		解放
	*/
	virtual bool Relese(int code) = 0;
	
	/*
		入力されている
	*/
	virtual bool On(int code) = 0;
	
	/*
		入力されていない
	*/
	virtual bool Off(int code) = 0;

	/*
		更新
	*/
	virtual bool Update();

};

#endif // __INPUT_BASE_H__