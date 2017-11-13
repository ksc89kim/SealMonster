//
//  ShapeSkill.cpp
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 18..
//
//

#include "ShapeSkill.h"

ShapeSkill::ShapeSkill()
{
    _skillName = "빈공간";
}
ShapeSkill::~ShapeSkill()
{
}

ShapeSkill *ShapeSkill::create()
{
    return ShapeSkill::create(1, 1,"","");
}


ShapeSkill *ShapeSkill::create(ShapeSkill *skill)
{
    return ShapeSkill::create(skill->_skillType, skill->_skillLevel,skill->_skillName,skill->_animationFileName);
}

ShapeSkill *ShapeSkill::create(int skillType, int skillLevel, std::string skillName, std::string animationFileName)
{
    ShapeSkill * ret = new ShapeSkill();
    if (ret && ret->init())
    {
        ret->_skillType = skillType;
        ret->_skillLevel = skillLevel;
        ret->_skillName = skillName;
        ret->_animationFileName = animationFileName;
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
	return ret;
}

ShapeSkill *ShapeSkill::create(int skillType, int skillLevel, const char*skillName, const char *animationFileName)
{
    ShapeSkill * ret = new ShapeSkill();
    if (ret && ret->init())
    {
        ret->_skillType = skillType;
        ret->_skillLevel = skillLevel;
        ret->_skillName = skillName;
        ret->_animationFileName = animationFileName;
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
	return ret;
}
void ShapeSkill::changeSkillData(int skillType, int skillLevel, std::string skillName, std::string animationFileName)
{
    _skillType = skillType;
    _skillLevel = skillLevel;
    _skillName = skillName;
    _animationFileName = animationFileName;
}
void ShapeSkill::changeSkillData(ShapeSkill *skill)
{
    _skillType = skill->_skillType;
    _skillLevel = skill->_skillLevel;
    _skillName = skill->_skillName;
    _animationFileName = skill->_animationFileName;
}
