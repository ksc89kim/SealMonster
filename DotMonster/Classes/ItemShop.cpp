//
//  ItemButton.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 10..
//
//

#include "ItemShop.h"
#include "TextDb.h"

ItemShopLayer *ItemShopLayer::create(Node *beforeLayer)
{
    ItemShopLayer * ret = new ItemShopLayer();
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


void ItemShopLayer::setImage()
{
    if(_beforeLayer!=nullptr)
        _beforeLayer->setVisible(false);
    
    Player::getInstance()->pauseMusic();

    _isTyping = false;
    _index = 0;
    _itemButtonBorder = nullptr;
    _isExit = false;
    _itemListBorder = nullptr;
    _itemIndex = 1;
    _count = 5;
    _shopPriceList.clear();
    auto shapeValue = ShapeValue::create("S", "P");
    shapeValue->setShapeValue(250);
    _shopPriceList[ItemType::kItemTypeResorative1] =  shapeValue;
    shapeValue = ShapeValue::create("S", "P");
    shapeValue->setShapeValue(500);
    _shopPriceList[ItemType::kItemTypeResorative2] = shapeValue;
    shapeValue = ShapeValue::create("S", "P");
    shapeValue->setShapeValue(1000);
    _shopPriceList[ItemType::kItemTypeResorative3] = shapeValue;
    shapeValue = ShapeValue::create("S", "P");
    shapeValue->setShapeValue(30000);
    _shopPriceList[ItemType::kItemTypePlusPower] = shapeValue;
    shapeValue = ShapeValue::create("S", "P");
    shapeValue->setShapeValue(20000);
    _shopPriceList[ItemType::kItemTypePlusAgility] = shapeValue;
    shapeValue = ShapeValue::create("S", "P");
    shapeValue->setShapeValue(10000);
    _shopPriceList[ItemType::kItemTypePlusStamina] = shapeValue;
    shapeValue = ShapeValue::create("S", "P");
    shapeValue->setShapeValue(1000);
    _shopPriceList[ItemType::kItemTypeReturnCity] = shapeValue;
    shapeValue = ShapeValue::create("S", "P");
    shapeValue->setShapeValue(250);
    _shopPriceList[ItemType::kItemTypeEradication] = shapeValue;
    shapeValue = ShapeValue::create("S", "P");
    shapeValue->setShapeValue(250);
    _shopPriceList[ItemType::kItemTypeTemptation] = shapeValue;
    shapeValue = ShapeValue::create("S", "P");
    shapeValue->setShapeValue(500);
    _shopPriceList[ItemType::kItemTypeVisibleCave] = shapeValue;
    shapeValue = ShapeValue::create("S", "P");
    shapeValue->setShapeValue(1500);
    _shopPriceList[ItemType::kItemTypeTransResorative1] = shapeValue;
    shapeValue = ShapeValue::create("S", "P");
    shapeValue->setShapeValue(2000);
    _shopPriceList[ItemType::kItemTypeTransResorative2] = shapeValue;
    shapeValue = ShapeValue::create("S", "P");
    shapeValue->setShapeValue(2500);
    _shopPriceList[ItemType::kItemTypeTransResorative3] = shapeValue;
    
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    auto positionListener = EventListenerTouchOneByOne::create();
    positionListener->setSwallowTouches(true);
    positionListener->onTouchBegan = CC_CALLBACK_2(ItemShopLayer::onTouchBegan, this);
    positionListener->onTouchMoved = CC_CALLBACK_2(ItemShopLayer::onTouchMoved, this);
    positionListener->onTouchEnded = CC_CALLBACK_2(ItemShopLayer::onTouchEnded, this);
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
    
    Sprite *title = CommonUtils::createLabelBorder(TextDb::getInstance()->getEtcText(16) , Size(150,100));
    title->setPosition(CommonUtils::changePosition(Vec2(100,550)));
    this->addChild(title);
    
     Adaptor::hideAd();
    
    _talkArray.push_back(TextDb::getInstance()->getEtcText(17));
    nextSetting();
}

void ItemShopLayer::nextTyping(float delayTime)
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
void ItemShopLayer::nextSetting()
{
    this->unschedule(schedule_selector(ItemShopLayer::nextTyping));
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
        this->schedule(schedule_selector(ItemShopLayer::nextTyping));
        _isTyping = true;
    }
    
}
void ItemShopLayer::setItemLayer()
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
        
        _buy = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(18), Size(100,50),CC_CALLBACK_1(ItemShopLayer::clickBuy, this));
        _buy->setUserObject(Node::create());
        MenuItem *exit = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(3), Size(100,50),CC_CALLBACK_1(ItemShopLayer::clickExit, this));
        Menu *menu = Menu::create(_buy,exit, nullptr);
        menu->alignItemsVerticallyWithPadding(10);
        menu->setPosition(Vec2(_itemButtonBorder->getContentSize().width/2, _itemButtonBorder->getContentSize().height/2-20));
        _itemButtonBorder->addChild(menu);
        this->addChild(_itemButtonBorder);
    }
    if(_itemListBorder==nullptr&& !_isExit)
    {
        _shopList.clear();
        std::map<unsigned int,ItemData *> list = TextDb::getInstance()->getItemDataMap();
        for(int i=1;i<=list.size();i++)
        {
            ItemData *listData = list[i];
            if(listData->_isShop>0)
            {
                _shopList.push_back(listData);
            }
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
        
        MenuItem *left = CommonUtils::createMenuItem("left.png", CC_CALLBACK_0(ItemShopLayer::prev, this));
        left->setPosition(Vec2(-left->getContentSize().width/2-10,_itemListBorder->getContentSize().height/2));
        
        MenuItem *right = CommonUtils::createMenuItem("right.png", CC_CALLBACK_0(ItemShopLayer::next, this));
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
bool ItemShopLayer::onTouchBegan(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    return true;
}
void ItemShopLayer::onTouchMoved(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    
}
void ItemShopLayer::onTouchEnded(Touch* touch, Event* event) {
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    nextSetting();
}

void ItemShopLayer::clickBuy(Ref *pSender)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    ItemData *itemData = dynamic_cast<ItemData *>(_buy->getUserObject());
    _talkArray.clear();
    _index = 0;
    if(itemData)
    {
        int price = isPrice(itemData->_itemType);
        if(price>0)
        {
            int gold = (int)_player->getGold();
            if(gold-price>=0)
            {
                _talkArray.push_back(TextDb::getInstance()->getEtcText(19));
                _player->minusGold(price);
                _player->_itemList->plusItem(itemData->_itemType, 1);
                nextSetting();
                
                __String *string = __String::createWithFormat(TextDb::getInstance()->getEtcText(1).c_str(), (int)Player::getInstance()->getGold());
                _goldLabel->setString(string->getCString());

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
void ItemShopLayer::clickItem(Ref *pSender)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    _index = 0;
     _talkArray.clear();
    ItemData *itemData = (ItemData *)((Node *)pSender)->getUserObject();
    _buy->setUserObject(itemData);
    int price = isPrice(itemData->_itemType);
    if(price>0)
    {
        string temp = __String::createWithFormat(TextDb::getInstance()->getEtcText(62).c_str(),itemData->_itemContent.c_str())->getCString();
        temp += __String::createWithFormat(TextDb::getInstance()->getEtcText(21).c_str(),itemData->_itemName.c_str(), price)->getCString();
        _talkArray.push_back(temp);
    }
    nextSetting();
}
void ItemShopLayer::clickExit(Ref *pSender)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    Player::getInstance()->resumeMusic();
     Adaptor::showAd();
    _beforeLayer->setVisible(true);
    
    for (std::map<unsigned int, ShapeValue*>::iterator it = _shopPriceList.begin(); it != _shopPriceList.end(); it++)
    {
        ShapeValue *value = it->second;
        if(value)
            value->release();
    }
    _shopPriceList.clear();
    _shopList.clear();
    this->removeFromParent();
}

void ItemShopLayer::refreshCount()
{
    int var = (_shopList.size()>0)? (_shopList.size()%_count==0)? _shopList.size()/_count:_shopList.size()/_count+1:1;
    _countLabel->setString(__String::createWithFormat("(%d/%d)",_itemIndex,var)->getCString());
}
void ItemShopLayer::refreshImage()
{
    
    _itemListBorder->removeChild(_menu,true);
    
    float space = 5;
    int count = _count;
    _menu= Menu::create();
    _menu->setPosition(Vec2(0, 0));
    int start = count*(_itemIndex-1);
    count = (_itemIndex*count>_shopList.size())? _shopList.size():count*_itemIndex;
    for(int i=_count-1,j=start;j<count;i--,j++)
    {
        ItemData *itemData = _shopList.at(j);
        int price = 0;
        std::map<unsigned int, ShapeValue*>::iterator it = _shopPriceList.find(itemData->_itemType);
        if (it != _shopPriceList.end())
        {
            price = (int)it->second->getShapeValue();
        }
        LayerColor *normalLayer =  LayerColor::create(Color4B(0,0,0,0),400,45);
        LayerColor *selectLayer = LayerColor::create(Color4B(0,0,0,150),400,46);
        
        MenuItemSprite *button = MenuItemSprite::create(normalLayer,selectLayer, CC_CALLBACK_1(ItemShopLayer::clickItem, this));
        button->setPosition(Vec2(_itemListBorder->getContentSize().width/2, (button->getContentSize().height*i)+(space*i)+button->getContentSize().height/2));
        button->setUserObject(itemData);
        _menu->addChild(button);
        
        Label *itemName = Label::createWithTTF(itemData->_itemName,CommonUtils::getFontName(), FONT_SIZE);
        itemName->setPosition(Vec2(10,button->getContentSize().height/2));
        itemName->setColor(Color3B::BLACK);
        itemName->setAnchorPoint(Vec2(0,0.5f));
        button->addChild(itemName);
        
        Label *itemPrice = Label::createWithTTF(__String::createWithFormat("%d",price)->getCString(),CommonUtils::getFontName(), FONT_SIZE);
        itemPrice->setPosition(Vec2(button->getContentSize().width-10,button->getContentSize().height/2));
        itemPrice->setColor(Color3B::BLACK);
        itemPrice->setAnchorPoint(Vec2(1.0f,0.5f));
        button->addChild(itemPrice);
    }
    
    _itemListBorder->addChild(_menu);
}
int ItemShopLayer::isPrice(int itemType)
{
    int price = 0;
    std::map<unsigned int, ShapeValue*>::iterator it = _shopPriceList.find(itemType);
    if (it != _shopPriceList.end())
    {
        price = (int)it->second->getShapeValue();
    }
    if(price<1)
    {
        _talkArray.push_back(TextDb::getInstance()->getEtcText(22));
    }
    return price;
}
void ItemShopLayer::next()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    int var = _shopList.size() % _count;
    var = (var>0)?(_shopList.size()/_count+1):_shopList.size()/_count;
    if(var<=_itemIndex)
        return;
    
    _itemIndex++;
    refreshImage();
    refreshCount();
}

void ItemShopLayer::prev()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    if(_itemIndex<2)
        return;
    
    _itemIndex--;
    refreshImage();
    refreshCount();
}