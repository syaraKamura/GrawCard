/*
				ファイル名		:ResourceLoader.h
				作成者			:
				作成日時		:2018/05/12
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __RESORUCE_LOADER_H__
#define __RESORUCE_LOADER_H__

#include <map>
#include <string>

class ResourceLoader {

public :

	
private:

	std::map<std::string, int> mResourceList;

protected:

	virtual int LoadResource(std::string fileName);
	virtual void DestoryResource(int handle);


public :

	ResourceLoader();
	virtual ~ResourceLoader();

	/*
		非同期読み読み込み
	*/
	bool LoadASync(std::string fileName, int* pOutHandle = nullptr);
	int Get(std::string fileName);

	bool Destory(std::string fileName);

};

#endif // __RESORUCE_LOADER_H__