//
//  UpgradeLoonShop.cpp
//  DotMonster
//
//  Created by 김선철 on 2016. 3. 13..
//
//

#include "UpgradeLoonShop.h"
#include "TextDb.h"

UpgradeLoonShop *UpgradeLoonShop::create(Node *beforeLayer)
{
    UpgradeLoonShop * ret = new UpgradeLoonShop();
    if (ret && ret->initWithColor(Color4B::WHITE))
    {
        ret->_player = Player::getInstance();
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


void UpgradeLoonShop::setImage()
{
    //if(_beforeLayer!=nullptr)
        //_beforeLayer->setVisible(false);
    
    Player::getInstance()->pauseMusic();
    
    _isTyping = false;
    _index = 0;
    _itemButtonBorder = nullptr;
    _isExit = false;
    _itemListBorder = nullptr;
    _itemIndex = 1;
    _count = 5;
    _itemList.clear();
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    auto positionListener = EventListenerTouchOneByOne::create();
    positionListener->setSwallowTouches(true);
    positionListener->onTouchBegan = CC_CALLBACK_2(UpgradeLoonShop::onTouchBegan, this);
    positionListener->onTouchMoved = CC_CALLBACK_2(UpgradeLoonShop::onTouchMoved, this);
    positionListener->onTouchEnded = CC_CALLBACK_2(UpgradeLoonShop::onTouchEnded, this);
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
    
    Sprite *title = CommonUtils::createLabelBorder(TextDb::getInstance()->getEtcText(76) , Size(150,100));
    title->setPosition(CommonUtils::changePosition(Vec2(100,550)));
    this->addChild(title);
    
    Adaptor::hideAd();
    
    _talkArray.push_back(TextDb::getInstance()->getEtcText(78));
    nextSetting();
}

void UpgradeLoonShop::nextTyping(float delayTime)
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
void UpgradeLoonShop::nextSetting()
{
    this->unschedule(schedule_selector(UpgradeLoonShop::nextTyping));
    if(_isTyping)
    {
        
        _content->setString(_currentTalk);
        _isTyping = false;
        if(_index>=_talkArray.size())
        {
            setItemLayer();
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
        this->schedule(schedule_selector(UpgradeLoonShop::nextTyping));
        _isTyping = true;
    }
    
}
void UpgradeLoonShop::setItemLayer()
{
    if(_itemButtonBorder==nullptr && !_isExit)
    {
        _itemButtonBorder = (Sprite *)Scale9Sprite::create("border.png");
        _itemButtonBorder->setContentSize(Size(230,250));
        _itemButtonBorder->setPosition(CommonUtils::changePosition(Vec2(835,470)));
        _itemButtonBorder->ignoreAnchorPointForPosition(false);
        
        __String *string = __String::createWithFormat(TextDb::getInstance()->getEtcText(1).c_str(), (int)Player::getInstance()->getGold());
        _goldLabel = Label::createWithTTF(string->getCString(), CommonUtils::getFontName(), FONT_SIZE);
        _goldLabel->setColor(Color3B::BLACK);
        _goldLabel->setPosition(Vec2(_itemButtonBorder->getContentSize().width/2, _itemButtonBorder->getContentSize().height/2+60));
        _itemButtonBorder->addChild(_goldLabel);
        
        _upgrade = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(81), Size(100,50),CC_CALLBACK_1(UpgradeLoonShop::clickUpgrade, this));
        _upgrade->setUserObject(Node::create());
        MenuItem *exit = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(3), Size(100,50),CC_CALLBACK_1(UpgradeLoonShop::clickExit, this));
        Menu *menu = Menu::create(_upgrade,exit, nullptr);
        menu->alignItemsVerticallyWithPadding(10);
        menu->setPosition(Vec2(_itemButtonBorder->getContentSize().width/2, _itemButtonBorder->getContentSize().height/2-20));
        _itemButtonBorder->addChild(menu);
        this->addChild(_itemButtonBorder);
    }
    if(_itemListBorder==nullptr&& !_isExit)
    {
        _itemList.clear();
        std::map<unsigned int,ItemData *> list = TextDb::getInstance()->getItemDataMap();
        for(int i=1;i<=list.size();i++)
        {
            ItemData *listData = list[i];
            Item *item = Player::getInstance()->_itemList->getItem(listData->_itemType);
            if(item && listData->_isLoon>0)
                _itemList.push_back(item);
        }
        _itemListBorder = (Sprite *)Scale9Sprite::create("border.png");
        _itemListBorder->setContentSize(Size(400,250));
        _itemListBorder->setPosition(CommonUtils::changePosition(Vec2(450,470)));
        _itemListBorder->ignoreAnchorPointForPosition(false);
        this->addChild(_itemListBorder);
        
        for(int i=1;i<5;i++)
        {
            LayerColor *line = LayerColor::create(Color4B::BLACK, 400, 5);
            line->setPosition(Vec2(0, (50*i)-5));
            _itemListBorder->addChild(line);
        }
        
        MenuItem *left = CommonUtils::createMenuItem("left.png", CC_CALLBACK_0(UpgradeLoonShop::prev, this));
        left->setPosition(Vec2(-left->getContentSize().width/2-10,_itemListBorder->getContentSize().height/2));
        
        MenuItem *right = CommonUtils::createMenuItem("right.png", CC_CALLBACK_0(UpgradeLoonShop::next, this));
        right->setPosition(Vec2(_itemListBorder->getContentSize().width+right->getContentSize().width/2+10,_itemListBorder->getContentSize().height/2));
        
        Menu *button = Menu::create(left,right, NULL);
        button->setPosition(Vec2(0,0));
        _itemListBorder->addChild(button);
        
        
        _countLabel = Label::createWithTTF("",CommonUtils::getFontName(), FONT_SIZE);
        _countLabel->setPosition(Vec2(_itemListBorder->getContentSize().width/2,-30));
        _countLabel->setColor(Color3B::BLACK);
        _itemListBorder->addChild(_countLabel);
        refreshCount();
        refreshImage();
    }
}
bool UpgradeLoonShop::onTouchBegan(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    return true;
}
void UpgradeLoonShop::onTouchMoved(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    
}
void UpgradeLoonShop::onTouchEnded(Touch* touch, Event* event) {
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    nextSetting();
}

void UpgradeLoonShop::clickUpgrade(Ref *pSender)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    Item *item = dynamic_cast<Item *>(_upgrade->getUserObject());
    _talkArray.clear();
    _index = 0;
    if(item)
    {
        int price = 30000;
        if(price>0)
        {
            int gold = (int)_player->getGold();
            if(gold-price>=0)
            {
                _player->minusGold(price);
                __String *string = __String::createWithFormat(TextDb::getInstance()->getEtcText(1).c_str(), (int)Player::getInstance()->getGold());
                _goldLabel->setString(string->getCString());
                int itemLevel = item->getItemLevel();
                int talkLevel = 80;
                if(itemLevel<7)
                {
                    talkLevel=79;
                    Player::getInstance()->_itemList->plusItemUpgrade(item);
                }
                else if(itemLevel>6&&itemLevel<9)
                {
                    if(arc4random()%5==1)
                    {
                        talkLevel=79;
                        Player::getInstance()->_itemList->plusItemUpgrade(item);
                    }
                }
                else if(itemLevel>8&&itemLevel<10)
                {
                    if(arc4random()%20==13)
                    {
                        talkLevel=79;
                        Player::getInstance()->_itemList->plusItemUpgrade(item);
                    }
                }
                else if(itemLevel>9&&itemLevel<13)
                {
                    if(arc4random()%50==25)
                    {
                        talkLevel=79;
                        Player::getInstance()->_itemList->plusItemUpgrade(item);
                    }
                }
                else
                {
                    if(arc4random()%1000==532)
                    {
                        talkLevel=79;
                        Player::getInstance()->_itemList->plusItemUpgrade(item);
                    }
                }
                _talkArray.push_back(TextDb::getInstance()->getEtcText(talkLevel));
                nextSetting();
                refreshImage();
                
            }
            else
            {
                _talkArray.push_back(TextDb::getInstance()->getEtcText(5));
                nextSetting();
            }
        }
    }
    else
    {
        _talkArray.push_back(TextDb::getInstance()->getEtcText(20));
        nextSetting();
    }
}
void UpgradeLoonShop::clickItem(Ref *pSender)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    _index = 0;
    _talkArray.clear();
    Item *item = (Item *)((Node *)pSender)->getUserObject();
    _upgrade->setUserObject(item);
    int price = 30000;
    
    string temp;
    switch (item->_itemType) {
        case ItemType::kItemTypeVailLoon:
        case ItemType::kItemTypeRailLoon:
        case ItemType::kItemTypeZailLoon:
        {
            temp = __String::createWithFormat(item->getItemContent(),(item->getItemLevel()*10)+10)->getCString();
            temp = __String::createWithFormat(TextDb::getInstance()->getEtcText(62).c_str(),temp.c_str())->getCString();
            break;
        }
        case ItemType::kItemTypeQailLoon:
        case ItemType::kItemTypeNailLoon:
        {
            temp = __String::createWithFormat(item->getItemContent(),(item->getItemLevel()*1)+1)->getCString();
            temp = __String::createWithFormat(TextDb::getInstance()->getEtcText(62).c_str(),temp.c_str())->getCString();
            break;
        }
        default:
            temp = __String::createWithFormat(TextDb::getInstance()->getEtcText(62).c_str(),item->getItemContent())->getCString();
            break;
    }
    temp += __String::createWithFormat(TextDb::getInstance()->getEtcText(77).c_str(),item->getItemName(), price)->getCString();

    _talkArray.push_back(temp);
    nextSetting();
}
void UpgradeLoonShop::clickExit(Ref *pSender)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    Player::getInstance()->resumeMusic();
    Adaptor::showAd();
    _beforeLayer->setVisible(true);
    _itemList.clear();
    this->removeFromParent();
}

