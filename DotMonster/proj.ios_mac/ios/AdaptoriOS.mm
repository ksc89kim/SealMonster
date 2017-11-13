//
//  AdaptoriOS.cpp
//  DotMonster
//
//  Created by 김선철 on 2016. 2. 4..
//
//

#include "AdaptoriOS.h"
#import "AppController.h"

void AdaptoriOS::hideAdMob()
{
    AppController *app = (AppController *)[[UIApplication sharedApplication] delegate];
    [app hideAdMob];
}
void AdaptoriOS::showAdMob()
{
    AppController *app = (AppController *)[[UIApplication sharedApplication] delegate];
    [app showAdMob];
}
void AdaptoriOS::showInterstital()
{
    AppController *app = (AppController *)[[UIApplication sharedApplication] delegate];
    [app showInterstital];
}
void AdaptoriOS::showVideo()
{
    AppController *app = (AppController *)[[UIApplication sharedApplication] delegate];
    [app showVideo];
}

void AdaptoriOS::loginGameCenter()
{
    AppController *app = (AppController *)[[UIApplication sharedApplication] delegate];
    [app loginGameCenter];
}
void AdaptoriOS::submitScore(int score)
{
    AppController *app = (AppController *)[[UIApplication sharedApplication] delegate];
    [app sendSocre:score];
}
void AdaptoriOS::showLeaderBoarder()
{
    AppController *app = (AppController *)[[UIApplication sharedApplication] delegate];
    [app showLeaderBoard];

}