//
//  LoadingLayer.cpp
//  DotMonster
//
//  Created by 김선철 on 2016. 2. 2..
//
//

#include "LoadingLayer.h"

LoadingLayer::LoadingLayer()
{
    
}
LoadingLayer::~LoadingLayer()
{
    stopLoading();
}
LoadingLayer *LoadingLayer::create()
{
    LoadingLayer *ret = new (std::nothrow) LoadingLayer();
    if (ret && ret->initWithColor(Color4B(0,0,0,150)))
    {
        ret->setClickRemove(false);
        ret->setClickVisible(false);
        ret->setImage();
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}
void LoadingLayer::setImage()
{
    _firstLabel = Label::createWithTTF("Loading.", CommonUtils::getFontName(), 30);
    _firstLabel->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    _firstLabel->setVisible(true);
    this->addChild(_firstLabel);
    
    _twoLabel = Label::createWithTTF("Loading..", CommonUtils::getFontName(), 30);
    _twoLabel->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    _twoLabel->setVisible(false);
    this->addChild(_twoLabel);
    
    _threeLabel = Label::createWithTTF("Loading...", CommonUtils::getFontName(), 30);
    _threeLabel->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    _threeLabel->setVisible(false);
    this->addChild(_threeLabel);
    
}
void LoadingLayer::startLoading()
{
    this->schedule(schedule_selector(LoadingLayer::schedulLabel), 0.2f);
}
void LoadingLayer::stopLoading()
{
    this->unschedule(schedule_selector(LoadingLayer::schedulLabel));
}
void LoadingLayer::schedulLabel(float dt)
{
    if(_firstLabel->isVisible())
    {
        _firstLabel->setVisible(false);
        _twoLabel->setVisible(true);
        _threeLabel->setVisible(false);
    }
    else if(_twoLabel->isVisible())
    {
        _firstLabel->setVisible(false);
        _twoLabel->setVisible(false);
        _threeLabel->setVisible(true);
    }
    else if(_threeLabel->isVisible())
    {
        _firstLabel->setVisible(true);
        _twoLabel->setVisible(false);
        _threeLabel->setVisible(false);
    }
}