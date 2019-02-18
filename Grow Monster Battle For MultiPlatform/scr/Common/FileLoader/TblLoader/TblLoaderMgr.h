/*
				ファイル名		:TblLoaderMgr.h
				作成者			:
				作成日時		:2019/02/17
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __TBL_LOADER_MGR_H__
#define __TBL_LOADER_MGR_H__

#include "Common/Task/TaskBase.h"


#include <vector>

class TblLoader;

namespace loader {


	class TblLoaderMgr : public TaskBase {

	private:

		static TblLoaderMgr* mInstance;
		int mOrder;
		std::vector<TblLoader*> mLoadList;

		TblLoaderMgr();


	public:

		~TblLoaderMgr();

		static void Create();

		static TblLoaderMgr* GetInstance();

		TblLoader* LoadRequest(const char* fileName, bool isAsync = false);

		bool Initialize()override;
		void Finalize()override;

		void PreviousUpdate()override;
		void InputUpdate() override;
		bool Updata()override;
		void PostUpdate() override;
		void Draw()override;

	};

}

#endif // __TBL_LOADER_MGR_H__