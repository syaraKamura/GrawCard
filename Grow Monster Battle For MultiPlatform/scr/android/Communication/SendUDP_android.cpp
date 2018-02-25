/*
				ファイル名		:SendUDP_android.cpp
				作成者			:
				作成日時		:2018/02/25
				ソース説明		:
					
					UDP通信 送信
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Common/Communication/SendUDP.h"


#ifdef __ANDROID__



SendUDP::SendUDP() {

	mAddress = 0;
	memset(&mIp, 0, sizeof(IPDATA));
	mHandle = 0;
	mSendPort = -1;
	ClearData();

}

SendUDP::~SendUDP() {


}

/*
	送信用のソケットの作成をする
	return	true	:成功
			false	:失敗 すでに作成されている
*/
bool SendUDP::MakeSocket(unsigned char ip1, unsigned char ip2, unsigned char ip3, unsigned char ip4, unsigned int sendPort) {

	IPDATA ip;

	ip.d1 = ip1;
	ip.d2 = ip2;
	ip.d3 = ip3;
	ip.d4 = ip4;

	return MakeSocket(ip, sendPort);
}

/*
	送信用ソケットの作成
	return	true	:成功
			false	:失敗 すでに作成されている
*/
bool SendUDP::MakeSocket(IPDATA ip, unsigned int sendPort) {

	if (mHandle != 0) return false;

	mIp = ip;
	mSendPort = sendPort;

	mHandle = -1;

	return false;
}

/*
	送信を実行する
	return	0以上	:成功
			-1		:失敗	通常エラー
			-2		:失敗	送信データのサイズが大きすぎる
			-3		:失敗	送信準備が完了していない
*/
int SendUDP::Execute() {

	return -1;
}

/*
	ソケットの削除をする
*/
void SendUDP::DeleteSocket() {

	
	mHandle = 0;
	mAddress = 0;
	mSendPort = -1;
	memset(&mIp, 0, sizeof(IPDATA));
	ClearData();
}


void SendUDP::WriteInt(int paramInt) {
	WriteData(&paramInt, sizeof(int));
}

void SendUDP::WriteFloat(float paramFloat) {
	WriteData(&paramFloat, sizeof(float));
}

void SendUDP::WriteDouble(double paramDouble) {
	WriteData(&paramDouble, sizeof(double));
}

void SendUDP::WriteBool(bool paramBool) {
	WriteData(&paramBool, sizeof(bool));
}
void SendUDP::WriteChar(char paramChr) {
	WriteData(&paramChr, sizeof(char));
}

void SendUDP::WriteString(const char* paramString) {

	size_t length = 0;
	//文字列の長さを取得
	length = strlenDx(paramString);
	//文字列の長さを書き込み
	WriteData(&length , sizeof(size_t));

	//文字列の長さ+1を書き込み
	WriteData(paramString,length + 1);
}

void SendUDP::WriteUChar(unsigned char paramUChar) {
	WriteData(&paramUChar, sizeof(unsigned char));
}

void SendUDP::WriteUInt(unsigned int paramUInt) {
	WriteData(&paramUInt, sizeof(unsigned int));
}

/*
送信データを削除する
*/
void SendUDP::ClearData() {
	memset(mBuffer, 0, sizeof(unsigned char) * DATA_BUFFER_SIZE);
}

/*
データの書き込み
*/
void SendUDP::WriteData(const void* data, int size) {

	const unsigned char* writeData = (const unsigned char*)data;

	for (int i = 0; i < size; i++) {

		if (mAddress == DATA_BUFFER_SIZE) {
			//NetWorkSendUDP(mHandle, mIp, mSendPort, mBuffer, mAddress);
			
			ClearData();
			mAddress = 0;

		}

		mBuffer[mAddress] = *writeData;

		writeData++;
		mAddress++;
	}

}


#endif	//__WINDOWS__

