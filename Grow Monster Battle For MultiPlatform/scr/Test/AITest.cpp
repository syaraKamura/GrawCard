
#include "Common/GameCommon.h"


#ifdef __MY_DEBUG__
#include "Scene/ISceneBase.h"
#include "Test/AITest.h"
#include "Common/Graphics/GraphicsMulti.h"
#include "Common/Graphics/Graphics.h"


const int MAP_WIDTH = 41;
const int MAP_HEIGHT= 37;
const int MAP_CHIP_SIZE = 20;

//�G���
const int ENEMY_KIND_NUM = 4;


enum eDirection{
	eDirection_Up,
	eDirection_Left,
	eDirection_Right,
	eDirection_Down,
};

const unsigned int EnemyColor[ENEMY_KIND_NUM] = 
{
	GetColor(255,255,0),	//���F
	GetColor(255,0,0),		//��
	GetColor(0,255,0),		//��
	GetColor(0,0,255),		//��
};

static int MapData[MAP_HEIGHT][MAP_WIDTH];

typedef struct{
	int posX;			//���W
	int posY;
	int direction;		//����
	int kind;			//���
	int counter;		//�J�E���^�[
	int moveStartTime;	//�ړ��J�n����
}Enemy_t;

Enemy_t enemy[ENEMY_KIND_NUM];

Graphics* mGraphics;
GraphicsMulti* mGraphicsMulti;
int posX = 0;
int vecX = 4;

void Map_Initialize(){

	//�}�b�v�̉��n���쐬
	for(int y = 0;y < MAP_HEIGHT;y++){
		for(int x = 0;x < MAP_WIDTH;x++){
			
			if(y == 0 || y == MAP_HEIGHT - 1 || 
				x == 0 || x == MAP_WIDTH - 1){
					MapData[y][x] = 1;
			}else if(y % 2 == 0 && x % 2 == 0){
				MapData[y][x] = 1;
			}else{
				MapData[y][x] = 0;
			}
		}
	}

	//���H�𐶐�
	for(int y = 2;y < MAP_HEIGHT - 2;y++){
		for(int x = 1;x < MAP_WIDTH - 2;x++){
			
			if(MapData[y][x] == 1){
				int dir = GetRand(3);
				int cnt = 0;
				bool flg = false;
				while(flg == false && cnt < 3){
					dir = GetRand(3);
					switch(dir){
						case eDirection_Up:
							if(MapData[y - 1][x] == 0){
								flg = true;
							}
							break;
						case eDirection_Left:
							if(MapData[y][x - 1] == 0){
								flg = true;
							}
							break;
						case eDirection_Right:
							if(MapData[y][x + 1] == 0){
								flg = true;
							}
							break;
						case eDirection_Down:
							if(MapData[y + 1][x] == 0){
								flg = true;
							}
							break;
					}
					cnt++;
				}
				
				if(flg == false){
					continue;
				}

				switch(dir){
				case eDirection_Up:
					MapData[y - 1][x] = 99;
					break;
				case eDirection_Left:
					MapData[y][x - 1] = 99;
					break;
				case eDirection_Right:
					MapData[y][x + 1] = 99;
					break;
				case eDirection_Down:
					MapData[y + 1][x] = 99;
				}
			}
		}
	}

	//�ʍs���肪����悤�ɒl���C��
	for(int y = 0;y < MAP_HEIGHT;y++){
		for(int x = 0;x < MAP_WIDTH;x++){
			if(MapData[y][x] == 99){
				MapData[y][x] = 1;
			}
		}
	}

	//�ʍs�\�}�X�̎l�����ʍs�s�\�Ȃ�A�ʍs�\�}�X�������_���ȕ����ɐ���
	for(int y = 2;y < MAP_HEIGHT - 2;y++){
		for(int x = 2;x < MAP_WIDTH - 2;x++){
			
			if(MapData[y - 1][x] == 1 &&MapData[y][x - 1] == 1 &&
			   MapData[y][x + 1] == 1 && MapData[y + 1][x] == 1){
				   int dir = GetRand(3);
					switch(dir){
				case eDirection_Up:
					MapData[y - 1][x] = 0;
					break;
				case eDirection_Left:
					MapData[y][x - 1] = 0;
					break;
				case eDirection_Right:
					MapData[y][x + 1] = 0;
					break;
				case eDirection_Down:
					MapData[y + 1][x] = 0;
				}
			}
		}
	}

	mGraphics = new Graphics();
	mGraphics->Load("Resources/Graphics/UI/start.png");

	mGraphicsMulti = new GraphicsMulti();
	mGraphicsMulti->Load("Resources/Graphics/UI/start.png", 0, 0);
	mGraphicsMulti->Load("Resources/Graphics/UI/start.png", 0, 100);
	mGraphicsMulti->Load("Resources/Graphics/UI/start.png", 0, 50);
	mGraphicsMulti->Load("Resources/Graphics/UI/start.png", -200, 0);
}

