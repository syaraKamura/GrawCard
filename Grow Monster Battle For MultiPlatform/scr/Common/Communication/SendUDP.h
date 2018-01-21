/*
				ファイル名		:SendUDP.h
				作成者			:
				作成日時		:2018/01/021
				ソース説明		:
					
					UDP通信 送信クラス
				
				備考
				
				
				
!*/

#ifndef __SEND_UDP_H__
#define __SEND_UDP_H__

class SendUDP {

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
		データの書き込み
	*/
	void WriteData(const void* data, int size);

public :
	
	SendUDP();
	~SendUDP();

	/*
		ソケットの作成をする
		return	true	:成功
				false	:失敗
	*/
	bool MakeSocket(short ip1,short ip2,short ip3, short ip4);
	bool MakeSocket(IPDATA ip);

	/*
		送信を実行する
	*/
	int Execute();

	/*
		ソケットの削除をする
	*/
	void DeleteSocket();


	void WriteInt(int paramInt);
	void WriteFloat(float paramFloat);
	void WriteDouble(double paramDouble);
	void WriteBool(bool paramBool);
	void WriteChar(char paramChr);
	void WriteString(const char* paramString);
	void WriteUChar(unsigned char paramUChar);
	void WriteUInt(unsigned int paramUInt);

	

};

#endif // __SEND_UDP_H__