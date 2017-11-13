//
//  ShapeCommon.cpp
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 2..
//
//

#include "ShapeCommon.h"
#include "ShapeF.h"
#include "ShapeW.h"
#include "ShapeT.h"
#include "ShapeI.h"
#include "ShapeZ.h"
#include "Player.h"

ShapeCommon::ShapeCommon():
_isSizeTest(false),_bgColor(nullptr)
{
    _shapeData = ShapeObject::create();
    this->addChild(_shapeData);

}

ShapeCommon::~ShapeCommon()
{
    
}

bool ShapeCommon::expUp(float exp)
{
    _shapeData->_exp->addShapeValue(exp);
    float maxExp = getMaxExp();
    if(_shapeData->_exp->getShapeValue()>=maxExp)
    {
        _shapeData->_level->addShapeValue(1);
        _shapeData->_exp->setShapeValue(0);
        switch (arc4random() % 5) {
            case 0:
                _shapeData->_plusPower->addShapeValue(2.0f);
                break;
            case 1:
                _shapeData->_plusAgility->addShapeValue(2.0f);
                break;
            case 2:
                _shapeData->_plusMaxHealth->addShapeValue(20.0f);
                break;
            case 3:
                _shapeData->_plusPower->addShapeValue(1.0f);
                _shapeData->_plusMaxHealth->addShapeValue(10.0f);
                break;
            case 4:
                _shapeData->_plusMaxHealth->addShapeValue(10.0f);
                _shapeData->_plusAgility->addShapeValue(1.0f);
                break;
            default:
                break;
        }
        ItemContainer  *container =  Player::getInstance()->_itemList;
        Item *zailLoon = container->getItem(ItemType::kItemTypeZailLoon);
        Item *qailLoon = container->getItem(ItemType::kItemTypeQailLoon);
        Item *nailLoon = container->getItem(ItemType::kItemTypeNailLoon);
        if(zailLoon!=nullptr && arc4random()%5==1)
        {
            _shapeData->_plusMaxHealth->addShapeValue((zailLoon->getItemLevel()*10)+10);
        }
        if(qailLoon!=nullptr && arc4random()%5==1)
        {
            _shapeData->_plusAgility->addShapeValue((qailLoon->getItemLevel()*1)+1);
        }
        if(nailLoon!=nullptr&& arc4random()%5==1)
        {
            _shapeData->_plusPower->addShapeValue((qailLoon->getItemLevel()*1)+1);
        }
        setStatus();
        return true;
    }
    return false;
}
float ShapeCommon::getMaxExp()
{
    float level = _shapeData->_level->getShapeValue();
    float maxExp = (level*3)*level;
    if(level<=8)
    {
        maxExp = level*3;
    }
    return maxExp;
}
void ShapeCommon::logStatus()
{
    log("------Shape Status-----");
    log("class %d,%d,%d", _shapeData->_name->getFirstNumber(),_shapeData->_name->getMidNumber(),_shapeData->_name->getLastNumber());
    log("name = %s", getFullName());
    log("level = %f", _shapeData->_level->getShapeValue());
    log("power = %f", _shapeData->_power->getShapeValue());
    log("plusPower = %f", _shapeData->_plusPower->getShapeValue());
    log("agility = %f", _shapeData->_agility->getShapeValue());
    log("plusAgility = %f", _shapeData->_plusAgility->getShapeValue());
    log("exp = %f", _shapeData->_exp->getShapeValue());
    log("maxExp = %f", getMaxExp());
    log("hp = %f", _shapeData->_health->getShapeValue());
    log("maxHp = %f", _shapeData->_maxHealth->getShapeValue());
    log("plusMaxHp = %f", _shapeData->_plusMaxHealth->getShapeValue());

    log("------Shape Status-----");

}
void ShapeCommon::setLegend(bool isLegend)
{
    if(isLegend)
    {
        setLegendValue(true);
        setName();
        setStatus();
        changeImage();
    }
    else
    {
        setLegendValue(false);
        setName();
        setStatus();
        changeImage();
    }
}
void ShapeCommon::setLegendValue(bool isLegend)
{
    if(isLegend)
    {
        _shapeData->_isLegend->setShapeValue(1.0f);
    }
    else
    {
        _shapeData->_isLegend->setShapeValue(0.0f);
    }
}
bool ShapeCommon::getLegendValue()
{
    return _shapeData->_isLegend->getShapeValue()>0?true:false;
}
void ShapeCommon::setClassScale()
{
    if(_shapeData->_class->getShapeValue()==1)
    {
        this->setScale(0.4f, 0.4f);
    }
    else if(_shapeData->_class->getShapeValue()==2)
    {
        this->setScale(0.5f, 0.5f);
    }
    else if(_shapeData->_class->getShapeValue()==3)
    {
        this->setScale(0.6f, 0.6f);
    }
    
    if(_isSizeTest) //test
    {
        if(_bgColor==nullptr)
        {
            _bgColor = LayerColor::create(Color4B(150,150,150,150), this->getContentSize().width, this->getContentSize().height);
            this->addChild(_bgColor);
        }
        else
        {
            _bgColor->setContentSize(this->getContentSize());
        }
    }
}
void ShapeCommon::checkEvolution()
{
    if(_shapeData->_level->getShapeValue()>=SKILL_FOUR)
    {
        _shapeData->_class->setShapeValue(3);
    }
    else if(_shapeData->_level->getShapeValue()>=SKILL_THREE)
    {
        _shapeData->_class->setShapeValue(2);
    }
    else
    {
        _shapeData->_class->setShapeValue(1);
    }
}
void ShapeCommon::setNameAndClassNumber(ShapeName *firstName, ShapeName *midName, ShapeName *lastName)
{
    this->setAnchorPoint(Vec2(0.5f,0.0f));
    
    _shapeData->_name->setName(firstName->getFirstName(),midName->getMidName(),lastName->getLastName());
    _shapeData->_name->setNumber(firstName->getFirstNumber(), midName->getMidNumber(), lastName->getLastNumber());
    
    _shapeData->_name->_class2->setName(firstName->_class2->getFirstName(), midName->_class2->getMidName(), lastName->_class2->getLastName());
    _shapeData->_name->_class2->setNumber(firstName->_class2->getFirstNumber(), midName->_class2->getMidNumber(), lastName->_class2->getLastNumber());

    _shapeData->_name->_class3->setName(firstName->_class3->getFirstName(), midName->_class3->getMidName(), lastName->_class3->getLastName());
    _shapeData->_name->_class3->setNumber(firstName->_class3->getFirstNumber(), midName->_class3->getMidNumber(), lastName->_class3->getLastNumber());
}
bool ShapeCommon::isLegend()
{
    return _shapeData->_isLegend->getShapeValue();
}
void ShapeCommon::damageAnimation(float delayTime)
{
    this->_imageMid->runAction(Sequence::create(DelayTime::create(0.1f+delayTime),FadeOut::create(0.2f),FadeIn::create(0.2f),FadeOut::create(0.2f),FadeIn::create(0.2f), NULL));
    this->_imageTop->runAction(Sequence::create(DelayTime::create(0.1f+delayTime),FadeOut::create(0.2f),FadeIn::create(0.2f),FadeOut::create(0.2f),FadeIn::create(0.2f), NULL));
    this->runAction(Sequence::create(DelayTime::create(0.1f+delayTime),FadeOut::create(0.2f),FadeIn::create(0.2f),FadeOut::create(0.2f),FadeIn::create(0.2f), NULL));
}
void ShapeCommon::stopAnimation()
{
    float scale = 1.0f/this->getScale();
    Label *stopLabel = Label::createWithTTF("STOP!!", CommonUtils::getFontName(), 50);
    stopLabel->setTextColor(Color4B::BLACK);
    stopLabel->setScale(scale);
    float targetSizeY = this->getContentSize().height/2;
    stopLabel->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    stopLabel->runAction(Sequence::create(MoveTo::create(0.5f, Vec2(stopLabel->getPositionX(),stopLabel->getPositionY()+targetSizeY+50)),CallFuncN::create(CC_CALLBACK_1(ShapeCommon::removeAnimation, this)),NULL));
    this->addChild(stopLabel);
    
    Vec2 originalPosition = this->getPosition();
    this->runAction(Sequence::create(MoveTo::create(0.1f, Vec2(originalPosition.x+10,originalPosition.y)),MoveTo::create(0.1f, Vec2(originalPosition.x-10,originalPosition.y)),
                                     MoveTo::create(0.1f, Vec2(originalPosition.x+10,originalPosition.y)),MoveTo::create(0.1f, Vec2(originalPosition.x-10,originalPosition.y)),
                                     MoveTo::create(0.1f, Vec2(originalPosition.x,originalPosition.y)),NULL));
}
void ShapeCommon::debufAnimation(float delayTime)
{
    this->runAction(Sequence::create(DelayTime::create(0.1f+delayTime), CallFunc::create(CC_CALLBACK_0(ShapeCommon::startDebufAnimation, this)),NULL));

}
void ShapeCommon::startDebufAnimation()
{
    if(_shapeData->_isDebufAnimation)
    {
        stopDebufAnimation();
        startDebufAnimation();
    }
    else
    {
        Action *action1 = RepeatForever::create(Sequence::create(TintTo::create(0.3f, 0, 0, 0),TintTo::create(0.3f, 255, 255, 255),NULL));
        action1->setTag(kDebuf);
        Action *action2 = RepeatForever::create(Sequence::create(TintTo::create(0.3f, 0, 0, 0),TintTo::create(0.3f, 255, 255, 255),NULL));
        action2->setTag(kDebuf);
        Action *action3 = RepeatForever::create(Sequence::create(TintTo::create(0.3f, 0, 0, 0),TintTo::create(0.3f, 255, 255, 255),NULL));
        action3->setTag(kDebuf);
        
        this->runAction(action1);
        this->_imageMid->runAction(action2);
        this->_imageTop->runAction(action3);
        
        
        float scale = 1.0f/this->getScale();
        Label *debufLabel = Label::createWithTTF("DEBUF!!", CommonUtils::getFontName(), 50);
        debufLabel->setTextColor(Color4B::BLACK);
        debufLabel->setScale(scale);
        float targetSizeY = this->getContentSize().height/2;
        debufLabel->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
        debufLabel->runAction(Sequence::create(MoveTo::create(0.5f, Vec2(debufLabel->getPositionX(),debufLabel->getPositionY()+targetSizeY+50)),CallFuncN::create(CC_CALLBACK_1(ShapeCommon::removeAnimation, this)),NULL));
        this->addChild(debufLabel);
        
        _shapeData->_isDebufAnimation = true;
    }
}
void ShapeCommon::stopDebufAnimation()
{
    if(_shapeData->_isDebufAnimation)
    {
        this->runAction(TintTo::create(0.2f, 255, 255, 255));
        this->_imageMid->runAction(TintTo::create(0.2f, 255, 255, 255));
        this->_imageTop->runAction(TintTo::create(0.2f, 255, 255, 255));
        
        this->stopActionByTag(kDebuf);
        this->_imageMid->stopActionByTag(kDebuf);
        this->_imageTop->stopActionByTag(kDebuf);
        _shapeData->_isDebufAnimation = false;
    }
}
void ShapeCommon::missAnimation()
{
    float scale = 1.0f/this->getScale();
    Label *missLabel = Label::createWithTTF("MISS!!", CommonUtils::getFontName(), 50);
    missLabel->setTextColor(Color4B::BLACK);
    missLabel->setScale(scale);
    float targetSizeY = this->getContentSize().height/2;
    missLabel->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    missLabel->runAction(Sequence::create(MoveTo::create(0.5f, Vec2(missLabel->getPositionX(),missLabel->getPositionY()+targetSizeY+50)),CallFuncN::create(CC_CALLBACK_1(ShapeCommon::removeAnimation, this)),NULL));
    this->addChild(missLabel);
}
void ShapeCommon::catchFailAnimation()
{
    float scale = 1.0f/this->getScale();
    Label *catchFail = Label::createWithTTF("FAIL", CommonUtils::getFontName(), 50);
    catchFail->setTextColor(Color4B::BLACK);
    catchFail->setScale(scale);
    float targetSizeY = this->getContentSize().height/2;
    catchFail->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    catchFail->runAction(Sequence::create(MoveTo::create(0.5f, Vec2(catchFail->getPositionX(),catchFail->getPositionY()+targetSizeY+50)),CallFuncN::create(CC_CALLBACK_1(ShapeCommon::removeAnimation, this)),NULL));
    this->addChild(catchFail);
}

