/*
				ファイル名		:CharConverter.h
				作成者			:http://kamoland.com/wiki/wiki.cgi?ShiftJIS%A1%A4Unicode%28UTF-8%29
				作成日時		:2019/09/10
				ソース説明		:
					
					文字コード変換
					
				備考
				
				
				
!*/

#ifndef __CHAR_CONVERTER_H__
#define __CHAR_CONVERTER_H__

class CharConverter {
public:
	static char* utf8_to_sjis(const char *pUtf8Str, int *nBytesOut);
	static char* sjis_to_utf8(const char *pAnsiStr, int *nBytesOut);
	static wchar_t* sjis_to_utf16be(const char *pAnsiStr, int *nBytesOut);
	static char* utf16be_to_utf8(const wchar_t *pUcsStr, int *nBytesOut);
	static char* utf16be_to_sjis(const wchar_t *pUcsStr, int *nBytesOut);
	static wchar_t* utf8_to_utf16be(const char *pUtf8Str, int *nNumOut, bool bBigEndian);

private:
	static int utf16be_to_utf8_sub(char *pUtf8, const wchar_t *pUcs2, int nUcsNum, bool bCountOnly);
	static int utf8_to_utf16be_sub(wchar_t *pUcs2, const char *pUtf8, int nUtf8Num, bool bCountOnly, bool bBigEndian);
};


#endif // __CHAR_CONVERTER_H__