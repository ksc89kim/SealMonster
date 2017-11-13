//
//  Setting.h
//  DotMonster
//
//  Created by 김선철 on 2016. 2. 3..
//
//

#ifndef __DotMonster__Setting__
#define __DotMonster__Setting__

#include "ModalLayer.h"

class SettingLayer:public ModalLayer
{
private:
    MenuItemSprite *_sound;
    MenuItemSprite *_music;
public:
    static SettingLayer *create();
    void setImage();
    void setSound(bool isSound, bool isFirst);
    void setMusic(bool isMusic, bool isFirst);
    
    void clickSound();
    void clickMusic();
    void clickClose();
};

#endif /* defined(__DotMonster__Setting__) */
