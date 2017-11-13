//
//  CocosHeader.h
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 22..
//
//

#ifndef dotMonster_CocosHeader_h
#define dotMonster_CocosHeader_h

#include "cocos2d.h"

#if(CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
#include "extensions/cocos-ext.h"
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "cocos-ext.h"
#endif


#include <iostream>
using namespace cocos2d;
USING_NS_CC_EXT;

//#define FONT_NAME "fonts/NanumGothic.ttf"

#define FONT_SIZE 23

#endif
