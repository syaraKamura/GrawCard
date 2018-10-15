/*
				ファイル名		:ClickInput.h
				作成者			:
				作成日時		:2018/10/07
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __CLICKINPUT_H__
#define __CLICKINPUT_H__

class MobileInput;

class ClickInput {

private:
	MobileInput * mInput;

	ClickInput();

	static ClickInput* mInstance;

public :

	static bool Create();
	static void Destroy();

	~ClickInput();
	static ClickInput* GetInstance();

	/*
	押下
	return	true	:押された
	false	:押されていない
	*/
	bool Press(int code);

	/*
	繰り返し
	return	true	:繰り返し入力中
	false	:繰り返し入力中ではない
	*/
	bool Repeate(int code);

	/*
	解放
	return	true	:解放されている
	false	:解放されていない
	*/
	virtual bool Relese(int code);

	/*
	入力されている
	return	true	:入力されている
	false	:入力されていない
	*/
	bool On(int code) ;

	/*
	入力されていない
	return	true	:入力されていない
	false	:入力されている
	*/
	bool Off(int code);

	/*
	更新
	*/
	bool Update() ;

	/*
	フリックデータを返却する
	int	axis	:取得方向 0:水平方向 1:垂直方向

	*/
	int GetFlick(int code, int axis);

	/*
	フリックの角度を度数法で返却する
	*/
	float GetFlickAngleDegree(int code);

	/*
	フリックの角度を弧度法で返却する
	*/
	float GetFlickAngleRadian(int code);

	/*
	座標を返却する
	*/
	int GetPositionX(int code) const ;
	int GetPositionY(int code) const ;


};


#endif // __CLICKINPUT_H__