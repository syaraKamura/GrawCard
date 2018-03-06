/*
				ファイル名		:
				作成者			:
				作成日時		:
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "DxLib.h"
#include <stdio.h>
#include <jni.h>
#include <android/native_activity.h>
#include "InputString.h"



static JNIEnv* env;
static const ANativeActivity* mNativeActivity;
static int InputEnd;
char InputString[1024];

void InputString_Initialize() {
	return;
	//mNativeActivity = new ANativeActivity();
	mNativeActivity = GetNativeActivity();
	
	// JavaVM とソフト実行用スレッドを関連付け( C++ から Java の機能を使用するために必要 )
	if (mNativeActivity->vm->AttachCurrentThreadAsDaemon(&env, NULL) != JNI_OK) {
		return;
	}

	//JavaクラスのGrawMonsterBattleを取得
	jclass jclass_GrawMonsterBattle = env->GetObjectClass(mNativeActivity->clazz);
	
	//JavaクラスのGrawMonsterBattleのメンバー関数StartInputStringDialogのIDを取得
	jmethodID jmethodID_StartInputDialog = env->GetMethodID(jclass_GrawMonsterBattle, "StartInputStringDialog", "()V");
	
	if (jmethodID_StartInputDialog != nullptr) {
		//JavaクラスのGrawMonsterBattleのメンバー関数StartInputStringDialogの呼び出し
		env->CallVoidMethod(mNativeActivity->clazz, jmethodID_StartInputDialog);
	}

	//JavaクラスのGrawMonsterBattleの参照を削除
	env->DeleteLocalRef(jclass_GrawMonsterBattle);

	//JavaVMとソフト実行用スレッドの関連付け終了
	mNativeActivity->vm->DetachCurrentThread();

	InputEnd = 0;

}

void InputString_Update() {
	return;

	if (InputEnd == 0) {

		// JavaVM とソフト実行用スレッドを関連付け( C++ から Java の機能を使用するために必要 )
		if (mNativeActivity->vm->AttachCurrentThreadAsDaemon(&env, NULL) != JNI_OK) {
			return;
		}

		//JavaクラスのGrawMonsterBattleを取得
		jclass jclass_GrawMonsterBattle = env->GetObjectClass(mNativeActivity->clazz);

		//JavaクラスのGrawMonsterBattleのメンバー変数InputEndのIDを取得
		jfieldID jfieldID_InputEnd = env->GetFieldID(jclass_GrawMonsterBattle, "InputEnd", "I");

		//JavaクラスのGrawMonsterBattleのメンバー変数InputEndの値をローカル変数InputEndに代入
		InputEnd = env->GetIntField(mNativeActivity->clazz, jfieldID_InputEnd);

		if (InputEnd == 1) {

			
			jfieldID jfieldID_InputString = env->GetFieldID(jclass_GrawMonsterBattle, "InputString", "Ljava/lang/String");

			jstring jstring_InputString = (jstring)env->GetObjectField(mNativeActivity->clazz, jfieldID_InputString);

			//JavaクラスのGrawMonsterBattleのメンバー変数InputStringのjstringｋらC++用の文字列のアドレスを取得
			const char* chars_InputString = env->GetStringUTFChars(jstring_InputString, NULL);

			strcpyDx(InputString, chars_InputString);

			// JavaクラスのGrawMonsterBattleのメンバー変数 InputString の jstring から取得した C++ 用の文字列のアドレスを解放
			env->ReleaseStringUTFChars(jstring_InputString, chars_InputString);

			//JavaクラスのGrawMonsterBattleのメンバー変数InputStringのjstreingオブジェクトの参照を削除
			env->DeleteLocalRef(jstring_InputString);

		}

		//javaクラスのGrawMonsterBattleの参照を削除
		env->DeleteLocalRef(jclass_GrawMonsterBattle);

		//JaavaVMとソフトの実行用スレッドの関連付け終了
		mNativeActivity->vm->DetachCurrentThread();

	}

	printfDx("%s\n",InputString);

}