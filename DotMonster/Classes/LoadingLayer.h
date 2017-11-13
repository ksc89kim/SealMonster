//
//  LoadingLayer.h
//  DotMonster
//
//  Created by 김선철 on 2016. 2. 2..
//
//

#ifndef __DotMonster__LoadingLayer__
#define __DotMonster__LoadingLayer__

#include "ModalLayer.h"

class LoadingLayer:public ModalLayer
{
private:
    Label *_firstLabel;
    Label *_twoLabel;
    Label *_threeLabel;
public:
    LoadingLayer();
    ~LoadingLayer();
    static LoadingLayer *create();
    void setImage();
    void startLoading();
    void stopLoading();
    void schedulLabel(float dt);
};

#endif /* defined(__DotMonster__LoadingLayer__) */
