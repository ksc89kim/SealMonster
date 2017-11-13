//
//  ItemBagLayer.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 6..
//
//

#include "ItemBagLayer.h"
#include "MonsterListLayer.h"
#include "MonsterChangeLayer.h"
#include "GameScene.h"
#include "BattleLayer.h"
#include "MapLayer.h"
#include "TextDb.h"

ItemBagLayer::ItemBagLayer()
{
    _index = 0;
    _count = 5;
    _itemIndex = 1;
    _isTyping = false;

}
ItemBagLayer::~ItemBagLayer()
{

}

ItemBagLayer *ItemBagLayer::create(Node *beforeLayer, bool isBattle)
{
    ItemBagLayer * layer = new ItemBagLayer();
    if(layer && layer->initWithColor(Color4B(255,255,255,255)))
    {
        layer->_isBattle = isBattle;
        layer->_player = Player::getInstance();
        layer->_beforeLayer = beforeLayer;
        layer->_beforeLayer->setVisible(false);
        layer->setImage();
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void ItemBagLayer::setImage()
{
    ignoreAnchorPointForPosition(false);
    
    if(_beforeLayer!=nullptr)
        _beforeLayer->setVisible(false);
    
    Player::getInstance()->pauseMusic();
    
    _player->_itemList->setCallBack(CC_CALLBACK_1(ItemBagLayer::clickItem,this));
    
    
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    auto positionListener = EventListenerTouchOneByOne::create();
    positionListener->setSwallowTouches(true);
    positionListener->onTouchBegan = CC_CALLBACK_2(ItemBagLayer::onTouchBegan, this);
    positionListener->onTouchMoved = CC_CALLBACK_2(ItemBagLayer::onTouchMoved, this);
    positionListener->onTouchEnded = CC_CALLBACK_2(ItemBagLayer::onTouchEnded, this);
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
    
    _border = (Sprite *)Scale9Sprite::create("border.png");
    _border->setContentSize(Size(500,250));
    _border->setPosition(CommonUtils::changePosition(Vec2(450,470)));
    addChild(_border);
    
    for(int i=1;i<_count;i++)
    {
        LayerColor *line = LayerColor::create(Color4B::BLACK, 500, 5);
        line->setPosition(Vec2(0, (50*i)-5));
        _border->addChild(line);
    }
    
    refreshImage();
    
    MenuItem *left = CommonUtils::createMenuItem("left.png", CC_CALLBACK_0(ItemBagLayer::prev, this));
    left->setPosition(Vec2(_border->getPositionX()-_border->getContentSize().width/2-left->getContentSize().width/2-50,_border->getPositionY()));
    
    MenuItem *right = CommonUtils::createMenuItem("right.png", CC_CALLBACK_0(ItemBagLayer::next, this));
    right->setPosition(Vec2(_border->getPositionX()+_border->getContentSize().width/2+right->getContentSize().width/2+50,_border->getPositionY()));

    _use = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(44), Size(100,50),CC_CALLBACK_1(ItemBagLayer::createUseItemPopup, this));
    _use->setUserObject(Node::create());
    _use->setPosition(Vec2(_talkBorder->getPositionX()+_talkBorder->getContentSize().width/2-_use->getContentSize().width/2-20,
                           _talkBorder->getPositionY()-_talkBorder->getContentSize().height/2+_use->getContentSize().height/2+20));
    
    MenuItem *close = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(3), Size(100,50),CC_CALLBACK_1(ItemBagLayer::close, this));
    close->setPosition(Vec2(this->getContentSize().width-80,this->getContentSize().height-60));
    
    Menu *button = Menu::create(left,right,close,_use, NULL);
    button->setPosition(Vec2(0,0));
    this->addChild(button);

    _countLabel = Label::createWithTTF("",CommonUtils::getFontName(), FONT_SIZE);
    _countLabel->setPosition(Vec2(_border->getPositionX(),_border->getPositionY()-_border->getContentSize().height/2-20));
    _countLabel->setColor(Color3B::BLACK);
    addChild(_countLabel);
    refreshCount();
    
    Adaptor::hideAd();
    
}

