/*
				ファイル名		:Loader.h
				作成者			:
				作成日時		:2018/05/20
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __LOADER_H__
#define __LOADER_H__

#include <list>
#include "File.h"

class Loader {

private:

	static Loader* mInst;

	

	std::list<File*> mFileList;

private:

	Loader();
	Loader(const Loader&);
	void operator = (const Loader&);

public:

	~Loader();

	static void Create();
	static void Destory();


	static Loader* Instance();

	File* CreateFile(File** file,const char* filePaht);	
	void DeleteFile(File** file);
	void Update();


};

#endif // __LOADER_H__