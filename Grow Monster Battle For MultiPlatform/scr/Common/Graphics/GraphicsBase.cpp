/*
				ファイル名		:GraphicsBase.cpp
				作成者			:
				作成日時		:2017/12/25
				ソース説明		:
				
				
				備考
				
				
				
!*/

//	------- インクルード宣言
#include "Common/GameCommon.h"
#include "GraphicsBase.h"
//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体

//	------- データテーブル

//	------- スタティック変数宣言

//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

//	------- プロトタイプ宣言していないスタティック関数(内部関数)

//	------- グローバル関数
void GraphicsBase::SetFileName(const char* fileName) {
	int length = strlenDx(fileName);

	const char* name = NULL;

	if (length >= 64) {
		name = (fileName + (length - 65));
	}
	else {
		name = fileName;
	}

	//#ifdef __MY_DEBUG__
	strcpyDx(mFileName, name);
	//#endif // __MY_DEBUG__

}

