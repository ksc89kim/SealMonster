//
//  ShapeSkill.h
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 18..
//
//

#ifndef __ShapeMaster__ShapeSkill__
#define __ShapeMaster__ShapeSkill__

#include "Define.h"


class ShapeSkill:public Node
{
public:
    ShapeSkill();
    ~ShapeSkill();
    
    int _skillType;
    int _skillLevel;
    std::string _skillName;
    std::string _animationFileName;

    static ShapeSkill *create();
    static ShapeSkill *create(ShapeSkill *skill);
    static ShapeSkill *create(int skillType, int skillLevel, const char *skillName, const char *animationFileName);
    static ShapeSkill *create(int skillType, int skillLevel, std::string skillName, std::string animationFileName);
    void changeSkillData(int skillType, int skillLevel, std::string skillName, std::string animationFileName);
    void changeSkillData(ShapeSkill *skill);
};

#endif /* defined(__ShapeMaster__ShapeSkill__) */
