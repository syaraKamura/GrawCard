/*
				ファイル名		:Touch.cpp
				作成者			:
				作成日時		:
				ソース説明		:
				
				
				備考
				
				
				
!*/

//	------- インクルード宣言
#include "DxLib.h"

#include "Touch.h"

//	------- 固定定数宣言
const int TOUCH_MAX_NUM = 10;		//タッチデータの最大数
//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体


typedef struct {
	int touchNum;	//タッチ数
	TOUCH_DATA touchData[TOUCH_MAX_NUM];
}TOUCH_MGR;

//	------- データテーブル

//	------- スタティック変数宣言
static TOUCH_MGR s_touch;
//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

//	------- プロトタイプ宣言していないスタティック関数(内部関数)

static int _TouchProc() {
	
	s_touch.touchNum = GetTouchInputNum();

	if (s_touch.touchNum >= TOUCH_MAX_NUM) {
		s_touch.touchNum = TOUCH_MAX_NUM;
	}

	for (int i = 0; i < TOUCH_MAX_NUM; i++) {
		TOUCH_DATA* touch = &s_touch.touchData[i];
		if (GetTouchInput(i, &touch->posX, &touch->posY, NULL, &touch->device) == 0) {
			touch->id = i;
		}
		else {
			touch->id = -1;
		}
	}

	for (int i = 0; i < TOUCH_MAX_NUM; i++) {
		TOUCH_DATA* touch = &s_touch.touchData[i];
		if (touch->id == i) {
			touch->touchCnt++;
		}
		else {
			touch->touchCnt = 0;
			touch->posX = 0;
			touch->posY = 0;
			touch->oldPosX = 0;
			touch->oldPosY = 0;
			touch->releseCnt = 0;
		}
	}

#if 0
#ifdef __MY_DEBUG__
	printfDx("TouchNum:%d\n", s_touch.touchNum);
	
	for (int i = 0; i < TOUCH_MAX_NUM; i++) {
		TOUCH_DATA* touch = &s_touch.touchData[i];
		printfDx("ID:%d device:%d posX:%d posY:%d cnt:%d\n", touch->id, touch->device, touch->posX, touch->posY, touch->touchCnt);
	}
#endif // __MY_DEBUG__
#endif // 0
	return 0;
}

//	------- グローバル関数

/*
	タッチしている数を数える
*/
int Touch_GetTouchNum() {
	return s_touch.touchNum;
}

/*
	タッチしている
	int		num	:タッチ番号
	return	true	:タッチしている
			false	:タッチしていない
*/
bool Touch_On(int num) {
	return s_touch.touchData[num].touchCnt > 0;
}

/*
	タッチしていない
	int		num	:タッチ番号
	return	true	:タッチしていない
			false	:タッチしてしている
*/
bool Touch_Off(int num) {
	return s_touch.touchData[num].touchCnt > 0;
}

/*
	スクリーンがタッチされた
	int		num		:タッチ番号
	return	true	:タッチされた
			false	:タッチされていない
*/
bool Touch_Press(int num) {
	return s_touch.touchData[num].touchCnt == 1;
}

/*
	スクリーンがタッチされ続けている
	int		num		:タッチ番号
	return	true	:タッチされた
			false	:タッチされていない
*/
bool Touch_Repeat(int num) {
	return s_touch.touchData[num].touchCnt > 0 && s_touch.touchData[num].touchCnt % 20 == 0;
}

/*
	スクリーンから指が離された
	int		num		:タッチ番号
	return	true	:指が離された
			false	:タッチされている
*/
bool Touch_Relese(int num) {

	if (s_touch.touchData[num].touchCnt > 0) {
		s_touch.touchData[num].releseCnt = 0;
	}
	else {
		s_touch.touchData[num].releseCnt ++;
	}

	return s_touch.touchData[num].releseCnt == 1;
}

/*
	フリック操作されたか(上下)
	int		num		:タッチ番号
	return	0		:フリックされていない
			1以上	:上方向にフリックされた
			-1以下	:下方向にフリックされた
*/
int Touch_FulickUpDown(int num) {

	TOUCH_DATA* touch = &s_touch.touchData[num];

	int dir = 0;

	if (Touch_Press(num) == true) {
		touch->oldPosY = touch->posY;
	}
	else if (Touch_Relese(num) == true) {

		dir = touch->oldPosY - touch->posY;

	}

	return dir;

}

/*
	フリック操作されたか(左右)
	int		num		:タッチ番号
	return	0		:フリックされていない
	1以上	:左方向にフリックされた
	-1以下	:右方向にフリックされた
*/
int Touch_FulickLeftRight(int num) {

	TOUCH_DATA* touch = &s_touch.touchData[num];

	int dir = 0;

	if (Touch_Press(num) == true) {
		touch->oldPosX = touch->posX;
	}
	else if (Touch_Relese(num) == true) {

		dir = touch->oldPosX - touch->posX;

	}
	return dir;
}

/*
	指定のタッチ番号のデータを返却する
	int num	:タッチ番号
	return TOUCH_DATAポインタ変数
*/
const TOUCH_DATA* Touch_GetParamData(int num){
	const TOUCH_DATA* touch = &s_touch.touchData[num];
	return touch;
}


/*
	タッチパッドエミュレータの初期化
*/
void TouchPadEmuletor_Initialize(){
	
	//システムでパッドをを使用する設定ならば,初期化処理を行う

	//画像の読み込み

	//画像がなければBOXの描画をするように設定する

}

/*
	タッチパッドエミュレータの終了処理
*/
void TouchPadEmuletor_Finalize(){

	//システムでパッドをを使用する設定ならば,初期化処理を行う

	//画像の削除

	//画像がなければBOXの削除処理を行わない


}

/*
	タッチパッドエミュレータの更新処理
*/
void TouchPadEmuletor_Updata(){

	//システムでパッドをを使用する設定ならば,更新処理を行う


	//タッチ処理の更新

}

/*
	タッチパッドエミュレータの描画処理
*/
void TouchPadEmuletor_Draw(){

	//システムでパッドをを使用する設定ならば,画像描画を行う


	//画像がなければBOXを描画する


}


/*
	タッチ処理の更新
*/
void Touch_Updata() {
	_TouchProc();
}

