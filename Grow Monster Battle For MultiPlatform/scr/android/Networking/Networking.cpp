/*
				ファイル名		:Networking.cpp
				作成者			:
				作成日時		:20118/12/12
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "Networking.h"

#include "net/ethertypes.h"

bool Networking::BeginNetwork(){
	
	//addrinfo info;
	//addrinfo* res = nullptr;
	//
	//int ret = android_getaddrinfofornetwork(0, "https:/www.google.com", "", &info, &res);
	int ret = 0;

	return ret != 0;
}

bool Networking::EndNetwork() {

	return false;
}