//
//  StampCharge.cpp
//  DotMonster
//
//  Created by 김선철 on 2015. 10. 7..
//
//

#include "StampCharge.h"
#include "Player.h"
#include "TextDb.h"

StampChargeLayer *StampChargeLayer::create(Node *beforeLayer)
{
    StampChargeLayer * ret = new StampChargeLayer();
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


void StampChargeLayer::setImage()
{
    if(_beforeLayer!=nullptr)
        _beforeLayer->setVisible(false);
    
    _isTyping = false;
    _index = 0;
    _stampBorder = nullptr;
    _isExit = false;
    
    Player::getInstance()->pauseMusic();
    
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    auto positionListener = EventListenerTouchOneByOne::create();
    positionListener->setSwallowTouches(true);
    positionListener->onTouchBegan = CC_CALLBACK_2(StampChargeLayer::onTouchBegan, this);
    positionListener->onTouchMoved = CC_CALLBACK_2(StampChargeLayer::onTouchMoved, this);
    positionListener->onTouchEnded = CC_CALLBACK_2(StampChargeLayer::onTouchEnded, this);
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
    
    Sprite *title = CommonUtils::createLabelBorder(TextDb::getInstance()->getEtcText(9) , Size(150,100));
    title->setPosition(CommonUtils::changePosition(Vec2(100,550)));
    this->addChild(title);
    
    Item *stamp = Player::getInstance()->_itemList->getItem(ItemType::kItemStamp);
    _talkArray.push_back(TextDb::getInstance()->getEtcText(10));
    if(stamp!=nullptr)
    {
        int  count =  (5*stamp->getItemLevel())-stamp->getItemCount();
        __String *string = __String::createWithFormat(TextDb::getInstance()->getEtcText(11).c_str(), count*STAMPCHARGE_PRICE);
        _talkArray.push_back(string->getCString());
    }
    else
    {
        _talkArray.push_back(TextDb::getInstance()->getEtcText(12));
        _isExit = true;
    }
    nextSetting();
}

void StampChargeLayer::nextTyping(float delayTime)
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
void StampChargeLayer::nextSetting()
{
    this->unschedule(schedule_selector(StampChargeLayer::nextTyping));
    if(_isTyping)
    {
        
        _content->setString(_currentTalk);
        _isTyping = false;
        if(_index>=_talkArray.size())
        {
            setStampLayer();
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
        this->schedule(schedule_selector(StampChargeLayer::nextTyping));
        _isTyping = true;
    }

}
void StampChargeLayer::setStampLayer()
{
    if(_stampBorder==nullptr && !_isExit)
    {
        _stampBorder = (Sprite *)Scale9Sprite::create("border.png");
        _stampBorder->setContentSize(Size(230,250));
        _stampBorder->setPosition(CommonUtils::changePosition(Vec2(835,470)));
        _stampBorder->ignoreAnchorPointForPosition(false);
        
        Item *stamp = Player::getInstance()->_itemList->getItem(ItemType::kItemStamp);
        if(stamp)
        {
            __String *string = __String::createWithFormat(TextDb::getInstance()->getEtcText(13).c_str(), stamp->getItemLevel(), stamp->getItemCount(),stamp->getItemLevel()*5,
                                                          (int)Player::getInstance()->getGold());
            Label *stampLabel = Label::createWithTTF(string->getCString(), CommonUtils::getFontName(), FONT_SIZE);
            stampLabel->setColor(Color3B::BLACK);
            stampLabel->setPosition(Vec2(_stampBorder->getContentSize().width/2, _stampBorder->getContentSize().height/2+70));
            _stampBorder->addChild(stampLabel);
        }
        MenuItem *charge = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(14), Size(100,50),CC_CALLBACK_1(StampChargeLayer::clickCharge, this));
        MenuItem *exit = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(3), Size(100,50),CC_CALLBACK_1(StampChargeLayer::clickExit, this));
        Menu *menu = Menu::create(charge,exit, nullptr);
        menu->alignItemsVerticallyWithPadding(10);
        menu->setPosition(Vec2(_stampBorder->getContentSize().width/2, _stampBorder->getContentSize().height/2-30));
        _stampBorder->addChild(menu);
        this->addChild(_stampBorder);
    }
}
bool StampChargeLayer::onTouchBegan(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    return true;
}
void StampChargeLayer::onTouchMoved(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    
}
void StampChargeLayer::onTouchEnded(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    Point location = target->convertToNodeSpace(touch->getLocation());
    nextSetting();
}

void StampChargeLayer::clickCharge(Ref *pSender)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    _talkArray.clear();
    _index = 0;
    Player *player = Player::getInstance();
    Item *stamp = Player::getInstance()->_itemList->getItem(ItemType::kItemStamp);
    int  count =  (5*stamp->getItemLevel())-stamp->getItemCount();
    if(player->getGold()>=(count*STAMPCHARGE_PRICE))
    {
        _stampBorder->setVisible(false);
        _talkArray.push_back(TextDb::getInstance()->getEtcText(15));
        player->_itemList->chargeItem(ItemType::kItemStamp);
        player->minusGold(count*STAMPCHARGE_PRICE);
        _isExit = true;
        nextSetting();
    }
    else
    {
        _talkArray.push_back(TextDb::getInstance()->getEtcText(5));
        nextSetting();
    }
}
void StampChargeLayer::clickExit(Ref *pSender)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    Player::getInstance()->resumeMusic();
    _beforeLayer->setVisible(true);
    this->removeFromParent();
}