//
//  StackObject.h
//  dotMonster
//
//  Created by 김선철 on 2014. 10. 21..
//
//

#ifndef __dotMonster__StackObject__
#define __dotMonster__StackObject__

#include "Define.h"
#include "ShapeSkill.h"

class StackObject:public Sprite
{
private:
public:
    StackObject();
    ~StackObject();
    ShapeSkill *_skillData;

    static StackObject* create(ShapeSkill *skillData);
    void changeSkillData(ShapeSkill *skillData);
    void setSkillData(ShapeSkill *skillData);
    const char*setImageFileName();
};

#endif /* defined(__dotMonster__StackObject__) */
