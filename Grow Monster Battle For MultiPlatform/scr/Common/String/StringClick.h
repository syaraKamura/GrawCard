/*
				ファイル名		:StringClick.h
				作成者			:
				作成日時		:2018/10/11
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __STRING_CLICK_H__
#define __STRING_CLICK_H__

class StringClick  {

public :

	enum eClickType {
		eClickType_On,
		eClickType_Press,
		eClickType_Relese,
	};



private:

	static const char* mString;
	static int mStringLength;
	static int mFontSize;
	static unsigned int mColor;
	static bool mIsClick;
	

public :

	/*	
		文字列を設定
		const char* str		: 文字列
		int fontSize  = 18	: フォントサイズ
	*/
	static void SetString(const char* str, int fontSize  = 18);

	/*
		色を設定する
		unsigned int color	: カラー値
	*/
	static void SetColor(unsigned int color);

	/*
		文字列の中にカーソルが存在しているか
		eClickType type	: クリック入力の種類
		int code = 0	: クリック判定コード
		return	true	: 文字列の中に存在している
				false	: 存在していない
	*/
	static bool IsInSide(eClickType type, int code = 0);

	/*
		文字列を描画する
		int posX	: 描画X座標
		int posY	: 描画Y座標
	*/
	static void Draw(int posX, int posY);


};


#endif // __STRING_CLICK_H__