/*
				ファイル名		:Mouse.h
				作成者			:
				作成日時		:2018/03/13
				ソース説明		:
				
					マウス入力
				
				備考
				
				
				
!*/

#ifndef __MOUSE_INPUT_H__
#define __MOUSE_INPUT_H__

#include "DxLib.h"
#include "InputBase.h"

class Mouse : public InputBase {

public :

	enum eInputType {
		eInputType_Left,	//左
		eInputType_Right,	//右
		eInputType_Middle,	//真ん中
		eInputType_1,
		eInputType_2,
		eInputType_3,
		eInputType_4,
		eInputType_5,
		eInputType_Num,
	};

private:

	typedef struct {
		int Counter;
		int ReleseCounter;
	}MOUSE_DATA_t;

	typedef struct {
		eInputType type;
		unsigned int code;
	}INPUT_TABLE_t;

private:

	const INPUT_TABLE_t INPUT_TABLE[eInputType_Num] = {
		{eInputType_Left,	MOUSE_INPUT_LEFT	},
		{eInputType_Right,	MOUSE_INPUT_RIGHT	},
		{eInputType_Middle,	MOUSE_INPUT_MIDDLE	},
		{eInputType_1,		MOUSE_INPUT_1		},
		{eInputType_2,		MOUSE_INPUT_2		},
		{eInputType_3,		MOUSE_INPUT_3		},
		{eInputType_4,		MOUSE_INPUT_4		},
		{eInputType_5,		MOUSE_INPUT_5		},
	};

public :

	MOUSE_DATA_t mData[eInputType_Num];

	int mPositionX;
	int mPositionY;
	int mOldPositionX;
	int mOldPositionY;
	float mWheel;

public :

	Mouse();

	/*
		押下
		return	true	:押された
				false	:押されていない
	*/
	bool Press(int code)override;

	/*
		繰り返し
		return	true	:繰り返し入力中
				false	:繰り返し入力中ではない
	*/
	bool Repeate(int code)override;

	/*
		解放
		return	true	:解放されている
				false	:解放されていない
	*/
	bool Relese(int code)override;

	/*
		入力されている
		return	true	:入力されている
				false	:入力されていない
	*/
	bool On(int code) override;

	/*
		入力されていない
		return	true	:入力されていない
				false	:入力されている
	*/
	bool Off(int code)override;

	/*
		更新
	*/
	bool Update() override;

	void GetPosition(int* posX, int* posY);

};

#endif // __MOUSE_INPUT_H__