void UpgradeLoonShop::refreshCount()
{
    int var = (_itemList.size()>0)? (_itemList.size()%_count==0)? _itemList.size()/_count:_itemList.size()/_count+1:1;
    _countLabel->setString(__String::createWithFormat("(%d/%d)",_itemIndex,var)->getCString());
}
void UpgradeLoonShop::refreshImage()
{
    
    _itemListBorder->removeChild(_menu,true);
    
    float space = 5;
    int count = _count;
    _menu= Menu::create();
    _menu->setPosition(Vec2(0, 0));
    int start = count*(_itemIndex-1);
    count = (_itemIndex*count>_itemList.size())? _itemList.size():count*_itemIndex;
    for(int i=_count-1,j=start;j<count;i--,j++)
    {
        Item *item = _itemList.at(j);
        LayerColor *normalLayer =  LayerColor::create(Color4B(0,0,0,0),400,45);
        LayerColor *selectLayer = LayerColor::create(Color4B(0,0,0,150),400,46);
        
        MenuItemSprite *button = MenuItemSprite::create(normalLayer,selectLayer, CC_CALLBACK_1(UpgradeLoonShop::clickItem, this));
        button->setPosition(Vec2(_itemListBorder->getContentSize().width/2, (button->getContentSize().height*i)+(space*i)+button->getContentSize().height/2));
        button->setUserObject(item);
        _menu->addChild(button);
        
        string temp = __String::createWithFormat("%s + (%d)", item->getItemName(),item->getItemLevel())->getCString();
        Label *itemName = Label::createWithTTF(temp,CommonUtils::getFontName(), FONT_SIZE);
        itemName->setPosition(Vec2(10,button->getContentSize().height/2));
        itemName->setColor(Color3B::BLACK);
        itemName->setAnchorPoint(Vec2(0,0.5f));
        button->addChild(itemName);
    }
    _itemListBorder->addChild(_menu);
}

void UpgradeLoonShop::next()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    int var = _itemList.size() % _count;
    var = (var>0)?(_itemList.size()/_count+1):_itemList.size()/_count;
    if(var<=_itemIndex)
        return;
    
    _itemIndex++;
    refreshImage();
    refreshCount();
}

void UpgradeLoonShop::prev()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    if(_itemIndex<2)
        return;
    
    _itemIndex--;
    refreshImage();
    refreshCount();
}