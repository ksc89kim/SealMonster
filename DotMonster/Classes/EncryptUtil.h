//
//  EncryptUtil.h
//  DotMonster
//
//  Created by 김선철 on 2015. 1. 13..
//
//

#ifndef __DotMonster__EncryptUtil__
#define __DotMonster__EncryptUtil__

#include <iostream>
#include "Base64Encoder.h"
#include "Rijndael.h"

class EncryptUtil
{
    
public:
    static void Char2Hex(unsigned char ch, char* szHex);
    static void Hex2Char(char const* szHex, unsigned char& rch);
    static void CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize);
    static void HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize);
    
    static std::string string_format(const std::string &fmt, ...);
    static std::string Encrypt(std::string input);
    static std::string Encrypt(int input);
    static std::string Decrypt(const std::string &input);
    static int DecryptInt(const std::string &input);

    static std::string EncryptTron(std::string input);
    static std::string DecryptTron(std::string input);
    
    
    static std::string base64_encode(const char* value);
    static std::string base64_decode(const char* value);
    
    std::string base64Encode(const char *value);
};

#endif /* defined(__DotMonster__EncryptUtil__) */
