/*
				ファイル名		:ScriptBase.cpp
				作成者			:
				作成日時		:2018/04/03
				ソース説明		:
				
					スクリプト基底クラス
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "ScriptBase.h"

ScriptBase::ScriptBase() : TaskBase() {

}

bool ScriptBase::Initialize() {
	return true;
}

void ScriptBase::Finalize() {

}

void ScriptBase::PreviousUpdate() {

}

void ScriptBase::InputUpdate() {

}

bool ScriptBase::Updata() {
	return true;
}

void ScriptBase::PostUpdate() {

}

void ScriptBase::Draw() {

}

