/*
				ファイル名		:ScriptBase.cpp
				作成者			:
				作成日時		:2018/04/03
				ソース説明		:
				
					スクリプト基底クラス
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "ScriptAnimation.h"
#include "ScriptBase.h"

#ifdef __ANDROID__
#include <string.h>
#endif


static char testScript[] = {
	"$mes 目が覚めると、木々の隙間から木漏れ日がゆらゆらとあゆみの頬を照らす。\n"
	"$label Label1\n"
	"$mes 今日はいいことがあるかもしれない\n"
	"$goto Label1\n"
	"$// これはコメントアウト\n"
	"$if フラグ確認\n"
	"$endif フラグ確認終了\n"
	"$yesno 確認ウィンドウ立ち上げ\n"
	"$flag フラグを設定(on/offを切り替える)\n"
	"$giveitem 指定アイテムを与える\n"
	"$haveitem 指定のアイテムをもらう\n"
	"$wait 入力待ち\n"
	"$setFlag name FlagID\n"
	"$end\n"

};

ScriptBase::ScriptBase() : TaskBase() {

	mString = new StringBase();
	mAdvData = NULL;
	mSaveData = AppData::GetInstance().GetSaveData();


}

ScriptBase::ScriptBase(const char* scriptName) : TaskBase() {
	mString = new StringBase();

	mAdvData = NULL;
	mSaveData = AppData::GetInstance().GetSaveData();

	CreateFilePath(scriptName);
	
}

bool ScriptBase::Initialize() {

	mIsAllDrawString = false;
	mIsEnd = false;
	mIsWait = false;
	mIsAutoFeed = false;
	mAutoFeedCount = 0;

	mNowLine = 0;
	mMaxLine = 0;

	mMsgGraphics = *ComRes::Instance()->GetGraphicHandle(ComRes::eComResName_MsgBox);

	mStringDrawState = StringBase::eDrawState_None;
	mOldStringDrawState = StringBase::eDrawState_None;
	mIsDrawNextIcon = false;

	mAnimation = new ScriptAnimation();
	TaskMgr::getInstance().Add(mAnimation);
	
	mAnimOrderIdList.clear();

	return Load(mFileName);

}

void ScriptBase::Finalize() {

	Delete(mString);
	DeleteArry(mAdvData);

	this->mStringDatas.clear();
	this->mFlagDatas.clear();

	int id = mAnimation->GetTaskId();
	TaskMgr::getInstance().RequestKill(id);

	
	//画像データ削除
	for (int i = 0; i < mGraphicsDatas.size(); i++) {
		mGraphicsDatas[i].mGraph->Relese();
		Delete(mGraphicsDatas[i].mGraph);
	}
	mGraphicsDatas.clear();

}

void ScriptBase::PreviousUpdate() {

	bool isWait = false;

	for (int i = 0; i < mAnimOrderIdList.size(); i++) {
		unsigned int id = mAnimOrderIdList[i];
		if (!mAnimation->IsPlay(id)) {
			auto itr = mAnimOrderIdList.begin() + i;
			mAnimOrderIdList.erase(itr);
			mAnimation->DetachGraphics(id);
			i--;
		}
		else {
			isWait = true;
		}
	}

	if (isWait == false) {
		Analysis();
	}

	mOldStringDrawState = mStringDrawState;
	int drawInterval = mIsAllDrawString ? 1 : 10;
	mStringDrawState = (StringBase::eDrawState)mString->Update(true, 60, drawInterval);
}

void ScriptBase::InputUpdate() {

	mIsAllDrawString = false;

	//処理待ちなら入力を行わない
	if (mIsWait) return;

	if (mIsAutoFeed == true) {

		if (mStringDrawState == StringBase::eDrawState_Drawing ||
			mStringDrawState == StringBase::eDrawState_DrawInterval) {

			mIsAllDrawString = true;

		}
		else if (mStringDrawState == StringBase::eDrawState_DrawEnd) {

			mAutoFeedCount++;
			if (mAutoFeedCount > AUTO_FEED_INTERVAL_TIME) {
				mNowLine++;
				mIsAllDrawString = false;
				mIsDrawNextIcon = true;
				mAutoFeedCount = 0;
			}
		}
	}

#ifdef __WINDOWS__

	if (mIsAutoFeed == false) {

		if (Keyboard_Press(KEY_INPUT_Z)) {

			if (mStringDrawState == StringBase::eDrawState_DrawEnd) {
				mNowLine++;
				mIsAllDrawString = false;
				mIsDrawNextIcon = true;
			}
		}
		else if (Keyboard_On(KEY_INPUT_Z)) {
			if (mStringDrawState == StringBase::eDrawState_Drawing ||
				mStringDrawState == StringBase::eDrawState_DrawInterval) {

				mIsAllDrawString = true;

			}
		}
	}

	//自動会話送りをON/OFF
	if (Keyboard_Press(KEY_INPUT_A)) {
		mIsAutoFeed = !mIsAutoFeed;
	}

#else 

	if (mIsAutoFeed == false) {
		if (Touch_Press(1)) {
			if (mStringDrawState == StringBase::eDrawState_DrawEnd) {
				//mString->SetString("目が覚めると、木々の隙間から木漏れ日がゆらゆらとあゆみの頬を照らす。");
				mNowLine++;
				mIsAllDrawString = false;
				mIsDrawNextIcon = true;
			}
		}
		else if (Touch_On(1)) {
			if (mStringDrawState == StringBase::eDrawState_Drawing ||
				mStringDrawState == StringBase::eDrawState_DrawInterval) {

				mIsAllDrawString = true;

			}
		}
	}

#endif

}

bool ScriptBase::Updata() {


	return true;
}

void ScriptBase::PostUpdate() {

}

void ScriptBase::Draw() {

	for (int i = 0; i < mGraphicsDatas.size(); i++) {
		if (mGraphicsDatas[i].mGraph->IsVisible()) {
			int posX = mGraphicsDatas[i].mGraph->GetPositionX();
			int posY = mGraphicsDatas[i].mGraph->GetPositionY();
			int alpha = mGraphicsDatas[i].mGraph->GetAlpah();
			mGraphicsDatas[i].mGraph->Draw(posX, posY, alpha, 0.0, 1.0);
		}
	}

	mMsgGraphics.Draw(180, 450, 255, 0.0, 1.0);
	mString->DrawString(200, 500);

	bool ret = false;

	
	if (mOldStringDrawState == StringBase::eDrawState_Drawing ||
		mOldStringDrawState == StringBase::eDrawState_DrawInterval || 
		mIsDrawNextIcon) {
		ret = true;
	}

	//次のメッセージの表示が可能
	if (ret && mStringDrawState == StringBase::eDrawState_DrawEnd) {
		DrawBox(820, 550, 840, 570, GetColor(255, 255, 255), TRUE);
		mIsDrawNextIcon = true;
	}

	char msg[126];
#ifdef __WINDOWS__
	strcpyDx(msg, "Aボタンでオート");
#else
	strcpyDx(msg, "2タップでオート");
#endif

	DrawString(780, 650, msg, GetColor(255, 255, 255));

}

void ScriptBase::SplitString(char* str,const char* delim,std::list<std::string>* list,char* context/* = NULL*/) {

	char* contex = context;
	
#ifdef __WINDOWS__
	char* ret = strtok_s(str,delim, &contex);
#else
	char* ret = strtok_r(str, delim, &contex);
#endif

	if (ret == NULL) return;

	list->push_back(std::string(ret));

	SplitString(NULL, delim, list, contex);

}