void ItemBagLayer::refreshImage()
{
    
    _border->removeChild(_menu,true);
    float space = 5;
    int count = _count;
    _menu= Menu::create();
    _menu->setPosition(Vec2(0, 0));
    int start = count*(_itemIndex-1);
    count = (_itemIndex*count>_player->_itemList->size())? _player->_itemList->size():count*_itemIndex;
    for(int i=_count-1,j=start;j<count;i--,j++)
    {
        Item *item = _player->_itemList->getIndexItem(j);
        item->setPosition(Vec2(_border->getContentSize().width/2, (item->getContentSize().height*i)+(space*i)+item->getContentSize().height/2));
        _menu->addChild(item);
    }

    _border->addChild(_menu);
}
void ItemBagLayer::refreshCount()
{
    int var = (_player->_itemList->size()>0)? (_player->_itemList->size()%_count==0)? _player->_itemList->size()/_count:_player->_itemList->size()/_count+1:1;

    _countLabel->setString(__String::createWithFormat("(%d/%d)",_itemIndex,var)->getCString());
}
void ItemBagLayer::next()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    int var = _player->_itemList->size() % _count;
    var = (var>0)?(_player->_itemList->size()/_count+1):_player->_itemList->size()/_count;
    if(var<=_itemIndex)
        return;
    
    _itemIndex++;
    refreshImage();
    refreshCount();
}

void ItemBagLayer::prev()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    if(_itemIndex<2)
        return;
    
    _itemIndex--;
    refreshImage();
    refreshCount();
}

void ItemBagLayer::clickItem(Ref *object)
{
    log("clickItem");
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    _index = 0;
    _talkArray.clear();
    Item *item = (Item *)object;
    ItemData *itemData = TextDb::getInstance()->getItemData(item->_itemType);
    _use->setUserObject(itemData);
    string temp;
    switch (itemData->_itemType) {
        case ItemType::kItemTypeVailLoon:
        case ItemType::kItemTypeRailLoon:
        case ItemType::kItemTypeZailLoon:
        {
            temp = __String::createWithFormat(itemData->_itemContent.c_str(),(item->getItemLevel()*10)+10)->getCString();
            temp = __String::createWithFormat(TextDb::getInstance()->getEtcText(62).c_str(),temp.c_str())->getCString();
            break;
        }
        case ItemType::kItemTypeQailLoon:
        case ItemType::kItemTypeNailLoon:
        {
            temp = __String::createWithFormat(itemData->_itemContent.c_str(),(item->getItemLevel()*1)+1)->getCString();
            temp = __String::createWithFormat(TextDb::getInstance()->getEtcText(62).c_str(),temp.c_str())->getCString();
            break;
        }
        default:
            temp = __String::createWithFormat(TextDb::getInstance()->getEtcText(62).c_str(),itemData->_itemContent.c_str())->getCString();
            break;
    }
    _talkArray.push_back(temp);
    nextSetting();

}
void ItemBagLayer::createUseItemPopup(Ref *object)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    Node *node = (Node *)object;
    ItemData *itemData = (ItemData *)node->getUserObject();
    switch (itemData->_itemUseType) {
        case ItemData::kAllUseType:
            (GameScene::runningScene())->createPopup(popUpType::kOkAndCanle, TextDb::getInstance()->getEtcText(38).c_str(), CC_CALLBACK_1(ItemBagLayer::useItem,this,object));
            break;
        case ItemData::kMapUseType:
        {
            if(_isBattle)
                (GameScene::runningScene())->createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(39).c_str(), nullptr);
            else
                (GameScene::runningScene())->createPopup(popUpType::kOkAndCanle, TextDb::getInstance()->getEtcText(38).c_str(), CC_CALLBACK_1(ItemBagLayer::useItem,this,object));
            break;
        }
        case ItemData::kBattleUseType:
        {
            if(_isBattle)
                (GameScene::runningScene())->createPopup(popUpType::kOkAndCanle, TextDb::getInstance()->getEtcText(38).c_str(), CC_CALLBACK_1(ItemBagLayer::useItem,this,object));
            else
                (GameScene::runningScene())->createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(39).c_str(), nullptr);
            break;
        }
        case ItemData::kNotUseType:
            (GameScene::runningScene())->createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(39).c_str(), nullptr);
            break;
    }
}

