//
//  AdaptoriOS.hpp
//  DotMonster
//
//  Created by 김선철 on 2016. 2. 4..
//
//

#ifndef AdaptoriOS_h
#define AdaptoriOS_h

#include <stdio.h>

class AdaptoriOS
{
public:
    static void hideAdMob();
    static void showAdMob();
    static void showInterstital();
    static void showVideo();
    
    static void loginGameCenter();
    static void submitScore(int score);
    static void showLeaderBoarder();

};
#endif /* AdaptoriOS_h */
