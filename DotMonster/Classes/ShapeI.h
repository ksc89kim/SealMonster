//
//  ShapeI.h
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 1..
//
//

#ifndef __ShapeMaster__ShapeI__
#define __ShapeMaster__ShapeI__

#include "ShapeCommon.h"

class ShapeI:public ShapeCommon
{
private:
    void setName();
    void setImage();
    void setValue();
    void setStatus();

public:
    static ShapeI *create();
    
    void changeImage();
    void changeRandShape(int minRandLevel,int maxRandLeve);
    void changeFindShape(int firstIndex,int midIndex, int lastIndex);
    void setLegend();
    ShapeObject *getStatusObject(int index);
};
#endif /* defined(__ShapeMaster__ShapeI__) */