void ItemBagLayer::useItem(Ref *pSender,Ref *object)
{
   // Item *item = (Item *)object;
    Node *node = (Node *)object;
    ItemData *item = (ItemData *)node->getUserObject();
    log("click %d", item->_itemType);
    switch (item->_itemType) {
        case ItemType::kItemTypePlusStamina:
        case ItemType::kItemTypePlusPower:
        case ItemType::kItemTypePlusAgility:
        case ItemType::kItemTypeResorative1:
        case ItemType::kItemTypeResorative2:
        case ItemType::kItemTypeResorative3:
        case ItemType::kItemTypePlusTransStamina:
        case ItemType::kItemTypePlusTransPower:
        case ItemType::kItemTypePlusTransAgility:
        case ItemType::kItemTypeTransResorative1:
        case ItemType::kItemTypeTransResorative2:
        case ItemType::kItemTypeTransResorative3:
        {
            if(_isBattle)
            {
                MonsterChangeLayer *monster =  MonsterChangeLayer::create(this, item->_itemType);
                monster->setPosition(Vec2((GameScene::runningScene())->getContentSize().width/2,(GameScene::runningScene())->getContentSize().height/2));
                (GameScene::runningScene())->addChild(monster);
            }
            else
            {
                MonsterListLayer *monster =  MonsterListLayer::create(this, item->_itemType);
                monster->setPosition(Vec2((GameScene::runningScene())->getContentSize().width/2,(GameScene::runningScene())->getContentSize().height/2));
                (GameScene::runningScene())->addChild(monster);
            }
            break;
        }
        case ItemType::kItemTypeReturnCity:
        {
            MapLayer *map = (MapLayer *)_beforeLayer;
            map->getMapArea()->retunVillage();
            _player->_itemList->minusItem(item->_itemType, 1);
            close(nullptr);
            break;
        }
        case ItemType::kItemStamp:
        {
            if(_isBattle)
            {
                BattleLayer *battle = (BattleLayer *)_beforeLayer;
                Item *stamp = _player->_itemList->getItem(item->_itemType);
                if(stamp->getItemCount()>0)
                {
                    
                    switch( battle->catchMonster())
                    {
                        case catchType::kCatch:
                        {
                            _player->_itemList->minusItem(item->_itemType, 1);
                            battle->catchMonsterAnimation();
                            close(nullptr);
                            break;
                        }
                        case catchType::kFail:
                        {
                            _player->_itemList->minusItem(item->_itemType, 1);
                            battle->catchFailMonsterAnimation();
                            close(nullptr);
                            break;
                        }
                        case catchType::kError:
                        {
                            break;
                        }
                            
                    }
                }
                else
                {
                    (GameScene::runningScene())->createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(40).c_str(), nullptr);
                }
                
            }
            break;
        }
        case ItemType::kItemTypeEradication:
        {
            MapLayer *map = (MapLayer *)_beforeLayer;
            map->getMapArea()->setEradicationItem(true);
            _player->_itemList->minusItem(item->_itemType, 1);
            refreshImage();
            break;
        }
        case ItemType::kItemTypeTemptation:
        {
            MapLayer *map = (MapLayer *)_beforeLayer;
            map->getMapArea()->setTemptationItem(true);
            _player->_itemList->minusItem(item->_itemType, 1);
            refreshImage();
            break;
        }
        case ItemType::kItemTypeVisibleCave:
        {
            MapLayer *map = (MapLayer *)_beforeLayer;
            map->getMapArea()->setVisibleCaveItem(true);
            map->refreshMapArea();
            _player->_itemList->minusItem(item->_itemType, 1);
            refreshImage();
            break;
        }

        default:
            break;
    }
}

void ItemBagLayer::close(Ref *object)
{
    Player::getInstance()->resumeMusic();
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    _beforeLayer->setVisible(true);
    BattleLayer *battleLayer = dynamic_cast<BattleLayer *>(_beforeLayer);
    if(battleLayer)
    {
        battleLayer->refreshHp();
    }
    else
    {
        Adaptor::showAd();
    }
    this->removeFromParent();
}

bool ItemBagLayer::onTouchBegan(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    return true;
}
void ItemBagLayer::onTouchMoved(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    
}
void ItemBagLayer::onTouchEnded(Touch* touch, Event* event) {
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    nextSetting();
}
void ItemBagLayer::nextTyping(float delayTime)
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
void ItemBagLayer::nextSetting()
{
    this->unschedule(schedule_selector(ItemBagLayer::nextTyping));
    if(_isTyping)
    {
        _content->setString(_currentTalk);
        _isTyping = false;
    }
    else
    {
        
        if(_index<_talkArray.size())
        {
            _content->setString("");
            _currentTalk = _talkArray.at(_index);
            _index++;
        }
        this->schedule(schedule_selector(ItemBagLayer::nextTyping));
        _isTyping = true;
    }
    
}