//
//  CommonPopUp.h
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 26..
//
//

#ifndef __dotMonster__CommonPopUp__
#define __dotMonster__CommonPopUp__

#include "CocosHeader.h"

namespace popUpType {
    enum{
        kDefault,
        kOk,
        kOkAndCanle,
    };
}
class CommonPopUp:public LayerColor
{
    float _time;
    int _type;
    MenuItem *_callbackItem;
    Scale9Sprite *_background;
    Label *_label;
public:
    CommonPopUp();
    ~CommonPopUp();
    static CommonPopUp *create(int type, const char *content, const ccMenuCallback &callback);
    static CommonPopUp *create(int type, const char *content,float time,const ccMenuCallback &callback);

    void setImage(const char *content);
    void setValue();
    void remove();
    void ok();
    void cancel();
    void fadeOut();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event *event);
};

#endif /* defined(__dotMonster__CommonPopUp__) */
