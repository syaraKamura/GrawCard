/*
				ファイル名		:TestEffectPlayer.cpp
				作成者			:
				作成日時		:2019/05/08
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"

#ifdef __MY_DEBUG__

#include "Scene/ISceneBase.h"

#include "Common/Effect/Effect.h"
#include "Common/Effect/Particle/Particle.h"

#include "TestEffectPlayer.h"

static Graphics mGraph;
static Graphics mGraph2;

TestEffectPlayer::TestEffectPlayer(ISceneBase* changer) : SceneBase(changer) {

	mHandle.push_back(Effect::EffectMgr::GetInstance()->Load("Resources/Effect/Test/Test00.png", 320, 120));
	mHandle.push_back(Effect::EffectMgr::GetInstance()->Load("Resources/Effect/Test/Test01.png", 120, 120));
	mHandle.push_back(Effect::EffectMgr::GetInstance()->Load("Resources/Effect/Test/Test02.png", 120, 120));
	mHandle.push_back(Effect::EffectMgr::GetInstance()->Load("Resources/Effect/Test/Test03.png", 240, 240));
	Effect::EffectMgr::GetInstance()->LoadSE("Resources/Sound/SE/Test00.mp3", mHandle[3]);

	mSelectY = 0;

	mGraph.Load("Resources/Effect/Test/Test04.png");
	mGraph.SetBright(255, 255, 0);
	mGraph.SetPosition(255, 255);
	mGraph.SetAlpha(0);
	mGraph.SetScale(0.0);

	mGraph2 = mGraph;
	mGraph2.SetAlpha(255);
	mGraph2.SetScale(1.0);
	mGraph2.SetBright(0, 0, 255);

	mEmitter = new Effect::Particle::ParticleEmmiter();
	Effect::Particle::ParticleGenerateData data = {
		10,0,2,Effect::Particle::eFigureType_Circle,
		{0,0,{255,255,0,255},{},20},
		{0,120,{255,123,0,0},{},20},
		Easing::eEasingType_InCubic,
		75.0f,105.0f,
		5.0f,
		60,
		3.0f,
	};
	mEmitter->Init(600, 600, data);

	mPosX = 600;
	mMoveX = 10;

}

TestEffectPlayer::~TestEffectPlayer() {
	
	for (int i = 0; i < mHandle.size(); i++) {
		Effect::EffectMgr::GetInstance()->Release(mHandle[i]);
	}

	mHandle.clear();
	mGraph.Relese();
}

bool TestEffectPlayer::Initialize() {

	Effect::EffectMgr::GetInstance()->Play(mHandle[0]);

	return true;
}

void TestEffectPlayer::Finalize() {

}

void TestEffectPlayer::PreviousUpdate() {

}

bool TestEffectPlayer::Updata() {
	
#ifdef __WINDOWS__
	if (Keyboard_Press(KEY_INPUT_Z)) {
		Effect::EffectMgr::GetInstance()->Play(mHandle[mSelectY], WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
	if (Keyboard_Press(KEY_INPUT_X)) {
		dbg_ChangeScene_TestMenu();
	}
	
	if (Keyboard_Press(KEY_INPUT_UP)) {
		mSelectY = (mSelectY + (mHandle.size() - 1)) % mHandle.size();
	}
	else if (Keyboard_Press(KEY_INPUT_DOWN)) {
		mSelectY = (mSelectY + 1) % mHandle.size();
	}

#endif //__WINDOWS__

	mEmitter->SetPosition(mPosX, 600);

	mEmitter->Updata();

	//mPosX += mMoveX;
	//if (mPosX < 0 || mPosX >= WINDOW_WIDTH) {
	//	mMoveX *= -1;
	//}

	return true;
}

void TestEffectPlayer::Draw() {

	//Effect::EffectMgr::GetInstance()->Draw();

	const char* textList[] = {
		"テスト1",
		"テスト2",
		"テスト3",
		"テスト4",
	};

	DrawString(20, 20 * mSelectY + 20, "■", GetColor(255, 255, 255));
	for (int i = 0; i < ArrySize(textList); i++) {
		DrawString(40, 20 * i + 20, textList[i], GetColor(255, 255, 255));
	}
	if (mGraph.GetScale() < 1.0) {
		mGraph.SetScale(mGraph.GetScale() + 0.05);
		mGraph.SetAngleDegree(mGraph.GetAngleDegree() + 1);
		if (mGraph.GetAlpah() < 255) {
			mGraph.SetAlpha(mGraph.GetAlpah() + 25);
		}
	}
	else {
		if (mGraph.GetAlpah() > 0) {
			mGraph.SetAlpha(mGraph.GetAlpah() - 10);
			mGraph.SetScale(mGraph.GetScale() + 0.01);
		}
	}

	mGraph2.SetScale(mGraph.GetScale() / 2.0);
	mGraph2.SetAngleDegree(mGraph.GetAngleDegree());
	mGraph2.SetAlpha(mGraph.GetAlpah());
	
	
	
	SetDrawBlendMode(DX_BLENDMODE_ADD, 123);
	mGraph2.Draw();
	mGraph.Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TestEffectPlayer::PostUpdate(){

}


#endif //__MY_DEBUG__




