//
//  ShapeName.cpp
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 1..
//
//

#include "ShapeName.h"

ShapeName::ShapeName()
{
    _firstName = __String::create("");
    _firstName->retain();
    _midName = __String::create("");
    _midName->retain();
    _lastName = __String::create("");
    _lastName->retain();
    
    _firstNumber = ShapeValue::create("F", "N");
    _midNumber = ShapeValue::create("M", "N");
    _lastNumber = ShapeValue::create("L", "N");

}
ShapeName::~ShapeName()
{
    if(_firstName)
        _firstName->release();
    if(_midName)
        _midName->release();
    if(_lastName)
        _lastName->release();
    
    if(_firstNumber)
        _firstNumber->release();
    if(_midNumber)
        _midNumber->release();
    if(_lastNumber)
        _lastNumber->release();

}

ShapeName *ShapeName::create()
{
    ShapeName * ret = new ShapeName();
    if (ret && ret->init())
    {

        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
	return ret;
    
}
ShapeName *ShapeName::create(const char *firstName, const char *midName, const char *lastName, int classNumber)
{
    return ShapeName::create(firstName, midName, lastName, classNumber, classNumber, classNumber);
}
ShapeName *ShapeName::create(const char *firstName, const char *midName, const char *lastName, int firstNumber, int midNumber, int lastNumber)
{
    ShapeName *pObject = new ShapeName();
    if (pObject)
    {
        pObject->setName(firstName, midName, lastName);
        pObject->setNumber(firstNumber, midNumber, lastNumber);
        pObject->autorelease();
        return pObject;
    }
    CC_SAFE_DELETE(pObject);
    return NULL;
}

void ShapeName::setName(const char *firstName, const char *midName, const char *lastName)
{
    setFirstName(firstName);
    setMidName(midName);
    setLastName(lastName);
}
void ShapeName::setNumber(int firstNumber, int midNumber, int lastNumber)
{
    setFirstNumber(firstNumber);
    setMidNumber(midNumber);
    setLastNumber(lastNumber);
}
void ShapeName::setFirstName(const char *firstName)
{
    _firstName->initWithFormat("%s", firstName);
}
void ShapeName::setMidName(const char *midName)
{
    _midName->initWithFormat("%s", midName);
}
void ShapeName::setLastName(const char *lastName)
{
    _lastName->initWithFormat("%s", lastName);
}
void ShapeName::setFirstNumber(int firstNumber)
{
    _firstNumber->setShapeValue(firstNumber);
}
void ShapeName::setMidNumber(int midNumber)
{
    _midNumber->setShapeValue(midNumber);
}
void ShapeName::setLastNumber(int lastNumber)
{
    _lastNumber->setShapeValue(lastNumber);
}

const char* ShapeName::getFirstName()
{
    return _firstName->getCString();
}
const char* ShapeName::getMidName()
{
    return _midName->getCString();
}
const char* ShapeName::getLastName()
{
    return _lastName->getCString();
}
const char* ShapeName::getFullName()
{
    __String *string = __String::createWithFormat("%s%s%s", _firstName->getCString(), _midName->getCString(), _lastName->getCString());
    return string->getCString();
}

int ShapeName::getFirstNumber()
{
    return _firstNumber->getShapeValue();
}
int ShapeName::getMidNumber()
{
    return _midNumber->getShapeValue();
}
int ShapeName::getLastNumber()
{
    return _lastNumber->getShapeValue();
}
 void ShapeName::copy(ShapeName *name)
{
    setFirstName(name->getFirstName());
    setMidName(name->getMidName());
    setLastName(name->getLastName());
    
    setFirstNumber(name->getFirstNumber());
    setMidNumber(name->getMidNumber());
    setLastNumber(name->getLastNumber());
    
    _class2->setFirstName(name->_class2->getFirstName());
    _class2->setMidName(name->_class2->getMidName());
    _class2->setLastName(name->_class2->getLastName());
    
    _class2->setFirstNumber(name->_class2->getFirstNumber());
    _class2->setMidNumber(name->_class2->getMidNumber());
    _class2->setLastNumber(name->_class2->getLastNumber());
    
    _class3->setFirstName(name->_class3->getFirstName());
    _class3->setMidName(name->_class3->getMidName());
    _class3->setLastName(name->_class3->getLastName());
    
    _class3->setFirstNumber(name->_class3->getFirstNumber());
    _class3->setMidNumber(name->_class3->getMidNumber());
    _class3->setLastNumber(name->_class3->getLastNumber());

}