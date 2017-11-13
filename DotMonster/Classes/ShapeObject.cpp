//
//  ShapeObject.cpp
//  ShapeMaster
//
//  Created by 김선철 on 2014. 2. 23..
//
//

#include "ShapeObject.h"


ShapeObject* ShapeObject::create()
{
	ShapeObject * ret = new ShapeObject();
    if (ret && ret->init())
    {
        ret->setValue();
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
	return ret;
}


ShapeObject::ShapeObject()
{
    
    
}
ShapeObject::~ShapeObject()
{
    if(_plusPower)
        _plusPower->release();
    if(_plusAgility)
        _plusAgility->release();
    if(_plusMaxHealth)
        _plusMaxHealth->release();
    if(_power)
        _power->release();
    if(_agility)
        _agility->release();
    if(_debufPower)
        _debufPower->release();
    if(_debufAgility)
        _debufAgility->release();
    if(_health)
        _health->release();
    if(_maxHealth)
        _maxHealth->release();
    if(_exp)
        _exp->release();
    if(_class)
        _class->release();
    if(_level)
        _level->release();
    if(_stopTurn)
        _stopTurn->release();
    if(_debufTurn)
        _debufTurn->release();
    if(_reflectCount)
        _reflectCount->release();
    if(_maxSkillLevel)
        _maxSkillLevel->release();
    if(_select)
        _select->release();
    if(_type)
        _type->release();
    if(_isLegend)
        _isLegend->release();
}

void ShapeObject::setValue()
{
    _isDebufAnimation = false;
    _plusPower = ShapeValue::create("L","R");
    _plusPower->setShapeValue(0);
    _plusAgility = ShapeValue::create("P", "A");
    _plusAgility->setShapeValue(0);
    _plusMaxHealth = ShapeValue::create("P", "H");
    _plusMaxHealth->setShapeValue(0);
    _power = ShapeValue::create("P","R");
    _power->setShapeValue(1);
    _agility = ShapeValue::create("A","Y");
    _agility->setShapeValue(1);
    _debufPower = ShapeValue::create("D","R");
    _debufPower->setShapeValue(0);
    _debufAgility = ShapeValue::create("D","Y");
    _debufAgility->setShapeValue(0);
    _health = ShapeValue::create("H","H");
    _health->setShapeValue(1);
    _maxHealth = ShapeValue::create("M","H");
    _maxHealth->setShapeValue(1);
    _exp = ShapeValue::create("E","P");
    _class = ShapeValue::create("C","S",3);
    _class->setShapeValue(1);
    _level = ShapeValue::create("L","L");
    _level->setShapeValue(1);
    _stopTurn = ShapeValue::create("S","N");
    _debufTurn = ShapeValue::create("D","N");
    _reflectCount = ShapeValue::create("R","T");
    _maxSkillLevel = ShapeValue::create("M", "L");
    _maxSkillLevel->setShapeValue(1);
    _isLegend = ShapeValue::create("I", "L");
    _select = ShapeValue::create("S", "T");
    _select->setShapeValue(0);
    _type = ShapeValue::create("T", "P");
    _name = ShapeName::create();
    _name->_class2 = ShapeName::create();
    _name->addChild(_name->_class2);
    _name->_class3 = ShapeName::create();
    _name->addChild(_name->_class3);
    this->addChild(_name);
    _reflectSkill = ShapeSkill::create();
    this->addChild(_reflectSkill);
    _stopSkill = ShapeSkill::create();
    this->addChild(_stopSkill);
    
}
void ShapeObject::plusHelath(float value)
{
    if(_maxHealth->getShapeValue()+_plusMaxHealth->getShapeValue()>_health->getShapeValue()+value)
        _health->addShapeValue(value);
    else
        _health->setShapeValue(_maxHealth->getShapeValue()+_plusMaxHealth->getShapeValue());

}
void ShapeObject::minusHelath(float value)
{
    if(0<=_health->getShapeValue()-value)
        _health->minusShapeValue(value);
    else
        _health->setShapeValue(0);
}
void ShapeObject::initData()
{
    _stopTurn->setShapeValue(0);
    _debufTurn->setShapeValue(0);
    _reflectCount->setShapeValue(0);
    _debufAgility->setShapeValue(0);
    _debufPower->setShapeValue(0);
}
void ShapeObject::copyData(ShapeObject *data)
{
    _isDebufAnimation = data->_isDebufAnimation;
    _name->copy(data->_name);
    _plusPower->setShapeValue(data->_plusPower->getShapeValue());
    _plusAgility->setShapeValue(data->_plusAgility->getShapeValue());
    _plusMaxHealth->setShapeValue(data->_plusMaxHealth->getShapeValue());
    _power->setShapeValue(data->_power->getShapeValue());
    _agility->setShapeValue(data->_agility->getShapeValue());
    _debufPower->setShapeValue(data->_debufPower->getShapeValue());
    _debufAgility->setShapeValue(data->_debufAgility->getShapeValue());
    _health->setShapeValue(data->_health->getShapeValue());
    _maxHealth->setShapeValue(data->_maxHealth->getShapeValue());
    _exp->setShapeValue(data->_exp->getShapeValue());
    _class->setShapeValue(data->_class->getShapeValue());
    _level->setShapeValue(data->_level->getShapeValue());
    _stopTurn->setShapeValue(data->_stopTurn->getShapeValue());
    _debufTurn->setShapeValue(data->_debufTurn->getShapeValue());
    _reflectCount->setShapeValue(data->_reflectCount->getShapeValue());
    _maxSkillLevel->setShapeValue(data->_maxSkillLevel->getShapeValue());
    _isLegend->setShapeValue(data->_isLegend->getShapeValue());
    _select->setShapeValue(data->_select->getShapeValue());
    _reflectSkill->changeSkillData(data->_reflectSkill);
    _stopSkill->changeSkillData(data->_stopSkill);
    _type->setShapeValue(data->_type->getShapeValue());
}