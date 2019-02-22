/*
				ファイル名		:TblLoader.h
				作成者			:
				作成日時		:2019/02/17
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __TBL_LOADER_H__
#define __TBL_LOADER_H__

namespace loader {

	class TblLoader {

	public:

		enum eState {
			eState_Load,
			eState_Wait,
			eState_Read,
			eState_End,
			eState_Error,
			eState_Exit,
		};

		struct FileData {
			char fileName[32];
			int startOffset;
			int endOffset;
		};

		struct Header {
			char tag[4];
			int dataNum;
		};

		struct Data {
			char* buffer;
			unsigned int dataSize;
		};

		struct TblData {
			int id;
			Header header;
			FileData* fileData;
			Data* data;

			void GetData(int idx,void* buffer) {
				int dataSize = data[idx].dataSize;
				memcpy(buffer, data[idx].buffer, dataSize);
			}

			int GetDataSize(int idx) {
				return data[idx].dataSize;
			}

			/*
				int idx		: データナンバー
				int size	: 型のサイズ(sizeof(型名))
				return		: 型のサイズで割った数
			*/
			int GetDataNum(int idx, int size) {
				int dataSize = data[idx].dataSize;
				return dataSize / size;
			}

			int GetDataNum() {
				return header.dataNum;
			}

		};


	private:

		char mFilePath[1024];
		int mHandle;
		int mStateCnt;		// ステート
		bool mIsAsync;		// 非同期読み込みが有効か
		bool mIsLoadEnd;	// ロードが終了したか
		bool mIsExist;		// ファイルが存在しているか

		TblData* mTableData;	// 読み込んだ―データ

	public:

		TblLoader();
		~TblLoader();

		bool LoadRequest(const char* filePath, bool isAsync = false);
		void Update();
		TblData& GetTableData() const;
		bool IsLoadEnd();
		bool IsExist();
	};

}


#endif // __TBL_LOADER_H__