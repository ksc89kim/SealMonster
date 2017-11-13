//
//  StampCharge.h
//  DotMonster
//
//  Created by 김선철 on 2015. 10. 7..
//
//

#ifndef __DotMonster__Hospital__
#define __DotMonster__Hospital__

#include "Define.h"

#define HOSPITAL_PRICE 500

class HospitalLayer:public LayerColor
{
    Node *_beforeLayer;
    Label *_content;
    std::string _currentTalk;
    bool _isTyping;
    vector<string> _talkArray;
    int _index;
    bool _isExit;
    Sprite *_talkBorder;
    Sprite *_healBorder;
public:
    static HospitalLayer *create(Node *beforeLayer);
    void setImage();
    void nextTyping(float delayTime);
    void nextSetting();
    void setHealLayer();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event *event);
    void clickHeal(Ref *pSender);
    void clickExit(Ref *pSender);
};
#endif /* defined(__DotMonster__StampCharge__) */
