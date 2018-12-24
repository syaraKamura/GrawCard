/*
				ファイル名		:TestMapField.h
				作成者			:
				作成日時		:2018/12/23
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __TEST_MAP_FILED_H__
#define __TEST_MAP_FILED_H__

#include "Scene/SceneBase.h"

class MapField;

class TestMapField : public SceneBase {

private:

	MapField* mMapField;

public :

	TestMapField(ISceneBase* changer);
	~TestMapField();

	virtual bool Initialize() override;
	virtual void Finalize() override;
	void PreviousUpdate()override;
	bool Updata()override;
	void Draw() override;
	void PostUpdate() override;

};

#endif // __TEST_MAP_FILED_H__