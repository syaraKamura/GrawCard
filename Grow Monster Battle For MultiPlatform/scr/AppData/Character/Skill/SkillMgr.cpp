/*
				ファイル名		:SkillMgr.cpp
				作成者			:
				作成日時		:2019/02/24
				ソース説明		:
				
				
				備考
				
				
				
!*/
#include "Common/GameCommon.h"
#include "Common/FileLoader/TblLoader/TblLoader.h"
#include "Common/FileLoader/TblLoader/TblLoaderMgr.h"
#include "SkillMgr.h"

#define FILE_PATH "Resources/Data/Table/SkillList/SkillList.dtl"
#define DEFAULT_OFSET (1000)

SkillMgr* SkillMgr::mInstance = nullptr;

SkillMgr::SkillMgr() {
	mLoad = loader::TblLoaderMgr::GetInstance()->LoadRequest(FILE_PATH);
	mStateCnt = SkillMgr::eState_Load;
}

SkillMgr::~SkillMgr() {

	
	for (auto itr = mPlayDataList.begin(); itr != mPlayDataList.end();) {
		PlaySkill* data = &(*itr);
#ifdef ENABLE_EFFEKSEER
		data->effect->ReleseRequest();
		EffekseerEffect::Effect::Instance()->Manual_Stop(data->effect);
#endif // ENABLE_EFFEKSEER
		
		mPlayDataList.erase(itr);
	}

	Delete(mLoad);

}

void SkillMgr::Create() {
	if (mInstance == nullptr) {
		mInstance = new SkillMgr();
	}
}

void SkillMgr::Destroy() {
	Delete(mInstance);
}

SkillMgr* SkillMgr::GetInstance() {
	return mInstance;
}

void SkillMgr::Updata() {
	
	switch (mStateCnt) {
	case SkillMgr::eState_Load:

		if (mLoad->IsExist() == false) {
			mStateCnt = SkillMgr::eState_Error;
		}
		else if (mLoad->IsLoadEnd()) {
			mStateCnt = SkillMgr::eState_Attach;
		}

		break;
	case SkillMgr::eState_Attach:
	{

		loader::TblLoader::TblData tableData = mLoad->GetTableData();
		int num = tableData.GetDataCnt();

		struct description {
			int id;
			char description[64];
			char filePath[64];
			int playTime;		// 再生時間
		};	

		struct data {
			int id;
			char name[64];
			int effectNo;
			short attackType;
			short elemntType;
			int hp;
			int mp;
			int attack;
			int deffence;
			int speed;
		};

		int size = tableData.GetDataNum(0, sizeof(data));
		data* d = new data[size];

		tableData.GetData(0, d);

		size = tableData.GetDataNum(1, sizeof(description));
		description* desc = new description[size];

		tableData.GetData(1, desc);

		for (int i = 0; i < size; i++) {
			data& skill = *(d + i);
			description& des = *(desc + i);

			SkillData add;
			add.id = skill.id + DEFAULT_OFSET;
			strcpyDx(add.name, skill.name);
			strcpyDx(add.description, des.description);
			add.attackType = skill.attackType;
			add.elemntType = skill.elemntType;
			add.effectNo = skill.effectNo;
			add.attack = skill.attack;
			add.deffence = skill.deffence;
			add.speed = skill.speed;
			add.hp = skill.hp;
			add.mp = skill.mp;
			add.effectPlayTime = des.playTime;
#ifdef ENABLE_EFFEKSEER
			EffekseerEffect::EffectLoader::Instance()->Load(add.id, des.filePath);
#endif // ENABLE_EFFEKSEER

			mSkillDataList.push_back(add);

		}


		mStateCnt = SkillMgr::eState_Exit;
	}
	break;
	case SkillMgr::eState_Error:
		mStateCnt = SkillMgr::eState_Exit;
		break;
	case SkillMgr::eState_Exit:

		break;
	}


	if (mStateCnt == SkillMgr::eState_Exit) {
		for (int i = 0; i < mPlayDataList.size();) {
			PlaySkill* data = &mPlayDataList[i];
			if (data->timer >= data->timerMax) {
#ifdef ENABLE_EFFEKSEER
				data->effect->ReleseRequest();
				EffekseerEffect::Effect::Instance()->Manual_Stop(data->effect);
#endif // #ifdef ENABLE_EFFEKSEER
				mPlayDataList.erase(mPlayDataList.begin() + i);
				continue;
			}
			data->timer++;

			i++;

		}
	}

}

PlaySkill* SkillMgr::Play(int id) {
	return Play(id,0.0f,0.0f);
}

PlaySkill* SkillMgr::Play(int id, float posX, float posY) {

	if (id == -1) {
		return nullptr;
	}

	for (int i = 0; i < mSkillDataList.size(); i++) {
		SkillData data = mSkillDataList[i];
		int eftId = data.id - DEFAULT_OFSET;
		if (eftId == id) {
#ifdef ENABLE_EFFEKSEER
			mPlayEffectHandle = EffekseerEffect::EffectLoader::Instance()->Get(data.id);
			EffekseerEffect::Effect::Instance()->Play(&mPlayEffectData, mPlayEffectHandle);
			EffekseerEffect::EffectManual* effectData = EffekseerEffect::Effect::Instance()->Manual_Play(mPlayEffectHandle);

			EffekseerEffect::Effect::Instance()->SetPosition(effectData->GetEffectPlayData(), 100, 100, 0);
			EffekseerEffect::Effect::Instance()->SetScale(effectData->GetEffectPlayData(), 10, 10, 10);

			GraphicsDrawMgr::GetInstance()->Add(effectData, 100);

			// 描画座標を設定
			EffekseerEffect::Effect::Instance()->SetPosition(effectData->GetEffectPlayData(),posX,posY,0.0f);

			PlaySkill skill;
			skill.effect = effectData;
			skill.timer = 0;
			skill.timerMax = data.effectPlayTime;
			skill.skillData = data;
			mPlayDataList.push_back(skill);
			
			return &skill;
#endif // #ifdef ENABLE_EFFEKSEER
		}

	}
	return nullptr;

}

SkillData SkillMgr::GetSkillData(int id) {

	for (int i = 0; i < mSkillDataList.size(); i++) {
		SkillData data = mSkillDataList[i];
		int dataId = data.id - DEFAULT_OFSET;
		if (id == dataId) {
			return data;
		}
	}

	return SkillData();
}

bool SkillMgr::IsEnd() {

	return false;
}


