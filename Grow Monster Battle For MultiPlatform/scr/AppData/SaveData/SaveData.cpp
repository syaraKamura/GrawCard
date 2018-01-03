/*
		ファイル名		:SaveData.cpp
		作成者			:
		作成日時		:2017/12/31
		ソース説明		:


		備考



!*/

#include "Common/GameCommon.h"
#include "SaveData.h"

SaveData::SaveData() {
	strcpyDx(mVersion, "1.00");
}

SaveData::~SaveData() {

}

SaveData SaveData::Load() {
	SaveData data;



	return data;
}

void SaveData::Save(SaveData save) {


}
