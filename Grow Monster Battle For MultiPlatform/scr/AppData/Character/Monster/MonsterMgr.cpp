/*
				ファイル名		:MonsterMgr.cpp
				作成者			:
				作成日時		:2018/05/27
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "MonsterMgr.h"

#define MONSTER_DATA_PATH "Resources/Data/Monster/MonsterData.dat"

#ifdef __MY_DEBUG__

#define SIZE(X) (sizeof(X)/sizeof(X[0]))
#define __TEST_DATA__	//テストデータ読み込み用

typedef struct MonsterData_t{

	Monster::eType mType;

	char mName[1024];
	int mId;		//管理番号
	int mHp;
	int mHpMax;
	int mMp;
	int mMpMax;

	int mAttack;
	int mDeffence;
	int mSpeed;
	
};

typedef struct MonsterGraphData_t {
	int mId;
	char mFilePath[1024];
};


static MonsterData_t MONSTER_DATA_TBL[] =
{
	{ Monster::eType_Fire ,"ベルフレア",0,20,20,10,10,6,5,2 },
	{ Monster::eType_Fire ,"フレアドラゴン",1,200,200,10,10,16,15,4 },
	{ Monster::eType_Water,"ウォルシャーク",2,20,20,10,10,6,5,2 },
	{ Monster::eType_Water,"ジルトゥーガー",3,200,200,10,10,16,20,2 },
	{ Monster::eType_Grass,"プラタン",4,20,20,10,10,6,5,2 },
	{ Monster::eType_Grass,"ディーバル",5,200,200,10,10,16,21,1 },
	
	{ Monster::eType_Fire,"ウォルフ",6,100,100,10,10,16,21,1 },
	{ Monster::eType_Fire,"フェリル",7,200,200,10,10,16,21,1 },
	{ Monster::eType_Fire,"レッドジェドー",8,200,200,10,10,16,21,1 },
	{ Monster::eType_Water,"ブルージェドー",9,200,200,10,10,16,21,1 },
	{ Monster::eType_Grass,"グリーンジェドー",10,200,200,10,10,16,21,1 },
	{ Monster::eType_Grass,"ディーバル",11,200,200,10,10,16,21,1 },
	{ Monster::eType_Grass,"ディーバル",12,200,200,10,10,16,21,1 },
	{ Monster::eType_Grass,"ディーバル",13,200,200,10,10,16,21,1 },
	{ Monster::eType_Grass,"ディーバル",14,200,200,10,10,16,21,1 },
	{ Monster::eType_Grass,"ディーバル",15,200,200,10,10,16,21,1 },
	{ Monster::eType_Grass,"ディーバル",16,200,200,10,10,16,21,1 },
	{ Monster::eType_Grass,"ディーバル",17,200,200,10,10,16,21,1 },
	{ Monster::eType_Grass,"ディーバル",18,200,200,10,10,16,21,1 },
	{ Monster::eType_Grass,"ディーバル",19,200,200,10,10,16,21,1 },
	{ Monster::eType_Grass,"ディーバル",20,200,200,10,10,16,21,1 },
	{ Monster::eType_Grass,"ディーバル",21,200,200,10,10,16,21,1 },
};

static MonsterGraphData_t MONSTER_GRAPH_DATA_TBL[] = 
{
	{  0,"Resources/Graphics/Monster/mon_00001.png" },
	{  1,"Resources/Graphics/Monster/mon_00002.png" },
	{  2,"Resources/Graphics/Monster/mon_00003.png" },
	{  3,"Resources/Graphics/Monster/mon_00004.png" },
	{  4,"Resources/Graphics/Monster/mon_00005.png" },
	{  5,"Resources/Graphics/Monster/mon_00006.png" },
	{  6,"Resources/Graphics/Monster/mon_00007.png" },
	{  7,"Resources/Graphics/Monster/mon_00008.png" },
	{  8,"Resources/Graphics/Monster/mon_00009.png" },
	{  9,"Resources/Graphics/Monster/mon_00010.png" },
	{ 10,"Resources/Graphics/Monster/mon_00011.png" },
	{ 11,"Resources/Graphics/Monster/mon_00012.png" },
	{ 12,"Resources/Graphics/Monster/mon_00013.png" },
	{ 13,"Resources/Graphics/Monster/mon_00014.png" },
	{ 14,"Resources/Graphics/Monster/mon_00015.png" },
	{ 15,"Resources/Graphics/Monster/mon_00016.png" },
	{ 16,"Resources/Graphics/Monster/mon_00017.png" },
	{ 17,"Resources/Graphics/Monster/mon_00018.png" },
	{ 18,"Resources/Graphics/Monster/mon_00019.png" },
	{ 19,"Resources/Graphics/Monster/mon_00020.png" },
	{ 20,"Resources/Graphics/Monster/mon_00021.png" },
	{ 21,"Resources/Graphics/Monster/mon_00022.png" },
};

#endif

MonsterMgr* MonsterMgr::mInstance = NULL;

MonsterMgr::MonsterMgr() {

	char filePath[1024] = MONSTER_DATA_PATH;

#ifdef __WINDOWS__ 
#ifdef  __MY_DEBUG__

	RESORCES_PATH(filePath);

#endif	
#endif
	std::ifstream file(filePath);

	if (file.is_open() == false) {
		Debug::ErorrMessage("モンスターデータの読み込みに失敗しました.");
	}

	
#if defined(__MY_DEBUG__) && defined(__TEST_DATA__)

	for (int i = 0; i < SIZE(MONSTER_DATA_TBL); i++) {

		Monster monster;

		monster.SetName(MONSTER_DATA_TBL[i].mName);
		monster.SetLevel(1);
		monster.SetCost(1);
		monster.SetId(MONSTER_DATA_TBL[i].mId);
		monster.SetType(MONSTER_DATA_TBL[i].mType);
		monster.SetHomePosition(Monster::eHomePosition_Front);
		monster.SetHp(MONSTER_DATA_TBL[i].mHp);
		monster.SetHpMax(MONSTER_DATA_TBL[i].mHpMax);
		monster.SetMp(MONSTER_DATA_TBL[i].mMp);
		monster.SetMpMax(MONSTER_DATA_TBL[i].mMpMax);
		monster.SetAttack(MONSTER_DATA_TBL[i].mAttack);
		monster.SetDeffence(MONSTER_DATA_TBL[i].mDeffence);
		monster.SetSpeed(MONSTER_DATA_TBL[i].mSpeed);


		mList.push_back(monster);

	}

	for (int i = 0; i < SIZE(MONSTER_GRAPH_DATA_TBL); i++) {
		MonsterGraph_t graph;
		MonsterGraphData_t data = MONSTER_GRAPH_DATA_TBL[i];
		
		graph.id = data.mId;
		
		graph.graph = new Graphics();
		graph.graph->Load(data.mFilePath);

		mGraphList.push_back(graph);

	}

#else

	



#endif
	
	file.close();
	
}

MonsterMgr::~MonsterMgr() {

	for (auto itr = this->mGraphList.begin(); itr != this->mGraphList.end(); ) {
		Graphics *graph = itr->graph;
		graph->Relese();
		Delete(graph);
		mGraphList.erase(itr);
		itr = this->mGraphList.begin();
	}

}

void MonsterMgr::Create() {
	if (MonsterMgr::mInstance == NULL) {
		MonsterMgr::mInstance = new MonsterMgr();
	}
}

void MonsterMgr::Destory() {
	Delete(MonsterMgr::mInstance);
}

MonsterMgr* MonsterMgr::Instance() {

#ifdef __MY_DEBUG__
	if (MonsterMgr::mInstance == NULL) {
		Debug::ErorrMessage("MonsterMgrシングルトンがNULLです.");
	}
#endif

	return MonsterMgr::mInstance;
}


/*
	モンスターデータを返却する
	int	number		:モンスターID
	return			:モンスターデータ
*/
Monster MonsterMgr::getMonsterData(int number) {

	if (this->mList.size() == 0) return Monster();
	
	Monster ret;

	for (auto itr = this->mList.begin(); itr != this->mList.end(); itr++) {

		if (itr->GetId() == number) {
			ret = *itr;
			break;
		}
	}
	return ret;
}

Graphics MonsterMgr::GetGraphics(int number) {

	if (this->mGraphList.size() == 0) return Graphics();

	Graphics graph;

	for (auto itr = this->mGraphList.begin(); itr != this->mGraphList.end(); itr++) {

		if (itr->id == number) {
			graph = *itr->graph;
			break;
		}
	}

	return graph;
}