void ScriptBase::Analysis() {
	

	if (mNowLine >= mMaxLine) {
		mIsEnd = true;
		return;
	}

	/*
		1.文字列リストからスクリプトで行う処理を取得する
		2.データを作成
		3.データをもとにスクリプトの再生を行う
		

		※必要なデータ
		処理の種類
		int型データ
		フラグデータ(フラグの名前など)
		文字列データ
	

	*/

	
	ADV_DATA_t data = mAdvData[mNowLine];

	ScriptBase::eAnalysis ret =  MethodAnalysis(data.mMethod);

	if (ret == ScriptBase::eAnalysis_Error) {
		Debug::ErorrMessage("スクリプトに無効な処理が含まれています");
		mIsEnd = true;
		return;
	}

	bool isNext = true;

	switch (ret) {
	case ScriptBase::eAnalysis_Mes:
		
		mString->SetString(data.mString);
		isNext = false;
		break;
	case ScriptBase::eAnalysis_Lable:
		//mNowLine++;
		break;
	case ScriptBase::eAnalysis_Goto:
	{
		char labelName[256];
		strcpyDx(labelName, data.mString);

#ifdef __MY_DEBUG__
		bool find = false;
#endif	//__MY_DEBUG__
		for (int i = 0; i < mMaxLine; i++) {
			data = mAdvData[i];
			ret = MethodAnalysis(data.mMethod);
			if (ret == ScriptBase::eAnalysis_Lable) {
				if (strcmpDx(labelName, data.mString) == 0) {
					mNowLine = i;
#ifdef __MY_DEBUG__
					find = true;
#endif	//__MY_DEBUG__
					break;
				}
			}
		}
#ifdef __MY_DEBUG__
		if (find == false) {
			Debug::ErorrMessage("ラベル%sを見つけることができませんでした.", labelName);
		}
#endif	//__MY_DEBUG__
	}
		break;
	case ScriptBase::eAnalyis_If:
	{
		SaveData::FLAG_DATA_t* mflagData = mSaveData->GetFlagData();
		char* name = data.mString;
		int id = -1;

		for (int i = 0; i < mFlagDatas.size(); i++) {
			char* flagName = mFlagDatas[i].mFlagName;
			if (strcmpDx(flagName, name) == 0) {
				id = mFlagDatas[i].mFlagID;
				break;
			}
		}

		if (id >= 0 && mflagData->mFlags[id]) {
			//mNowLine++;
		}
		else {

			isNext = false;

#ifdef __MY_DEBUG__
			bool find = false;
#endif	//__MY_DEBUG__
			int ifId = data.mInt[0];
			for (int i = mNowLine; i < mMaxLine; i++) {
				data = mAdvData[i];
				ret = MethodAnalysis(data.mMethod);
				if (ret == ScriptBase::eAnalysis_endif) {
					if (data.mInt[0] != ifId) continue;
					mNowLine = i;
#ifdef __MY_DEBUG__
					find = true;
#endif	//__MY_DEBUG__
					break;
				}
			}
#ifdef __MY_DEBUG__
			if (find == false) {
				Debug::ErorrMessage("$endifを見つけることができませんでした.");
			}
#endif	//__MY_DEBUG__
		}
	}
		break;
	case ScriptBase::eAnalyis_Ifn:
	{
		SaveData::FLAG_DATA_t* mflagData = mSaveData->GetFlagData();
		char* name = data.mString;
		int id = -1;

		for (int i = 0; i < mFlagDatas.size(); i++) {
			char* flagName = mFlagDatas[i].mFlagName;
			if (strcmpDx(flagName, name) == 0) {
				id = mFlagDatas[i].mFlagID;
				break;
			}
		}

		if (id >= 0 && !mflagData->mFlags[id]) {
			//mNowLine++;
		}
		else {

			isNext = false;

#ifdef __MY_DEBUG__
			bool find = false;
#endif	//__MY_DEBUG__
			int ifId = data.mInt[0];
			for (int i = mNowLine; i < mMaxLine; i++) {
				data = mAdvData[i];
				ret = MethodAnalysis(data.mMethod);
				if (ret == ScriptBase::eAnalysis_endif) {
					if (data.mInt[0] != ifId) continue;
					mNowLine = i;
#ifdef __MY_DEBUG__
					find = true;
#endif	//__MY_DEBUG__
					break;
				}
			}
#ifdef __MY_DEBUG__
			if (find == false) {
				Debug::ErorrMessage("$endifを見つけることができませんでした.");
			}
#endif	//__MY_DEBUG__
		}
	}
		break;
	case ScriptBase::eAnalysis_endif:
		//mNowLine++;
		break;
	case ScriptBase::eAnalyis_FlagOn:
		SetFlag(data.mString, TRUE);
		//mNowLine++;
		break;
	case ScriptBase::eAnalyis_FlagOff:
		SetFlag(data.mString, FALSE);
		//mNowLine++;
		break;
	case ScriptBase::eAnalysis_LoadScript:
		CreateFilePath(data.mString);
		if (ScriptBase::Load(mFileName) == false) {
			Debug::ErorrMessage("%sの読み込みに失敗しました.",data.mString);
		}
		//mNowLine++;
		break;
	case ScriptBase::eAnalysis_LoadGraph:
		//mNowLine++;
		break;
	case ScriptBase::eAnalysis_DrawGraph:
	{
		Graphics* graph = NULL;
		for (int i = 0; i < mGraphicsDatas.size(); i++) {
			if (mGraphicsDatas[i].mGraphId == data.mInt[0]) {
				graph = mGraphicsDatas[i].mGraph;
				break;
			}
		}

		if (graph != NULL) {
			int posX = graph->GetPositionX();
			int posY = graph->GetPositionY();
			
			if (data.mInt[1] > -1) {
				posX = data.mInt[1];
			}
			if (data.mInt[2] > -1) {
				posY = data.mInt[2];
			}
			graph->SetPosition(posX, posY);
			graph->SetVisible(true);

			if (data.mInt[3] > -1) {

				int fade = (data.mInt[3] == 1) ? ScriptAnimation::eAnimationNo_FadeIn : ScriptAnimation::eAnimationNo_None;

				if (fade != ScriptAnimation::eAnimationNo_None) {
					bool isLoop = false;
					bool isNowBasePos = true;
					unsigned int id = mAnimation->AttachGraphics(graph, fade, isLoop, isNowBasePos);
					mAnimOrderIdList.push_back(id);
				}
			}

		}
		//mNowLine++;
	}
		break;
	case ScriptBase::eAnalysis_HideGraph:
	{
		Graphics* graph = NULL;
		for (int i = 0; i < mGraphicsDatas.size(); i++) {
			if (mGraphicsDatas[i].mGraphId == data.mInt[0]) {
				graph = mGraphicsDatas[i].mGraph;
				break;
			}
		}

		if (graph != NULL) {

			float tmp = (float)graph->GetAlpah();
			if (tmp > 0.0f) {
				tmp -= 255.0f / (float)data.mInt[1];
				graph->SetAlpha(tmp);
				isNext = false;
				mIsWait = true;
			}
			else {
				graph->SetVisible(false);
			}

		}

	}
		break;
	case ScriptBase::eAnalysis_AnimGraph:
	{
		Graphics * graph = NULL;
		for (int i = 0; i < mGraphicsDatas.size(); i++) {
			if (mGraphicsDatas[i].mGraphId == data.mInt[0]) {
				graph = mGraphicsDatas[i].mGraph;
				break;
			}
		}

		if (graph != NULL) {
			bool isLoop = (data.mInt[2] == 1) ? true : false;
			bool isNowBasePos = (data.mInt[3] == 1) ? true : false;
			unsigned int id = mAnimation->AttachGraphics(graph, data.mInt[1], isLoop,isNowBasePos);
			mAnimOrderIdList.push_back(id);
		}
	}
		break;
	case ScriptBase::eAnalysis_End:
		mIsEnd = true;
		isNext = false;
		break;
	default:
		//mNowLine++;
		break;
	}

	if (isNext) {
		mIsWait = false;	//処理待ち解除
		mNowLine++;
	}



}

