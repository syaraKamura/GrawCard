/*
				ファイル名		:XmlPurser.cpp
				作成者			:
				作成日時		:2018/02/15
				ソース説明		:
				
				
				備考
				
				
				
!*/


#include<list>
#include "Common/GameCommon.h"
#include "XmlPurser.h"


/*
	コンストラクタ
*/
XmlPurser::XmlPurser(const std::string& path) : ROOT_PATH("root") , mFilePath(path){

	
#ifndef XML_PURSER_USE
	Debug::LogPrintf("boostライブラリを設定してください\n");
#else
	Initialize();
#endif // !#ifndef XML_PURSER_USE




}

/*
	デストラクタ
*/
XmlPurser::~XmlPurser() {

}

void XmlPurser::Initialize() {
	if (IsExists(mFilePath) == true) {
		this->Read();
	}
}

/*
読み込み
return	true	:成功
false	:失敗
*/
bool XmlPurser::Read() {

#ifndef XML_PURSER_USE
	return false;
#else

	if (this->IsExists(mFilePath) == false) return false;

	std::ifstream file;
	file.open(mFilePath);
	std::stringstream  strStream;

	strStream << file.rdbuf();

	boost::property_tree::read_xml(strStream, pt);

	return true;
#endif//XML_PURSER_USE
}


/*
書き込み
return	true	:成功
false	:失敗
*/
bool XmlPurser::Write() {

#ifndef XML_PURSER_USE
	return false;
#else
	std::stringstream tmpStream;

	using namespace boost::property_tree::xml_parser;
	using boost::property_tree::ptree;

	const int indent = 2;
	const xml_writer_settings<typename ptree::key_type> &setting = xml_writer_make_settings<ptree::key_type>(' ', 2);
	write_xml(tmpStream, pt, setting);

	std::string tmpSjis = tmpStream.str();
	std::ofstream tmpOutStream(mFilePath.c_str());

	if (tmpOutStream.is_open() == false) {
		return false;
	}

	tmpOutStream << tmpSjis;

	return true;
#endif	//XML_PURSER_USE
}


/*
ファイルが存在しているか確認する
return	true	:存在している
false	:存在していない
*/
bool XmlPurser::IsExists(const std::string& path) {
	std::ifstream file(path.c_str());
	return file.good();
}

/*
	文字列を返却する
*/
std::string XmlPurser::GetString(const std::string& title) {
#ifndef XML_PURSER_USE
	return "";
#else
	if (boost::optional<std::string> id = pt.get_optional<std::string>(ROOT_PATH +"."+ title)) {
		return id.get();
	}
	else {
		return "";
	}
#endif//XML_PURSER_USE
}

std::string XmlPurser::GetChildString(const std::string& title,const std::string& childTitle) {
#ifndef XML_PURSER_USE
	return -1;
#else
	auto child = pt.get_child(ROOT_PATH + "." + title);

	boost::optional<std::string> id = child.get_optional<std::string>(childTitle);

	const std::string value = id.get();

	return value;
#endif//XML_PURSER_USE
}

/*
	int型の値を読み取る

*/
int XmlPurser::GetInt(const std::string& title) {
#ifndef XML_PURSER_USE
	return -1;
#else
	if (boost::optional<int> id = pt.get_optional<int>(ROOT_PATH + "." + title)) {
		return id.get();
	}
	else {
		return -1;
	}
#endif	//XML_PURSER_USE
}

int  XmlPurser::GetChildInt(const std::string& title,const std::string& childTitle) {
#ifndef XML_PURSER_USE
	return -1;
#else
	auto child = pt.get_child(ROOT_PATH + "." + title);
	
	boost::optional<int> id = child.get_optional<int>(childTitle);
	
	const int value = id.get();

	return value;
#endif
}

/*
	double型の値を読み取る
*/
double XmlPurser::GetDouble(const std::string& title) {
#ifndef XML_PURSER_USE
	return -1.0;
#else
	if (boost::optional<double> id = pt.get_optional<double>(ROOT_PATH + "." + title)) {
		return id.get();
	}
	else {
		return -1.0;
	}
#endif
}


double  XmlPurser::GetChildDouble(const std::string& title, const std::string& childTitle) {
#ifndef XML_PURSER_USE
	return -1.0;
#else
	auto child = pt.get_child(ROOT_PATH + "." + title);

	boost::optional<double> id = child.get_optional<double>(childTitle);

	const double value = id.get();

	return value;
#endif
}