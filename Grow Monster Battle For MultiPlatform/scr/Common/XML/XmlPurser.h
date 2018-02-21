/*
				ファイル名		:XmlPurser.h
				作成者			:
				作成日時		:2018/02/15
				ソース説明		:
				
					Xml読み込みを行う
				
				備考
				
				
				
!*/

#ifndef __XML_PURSER_H__
#define __XML_PURSER_H__


#include <iostream>
#include <string>

#if __has_include(<boost/property_tree/ptree.hpp>)	//ヘッダーファイルが存在していればインクルードする
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#endif	//__has_include(<boost/property_tree/ptree.hpp>)

#ifdef BOOST_PROPERTY_TREE_PTREE_HPP_INCLUDED
#define XML_PURSER_USE
#endif


class XmlPurser {

#ifdef XML_PURSER_USE
private:

	boost::property_tree::ptree pt;

protected:

	const std::string ROOT_PATH;

	std::string mFilePath;
#endif	//XML_PURSER_USE

public :
	
	XmlPurser(const std::string& path);
	~XmlPurser();

	void Initialize();

	/*
		読み込み
		return	true	:成功
				false	:失敗
	*/
	bool Read();
	
	/*
		書き込み
		return	true	:成功
				false	:失敗
	*/
	bool Write();

	/*
		ファイルが存在しているか確認する
		return	true	:存在している
				false	:存在していない
	*/
	bool IsExists(const std::string& path = "");


	
	std::string GetString(const std::string& title);

	std::string GetChildString(const std::string& title, const std::string& childTitle);

	//書き込み

	/*
		値を設定する
		const std::string& title	:題名
		T value						:任意の型の値
	*/
	template<typename T>
	void Set(const std::string& title, T value) {
#ifdef XML_PURSER_USE
		pt.put(ROOT_PATH + "." + title, std::to_string(value));
#endif	//XML_PURSER_USE
	}

	template<typename T>
	void SetChild(const std::string& title,const std::string& childTitle,T value) {
#ifdef XML_PURSER_USE
		boost::property_tree::ptree& child = pt.put(ROOT_PATH + "." + title,"");
		child.put(childTitle, std::to_string(value));
#endif	//XML_PURSER_USE
	}

	//読み込み
	int GetInt(const std::string& title);
	double GetDouble(const std::string& title);

	int  GetChildInt(const std::string& title, const std::string& childTitle);
	double  GetChildDouble(const std::string& title, const std::string& childTitle);
	
};

template<>
inline void XmlPurser::Set(const std::string& title, std::string& value) {
#ifdef XML_PURSER_USE
	pt.put(ROOT_PATH + "." + title, value);
#endif	//XML_PURSER_USE
}

template<>
inline void XmlPurser::Set(const std::string& title, const char* value) {
#ifdef XML_PURSER_USE
	pt.put(ROOT_PATH + "." + title, value);
#endif	//XML_PURSER_USE
}


#endif // __XML_PURSER_H__