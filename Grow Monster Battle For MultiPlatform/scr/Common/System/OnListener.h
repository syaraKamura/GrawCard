/*
				ファイル名		:OnClickListener.h
				作成者			:
				作成日時		:2018/11/05
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __ON_LISTENER_H__
#define __ON_LISTENER_H__

class View;

class OnListener{

public :
	virtual ~OnListener() {};
	virtual void OnClick(View* view) {};

private:

};

#endif // __ON_CLICK_LISTENER_H__