void ShapeCommon::removeAnimation(Node *target)
{
    target->removeFromParent();
}
ShapeCommon *ShapeCommon::copyShapeCommonImage(ShapeCommon *copyObject)
{
    ShapeCommon *monster = nullptr;
    ShapeF *myShapeF = dynamic_cast<ShapeF *>(copyObject);
    ShapeW *myShapeW = dynamic_cast<ShapeW *>(copyObject);
    ShapeT *myShapeT = dynamic_cast<ShapeT *>(copyObject);
    ShapeI *myShapeI = dynamic_cast<ShapeI *>(copyObject);
    ShapeZ *myShapeZ = dynamic_cast<ShapeZ *>(copyObject);
    if(myShapeF!=NULL)
    {
        monster = ShapeF::create();
    }
    else if(myShapeW!=NULL)
    {
        monster = ShapeW::create();
    }
    else if(myShapeT!=NULL)
    {
        monster = ShapeT::create();
    }
    else if(myShapeI!=NULL)
    {
        monster = ShapeI::create();
    }
    else if(myShapeZ!=NULL)
    {
        monster = ShapeZ::create();
    }
    monster->_shapeData->_level->setShapeValue(copyObject->_shapeData->_level->getShapeValue());
    monster->changeFindShape(copyObject->_shapeData->_name->_firstNumber->getShapeValue(),
                             copyObject->_shapeData->_name->_midNumber->getShapeValue(), copyObject->_shapeData->_name->_lastNumber->getShapeValue());
    if(copyObject->getLegendValue())
        monster->setLegend(copyObject->getLegendValue());
    
    return monster;
}
ShapeCommon *ShapeCommon::copyShapeCommon(ShapeCommon *copyObject)
{
    ShapeCommon *monster = nullptr;
    monster = copyShapeCommonImage(copyObject);
    monster->_shapeData->copyData(copyObject->_shapeData);
    return monster;
}
void ShapeCommon::setOpacityShape(GLubyte opacity)
{
    _imageTop->setOpacity(opacity);
    _imageMid->setOpacity(opacity);
    this->setOpacity(opacity);
}
void ShapeCommon::setColorShape(const Color3B& color)
{
    _imageTop->setColor(color);
    _imageMid->setColor(color);
    this->setColor(color);
}
Size ShapeCommon::getVisibleContentSize()
{
    Size visibleContentSize = Size(this->getContentSize().width*this->getScaleX(),  this->getContentSize().width*this->getScaleY());
    return visibleContentSize;
}
void ShapeCommon::setFlippedXShape(bool isFlipped)
{
    _imageTop->setFlippedX(isFlipped);
    _imageMid->setFlippedX(isFlipped);
    this->setFlippedX(isFlipped);
}

