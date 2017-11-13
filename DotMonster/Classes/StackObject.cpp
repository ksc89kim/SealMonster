//
//  StackObject.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 10. 21..
//
//

#include "StackObject.h"


StackObject::StackObject()
{
}

StackObject::~StackObject()
{

}

StackObject *StackObject::create(ShapeSkill *skillData)
{

    StackObject *sprite = new (std::nothrow) StackObject();
    if (sprite && sprite->initWithFile("stackSkill1.png"))
    {
        sprite->setSkillData(skillData);
        sprite->setSpriteFrame(Sprite::create(sprite->setImageFileName())->getSpriteFrame());
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void StackObject::changeSkillData(ShapeSkill *skillData)
{
    _skillData->changeSkillData(skillData);
    this->setSpriteFrame(Sprite::create(setImageFileName())->getSpriteFrame());
}
const char *StackObject::setImageFileName()
{
    switch(_skillData->_skillLevel){
        case 1:
            return "stackSkill1.png";
            break;
        case 2:
            return "stackSkill2.png";
            break;
        case 3:
            return "stackSkill3.png";
            break;
        case 4:
            return "stackSkill4.png";
            break;
    }
    return "stackSkill1.png";
}
void StackObject::setSkillData(ShapeSkill *skillData)
{
    this->removeChild(_skillData, true);
    _skillData = ShapeSkill::create(skillData);
    this->addChild(_skillData);
}