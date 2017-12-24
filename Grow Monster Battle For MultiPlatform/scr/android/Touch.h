/*
				ファイル名		:Touch.h
				作成者			:
				作成日時		:
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __TOUCH_H__
#define __TOUCH_H__

//	------- インクルード宣言

//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体

typedef struct {

	int id;			//タッチID
	int device;		//デバイス

	int posX;		//タッチ座標
	int posY;
	int oldPosX;	//前回のタッチ座標
	int oldPosY;
	int touchCnt;	//タッチ時間

	int releseCnt;	//離された時間

}TOUCH_DATA;

//	------- グローバル関数

/*
	タッチ更新処理
*/
extern void Touch_Updata();

/*
タッチしている数を数える
*/
extern int Touch_GetTouchNum();

/*
タッチしている
int		num	:タッチ番号
return	true	:タッチしている
false	:タッチしていない
*/
extern bool Touch_On(int num);

/*
タッチしていない
int		num	:タッチ番号
return	true	:タッチしていない
false	:タッチしてしている
*/
extern bool Touch_Off(int num);

/*
スクリーンがタッチされた
int		num		:タッチ番号
return	true	:タッチされた
false	:タッチされていない
*/
extern bool Touch_Press(int num);

/*
スクリーンがタッチされ続けている
int		num		:タッチ番号
return	true	:タッチされた
false	:タッチされていない
*/
extern bool Touch_Repeat(int num);

/*
スクリーンから指が離された
int		num		:タッチ番号
return	true	:指が離された
false	:タッチされている
*/
extern bool Touch_Relese(int num);

/*
フリック操作されたか(上下)
int		num		:タッチ番号
return	0		:フリックされていない
1以上	:上方向にフリックされた
-1以下	:下方向にフリックされた
*/
extern int Touch_FulickUpDown(int num);

/*
フリック操作されたか(左右)
int		num		:タッチ番号
return	0		:フリックされていない
1以上	:左方向にフリックされた
-1以下	:右方向にフリックされた
*/
extern int Touch_FulickLeftRight(int num);

/*
	指定のタッチ番号のデータを返却する
	int num	:タッチ番号
	return TOUCH_DATAポインタ変数
*/
extern const TOUCH_DATA* Touch_GetParamData(int num);

//	------- インライン関数(ヘッダー内関数)

#endif // __TOUCH_H__