/*
				ファイル名		:ReceiveUDP.h
				作成者			:
				作成日時		:2018/01/22
				ソース説明		:
					
					UDP通信 受信クラス
				
				備考
				
				
				
!*/

#ifndef __RECEVE_UDP_H__
#define __RECEVE_UDP_H__

class ReceiveUDP {

private:

	static const int DATA_BUFFER_SIZE = 500;

private:

	int mHandle;
	IPDATA mIp;
	unsigned char mBuffer[DATA_BUFFER_SIZE];
	int mAddress;

private:

	/*
	送信データを削除する
	*/
	void ClearData();

	/*
	データの読み込み
	*/
	void ReadData(const void* data, int size);
public :

	ReceiveUDP();
	~ReceiveUDP();

	/*
	ソケットの作成をする
	return	true	:成功
	false	:失敗
	*/
	bool MakeSocket(short ip1, short ip2, short ip3, short ip4);
	bool MakeSocket(IPDATA ip);

	/*
	送信を実行する
	*/
	int Execute();

	/*
	ソケットの削除をする
	*/
	void DeleteSocket();


	bool ReadInt(int paramInt);
	bool ReadFloat(float paramFloat);
	bool ReadDouble(double paramDouble);
	bool ReadBool(bool paramBool);
	bool ReadChar(char paramChr);
	bool ReadString(char* paramString);
	bool ReadUChar(unsigned char paramUChar);

};

#endif // __RECEVE_UDP_H__