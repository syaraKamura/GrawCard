
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__


//�L�[���͂���Ă���
bool Keyboard_On(int keyCode);

//�L�[���͂���Ă��Ȃ�
bool Keyboard_Off(int keyCode);

//�L�[�������ꂽ��Ԃ��������ꂽ
bool Keyboard_Relese(int keyCode);

//�L�[�������ꑱ���Ă���
bool Keyboard_Repeat(int keyCode);

//�L�[�������ꂽ
bool Keyboard_Press(int keyCode);

void Keyboard_Updata();

#endif