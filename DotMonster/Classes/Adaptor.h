//
//  Adaptor.h
//  DotMonster
//
//  Created by 김선철 on 2016. 2. 3..
//
//

#ifndef __DotMonster__AdaptorHelper__
#define __DotMonster__AdaptorHelper__

#include <stdio.h>

class Adaptor
{
public:
    static void hideAd();
    static void showAd();
    static void showInterstitalAd();
    static void showVedio();
    static void login();
    static void submitScore(int score);
    static void showLeaderBoard();

    static bool isAdShowing;
    
    static void createAdmob(const char *adKey);
    static void createInterstitalAd(const char *adKey);
    static void checkAdmobKey();
    static void checkInterstitalAd();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    static void videoSuccess();
    static void videoNotContent();
    static void videoFail();
#else
#endif
    
};

#endif /* defined(__DotMonster__AdaptorHelper__) */
