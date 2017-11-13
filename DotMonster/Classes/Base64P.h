#ifndef __MYGAME_UTIL_BASE64P_H__
#define __MYGAME_UTIL_BASE64P_H__

#include <stdlib.h>
#include <string.h>
#include "Define.h"

/* ENCODE EX)
	char* buf = new char[json.size() + 1];		
	int bufLen = Base64P::base64Encode(json.c_str(),json.length(),&buf);
	buf[bufLen] = '\0';
*/
/* DECODE EX)
	string data = dataStr.substr(5);
	char* decodeData = new char[data.size() + 1];
	decodeData[data.size()] = '\0';

	int len = Base64P::base64Decode(data.c_str(),decodeData);
	decodeData[len] = '\0';
	string finalResult = decodeData;
	delete [] decodeData;
*/

class Base64P
{
public:
	Base64P(){}
	~Base64P(){}
    static string enCode(string &data);
    static string enCode(int data);
    static string deCode(string data);
    static int deCodeInt(string data);

	static int base64Encode(const void *data, int size, char **str);
	static int base64Decode(const char *str, void *data);
};

#endif
