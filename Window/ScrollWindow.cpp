﻿/*
				ファイル名		:ScrollWindow.cpp
				作成者			:Syara
				作成日時		:201/01/28
				ソース説明		:
				
					スクロール機能付きウィンドウ
				
				備考
				
				
				
!*/
#include "DxLib.h"

#include "../Code/AppData/Item/ItemData.h"
#include "ScrollWindow.h"


void ScrollWindow_Initialize(SCROLL_WINDOW_DATA_t* window,int drawX,int drawY,int windowWidth,int windowHeigh,int scrollSize) {

	WindowBase_Initialize(&window->window, drawX, drawY, windowWidth, windowHeigh);
	Scrollbar_Initialize(&window->scrollbar, scrollSize, ItemData_GetItemDataNum());
	window->alpha = 255;
	window->windowColor = GetColor(0, 255, 255);
	window->frameColor = GetColor(0, 255, 0);



	int winHeigh = windowHeigh / ITEM_WINDOW_NUM;
	for (int i = 0; i < ITEM_WINDOW_NUM; i++) {
		int x = drawX + 5;
		int y = (i * winHeigh) + drawY + 5;
		int width = x + windowWidth - 75;
		int height = winHeigh - 5;
		WindowBase_Initialize(&window->itemWindow[i], x, y, width, height);
	}

	/*
	アイテムデータ一覧
	*/
#if false
	int itemNum = ItemData_GetItemDataNum();
	ITEM_PARAM_DATA_t itemData;
	for (int i = 0; i < itemNum; i++) {
		ItemData_GetItemData(i, &itemData);
		DrawString(20, 60 + i * 20, itemData.name, GetColor(255, 255, 255));
	}
#endif

}

/*
	スクロール機能付きウィンドウ描画
*/
void ScrollWindow_Draw(SCROLL_WINDOW_DATA_t window,int scrollbarType) {

	WindowBase_Draw(window.window, window.alpha, window.windowColor, window.frameColor);
	
	int scrollbarDrawX = 0;
	int scrollbarDrawY = 0;

	switch (scrollbarType) {
	case eScrollWindow_ScrollbarVertical:
		scrollbarDrawX = window.window.drawPosX + window.window.width - 40;
		scrollbarDrawY = window.window.drawPosY;
		Scrollbar_DrawVertical(window.scrollbar, scrollbarDrawX, scrollbarDrawY);
		break;
	case eScrollWindow_ScrollbarHorizontal:
		
		scrollbarDrawY = window.window.drawPosX;
		scrollbarDrawY = window.window.drawPosY + window.window.width - 40;
		Scrollbar_DrawHorizontal(window.scrollbar, scrollbarDrawX, scrollbarDrawY);
		break;
	}	
#if false
	ITEM_PARAM_DATA_t itemData;
	for (int i = 0; i < window.scrollbar.valueMax; i++) {
		
		
		int drawItem = i + (int)window.scrollbar.nowValue;
		if (drawItem >= 0 && drawItem < window.scrollbar.valueMax) {
			
			int alpha = 100;
			if (drawItem == ((int)window.scrollbar.nowValue)) {
				alpha = 255;
			}


			WindowBase_Draw(window.itemWindow[i], alpha, GetColor(255, 255, 0), GetColor(255, 255, 255));

			if (drawItem < ItemData_GetItemDataNum()) {
				ItemData_GetItemData(drawItem, &itemData);
				DrawString(20, 60 + i * 181, itemData.name, GetColor(0, 0, 0));
			}
		}
		
	}
#endif
}

/*
	スクロール機能付きウィンドウ描画
*/
void ScrollWindow_DrawGraph(SCROLL_WINDOW_DATA_t window,int graphichandle,int scrollbarType) {

	WindowBase_DrawGraph(window.window, graphichandle, window.alpha);

	int scrollbarDrawX = 0;
	int scrollbarDrawY = 0;

	switch (scrollbarType) {
	case eScrollWindow_ScrollbarVertical:
		scrollbarDrawX = window.window.drawPosX + window.window.width - 40;
		scrollbarDrawY = window.window.drawPosY;
		Scrollbar_DrawVertical(window.scrollbar, scrollbarDrawX, scrollbarDrawY);
		break;
	case eScrollWindow_ScrollbarHorizontal:

		scrollbarDrawY = window.window.drawPosX;
		scrollbarDrawY = window.window.drawPosY + window.window.width - 40;
		Scrollbar_DrawHorizontal(window.scrollbar, scrollbarDrawX, scrollbarDrawY);
		break;
	}

	ITEM_PARAM_DATA_t itemData;
	for (int i = 0; i < window.scrollbar.valueMax; i++) {


		int drawSelectItem = (int)window.scrollbar.nowValue;
		int drawItem = i;


		if ((int)window.scrollbar.nowValue > window.scrollbar.valueMax - (ITEM_WINDOW_NUM / 2)) {
			drawSelectItem = ITEM_WINDOW_NUM - (int)(window.scrollbar.valueMax - window.scrollbar.nowValue);
			drawItem = (i + window.scrollbar.valueMax) - (ITEM_WINDOW_NUM);
		}
		else if ((int)window.scrollbar.nowValue < ITEM_WINDOW_NUM / 2) {
			drawSelectItem = (int)window.scrollbar.nowValue;
			drawItem = i;
		}
		else {
			drawSelectItem = ITEM_WINDOW_NUM / 2;
			drawItem = (i + (int)window.scrollbar.nowValue) - (ITEM_WINDOW_NUM / 2);
		}
		

		char str[256];
		sprintf_s(str, "テスト%d", drawItem);
		if (drawSelectItem >= 0 && drawSelectItem < window.scrollbar.valueMax) {

			int alpha = 100;
			if (drawSelectItem == i) {
				alpha = 255;
			}


			WindowBase_Draw(window.itemWindow[i], alpha, GetColor(255, 255, 0), GetColor(255, 255, 255));

			if (drawSelectItem < ItemData_GetItemDataNum()) {
				//ItemData_GetItemData(drawItem, &itemData);
				
				//DrawString(20, 60 + i * 181, itemData.name, GetColor(0, 0, 0));
				DrawString(20, 36 + i * 72, str, GetColor(0, 0, 0));
			}
		}

	}
}

/*
	ウィンドウの描画座標設定
*/
void ScrollWindow_SetWindowPosition(SCROLL_WINDOW_DATA_t* window,int drawPosX,int drawPosY) {
	window->window.drawPosX = drawPosX;
	window->window.drawPosY = drawPosY;

}

/*
	スクロールバーをスクロールする
	SCROLL_WINDOW_DATA_t* window
	int value						:設定した値だけスクロールする
*/
void ScrollWindow_Scroll(SCROLL_WINDOW_DATA_t* window,int value) {
	Scrollbar_AddValue(&window->scrollbar, value);
}

void ScrolWindow_SetValue(SCROLL_WINDOW_DATA_t* window, int value) {
	Scrollbar_SetValue(&window->scrollbar, value);
}

/*
	値を返却する
*/
int ScrollWindow_GetValue(SCROLL_WINDOW_DATA_t window,int posX,int posY) {
	
	int result = -1;

	for (int i = 0; i < ITEM_WINDOW_NUM; i++) {
	
		if (WindowBase_IsInSide(window.itemWindow[i], posX, posY) == true) {

			int drawItem = i + (int)window.scrollbar.nowValue;
			if (drawItem >= 0 && drawItem < window.scrollbar.valueMax) {
				result = drawItem;
				break;
			}
		}
	}
	return result;
}
