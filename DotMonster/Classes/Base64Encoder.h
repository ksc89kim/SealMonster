//
//  Base64Encoder.h
//  DotMonster
//
//  Created by 김선철 on 2015. 1. 13..
//
//

#ifndef __DotMonster__Base64Encoder__
#define __DotMonster__Base64Encoder__

class Base64Encoder{
public:
    Base64Encoder();
    int base64_decode(char* text, unsigned char* dst, int numBytes);
    int base64_encode(char* text, int numBytes, char **encodedText);
    
private:
    static const char MimeBase64[64];
    static int DecodeMimeBase64[256];
};
#endif /* defined(__DotMonster__Base64Encoder__) */
