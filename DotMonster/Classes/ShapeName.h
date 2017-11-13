//
//  ShapeName.h
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 1..
//
//

#ifndef __ShapeMaster__ShapeName__
#define __ShapeMaster__ShapeName__

#include "cocos2d.h"
#include "ShapeValue.h"

using namespace cocos2d;

class ShapeName:public Node
{
private:
    __String *_firstName;
    __String *_midName;
    __String *_lastName;

public:
    ShapeName *_class2;
    ShapeName *_class3;
    
    ShapeValue *_firstNumber; //등급 넘버.
    ShapeValue *_midNumber; //등급 넘버.
    ShapeValue *_lastNumber; //등급 넘버.

    ShapeName();
    ~ShapeName();

    void setFirstName(const char*firstName);
    void setMidName(const char*midName);
    void setLastName(const char*lastName);
    
    void setFirstNumber(int firstNumber);
    void setMidNumber(int midNumber);
    void setLastNumber(int lastNumber);
    
    void setName(const char*firstName, const char*midName, const char*lastName);
    void setNumber(int firstNumber, int midNumber, int lastNumber);

    const char* getFirstName();
    const char* getMidName();
    const char* getLastName();
    const char* getFullName();
    
    int getFirstNumber();
    int getMidNumber();
    int getLastNumber();

    static ShapeName *create();
    static ShapeName *create(const char*firstName, const char*midName, const char*lastName, int classNumber);
    static ShapeName *create(const char*firstName, const char*midName, const char*lastName, int firstNumber, int midNumber, int lastNumber);
    
    void copy(ShapeName *name);

};
#endif /* defined(__ShapeMaster__ShapeName__) */
