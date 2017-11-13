//
//  EndingLayer.h
//  DotMonster
//
//  Created by 김선철 on 2016. 2. 1..
//
//

#ifndef __DotMonster__EndingLayer__
#define __DotMonster__EndingLayer__

#include "Define.h"

class EndingLayer:public LayerColor
{
public:
    static EndingLayer *create();
    void setImage();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event *event);
    void end();
};


#endif /* defined(__DotMonster__EndingLayer__) */