float ShapeCommon::getClassAll()
{
    float firstNumber = _shapeData->_name->getFirstNumber();
    float midNumber = _shapeData->_name->getMidNumber();
    float lastNumber = _shapeData->_name->getLastNumber();
    return (firstNumber+midNumber+lastNumber)/3;
}
const char* ShapeCommon::getClassAllName()
{
    if(isLegend()) return "L";

    float tempClassNumber = getClassAll();
    int classNumber = getClassAll();
    tempClassNumber = tempClassNumber - classNumber;
    classNumber = (tempClassNumber>0)?classNumber+1:classNumber;
    switch (classNumber) {
        case 0:
            return "SSS";
            break;
        case 1:
            return "SS";
            break;
        case 2:
            return "S";
            break;
        case 3:
            return "A";
            break;
        case 4:
            return "B";
            break;
        case 5:
            return "C";
            break;
        case 6:
            return "D";
            break;
        case 7:
            return "E";
            break;
        case 8:
            return "F";
            break;
        case 9:
            return "G";
            break;
        default:
            break;
    }
    return "G";
}
const char *ShapeCommon::getFullName()
{
    if(!getLegendValue())
    {
        int classNumber = (int)_shapeData->_class->getShapeValue();
        
        switch(classNumber)
        {
            case 2:
                return _shapeData->_name->_class2->getFullName();
                break;
            case 3:
                return _shapeData->_name->_class3->getFullName();
                break;
        }
    }
    return _shapeData->_name->getFullName();
}
void ShapeCommon::setSizeTest(bool isSizeTest)
{
    _isSizeTest = isSizeTest;
    if(_isSizeTest)
    {
        if(_bgColor==nullptr)
        {
            _bgColor = LayerColor::create(Color4B(150,150,150,150), this->getContentSize().width, this->getContentSize().height);
            this->addChild(_bgColor);
        }
        else
        {
            _bgColor->setContentSize(this->getContentSize());
        }
    }
    else
    {
        this->removeChild(_bgColor, true);
        _bgColor = nullptr;
    }
}