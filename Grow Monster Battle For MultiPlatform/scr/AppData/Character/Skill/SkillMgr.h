/*
				ファイル名		:SkillMgr.h
				作成者			:
				作成日時		:2019/2/24
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __SKILL_MGR_H__
#define __SKILL_MGR_H__

#include <vector>
#include "SkillAttackType.inc"

namespace loader {
	class TblLoader;
}

typedef struct SkillData {
	int id;
	char name[64];
	char description[64];
	int effectNo;
	int effectPlayTime;
	short attackType;
	short elemntType;
	int hp;
	int mp;
	int attack;
	int deffence;
	int speed;
}SkillData;

typedef struct PlaySkill {
#ifdef ENABLE_EFFEKSEER
	EffekseerEffect::EffectManual* effect;	 // エフェクトデータ
#endif // ENABLE_EFFEKSEER
	int timerMax;		// 再生時間
	int timer;			// 経過時間

	SkillData skillData;

	bool IsPlay() {
		return timer < timerMax;
	}

}PlaySkill;

class SkillMgr {

private:

	enum eState{
		eState_Load,
		eState_Attach,
		eState_Error,
		eState_Exit,

	};

	loader::TblLoader* mLoad ;
	int mStateCnt;

	static SkillMgr* mInstance;

	std::vector<SkillData> mSkillDataList;
	std::vector<PlaySkill> mPlayDataList;

	int mPlayEffectHandle;
#ifdef ENABLE_EFFEKSEER
	EffekseerEffect::EffectPlayData mPlayEffectData;
#endif // ENABLE_EFFEKSEER
	SkillMgr();
	~SkillMgr();

	std::vector<int> mHandle;

public :

	/*
		生成
	*/
	static void Create();

	/*
		削除
	*/
	static void Destroy();

	static SkillMgr* GetInstance();

	/*
		更新
	*/
	void Updata();
	PlaySkill* Play(int id);
	PlaySkill* Play(int id,float posX,float posY);
	
	SkillData GetSkillData(int id);

	bool IsEnd();

};


#endif // __SKILL_MGR_H__