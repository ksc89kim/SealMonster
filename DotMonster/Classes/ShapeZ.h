//
//  ShapeZ.h
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 1..
//
//

#ifndef __ShapeMaster__ShapeZ__
#define __ShapeMaster__ShapeZ__

#include "ShapeCommon.h"

class ShapeZ:public ShapeCommon
{
private:
    void setName();
    void setImage();
    void setValue();
    void setStatus();

public:
    static ShapeZ *create();
    void changeImage();
    void changeRandShape(int minRandLevel,int maxRandLeve);
    void changeFindShape(int firstIndex,int midIndex, int lastIndex);
    ShapeObject *getStatusObject(int index);
};

#endif /* defined(__ShapeMaster__ShapeZ__) */
