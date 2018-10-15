/*
				ファイル名		:PadInput.h
				作成者			:
				作成日時		:2018/10/05
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __PADINPUT_H__
#define __PADINPUT_H__

class PadInput {

private :

	PadInput* mInstance;

	PadInput();
	
public:
	~PadInput();

	bool Create();
	void Destroy();

	const PadInput* GetInstance();

};


#endif // __PADINPUT_H__