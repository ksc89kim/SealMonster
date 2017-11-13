//
//  ShapeValue.cpp
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 19..
//
//

#include "ShapeValue.h"


ShapeValue::ShapeValue()
{
}
ShapeValue::~ShapeValue()
{
}
ShapeValue *ShapeValue::create(const char *compareFirstId, const char *compareLastId,int limit)
{
    
    ShapeValue* pRet = new ShapeValue();
    if( pRet&&pRet->initWithFormat("%s0%s", compareFirstId, compareLastId))
    {
        pRet->_compareFirstId = compareFirstId;
        pRet->_compareLastId = compareLastId;
        pRet->_limit = limit;
        pRet->retain();
        pRet->autorelease();
    }
    return pRet;
}

void ShapeValue::setShapeValue(float value)
{
    this->initWithFormat("%s%f%s", _compareFirstId.c_str(),value, _compareLastId.c_str());
}

float ShapeValue::getShapeValue()
{
    std::string checkId = this->getCString();
    std::string firstCheckId = checkId.substr(0,1);
    std::string lastCheckId = checkId.substr(checkId.length()-1);
    if((!_compareFirstId.compare(firstCheckId.c_str())) && (!_compareLastId.compare(lastCheckId.c_str())))
    {
        return atof((checkId.substr(1, checkId.length()-2)).c_str());
    }
    else
    {
        return 0;
    }
    return 0;
}

void ShapeValue::addShapeValue(float value)
{
    if(getShapeValue()<=_limit || _limit==0)
    {
        setShapeValue(getShapeValue()+value);
    }
}
void ShapeValue::minusShapeValue(float value)
{
    setShapeValue(getShapeValue()-value);
}