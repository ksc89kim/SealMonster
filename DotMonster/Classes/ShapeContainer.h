//
//  ShapeContainer.h
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 9..
//
//

#ifndef __ShapeMaster__ShapeContainer__
#define __ShapeMaster__ShapeContainer__

#include "ShapeName.h"


namespace shapeType {
    enum
    {
        kShapeF,
        kShapeW,
        kShapeT,
        kShapeI,
        kShapeZ,
    };
}

class ShapeNameContainer:public Ref
{
private:
    Vector<Ref *> *_containerShapeF;
    Vector<Ref *> *_containerShapeW;
    Vector<Ref *> *_containerShapeT;
    Vector<Ref *> *_containerShapeI;
    Vector<Ref *> *_containerShapeZ;
public:
    ShapeNameContainer();
    ~ShapeNameContainer();

    static ShapeNameContainer*getInstance();
    
    void setShapeFName();
    void setShapeWName();
    void setShapeTName();
    void setShapeIName();
    void setShapeZNmae();
    
    void addName(int shapeType, int classNumber, const char*firstName1, const char*midName1, const char*lastName1, const char*firstName2="", const char*midName2="", const char*lastName2="",const char*firstName3="", const char*midName3="", const char*lastName3="");

    ShapeName *getRandShapeName(int shapeType);
    ShapeName *getRandShapeName(int shapeType, int minRandLevel, int maxRandLevel);
    ShapeName *getFindShapeName(int shapeType, int index);


    Vector<Ref *> *getShapeArray(int shapeType);
    bool checkFirstName(int shapeType, const char*name);
    bool checkMidName(int shapeType, const char*name);
    bool checkLastName(int shapeType, const char*name);

    
    
};

class ShapeSkillContainer:public Ref
{
private:
    Vector<Ref *> *_containerShapeSkillF;
    Vector<Ref *> *_containerShapeSkillW;
    Vector<Ref *> *_containerShapeSkillT;
    Vector<Ref *> *_containerShapeSkillI;
    Vector<Ref *> *_containerShapeSkillZ;
    
    
public:
    ShapeSkillContainer();
    ~ShapeSkillContainer();
    
    static ShapeSkillContainer* getInstance();
    
    
    void addSkill(int shapeType, std::string skillName1, std::string animationName1, int skillType1, std::string skillName2, std::string animationName2, int skillType2, std::string skillName3, std::string animationName3, int skillType3, std::string skillName4,std::string animationName4, int skillType4);

    
    
    void setShapeFSkill();
    void setShapeWSkill();
    void setShapeTSkill();
    void setShapeISkill();
    void setShapeZSkill();
    const char *getShapeFile(int shapeType,const char *skillName);
    Vector<Ref *> *getShapeArray(int shapeType);

};

#endif /* defined(__ShapeMaster__ShapeContainer__) */
