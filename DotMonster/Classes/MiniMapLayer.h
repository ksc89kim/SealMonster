//
//  MiniMapLayer.hpp
//  DotMonster
//
//  Created by 김선철 on 2016. 3. 7..
//
//

#ifndef MiniMapLayer_h
#define MiniMapLayer_h

#include "ModalLayer.h"

class MiniMapLayer:public ModalLayer
{
private:
    ScrollView *_scroll;
    Sprite *_container;
public:
    static MiniMapLayer *create();
    void setImage();
    void clickClose();
};

#endif /* MiniMapLayer_h */
