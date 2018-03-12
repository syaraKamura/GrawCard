/*
				ファイル名		:CommonResource.h
				作成者			:
				作成日時		:2018/02/13
				ソース説明		:
				
					汎用リソース
				
				備考
				
				
				
!*/

#ifndef __COMMON_RESOURCE_H__
#define __COMMON_RESOURCE_H__

class Graphics;

class ComRes {

public :
	enum eComResName {
		eComResName_MainMenuBG,			//メインメニュー背景
		eComResName_CommonBG,			//汎用背景

		eComResName_Num,
	};

private:

	

	enum eComResKind {
		eComResKind_Graphic,
		eComResKind_Num,
	};

	typedef struct {
		eComResKind kind;
		char fileName[1024];
		Graphics* Graphic;
	}COMMON_RES_t;


	COMMON_RES_t mComRes[eComResName_Num];

protected:
	
	static ComRes* mInstance;
	ComRes();
	
public :

	static void Create();
	static void Destory();
	static ComRes* Instance();
	
	bool Load();
	void Relese();

	Graphics* GetGraphicHandle(eComResName name);

};

#endif // __COMMON_RESOURCE_H__