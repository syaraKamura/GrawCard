/*
				ファイル名		:MapField.h
				作成者			:
				作成日時		:2018/12/22
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __MAP_FIELD_H__
#define __MAP_FIELD_H__

#include "Common/Task/TaskBase.h"
#include "Common/Graphics/Button/Button.h"
#include <vector>

class Map;

class MapField : public TaskBase{

private:
	
	Graphics* mMapImageHandle;
	std::vector<Map*> mMapIcons;

public :

	MapField();
	
	MapField(int stageNum);

	~MapField();

	bool Initialize()override;
	void Finalize()override;

	void PreviousUpdate()override;
	void InputUpdate() override;
	bool Updata()override;
	void PostUpdate() override;
	void Draw()override;


};


#endif // __MAP_FIELD_H__