/*
				ファイル名		:File.h
				作成者			:
				作成日時		:2018/05/19
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __FILE_H__
#define __FILE_H__

class File {

private :

	const char* mFileData;	//ファイルデータ
	const char* mFileName;		//ファイル名
	int mSize;

	friend class Loader;

public:


	/*
		読み込み
	*/
	File(const char* filePath);
	
	~File();

	/*
		ファイルデータを返却する
	*/
	const char* GetFile();

	int Size();

	/*
		ファイルの読み込みができているか？
		return	true	:読み込み済み
				false	:読み込みができていない
	*/
	bool IsReady();

};

#endif // __FILE_H__