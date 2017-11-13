//
//  CommonScene.h
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 21..
//
//

#ifndef __dotMonster__CommonScene__
#define __dotMonster__CommonScene__

#include "Define.h"

class Common : public LayerColor
{
public:
    virtual bool init();
    bool init(cocos2d::Color4B color, bool isScaleSet = true);
    void setDefine();
    
    
    void setScreenSizeScale(bool bScale);
    void exitApp();
    
};

#endif /* defined(__dotMonster__CommonScene__) */
