//
//  ShapeValue.h
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 19..
//
//

#ifndef __ShapeMaster__ShapeValue__
#define __ShapeMaster__ShapeValue__

#include "Define.h"

class ShapeValue:public __String
{
private:
    int _limit;
    std::string _compareFirstId;
    std::string _compareLastId;
    
public:
    ShapeValue();
    ~ShapeValue();
    
    static ShapeValue* create(const char*compareFirstId, const char *compareLastId, int limit = 0);
    void setShapeValue(float value);
    float getShapeValue();
    void addShapeValue(float value);
    void minusShapeValue(float value);
};

#endif /* defined(__ShapeMaster__ShapeValue__) */
