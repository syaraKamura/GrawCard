/*
				ファイル名		:ReceveUDP_win32.cpp
				作成者			:
				作成日時		:2018/01/22
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Common/GameCommon.h"
#include "Common/Communication/ReceiveUDP.h"


#ifdef __WINDOWS__




ReceiveUDP::ReceiveUDP() {

	mAddress = 0;
	mHandle = 0;
	mReceivePort = -1;
	ClearData();

}

ReceiveUDP::~ReceiveUDP() {

}

/*
	受信用ソケットの作成をする
	return	true	:成功
			false	:失敗
*/

bool ReceiveUDP::MakeSocket(unsigned int receivePort) {
	
	if (mHandle != 0) return false;

	mReceivePort = receivePort;

	mHandle = DxLib::MakeUDPSocket(mReceivePort);
}

/*
	受信を実行する
	return	0以上	:成功
			-1		:失敗	通常エラー
			-2		:失敗	受信データよりバッファサイズの方が小さい
			-3		:失敗	受信データがない
*/
int ReceiveUDP::Execute() {
	
	int relust = -3;

	if (CheckNetWorkRecvUDP(mHandle) == TRUE) {
		relust = NetWorkRecvUDP(mHandle, NULL, NULL, mBuffer, DATA_BUFFER_SIZE, FALSE);
		mAddress = 0;
	}
	return relust;
}

/*
	ソケットの削除をする
*/
void ReceiveUDP::DeleteSocket() {
	DeleteUDPSocket(mHandle);
	mHandle = 0;
	mAddress = 0;
	mReceivePort = -1;
	ClearData();
}



bool ReceiveUDP::ReadInt(int* paramInt) {
	return ReadData(paramInt, sizeof(int));
}

bool ReceiveUDP::ReadFloat(float* paramFloat) {
	return ReadData(paramFloat, sizeof(float));
}

bool ReceiveUDP::ReadDouble(double* paramDouble) {
	return ReadData(paramDouble, sizeof(double));
}

bool ReceiveUDP::ReadBool(bool* paramBool) {
	return ReadData(paramBool, sizeof(bool));
}

bool ReceiveUDP::ReadChar(char* paramChr) {
	return ReadData(paramChr, sizeof(char));
}

bool ReceiveUDP::ReadString(char* paramString) {

	size_t length = 0;

	if (ReadData(&length, sizeof(size_t)) == false) {
		return false;
	}

	return ReadData(paramString, length + 1);
}

bool ReceiveUDP::ReadUChar(unsigned char* paramUChar) {
	return ReadData(paramUChar, sizeof(unsigned char));
}

bool  ReceiveUDP::ReadUInt(unsigned int* paramUInt) {
	return ReadData(paramUInt, sizeof(unsigned int));
}

/*
	受信データを削除する
*/
void ReceiveUDP::ClearData() {
	memset(mBuffer, 0, sizeof(unsigned char) * DATA_BUFFER_SIZE);
}

/*
データの読み込み
*/
bool ReceiveUDP::ReadData(const void* data, int size) {

	unsigned char* readData = (unsigned char*)data;

	for (int i = 0; i < size; i++) {
		
		if (mAddress == DATA_BUFFER_SIZE) {
			if (CheckNetWorkRecvUDP(mHandle) == TRUE) {
				NetWorkRecvUDP(mHandle, NULL, NULL, mBuffer, DATA_BUFFER_SIZE, FALSE);
				mAddress = 0;
			}
			else {
				break;
			}
		}

		*readData = mBuffer[mAddress];

		readData++;
		mAddress++;

	}
	return true;
}

#endif // __WINDOWS__
