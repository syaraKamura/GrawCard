/*
				ファイル名		:View.h
				作成者			:
				作成日時		:2018/11/05
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __VIEW_H__
#define __VIEW_H__

class View {

public :

	virtual ~View() {}
	virtual bool Update() { return true; };
	virtual void Draw() {};

};


#endif // __TEMPLETE_H__