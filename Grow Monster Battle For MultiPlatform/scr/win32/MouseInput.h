/*
				ファイル名		:MouseInput
				作成者			:
				作成日時		:2018/03/13
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __MOUSE_INPUT_FUNC_H__
#define __MOUSE_INPUT_FUNC_H__

#include "Common/Input/Mouse.h"

//キー入力されている
bool Mouse_On(Mouse::eInputType code);

//キー入力されていない
bool Mouse_Off(Mouse::eInputType code);

//キーが押された状態から解放された
bool Mouse_Relese(Mouse::eInputType code);

//キーが押され続けている
bool Mouse_Repeat(Mouse::eInputType code);

//キーが押された
bool Mouse_Press(Mouse::eInputType code);

void Mouse_GetPosition(int* posX, int* posY);

void Mouse_Initialize();
void Mouse_Finalize();

void Mouse_Updata();

#endif // __MOUSE_INPUT_FUNC_H__