//
//  Tutorial.hpp
//  DotMonster
//
//  Created by 김선철 on 2016. 3. 9..
//
//

#ifndef Tutorial_h
#define Tutorial_h

#include "ModalLayer.h"

class Tutorial:public LayerColor
{
private:
    Sprite *_tutorial1;
    Sprite *_tutorial2;
    Sprite *_tutorial3;
    Sprite *_tutorial4;
    Node *_mapArea;
    Node *_enemy;
    Node *_beforeLayer;
public:
    static Tutorial *create(Node *beforeLayer, Node *enemy,Node *mapArea);
    void setImage();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event *event);
};

#endif /* Tutorial_h */
