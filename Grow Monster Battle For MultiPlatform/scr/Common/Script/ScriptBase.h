/*
				ファイル名		:ScriptBase.h
				作成者			:
				作成日時		:2018/04/03
				ソース説明		:
					
					スクリプト基底クラス
				
				備考
				
					基本的な動作を作成していく

					〇スクリプトの解読機能
					〇スクリプトファイル読み込み
				
!*/



#ifndef __SCRIPT_BASE_H__
#define __SCRIPT_BASE_H__

#include "Common/Task/TaskBase.h" 
#include "Common/String/StringBase.h"
#include "Common/Graphics/Graphics.h"
#include <vector>

class ScriptAnimation;
class BMFont;
class SaveData;

namespace AdvScript {

	class ScriptBase : public TaskBase {

	private:

		const static int MAX_INT_VALUE = 6;
		const static int MAX_FLOAT_VALUE = 6;
		const char* SCRIPT_DATA_PATH = "Resources/Data/AdvScripts/";
		const char* DELIM_STRINGS = " ";

		const int AUTO_FEED_INTERVAL_TIME = 60 * 6;		//自動会話送り待ち時間

	public:

		enum eAnalysis {
			eAnalysis_Error = -1,		//エラー							
			eAnalysis_Talk,				//会話									[話者名][文字列]
			eAnalysis_Mes,				//メッセージ							[文字列]
			eAnalysis_SetFlag,			//フラグを設定							[フラグ名][フラグ番号]
			eAnalysis_FlagOn,			//フラグをオンにする					[フラグ名]
			eAnalysis_FlagOff,			//フラグをオフにする					[フラグ名]
			eAnalysis_If,				//if文	:ONになっているか確認する		[フラグ名]
			eAnalysis_Ifn,				//ifn文	:OFFになっているか確認する		[フラグ名]
			eAnalysis_endif,			//if文終了								
			eAnalysis_Lable,			//ラベル								[ラベル名]
			eAnalysis_Goto,				//指定のラベル位置に移動する			[ラベル名]
			eAnalysis_LoadScript,		//スクリプトの読み込みを行う			[スクリプトファイルパス]
			eAnalysis_LoadGraph,		//画像読み込み							[管理番号][画像ファイルパス]
			eAnalysis_DrawGraph,		//画像表示								[管理番号][X座標][Y座標][フェードインを行うか(0 or 1)]
			eAnalysis_HideGraph,		//画像を非表示にする					[管理番号][非表示までにかかる時間(1以上)]
			eAnalysis_AnimGraph,		//画像をアニメーションさせる			[管理番号][アニメーション番号][ループ再生か(0 or 1)][今の座標を原点とするか(0 or 1)]
			eAnalysis_SetGraphAlpha,	//画像のアルファ値を設定する			[管理番号][アルファ値(0 ~ 255)]
			eAnalysis_LoadSound,		//サウンドの読み込み					[管理番号][ファイルパス]
			eAnalysis_PlaySound,		//サウンドの再生						[管理番号]
			eAnalysis_StopSound,		//サウンドの停止						[管理番号]
			eAnalysis_End,				//スクリプト終了

		};


		enum eActType {
			eActType_Error = -2,
			eActType_None = -1,
			eActType_Next,
			eActType_Wait,				// 遷移待ち
			eActType_InputWait,			// 入力待ち
			eActType_End,				// スクリプト終了
		};
	
		typedef struct {
			int mGraphId;
			Graphics* mGraph;
		}GRAPHICS_DATA_t;

		typedef struct {
			int mSoundId;
			std::string mSoundStrId;
		}SOUND_DATA_t;

		typedef struct {
			int mFlagID;
			char mFlagName[256];
		}FLAG_DATA_t;

	
		typedef struct {
			eAnalysis mMethodId;
			char mMethod[27];
			char mString[1024];
			char mString2[1024];
			int mInt[MAX_INT_VALUE];
			float mFloat[MAX_FLOAT_VALUE];
		}ADV_DATA_t;
	

		char mFileName[256];
		std::list<std::string> mStringDatas;
		int mNowLine;			//現在の行
		int mMaxLine;			//最大行
		bool mIsEnd;			//スクリプト終了判定
		bool mIsAutoFeed;		//自動送りが有効か
		int mAutoFeedCount;		//自動会話送りインターバル用カウンター


		Graphics mMsgGraphics;

		StringBase* mTalkName;	// 話している人の名前を設定
		StringBase* mString;

		BMFont* mBMFont;

		StringBase::eDrawState mOldStringDrawState;	//文字列描画状態
		StringBase::eDrawState mStringDrawState;	//文字列描画状態
		bool mIsAllDrawString;						//文字をすべて描画するか
		bool mIsDrawNextIcon;						//次へのアイコンを描画するか
		bool mIsWait;								//次の処理を行うのを待つか
		SaveData* mSaveData;

		ADV_DATA_t* mAdvData;

		ScriptAnimation* mAnimation;

		std::vector<FLAG_DATA_t> mFlagDatas;
		std::vector<GRAPHICS_DATA_t> mGraphicsDatas;
		std::vector<SOUND_DATA_t> mSoundDatas;

		std::vector<unsigned int> mAnimOrderIdList;


	private:



		void SplitString(char* str, const char* delim, std::list<std::string>* list, char* context = NULL);
		
		/*
			スクリプト解析
		*/
		void Analysis();

		eAnalysis MethodAnalysis(const char* str);

		// スクリプト実行関数軍
		eActType MessageFunc(ADV_DATA_t& data);
		eActType TalkFunc(ADV_DATA_t& data);



	public:

		ScriptBase();
		ScriptBase(const char* scriptName);

		bool Initialize()override;
		void Finalize()override;

		void PreviousUpdate()override;
		void InputUpdate() override;
		bool Updata()override;
		void PostUpdate() override;
		void Draw()override;

		bool IsEnd();

		bool Load(const char* fileName);
		void CreateFilePath(const char* fileName);
		bool SetFlag(const char* flagName, unsigned int flag);

		/*
			現在実行するスクリプト関数
			return	実行する関数ID
		*/
		eAnalysis GetNowActFunction();

		/*
			現在実行実行するスクリプトデータ
			return 実行するデータ
		*/
		ADV_DATA_t& GetNowActAdvData();



	};

}

#endif // __TEMPLETE_H__