/*
	関数分析
	char*	str		:文字列
	return	-1		:エラー
			0以上	:解析結果	
*/
ScriptBase::eAnalysis ScriptBase::MethodAnalysis(const char* str) {

	if (strcmpDx(str, "$mes") == 0) return ScriptBase::eAnalysis_Mes;
	else if (strcmpDx(str, "$label") == 0) return ScriptBase::eAnalysis_Lable;
	else if (strcmpDx(str, "$goto") == 0) return ScriptBase::eAnalysis_Goto;
	else if (strcmpDx(str, "$setFlag") == 0) return ScriptBase::eAnalyis_SetFlag;
	else if (strcmpDx(str, "$flagOn") == 0) return ScriptBase::eAnalyis_FlagOn;
	else if (strcmpDx(str, "$flagOff") == 0) return ScriptBase::eAnalyis_FlagOff;
	else if (strcmpDx(str, "$if") == 0) return ScriptBase::eAnalyis_If;
	else if (strcmpDx(str, "$ifn") == 0) return ScriptBase::eAnalyis_Ifn;
	else if (strcmpDx(str, "$endif") == 0) return ScriptBase::eAnalysis_endif;
	else if (strcmpDx(str, "$loadScript") == 0) return ScriptBase::eAnalysis_LoadScript;
	else if (strcmpDx(str, "$loadGraph") == 0) return ScriptBase::eAnalysis_LoadGraph;
	else if (strcmpDx(str, "$drawGraph") == 0) return ScriptBase::eAnalysis_DrawGraph;
	else if (strcmpDx(str, "$hideGraph") == 0) return ScriptBase::eAnalysis_HideGraph;
	else if (strcmpDx(str, "$animGraph") == 0) return ScriptBase::eAnalysis_AnimGraph;
	else if (strcmpDx(str, "$end") == 0) return ScriptBase::eAnalysis_End;
	
	return ScriptBase::eAnalysis_Error;
}

