//
//  MoveObject.h
//  dotMonster
//
//  Created by 김선철 on 2014. 10. 19..
//
//

#ifndef __dotMonster__MoveObject__
#define __dotMonster__MoveObject__

#include "Define.h"

class MoveObject:public Sprite
{
public:
    MoveObject();
    ~MoveObject();

    static MoveObject* create(const char *fileName);
    int _way;
    int _maxMoveRange;
    int _minMoveRange;
    int _gap;
    
    void setMoveRange(Node *target);
    void move();
    float getTime(float distance);
    float checkDistance();
};

#endif /* defined(__dotMonster__MoveObject__) */
