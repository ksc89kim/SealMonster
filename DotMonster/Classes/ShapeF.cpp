//
//  ShapeF.cpp
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 1..
//
//

#include "ShapeF.h"
#include "ShapeContainer.h"

ShapeF::ShapeF()
{
}
ShapeF::~ShapeF()
{
}

ShapeF* ShapeF::create()
{
    ShapeF *pSprite = new ShapeF();
    if (pSprite && pSprite->init())
    {
        pSprite->setValue();
        pSprite->setImage();
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}
void ShapeF::setImage()
{
    this->setSpriteFrame(Sprite::create(getLastImageName())->getSpriteFrame());
    
    _imageMid = Sprite::create(getMidImageName());
    _imageMid->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(_imageMid);
    
    _imageTop = Sprite::create(getFirstImageName());
    _imageTop->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(_imageTop);
    
    changeImage();
}
void ShapeF::changeImage()
{
    if(isLegend())
    {
        this->setSpriteFrame(Sprite::create( "shapeF/l.png")->getSpriteFrame());
        _imageMid->setSpriteFrame(Sprite::create("1pixel.png")->getSpriteFrame());
        _imageMid->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
        _imageTop->setSpriteFrame(Sprite::create("1pixel.png")->getSpriteFrame());
        _imageTop->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
        this->setScale(0.7f, 0.7f);
    }
    else
    {
        checkEvolution();
        this->setSpriteFrame(Sprite::create(getLastImageName())->getSpriteFrame());
        _imageMid->setSpriteFrame(Sprite::create(getMidImageName())->getSpriteFrame());
        _imageMid->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
        _imageTop->setSpriteFrame(Sprite::create(getFirstImageName())->getSpriteFrame());
        _imageTop->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
        setClassScale();
    }
   
}
void ShapeF::setValue()
{
    setLegendValue(false);
    _shapeData->_type->setShapeValue(bushType::kBushShapeF);
    setName();
    setStatus();
}
const char *ShapeF::getFirstImageName()
{
    Vector<Ref *> *nameArray = ShapeNameContainer::getInstance()->getShapeArray(shapeType::kShapeF);
    for(int i=0;i<nameArray->size();i++)
    {
        ShapeName *name =  (ShapeName *)nameArray->at(i);
        if(!strcmp(name->getFirstName(), _shapeData->_name->getFirstName()))
        {
            if(_shapeData->_class->getShapeValue()==1)
            {
                return __String::createWithFormat("shapeF/f1-3-%d.png",i+1)->getCString();
            }
            else if(_shapeData->_class->getShapeValue()==2)
            {
                return __String::createWithFormat("shapeF/f2-3-%d.png",i+1)->getCString();
            }
            else if(_shapeData->_class->getShapeValue()==3)
            {
                return __String::createWithFormat("shapeF/f3-3-%d.png",i+1)->getCString();
            }
            break;
        }
    }
    return "";
}
const char *ShapeF::getMidImageName()
{
    Vector<Ref *> *nameArray = ShapeNameContainer::getInstance()->getShapeArray(shapeType::kShapeF);
    for(int i=0;i<nameArray->size();i++)
    {
        ShapeName *name =  (ShapeName *)nameArray->at(i);
        if(!strcmp(name->getMidName(), _shapeData->_name->getMidName()))
        {
            if(_shapeData->_class->getShapeValue()==1)
            {
                return __String::createWithFormat("shapeF/f1-2-%d.png",i+1)->getCString();
            }
            else if(_shapeData->_class->getShapeValue()==2)
            {
                return __String::createWithFormat("shapeF/f2-2-%d.png",i+1)->getCString();
            }
            else if(_shapeData->_class->getShapeValue()==3)
            {
                return __String::createWithFormat("shapeF/f3-2-%d.png",i+1)->getCString();
            }            break;
        }
    }
    return "";
}
const char *ShapeF::getLastImageName()
{
    Vector<Ref *> *nameArray = ShapeNameContainer::getInstance()->getShapeArray(shapeType::kShapeF);
    for(int i=0;i<nameArray->size();i++)
    {
        ShapeName *name =  (ShapeName *)nameArray->at(i);
        if(!strcmp(name->getLastName(), _shapeData->_name->getLastName()))
        {
            if(_shapeData->_class->getShapeValue()==1)
            {
                return __String::createWithFormat("shapeF/f1-1-%d.png",i+1)->getCString();
            }
            else if(_shapeData->_class->getShapeValue()==2)
            {
                return __String::createWithFormat("shapeF/f2-1-%d.png",i+1)->getCString();
            }
            else if(_shapeData->_class->getShapeValue()==3)
            {
                return __String::createWithFormat("shapeF/f3-1-%d.png",i+1)->getCString();
            }
            break;
        }
    }
    
    return "";
}
void ShapeF::setName()
{
    ShapeName *firstName, *midName, *lastName;
    if(isLegend())
    {
        ShapeNameData lengend = ShapeNameData(0,0,"","","","","","","","","");
        TextDb::getInstance()->runQueryShapeName(990, lengend);
       firstName = ShapeName::create(lengend._firstName1.c_str(), lengend._firstName2.c_str(), lengend._firstName3.c_str(), 0, 0, 0);
       midName = ShapeName::create(lengend._midName1.c_str(), lengend._midName2.c_str(), lengend._midName3.c_str(), 0, 0, 0);
        lastName = ShapeName::create(lengend._lastName1.c_str(), lengend._lastName2.c_str(), lengend._lastName3.c_str(), 0, 0, 0);
        _shapeData->_name->setName(firstName->getFirstName(),midName->getMidName(),lastName->getLastName());
    }
    else
    {
        firstName = ShapeNameContainer::getInstance()->getRandShapeName(shapeType::kShapeF);
        midName = ShapeNameContainer::getInstance()->getRandShapeName(shapeType::kShapeF);
        lastName = ShapeNameContainer::getInstance()->getRandShapeName(shapeType::kShapeF);
        setNameAndClassNumber(firstName,midName,lastName);
    }

}
void ShapeF::changeRandShape(int minRandLevel, int maxRandLeve)
{
    setLegendValue(false);
    ShapeName *firstName = ShapeNameContainer::getInstance()->getRandShapeName(shapeType::kShapeF, minRandLevel, maxRandLeve);
    ShapeName *midName = ShapeNameContainer::getInstance()->getRandShapeName(shapeType::kShapeF, minRandLevel, maxRandLeve);
    ShapeName *lastName = ShapeNameContainer::getInstance()->getRandShapeName(shapeType::kShapeF, minRandLevel, maxRandLeve);
    setNameAndClassNumber(firstName,midName,lastName);
    log("changeRandShape %d,%d,%d", firstName->getFirstNumber(),midName->getMidNumber(),midName->getLastNumber());
    setStatus();
    changeImage();

}
void ShapeF::changeFindShape(int firstIndex,int midIndex, int lastIndex)
{
    setLegendValue(false);
    ShapeName *firstName = ShapeNameContainer::getInstance()->getFindShapeName(shapeType::kShapeF, firstIndex);
    ShapeName *midName = ShapeNameContainer::getInstance()->getFindShapeName(shapeType::kShapeF, midIndex);
    ShapeName *lastName = ShapeNameContainer::getInstance()->getFindShapeName(shapeType::kShapeF,lastIndex);
    setNameAndClassNumber(firstName,midName,lastName);
    setStatus();
    changeImage();
}

void ShapeF::setStatus()
{
    if(isLegend())
    {
        _shapeData->_class->setShapeValue(3.0f);
        Vector<Ref *> *skillArray = ShapeSkillContainer::getInstance()->getShapeArray(shapeType::kShapeF);
        ShapeObject *statusObject = getStatusObject(-1);
        _shapeData->_power->setShapeValue(statusObject->_power->getShapeValue());
        ShapeObject *skill = (ShapeObject *)skillArray->at(0);
        _shapeData->_skill1 = skill->_skill1;
        statusObject = getStatusObject(-1);
        _shapeData->_agility->setShapeValue(statusObject->_agility->getShapeValue());
        skill = (ShapeObject *)skillArray->at(0);
        _shapeData->_skill2 = skill->_skill2;
        _shapeData->_skill3 = skill->_skill3;
        statusObject = getStatusObject(-1);
        _shapeData->_health->setShapeValue(statusObject->_health->getShapeValue()+_shapeData->_plusMaxHealth->getShapeValue());
        _shapeData->_maxHealth->setShapeValue(statusObject->_health->getShapeValue());
        skill = (ShapeObject *)skillArray->at(0);
        _shapeData->_skill4 = skill->_skill4;
    }
    else
    {
        checkEvolution();
        Vector<Ref *> *skillArray = ShapeSkillContainer::getInstance()->getShapeArray(shapeType::kShapeF);
        int classNumber = _shapeData->_name->getFirstNumber();
        ShapeObject *statusObject = getStatusObject(classNumber);
        _shapeData->_power->setShapeValue(statusObject->_power->getShapeValue());
        ShapeObject *skill = (ShapeObject *)skillArray->at(classNumber);
        _shapeData->_skill1 = skill->_skill1;
        
        classNumber = _shapeData->_name->getMidNumber();
        statusObject = getStatusObject(classNumber);
        _shapeData->_agility->setShapeValue(statusObject->_agility->getShapeValue());
        skill = (ShapeObject *)skillArray->at(classNumber);
        _shapeData->_skill2 = skill->_skill2;
        _shapeData->_skill3 = skill->_skill3;
        
        classNumber = _shapeData->_name->getLastNumber();
        statusObject = getStatusObject(classNumber);
        _shapeData->_health->setShapeValue(statusObject->_health->getShapeValue()+_shapeData->_plusMaxHealth->getShapeValue());
        _shapeData->_maxHealth->setShapeValue(statusObject->_health->getShapeValue());
        skill = (ShapeObject *)skillArray->at(classNumber);
        _shapeData->_skill4 = skill->_skill4;
    }
}
ShapeObject *ShapeF::getStatusObject(int index)
{
    ShapeObject *statusObject = ShapeObject::create();
    switch (index) {
        case -1: //전설
            statusObject->_power->setShapeValue(20);
            statusObject->_agility->setShapeValue(20);
            break;
        case 0:
            statusObject->_power->setShapeValue(14);
            statusObject->_agility->setShapeValue(9);
            break;
        case 1:
            statusObject->_power->setShapeValue(12);
            statusObject->_agility->setShapeValue(11);
            break;
        case 2:
            statusObject->_power->setShapeValue(10);
            statusObject->_agility->setShapeValue(6);
            break;
        case 3:
            statusObject->_power->setShapeValue(9);
            statusObject->_agility->setShapeValue(8);
            break;
        case 4:
            statusObject->_power->setShapeValue(9);
            statusObject->_agility->setShapeValue(6);
            break;
        case 5:
            statusObject->_power->setShapeValue(8);
            statusObject->_agility->setShapeValue(7);
            break;
        case 6:
            statusObject->_power->setShapeValue(8);
            statusObject->_agility->setShapeValue(5);
            break;
        case 7:
            statusObject->_power->setShapeValue(7);
            statusObject->_agility->setShapeValue(6);
            break;
        case 8:
            statusObject->_power->setShapeValue(7);
            statusObject->_agility->setShapeValue(4);
            break;
        case 9:
            statusObject->_power->setShapeValue(6);
            statusObject->_agility->setShapeValue(5);
            break;
        default:
            statusObject->_power->setShapeValue(6);
            statusObject->_agility->setShapeValue(5);
            break;
    }
    
    float health = 0;
    float power = statusObject->_power->getShapeValue();
    float agility = statusObject->_agility->getShapeValue();
    float level = _shapeData->_level->getShapeValue();
    float classPower =  20*statusObject->_class->getShapeValue();
    float classAgility =  20*statusObject->_class->getShapeValue();
    power = power*level;
    agility = agility*level;
    float baseHealth = 50.0f;
    if(level>=SKILL_FOUR)
    {
        health = ((power+power*1.5f+power*2.5f)+classPower)*4;
    }
    else if(level>=SKILL_THREE)
    {
        health = ((power+power*1.5f)+classPower)*4;
    }
    else
    {
        health = ((power+power*0.4f)+classPower)*4;
    }
    statusObject->_power->setShapeValue(power+classPower);
    statusObject->_agility->setShapeValue(agility+classAgility);
    statusObject->_health->setShapeValue(health+baseHealth);
    return statusObject;
}