bool ScriptBase::IsEnd() {
	return mIsEnd;
}

/*
	フラグの設定を行う
	const char*		flagName	:フラグ名
	unsigned int	flag		:フラグの状態を設定
	return			true		:成功
					false		:失敗
*/
bool ScriptBase::SetFlag(const char* flagName, unsigned int flag) {

	SaveData::FLAG_DATA_t* mflagData = mSaveData->GetFlagData();
	
	int id = -1;

	for (int i = 0; i < mFlagDatas.size(); i++) {
		char* name = mFlagDatas[i].mFlagName;
		if (strcmpDx(flagName, name) == 0) {
			id = mFlagDatas[i].mFlagID;
			break;
		}
	}

	if (id >= 0) {
		mflagData->mFlags[id] = flag;
		return true;
	}

	return false;
}

/*
	ファイル読み込み
*/
bool ScriptBase::Load(const char* filename) {

	std::ifstream file(filename);

	if (file.is_open() == false) {
		TaskMgr::getInstance().RequestKill(this->mTaskId);
		return false;
	}

	char data[1024] = "";
	int pos = 0;
	int readCnt = 0;

	while (1) {

		//char ch = testScript[pos];

		if (file.eof()) break;

		char ch = file.get();

		//if (ch == '\0') break;
		if (readCnt == 0 && ch == '\t') continue;
		else if (ch == '\n' || ch == '\0') {
			if (strcmpDx(data, "") != 0) {
				mStringDatas.push_back(std::string(data));
			}
			memset(data, 0, sizeof(char) * 1024);
			readCnt = 0;
			pos++;
			continue;
		}

		data[readCnt] = ch;

		readCnt++;
		pos++;

	}

	file.close();
	
	std::vector<ADV_DATA_t> advDataList;

	char* str = NULL;
	int inputLine = 0;

	int ifcnt = 0;
	int maxIfcnt = 0;
	int endifcnt = 0;

	for (auto itr = mStringDatas.begin(); itr != mStringDatas.end(); itr++) {

		str = (char*)itr->data();
		if (str == NULL) break;

		std::list<std::string> list;
		SplitString(str, DELIM_STRINGS, &list);

		int cnt = 0;
		//ADV_DATA_t* advData = (mAdvData + inputLine);
		ADV_DATA_t advData = {};

		FLAG_DATA_t flagData = { -1,"" };
		GRAPHICS_DATA_t graphicsData = { -1,NULL };

		for (auto data = list.begin(); data != list.end(); data++) {

			if (cnt == 0) {

				//コメントならデータに含まない
				if (strcmpDx(data->data(), "$//") == 0) break;

				strcpyDx(advData.mMethod, data->data());

				ScriptBase::eAnalysis ret = MethodAnalysis(advData.mMethod);

				switch (ret) {
				case ScriptBase::eAnalysis_endif:
					advData.mInt[0] = maxIfcnt - endifcnt;
					endifcnt++;
					break;
				}

			}
			else {

				ScriptBase::eAnalysis ret = MethodAnalysis(advData.mMethod);

				switch (ret) {
				case ScriptBase::eAnalysis_Mes:
					strcpyDx(advData.mString, data->data());
					break;
				case ScriptBase::eAnalysis_Lable:
					strcpyDx(advData.mString, data->data());
					break;
				case ScriptBase::eAnalysis_Goto:
					strcpyDx(advData.mString, data->data());
					break;
				case ScriptBase::eAnalyis_Ifn:
				case ScriptBase::eAnalyis_If:
					if (cnt == 1) {
						strcpyDx(advData.mString, data->data());
						advData.mInt[0] = ifcnt;
						if (maxIfcnt < ifcnt) {
							maxIfcnt = ifcnt;
							endifcnt = 0;
						}
						ifcnt++;
					}
					break;
				case ScriptBase::eAnalyis_SetFlag:
					if (cnt == 1) {
						strcpyDx(flagData.mFlagName, data->data());
						data++;
						flagData.mFlagID = atoiDx(data->data());
						//フラグデータが正常の場合追加する
						if (flagData.mFlagID >= 0) {
							mFlagDatas.push_back(flagData);
						}
					}
					break;
				case ScriptBase::eAnalyis_FlagOn:
					strcpyDx(advData.mString, data->data());
					break;
				case ScriptBase::eAnalyis_FlagOff:
					strcpyDx(advData.mString, data->data());
					break;
				case ScriptBase::eAnalysis_LoadScript:
					strcpyDx(advData.mString, data->data());
					break;
				case ScriptBase::eAnalysis_LoadGraph:

					if (cnt == 1){
						int posX = 0;
						int posY = 0;
						//画像ID
						graphicsData.mGraphId = atoiDx(data->data());
						
						//画像読み込み
						data++;
						graphicsData.mGraph = new Graphics();
						graphicsData.mGraph->Load(data->data());

						//座標取得
						data++;
						if (data != list.end()) {
							posX = atoiDx(data->data());
						}
						else {
							data--;

							//座標設定
							graphicsData.mGraph->SetPosition(posX, posY);

							//非表示状態に設定
							graphicsData.mGraph->SetVisible(false);

							//グラフィックデータ追加
							mGraphicsDatas.push_back(graphicsData);
							continue;
						}
						
						data++;
						if (data != list.end()) {
							posY = atoiDx(data->data());
						}

						//座標設定
						graphicsData.mGraph->SetPosition(posX, posY);

						//非表示状態に設定
						graphicsData.mGraph->SetVisible(false);
						
						//グラフィックデータ追加
						mGraphicsDatas.push_back(graphicsData);

					}

					break;
				case ScriptBase::eAnalysis_DrawGraph:

					if (cnt == 1) {
						//表示する画像ID
						advData.mInt[0] = atoiDx(data->data());
						data++;
						if (data == list.end()) {
							data--;
							advData.mInt[1] = -1;
							advData.mInt[2] = -1;
						}
						else {
							//描画座標X
							advData.mInt[1] = atoiDx(data->data());
							data++;
							//描画座標Y
							advData.mInt[2] = atoiDx(data->data());

							data++;
							if (data == list.end()) {
								data--;
								advData.mInt[3] = -1;
							}
							else {
								advData.mInt[3] = atoiDx(data->data());
							}

						}
					}

					break;
				case ScriptBase::eAnalysis_HideGraph:

					if (cnt == 1) {
						//非表示にする画像ID
						advData.mInt[0] = atoiDx(data->data());
						advData.mInt[1] = 0;
					}
					else if (cnt == 2) {
						//日表示するまでの時間
						advData.mInt[1] = atoiDx(data->data());
					}

					break;
				case ScriptBase::eAnalysis_AnimGraph:

					if (cnt == 1) {
						advData.mInt[0] = atoiDx(data->data());
					}
					else if(cnt == 2) {
						advData.mInt[1] = atoiDx(data->data());
					}
					else if (cnt == 3) {
						advData.mInt[2] = atoiDx(data->data());
					}
					else if (cnt == 4) {
						advData.mInt[3] = atoiDx(data->data());
					}

					break;
				}

			}
			cnt++;
		}

		if (cnt > 0) {
			advDataList.push_back(advData);
		}

#ifdef __MY_DEBUG__
		if (cnt > 0) {
			Debug::LogPrintf("%s %s %d %d %d %d %d %d %f %f %f %f %f %f\n", advData.mMethod, advData.mString,
				advData.mInt[0], advData.mInt[1], advData.mInt[2], advData.mInt[3], advData.mInt[4], advData.mInt[5],
				advData.mFloat[0], advData.mFloat[1], advData.mFloat[2], advData.mFloat[3], advData.mFloat[4], advData.mFloat[5] );
		}
#endif	//__MY_DEBUG__

		inputLine++;
	}

	mStringDatas.clear();

	int nowMaxLine = mMaxLine;
	const ADV_DATA_t* tempData = mAdvData;
	mMaxLine += advDataList.size();
	
	mAdvData = new ADV_DATA_t[mMaxLine];

	for (int i = 0; i < nowMaxLine; i++) {
		mAdvData[i] = tempData[i];
	}

	for (int i = nowMaxLine; i < mMaxLine; i++) {
		int cnt = i - nowMaxLine;
		mAdvData[i] = advDataList[cnt];
	}

	return true;
}

/*
	ファイルパスの作成を行う
*/
void ScriptBase::CreateFilePath(const char* fileName) {
	
	memset(mFileName, 0, sizeof(mFileName));

	strcatDx(mFileName, SCRIPT_DATA_PATH);
	strcatDx(mFileName, fileName);

#ifdef __WINDOWS__ 
#ifdef  __MY_DEBUG__

	RESORCES_PATH(mFileName);

#endif	
#endif

}