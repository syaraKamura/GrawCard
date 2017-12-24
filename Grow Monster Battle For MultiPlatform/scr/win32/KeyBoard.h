
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__


//キー入力されている
bool Keyboard_On(int keyCode);

//キー入力されていない
bool Keyboard_Off(int keyCode);

//キーが押された状態から解放された
bool Keyboard_Relese(int keyCode);

//キーが押され続けている
bool Keyboard_Repeat(int keyCode);

//キーが押された
bool Keyboard_Press(int keyCode);

void Keyboard_Updata();

#endif