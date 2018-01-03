/*
		ファイル名		:SaveData.h
		作成者			:
		作成日時		:2017/12/31
		ソース説明		:セーブデータ


		備考



!*/

#ifndef __SAE_DATA_H__
#define __SAE_DATA_H__

#define SAVE_HASH(S,A,V,E,N) ((S << 16) || (A << 8) || (V << 4) || (E << 2) || (N))

class SaveData {

private:

	const int HASTH = SAVE_HASH('M','A','K','E','0');

private:

	char mVersion[4];


public :

	SaveData();
	~SaveData();

	SaveData Load();
	void Save(SaveData save);

};

#endif //__SAE_DATA_H__