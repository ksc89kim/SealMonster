//
//  ShapeObject.h
//  ShapeMaster
//
//  Created by 김선철 on 2014. 2. 23..
//
//

#ifndef __ShapeMaster__ShapeObject__
#define __ShapeMaster__ShapeObject__

#include "cocos2d.h"
#include "ShapeName.h"
#include "ShapeSkill.h"

using namespace cocos2d;


class ShapeObject:public Node
{

public:
    ShapeName *_name;
    ShapeValue *_plusPower;
    ShapeValue *_plusAgility;
    ShapeValue *_plusMaxHealth;
    ShapeValue *_power;
    ShapeValue *_agility;
    ShapeValue *_health;
    ShapeValue *_maxHealth;
    ShapeValue *_exp;
    ShapeValue *_class;
    ShapeValue *_level;
    ShapeSkill *_reflectSkill;
    ShapeValue *_reflectCount;
    ShapeSkill *_stopSkill;
    ShapeValue *_stopTurn;
    ShapeValue *_debufTurn;
    ShapeValue *_maxSkillLevel;
    ShapeValue *_select;
    ShapeValue *_debufPower;
    ShapeValue *_debufAgility;
    ShapeValue *_type;
    ShapeValue *_isLegend;

    ShapeSkill *_skill1;
    ShapeSkill *_skill2;
    ShapeSkill *_skill3;
    ShapeSkill *_skill4;
    
    bool _isDebufAnimation;
    
    ShapeObject();
    ~ShapeObject();

    static ShapeObject* create();
    void setValue();
    void plusHelath(float value);
    void minusHelath(float value);
    void initData();
    void copyData(ShapeObject *data);
};

#endif /* defined(__ShapeMaster__ShapeObject__) */
