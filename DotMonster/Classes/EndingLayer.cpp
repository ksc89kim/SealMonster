//
//  EndingLayer.cpp
//  DotMonster
//
//  Created by 김선철 on 2016. 2. 1..
//
//

#include "EndingLayer.h"
#include "TextDb.h"

EndingLayer *EndingLayer::create()
{
    EndingLayer * ret = new EndingLayer();
    if (ret && ret->initWithColor(Color4B::WHITE))
    {
        ret->setImage();
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}


void EndingLayer::setImage()
{
    Label *label = Label::createWithTTF(TextDb::getInstance()->getEtcText(23), CommonUtils::getFontName(), 30);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    label->setVerticalAlignment(TextVAlignment::CENTER);
    label->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height+label->getContentSize().height/2));
    label->setTextColor(Color4B::BLACK);
    this->addChild(label);
    label->runAction(Sequence::create(MoveTo::create(10.0f, Vec2(this->getContentSize().width/2,-label->getContentSize().height/2)),
                                      CallFunc::create(CC_CALLBACK_0(EndingLayer::end, this)), NULL));
    
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    auto positionListener = EventListenerTouchOneByOne::create();
    positionListener->setSwallowTouches(true);
    positionListener->onTouchBegan = CC_CALLBACK_2(EndingLayer::onTouchBegan, this);
    positionListener->onTouchMoved = CC_CALLBACK_2(EndingLayer::onTouchMoved, this);
    positionListener->onTouchEnded = CC_CALLBACK_2(EndingLayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(positionListener, this);
}

bool EndingLayer::onTouchBegan(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    return true;
}
void EndingLayer::onTouchMoved(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    
}
void EndingLayer::onTouchEnded(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());

}
void EndingLayer::end()
{
    this->removeFromParent();
}