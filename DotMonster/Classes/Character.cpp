//
//  Character.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 15..
//
//

#include "Character.h"
#include "ShapeF.h"

Character::Character()
{
    _characterType = 0;
    _mapSprite = "field/fieldSp.png";
    _monsterList = new Vector<Ref *>();
}

Character::~Character()
{
    if(_monsterList)
        delete _monsterList;

}

Character *Character::create()
{
    Character * ret = new Character();
    if (ret && ret->init())
    {
        ret->setValue();
        ret->setImage();
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void Character::setValue()
{
    
}

void Character::setImage()
{
}

const char*Character::getCharacterMapSprite()
{
    return _mapSprite.c_str();
}
int Character::getCharacterType()
{
    return _characterType;
}
void Character::recoveryMonster()
{
    for(int j=0;j<_monsterList->size();j++)
    {
        ShapeCommon *monster = (ShapeCommon *)_monsterList->at(j);
        monster->_shapeData->_health->setShapeValue(monster->_shapeData->_maxHealth->getShapeValue()+monster->_shapeData->_plusMaxHealth->getShapeValue());
        monster->_shapeData->initData();
    }
}
void Character::dieRecoveryMonster()
{
    for(int i=1;i<=3;i++)
    {
        for(int j=0;j<_monsterList->size();j++)
        {
            ShapeCommon *monster = (ShapeCommon *)_monsterList->at(j);
            if(monster->_shapeData->_select->getShapeValue()==i)
            {
                monster->_shapeData->_health->setShapeValue(monster->_shapeData->_maxHealth->getShapeValue()+monster->_shapeData->_plusMaxHealth->getShapeValue());
                monster->_shapeData->initData();
                break;
            }
        }
    }
}
void Character::initDataMonster()
{
    for(int j=0;j<_monsterList->size();j++)
    {
        ShapeCommon *monster = (ShapeCommon *)_monsterList->at(j);
        monster->_shapeData->initData();
    }
}
void Character::setCharacterType(int type)
{
     _characterType = type;
}
int Character::getMaxLevelMonster()
{
    int maxLevel = 0;
    for(int i=0;i<_monsterList->size();i++)
    {
        ShapeCommon *catchMonster = (ShapeCommon *)_monsterList->at(i);
        if(maxLevel<(int)catchMonster->_shapeData->_level->getShapeValue())
        {
            maxLevel = (int )catchMonster->_shapeData->_level->getShapeValue();
        }
    }
    return maxLevel;
}
int Character::getSelectMaxLevelMonster()
{
    int maxLevel = 0;
    for(int i=1;i<=3;i++)
    {
        for(int j=0;j<_monsterList->size();j++)
        {
            ShapeCommon *catchMonster = (ShapeCommon *)_monsterList->at(j);
            if((int)catchMonster->_shapeData->_select->getShapeValue()==i)
            {
                if(maxLevel<(int)catchMonster->_shapeData->_level->getShapeValue())
                {
                    maxLevel = (int )catchMonster->_shapeData->_level->getShapeValue();
                }
                break;
            }
        }
    }
    return maxLevel;
}