/*
				ファイル名		:SkillBase.h
				作成者			:
				作成日時		:2019/02/07
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __SKILL_BASE_H__
#define __SKILL_BASE_H__

class SkillBase {

private:

	bool mIsEnd;	// エフェクトの再生が終了したか？

public :

	SkillBase() : mIsEnd(false){};
	virtual ~SkillBase() {};

	virtual bool Initialize(int effeckId,float posX,float posY) = 0;

	virtual void Draw() = 0;
	virtual void Update() = 0;

	bool IsEnd() { return mIsEnd; }

};


#endif // __SKILL_BASE_H__