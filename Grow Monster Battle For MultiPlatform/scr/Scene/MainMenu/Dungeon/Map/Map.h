/*
				ファイル名		:Map.h
				作成者			:
				作成日時		:2018/11/24
				ソース説明		:
				
				
				備考
				

					マップの使用について
					
				マップアイコンをクリックする
				クエスト一覧


				マップ番号
				マップイコン番号
				クエスト番号

				Quest_0_00_000.txt

				
				
!*/

#ifndef __MAP_H__
#define __MAP_H__

#include "Common/Task/TaskBase.h"

class Button;
class ButtonGraph;
class BMFont;

class Map : public TaskBase {

public:

	enum eAnimState {
		eAnimState_None = -1,
		eAnimState_In,
		eAnimState_Out,
	};

	struct StoryData {
		int id;					// 管理番号
		char title[64];			// タイトル名
		int beforADV;			// バトル前ADV
		int afterADV;			// バトル後ADV
		int isBattle;			// バトルがあるか？
		int battleId;			// バトル用データID

		void Set(StoryData data) {
			*this = data;
		}
	};

private:

	static const int DUGEON_TITLE_POS_X = 200;	// ダンジョン題名表示座標
	static const int DUGEON_TITLE_POS_Y = 40;

	eAnimState mAnimState;

	BMFont* mFontString;

	// ダンジョンのデータ
	Graphics* mMapIcon; // マップアイコン

	char mDungeonDataFileName[1024];

	// クエストボタン
	std::vector<Button*> mButtons;
	ButtonGraph* mButtonGraph;
	
	std::vector<StoryData> mStoryDataList;

	int mSelectButtonNum;
	int mSelectButtonMax;
	int mOrderDrawGraphic;	// 描画タスクの番号

	bool mIsTouchEnable;	// マップアイコンのクリックを有効にするか？
	bool mIsOpenSelectButton;	// 選択ボタンが開いているか？

	char mMapTitleText[1024];

	void OnClick(View* view) override;

public:

	Map();
	Map(int posX, int posY, const char* mapTitle);
	~Map();

	void Draw() override;
	void PostUpdate() override;
	bool Updata() override;

	void SetUp(StoryData* pinData,int size);

	bool GetStoryData(StoryData* poutData);

	int GetIndex();

	/*
		マップアイコンのクリックが有効か？
		return	true	:有効
				false	:無効
	*/
	bool IsTouchEnable();
	void SetToucheEnable(bool enable);

	/*
		ダンジョン選択ボタンが開いているか
		return	true	:開いている
				false	:開いていない
	*/
	bool IsOpenSelectButton();

	void SetDrawFlag(bool isDraw);

};


#endif // __MAP_H__