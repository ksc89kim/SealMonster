//
//  StampCharge.cpp
//  DotMonster
//
//  Created by 김선철 on 2015. 10. 7..
//
//

#include "Hospital.h"
#include "Player.h"
#include "TextDb.h"

HospitalLayer *HospitalLayer::create(Node *beforeLayer)
{
    HospitalLayer * ret = new HospitalLayer();
    if (ret && ret->initWithColor(Color4B::WHITE))
    {
        ret->_beforeLayer = beforeLayer;
        ret->setImage();
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}


void HospitalLayer::setImage()
{
    if(_beforeLayer!=nullptr)
        _beforeLayer->setVisible(false);
    
    _isTyping = false;
    _index = 0;
    _healBorder = nullptr;
    _isExit = false;
    
    Player::getInstance()->pauseMusic();

    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    auto positionListener = EventListenerTouchOneByOne::create();
    positionListener->setSwallowTouches(true);
    positionListener->onTouchBegan = CC_CALLBACK_2(HospitalLayer::onTouchBegan, this);
    positionListener->onTouchMoved = CC_CALLBACK_2(HospitalLayer::onTouchMoved, this);
    positionListener->onTouchEnded = CC_CALLBACK_2(HospitalLayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(positionListener, this);
    
    _talkBorder = (Sprite *)Scale9Sprite::create("border.png");
    _talkBorder->setContentSize(Size(this->getContentSize().width-50,250));
    _talkBorder->setPosition(Vec2(this->getContentSize().width/2,this->getContentSize().height*0.25));
    _talkBorder->ignoreAnchorPointForPosition(false);
    _content = Label::createWithTTF("",CommonUtils::getFontName(),FONT_SIZE);
    _content->setDimensions(_talkBorder->getContentSize().width-40, _talkBorder->getContentSize().height-40);
    _content->setVerticalAlignment(TextVAlignment::CENTER);
    _content->setHorizontalAlignment(TextHAlignment::LEFT);
    _content->setColor(Color3B(0,0,0));
    _content->setPosition(Vec2(_talkBorder->getContentSize().width/2,_talkBorder->getContentSize().height/2));
    _talkBorder->addChild(_content);
    this->addChild(_talkBorder);
    
    Sprite *title = CommonUtils::createLabelBorder(TextDb::getInstance()->getEtcText(8) , Size(150,100));
    title->setPosition(CommonUtils::changePosition(Vec2(100,550)));
    this->addChild(title);
    
    _talkArray.push_back(TextDb::getInstance()->getEtcText(6).c_str());
    __String *string = __String::createWithFormat(TextDb::getInstance()->getEtcText(7).c_str(), HOSPITAL_PRICE);
    _talkArray.push_back(string->getCString());
    nextSetting();
}

void HospitalLayer::nextTyping(float delayTime)
{
    
    if(_content->getString().size()<_currentTalk.size())
    {
        string temp;
        for(int i=1;i<=3;i++) //한글 버전.
        {
            if((_currentTalk.at(_content->getString().size()+i-1) & 0x80)==0x80)
            {
                temp += _currentTalk.at(_content->getString().size()+i-1);
            }
            else
            {
                temp = _currentTalk.at(_content->getString().size()+i-1);
                break;
            }
        }
        _content->setString(_content->getString()+temp);
    }
    else{
        nextSetting();
    }
}
void HospitalLayer::nextSetting()
{
    this->unschedule(schedule_selector(HospitalLayer::nextTyping));
    if(_isTyping)
    {
        
        _content->setString(_currentTalk);
        _isTyping = false;
        if(_index>=_talkArray.size())
        {
            setHealLayer();
        }
    }
    else
    {
        
        if(_index<_talkArray.size())
        {
            _content->setString("");
            _currentTalk = _talkArray.at(_index);
            _index++;
        }
        else
        {
            if(_isExit)
            {
                clickExit(nullptr);
                return;
            }
        }
        this->schedule(schedule_selector(HospitalLayer::nextTyping));
        _isTyping = true;
    }

}
void HospitalLayer::setHealLayer()
{
    if(_healBorder==nullptr && !_isExit)
    {
        _healBorder = (Sprite *)Scale9Sprite::create("border.png");
        _healBorder->setContentSize(Size(230,250));
        _healBorder->setPosition(CommonUtils::changePosition(Vec2(835,470)));
        _healBorder->ignoreAnchorPointForPosition(false);
        
        __String *string = __String::createWithFormat(TextDb::getInstance()->getEtcText(1).c_str(), (int)Player::getInstance()->getGold());
        Label *goldLabel = Label::createWithTTF(string->getCString(), CommonUtils::getFontName(), FONT_SIZE);
        goldLabel->setColor(Color3B::BLACK);
        goldLabel->setPosition(Vec2(_healBorder->getContentSize().width/2, _healBorder->getContentSize().height/2+60));
        _healBorder->addChild(goldLabel);
        
        MenuItem *charge = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(2), Size(100,50),CC_CALLBACK_1(HospitalLayer::clickHeal, this));
        MenuItem *exit = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(3), Size(100,50),CC_CALLBACK_1(HospitalLayer::clickExit, this));
        Menu *menu = Menu::create(charge,exit, nullptr);
        menu->alignItemsVerticallyWithPadding(10);
        menu->setPosition(Vec2(_healBorder->getContentSize().width/2, _healBorder->getContentSize().height/2-20));
        _healBorder->addChild(menu);
        this->addChild(_healBorder);
    }
}
bool HospitalLayer::onTouchBegan(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    return true;
}
void HospitalLayer::onTouchMoved(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    
}
void HospitalLayer::onTouchEnded(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    nextSetting();
}

void HospitalLayer::clickHeal(Ref *pSender)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    Player *player = Player::getInstance();
    _talkArray.clear();
    _index = 0;
    if(player->getGold()>=HOSPITAL_PRICE)
    {
        _healBorder->setVisible(false);
        _talkArray.push_back(TextDb::getInstance()->getEtcText(4));
        _isExit = true;
        player->minusGold(HOSPITAL_PRICE);
        player->recoveryMonster();
        nextSetting();
    }
    else
    {
        _talkArray.push_back(TextDb::getInstance()->getEtcText(5));
        nextSetting();
    }
}
void HospitalLayer::clickExit(Ref *pSender)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    Player::getInstance()->resumeMusic();
    _beforeLayer->setVisible(true);
    this->removeFromParent();
}