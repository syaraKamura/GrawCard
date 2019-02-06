/*
				ファイル名		:ScriptFunc.h
				作成者			:
				作成日時		:2019/01/31
				ソース説明		:
					
					スクリプトの関数群
				
				備考
				
				
				
!*/

#ifndef __SCRIPT_FUNC_H__
#define __SCRIPT_FUNC_H__

namespace AdvScript {
	class ScriptBase;

	void ScriptFunc_Initialize(ScriptBase& script);
	void ScriptFunc_Finalize();
	
	/*
		スクリプトの関数を実行する
	*/
	int ScriptFunc_FunctionUpdate();
	

}

#endif // __SCRIPT_FUNC_H__