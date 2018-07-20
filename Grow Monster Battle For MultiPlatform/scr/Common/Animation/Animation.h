/*
				ファイル名		:Animation.h
				作成者			:
				作成日時		:2018/03/22
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

//アニメーション作成用構造体
typedef struct {
	int keyframe;
	float positionX;
	float positionY;
	float angle;
	float scale;
	float alpha;
}ANIMATION_DATA_t;

class Animation {

private:

	bool mIsPlay;	//再生中か
	bool mIsStop;	//停止中か
	bool mIsLoop;	//ループするか
	bool mIsPause;	//一時停止中か

	int mCounter;		//カウンター
	int mTimeLength;	//アニメーションの長さ

	int mNowFrame;

	ANIMATION_DATA_t mAnimationValue;	//アニメーションデータ値

	ANIMATION_DATA_t mValue;

	std::list<ANIMATION_DATA_t> mAnimationDataList;
	
private:

	/*
		値が0になっているか判断する
		return	true	:0になっている
				false	:なっていない
	*/
	bool CheckVeluesZero();

public:

	Animation();
	~Animation();

	/*
		アニメーションデータを追加する
	*/
	void AddAnimationData(ANIMATION_DATA_t animationData);
	
	/*
		アニメーションの再生時間を設定する
	*/
	void SetAnimationTime(int timeLength);

	/*
		アニメーションデータを削除する
	*/
	void DeleteAnimationData();

	/*
		再生
	*/
	void Play();

	/*
		停止
	*/
	void Stop();

	/*
		一時停止
	*/
	void Pause();

	/*
		ループ再生
	*/
	void Loop();

	/*
		更新
	*/
	bool Update();

	void AnimationAttach(GraphicsDraw* graph, bool isNowBasePos = false);
	void AnimationAttach(float* posX, float* posY, float*alpha,float*angle = NULL,float*scale = NULL);

	/*
		再生中か?
	*/
	bool IsPlay();
	
	/*
		停止中か
	*/
	bool IsStop();

	/*
		一時中か
	*/
	bool IsPause();
};

#endif // __ANIMATION_H__