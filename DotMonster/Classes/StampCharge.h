//
//  StampCharge.h
//  DotMonster
//
//  Created by 김선철 on 2015. 10. 7..
//
//

#ifndef __DotMonster__StampCharge__
#define __DotMonster__StampCharge__

#include "Define.h"

#define STAMPCHARGE_PRICE 200

class StampChargeLayer:public LayerColor
{
    Node *_beforeLayer;
    Label *_content;
    std::string _currentTalk;
    bool _isTyping;
    vector<string> _talkArray;
    int _index;
    bool _isExit;
    Sprite *_talkBorder;
    Sprite *_stampBorder;
public:
    static StampChargeLayer *create(Node *beforeLayer);
    void setImage();
    void nextTyping(float delayTime);
    void nextSetting();
    void setStampLayer();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event *event);
    void clickCharge(Ref *pSender);
    void clickExit(Ref *pSender);
};
#endif /* defined(__DotMonster__StampCharge__) */