/*
	�}�b�v�`��
*/
static void Map_Draw(){

	//�}�b�v�̕`��
	for(int y = 0;y < MAP_HEIGHT;y++){
		for(int x = 0;x < MAP_WIDTH;x++){

			int X1 = x * MAP_CHIP_SIZE;
			int Y1 = y * MAP_CHIP_SIZE;
			int X2 = X1 + MAP_CHIP_SIZE;
			int Y2 = Y1 + MAP_CHIP_SIZE;

			if(MapData[y][x] == 1){
				DrawBox(X1,Y1,X2,Y2,GetColor(255,255,255),TRUE);
			}

		}
	}

	//mGraphics->Draw(20, 100, 255);

	mGraphicsMulti->Draw(posX, 200, 255);

}

/*
	�G������
*/
static void Enemy_Initialize(){

	for(int i = 0;i < ENEMY_KIND_NUM;i++){
		enemy[i].posX = GetRand(MAP_WIDTH);
		enemy[i].posY = GetRand(MAP_HEIGHT);

		//�ʍs�\�ȏꏊ�ɐݒ肳���܂Őݒ肵�Ȃ���
		while(MapData[enemy[i].posY][ enemy[i].posX] == 1){
			enemy[i].posX = GetRand(MAP_WIDTH);
			enemy[i].posY = GetRand(MAP_HEIGHT);
		}

		enemy[i].counter = 0;
		enemy[i].moveStartTime = GetRand(60);

		enemy[i].kind = i;
		enemy[i].direction = 0;
	}
}

/*
	�ړ��\���m�F����
	return	true	:�ړ��\
			false	:�ړ��s�\
*/
static bool isMoveCheck(Enemy_t enemy){

	int posX = enemy.posX;
	int posY = enemy.posY;
	int dir = enemy.direction;

	bool flg = false;


	switch(dir){
	case eDirection_Up:
		if(MapData[posY - 1][posX] == 0){
			flg = true;
		}
		break;
	case eDirection_Left:
		if(MapData[posY][posX - 1] == 0){
			flg = true;
		}
		break;
	case eDirection_Right:
		if(MapData[posY][posX + 1] == 0){
			flg = true;
		}
		break;
	case eDirection_Down:
		if(MapData[posY + 1][posX] == 0){
			flg = true;
		}
		break;

	}

	return flg;
}

/*
	�G�̈ړ�
*/
static void EnemyMove(Enemy_t* enemy){

	int dir = enemy->direction;

	switch(dir){
	case eDirection_Up:
		enemy->posY --;
		break;
	case eDirection_Left:
		enemy->posX --;
		break;
	case eDirection_Right:
		enemy->posX ++;
		break;
	case eDirection_Down:
		enemy->posY ++;
		break;

	}

}

/*
	�G�X�X�V����
*/
static void Enemy_Updata(){
	
	for(int i = 0;i < ENEMY_KIND_NUM;i++){
		
		enemy[i].counter++;

		//�s���J�n���ԂɂȂ������H
		if(enemy[i].counter >= enemy[i].moveStartTime){

			//�ړ������̌���
			enemy[i].direction = GetRand(3);	//0 ~ 3

			//�ړ������ֈړ��ł��邩�m�F
			if(isMoveCheck(enemy[i]) == true){
				//�ړ��J�n
				EnemyMove(&enemy[i]);
			}


			//���̈ړ��J�n���Ԃ�ݒ�
			enemy[i].moveStartTime = GetRand(60);
			//�J�E���^�[������
			enemy[i].counter = 0;
		}

	}

}

/*
	�G�̕`��
*/
static void Enemy_Draw(){
	
	for(int i = 0;i < ENEMY_KIND_NUM;i++){

		int X1 = enemy[i].posX * MAP_CHIP_SIZE;
		int Y1 = enemy[i].posY * MAP_CHIP_SIZE;
		int X2 = X1 + MAP_CHIP_SIZE;
		int Y2 = Y1 + MAP_CHIP_SIZE;

		int kind = enemy[i].kind;
		
		DrawBox(X1,Y1,X2,Y2,EnemyColor[kind],TRUE);
		DrawFormatString(X1,Y1-MAP_CHIP_SIZE,GetColor(0,255,255),"T:%d",enemy[i].counter);

	}
}


AITest::AITest(ISceneBase* changer) : SceneBase(changer){
	SRand(GetNowCount());
}

void AITest::Initialize(){
	
	Map_Initialize();
	Enemy_Initialize();
	

}

void AITest::Finalize(){

	mGraphics->Relese();
	mGraphicsMulti->Relese();

	Delete(mGraphics);
	Delete(mGraphicsMulti);

}

bool AITest::Updata(){

#ifdef __WINDOWS__
	//�e�X�g���j���[�֖߂�
	if(Keyboard_Press(KEY_INPUT_X)){
		mNextScene->SceneChange(ISceneBase::eScene_TestMenu);
		return true;
	}
#endif
	Enemy_Updata();

	if (posX < 0 || posX > 700) {
		vecX *= -1;
	}

	posX += vecX;

	return true;
}

void AITest::Draw(){

	
	Map_Draw();
	Enemy_Draw();

}

#endif