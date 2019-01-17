/*
				ファイル名		:MapField.cpp
				作成者			:
				作成日時		:2018/12/22
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"

#include "Map.h"
#include "MapField.h"


MapField::MapField() : TaskBase(){
	
	this->mMapImageHandle = new Graphics();
	this->mMapImageHandle->Load("Resources/Graphics/Map/forest.png");


	this->mMapIcons.push_back(new Map(200.0f, 300.0f,"テスト１"));
	this->mMapIcons.push_back(new Map(380.0f,380.0f,"テスト２"));

}

MapField::MapField(int stageNum) {

	// 受け取ったステージ番号からステージを生成
		// マップ背景画像読み込み
		// マップデータ読み込み

	// クリア状況を取得

}

MapField::~MapField() {

	mMapImageHandle->Relese();
	Delete(mMapImageHandle);

	for (int i = 0; i < mMapIcons.size(); i++) {
		Delete(mMapIcons[i]);
	}
	
	mMapIcons.clear();

}

bool MapField::Initialize(){

	return true;
}

void MapField::Finalize(){

}

void MapField::PreviousUpdate(){

}

void MapField::InputUpdate() {

}

bool MapField::Updata(){
	
	int openMapNum = -1;
	for (int i = 0; i < this->mMapIcons.size(); i++) {
		if (this->mMapIcons[i]->IsOpenSelectButton()) {
			openMapNum = i;
			break;
		}
	}

	for (int i = 0; i < this->mMapIcons.size(); i++) {
		if (openMapNum >= 0 && openMapNum != i) {
			this->mMapIcons[i]->SetToucheEnable(false);
		}
		else {
			this->mMapIcons[i]->SetToucheEnable(true);
		}
		this->mMapIcons[i]->Updata();
	}
	
	return true;
}

void MapField::PostUpdate() {

}

void MapField::Draw() {

	this->mMapImageHandle->Draw();

	for (int i = 0; i < this->mMapIcons.size(); i++) {
		this->mMapIcons[i]->Draw();
	}

}



