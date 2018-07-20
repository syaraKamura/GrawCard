/*
				ファイル名		:ScriptBase.h
				作成者			:
				作成日時		:2018/04/03
				ソース説明		:
					
					スクリプト基底クラス
				
				備考
				
					基本的な動作を作成していく

					〇スクリプトの解読機能
					〇スクリプトファイル読み込み
				
!*/

#include "Common/Task/TaskBase.h"

#ifndef __SCRIPT_BASE_H__
#define __SCRIPT_BASE_H__

class ScriptBase : public TaskBase {

private:

	Graphics mGraphics;

public:

	ScriptBase();

	bool Initialize()override;
	void Finalize()override;

	void PreviousUpdate()override;
	void InputUpdate() override;
	bool Updata()override;
	void PostUpdate() override;
	void Draw()override;

};

#endif // __TEMPLETE_H__