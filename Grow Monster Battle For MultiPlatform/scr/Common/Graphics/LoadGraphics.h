/*
				ファイル名		:LoadGraphcis.h
				作成者			:
				作成日時		:22019/03/20
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __LOAD_GRAPHICS_H__
#define __LOAD_GRAPHICS_H__

#include "Common/ResourceLoader/ResourceLoader.h"

namespace graphics {

	class Loader : public ResourceLoader {

	private :

	public :

		~Loader() {}

		int LoadResource(std::string fileName) override;
		void DestoryResource(int handle) override;

	};

	class LoadGraphics {

	private:

		Loader mLoader;

		std::map<std::string, std::string> mTag;

	public:

		static LoadGraphics* GetInstance() {
			static LoadGraphics inst;
			return &inst;
		}

		/*
			画像読み込み
			std::string fileName	:	ファイルパス
			std::string tag			:	識別タグ(固有名を設定すること)
			return	true	:	成功
					false	:	失敗
		*/
		bool Load(std::string fileName,std::string tag);
		void Destroy(int handle);
		void Destroy(std::string tag);

		/*
			グラフィックスハンドルを取得する
			std::string& tag
			return ハンドル
		*/
		int Get(std::string tag);
		

	};
}

#endif // __LOAD_GRAPHICS_H__