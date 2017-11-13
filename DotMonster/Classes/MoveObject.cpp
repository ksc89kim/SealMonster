//
//  MoveObject.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 10. 19..
//
//

#include "MoveObject.h"

MoveObject::MoveObject()
{
    _way = 0;
    _maxMoveRange = 0;
    _minMoveRange = 0;
    _gap = 0;
}
MoveObject::~MoveObject()
{
    
}

MoveObject *MoveObject::create(const char*fileName)
{
    MoveObject *sprite = new (std::nothrow) MoveObject();
    if (sprite && sprite->initWithFile(fileName))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}
void MoveObject::setMoveRange(Node *target)
{
    _maxMoveRange = target->getContentSize().width;
    _minMoveRange = 0;
    _way = 0;
    this->setPosition(Vec2(_minMoveRange, target->getContentSize().height+this->getContentSize().height/2-70));
}
void MoveObject::move()
{
    float distance = checkDistance();
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(MoveObject::move, this));
    MoveTo *moveTo = MoveTo::create(getTime(distance), Vec2(this->getPositionX()+distance, this->getPositionY()));
    this->runAction(Sequence::create(moveTo, func, NULL));
}
float MoveObject::getTime(float distance)
{
    distance = (distance>0)?distance:distance*-1;
    int probability = (20-_gap>3)? 20-_gap:3;
    float time = 1.0f;
    if(_gap>0)
    {
        switch (arc4random()%probability) {
            case 0:
                time = 1.3f;
                break;
            case 1:
                time = 1.6f;
                break;
            case 2:
                time = 0.8f;
                break;
        }
    }
    float speed =  time/_maxMoveRange;
    return speed*distance;
}
float MoveObject::checkDistance()
{

    int probability = (20-_gap>2)? 20-_gap:2;
    float distance = this->getPositionX();
    if(_way)
        _way = 0;
    else
    {
        _way = 1;
        distance = _maxMoveRange - this->getPositionX();
    }
    int distance2 = (int)distance;
    if(arc4random()%probability==0 && _gap>0)
    {
        distance = (arc4random() % ((distance2/3)*2)) + (distance2/3);
    }
    return (_way>0)?distance:distance*-1;
}