//
//  EncryptUtil.cpp
//  DotMonster
//
//  Created by 김선철 on 2015. 1. 13..
//
//

#include "EncryptUtil.h"

#include <cmath>



#define Key "TronPlay"
#define iv "fedcba9876543210"

//Function to convert unsigned char to string of length 2
void EncryptUtil::Char2Hex(unsigned char ch, char* szHex)
{
	unsigned char byte[2];
	byte[0] = ch/16;
	byte[1] = ch%16;
	for(int i=0; i<2; i++)
	{
		if(byte[i] >= 0 && byte[i] <= 9)
			szHex[i] = '0' + byte[i];
		else
			szHex[i] = 'A' + byte[i] - 10;
	}
	szHex[2] = 0;
}

//Function to convert string of length 2 to unsigned char
void EncryptUtil::Hex2Char(char const* szHex, unsigned char& rch)
{
	rch = 0;
	for(int i=0; i<2; i++)
	{
		if(*(szHex + i) >='0' && *(szHex + i) <= '9')
			rch = (rch << 4) + (*(szHex + i) - '0');
		else if(*(szHex + i) >='A' && *(szHex + i) <= 'F')
			rch = (rch << 4) + (*(szHex + i) - 'A' + 10);
		else
			break;
	}
}

//Function to convert string of unsigned chars to string of chars
void EncryptUtil::CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize)
{
	int i;
	char szHex[3];
	pszHexStr[0] = 0;
	for(i=0; i<iSize; i++)
	{
        memset(szHex, 0, sizeof(szHex));
		Char2Hex(pucCharStr[i], szHex);
		strcat(pszHexStr, szHex);
	}
}

//Function to convert string of chars to string of unsigned chars
void EncryptUtil::HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize)
{
	int i;
	unsigned char ch;
	for(i=0; i<iSize; i++)
	{
		Hex2Char(pszHexStr+2*i, ch);
		pucCharStr[i] = ch;
	}
}

std::string EncryptUtil::base64_encode(const char *value)
{
    Base64Encoder* base64Helper = new Base64Encoder();
    
    char* b64encoded_text = NULL;
    
    base64Helper->base64_encode((char*)value, strlen(value), &b64encoded_text);
    
    std::string return_str = b64encoded_text;
    
    delete b64encoded_text;
    
    return return_str;
}

std::string EncryptUtil::base64_decode(const char *value)
{
    Base64Encoder* base64Helper = new Base64Encoder();
    
    //unsigned char* dst = new unsigned char[1000];
    unsigned char* dst = new unsigned char[1048576];
    base64Helper->base64_decode((char*)value, dst, 1048576);
    
    std::string return_str = (char*)dst;
    
    delete dst;
    
    return return_str;
}


std::string EncryptUtil::EncryptTron(std::string input)
{
    std::string str;
    str = EncryptUtil::base64_encode(input.c_str());
    
    return EncryptUtil::Encrypt(str);
}

std::string EncryptUtil::DecryptTron(std::string input)
{
    std::string str = EncryptUtil::Decrypt(input.c_str());
    return EncryptUtil::base64_decode(str.c_str());
}
std::string EncryptUtil::Encrypt(int input)
{
    return EncryptUtil::Encrypt(to_string(input));
}
std::string EncryptUtil::Encrypt(std::string input)
{
    CRijndael oRijndael;
    oRijndael.MakeKey(Key, iv, 16, 16);
    int blockSize = input.length()+1;
    char szDataIn[blockSize];
    
    if (blockSize < 16) blockSize = 16;
    blockSize = ceil(blockSize/16.0f)*16;
    char szDataOut[blockSize] ;
    char szHex[blockSize*3];
    memset(szDataIn, 0, sizeof(szDataIn));
    memset(szDataOut, 0, sizeof(szDataOut));
    memset(szHex, 0, sizeof(szHex));
    //    cout << " szDataIn : " << sizeof(szDataIn) << endl;
    //    cout << " szDataOut : " << sizeof(szDataOut) << endl;
    //    cout << " szHex : " << sizeof(szHex) << endl;
    //Test CBC
    oRijndael.ResetChain();
    strcpy(szDataIn, input.c_str());
    //    cout << " szDataIn : " << szDataIn << endl;
    
    oRijndael.Encrypt(szDataIn, szDataOut, sizeof(szDataOut), CRijndael::CBC);
    CharStr2HexStr((unsigned char*)szDataOut, szHex, sizeof(szDataOut));
    //    cout << " szHex : " << szHex << endl;
    return string_format("%s",szHex);
}

std::string EncryptUtil::Decrypt(const std::string &input)
{
    CRijndael oRijndael;
    oRijndael.MakeKey(Key, iv, 16, 16);
    size_t blockSize = input.length();
    if (blockSize < 16) blockSize = 16;
    char szHex[blockSize];
    unsigned char szDataIn[blockSize/2+1];
    char szDataOut[blockSize/2+1];
    memset(szDataIn, 0, sizeof(szDataIn));
    memset(szDataOut, 0, sizeof(szDataOut));
    memset(szHex, 0, sizeof(szHex));
    strcpy(szHex, input.c_str());
    HexStr2CharStr(szHex, szDataIn, strlen(szHex));
    oRijndael.Decrypt((char*)szDataIn, szDataOut, sizeof(szDataOut), CRijndael::CBC);
    return string_format("%s",szDataOut);
}
int EncryptUtil::DecryptInt(const std::string &input)
{
    return atoi(EncryptUtil::Decrypt(input).c_str());
}
std::string EncryptUtil::string_format(const std::string &fmt, ...) {
    int size=3000;
    std::string str;
    va_list ap;
    while (1) {
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *)str.c_str(), size, fmt.c_str(), ap);
        va_end(ap);
        if (n > -1 && n < size) {
            str.resize(n);
            return str;
        }
        if (n > -1)
            size=n+1;
        else
            size*=2;
    }
}