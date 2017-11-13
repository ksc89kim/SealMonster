//
//  VillageLayer.h
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 22..
//
//

#ifndef __dotMonster__VillageLayer__
#define __dotMonster__VillageLayer__

#include "Define.h"


class VillageLayer:public LayerColor
{
    Node *_beforeLayer;
   int _villageTag;
public:
    VillageLayer();
    ~VillageLayer();
    static VillageLayer *create(Node *beforeLayer, int villageTag);
    void setImage();
    void setValue();
    void clickHospital();
    void clickCharge();
    void clickItemShop();

    void click(Ref *object);
    void exit();

};

#endif /* defined(__dotMonster__VillageLayer__) */
