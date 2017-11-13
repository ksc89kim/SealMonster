//
//  ShapeW.h
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 1..
//
//

#ifndef __ShapeMaster__ShapeW__
#define __ShapeMaster__ShapeW__

#include "ShapeCommon.h"

class ShapeW:public ShapeCommon
{
private:
    void setImage();
    void setValue();
    void setName();
    void setStatus();
    const char *getFirstImageName();
    const char *getMidImageName();
    const char *getLastImageName();
    
public:
    ShapeW();
    ~ShapeW();

    static ShapeW *create();
    
    void changeImage();
    void changeRandShape(int minRandLevel,int maxRandLeve);
    void changeFindShape(int firstIndex,int midIndex, int lastIndex);
    ShapeObject *getStatusObject(int index);
};


#endif /* defined(__ShapeMaster__ShapeW__) */
