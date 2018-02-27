/*
				ファイル名		:GameCommon.cpp
				作成者			:
				作成日時		:2018/02/26
				ソース説明		:
				
				
				備考
				
				
				
!*/

#include "GameCommon.h"


namespace my_std {

	template < typename T >
	std::string StringTool::to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}


};