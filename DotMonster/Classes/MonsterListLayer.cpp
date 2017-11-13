//
//  MosterListLayer.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 12..
//
//

#include "MonsterListLayer.h"
#include "Player.h"
#include "ItemBagLayer.h"
#include "BattleLayer.h"
#include "GameScene.h"


MonsterBattleSelectLayer::MonsterBattleSelectLayer()
{
    _monsterListLayer = nullptr;
}

MonsterBattleSelectLayer::~MonsterBattleSelectLayer()
{
    
}
MonsterBattleSelectLayer *MonsterBattleSelectLayer::create(ShapeCommon *shape, MonsterListLayer *mLayer)
{
    MonsterBattleSelectLayer * layer = new MonsterBattleSelectLayer();
    if(layer && layer->initWithColor(Color4B(0,0,0,150)))
    {
        layer->_monsterListLayer = mLayer;
        layer->_shape = shape;
        layer->setImage();
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void MonsterBattleSelectLayer::setImage()
{
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    auto positionListener = EventListenerTouchOneByOne::create();
    positionListener->setSwallowTouches(true);
    positionListener->onTouchBegan = CC_CALLBACK_2(MonsterBattleSelectLayer::onTouchBegan, this);
    positionListener->onTouchMoved = CC_CALLBACK_2(MonsterBattleSelectLayer::onTouchMoved, this);
    positionListener->onTouchEnded = CC_CALLBACK_2(MonsterBattleSelectLayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(positionListener, this);
    

    
    Menu *menu = Menu::create();
    Size tempSize = Size::ZERO;
    for(int i=0;i<4;i++)
    {
        __String *temp = (i<3)? __String::createWithFormat(TextDb::getInstance()->getEtcText(42).c_str(), i+1):__String::create(TextDb::getInstance()->getEtcText(3).c_str());
        MenuItem *item = CommonUtils::createMenuItemLabel(temp->getCString(), CC_CALLBACK_1(MonsterBattleSelectLayer::click, this));
        item->setTag(i);
        menu->addChild(item);
        if(item->getContentSize().width>tempSize.width)
        {
            tempSize.width = item->getContentSize().width + 30;
        }
        tempSize.height += item->getContentSize().height + 10;
    }
    tempSize.height += 30;
    Sprite *border = (Sprite *)Scale9Sprite::create("border.png");
    border->setContentSize(tempSize);
    border->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(border);
    
    menu->alignItemsVerticallyWithPadding(10.0f);
    menu->setPosition(Vec2(border->getContentSize().width/2, border->getContentSize().height/2));
    border->addChild(menu);
   
}

void MonsterBattleSelectLayer::click(Ref *pSender)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    MenuItem *item = (MenuItem *)pSender;
    if(_shape->_shapeData->_health->getShapeValue()<=0 && item->getTag()>-1 && item->getTag()<3)
    {
        (GameScene::runningScene())->createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(43).c_str(), nullptr);
        return;
    }

    switch (item->getTag()) {
        case 0:
            Player::getInstance()->setSelectMonster(_shape, 1);
            break;
        case 1:
            Player::getInstance()->setSelectMonster(_shape, 2);
            break;
        case 2:
            Player::getInstance()->setSelectMonster(_shape, 3);
            break;
        default:
            break;
    }
    if(_monsterListLayer)
    {
        _monsterListLayer->refreshImage();
    }
    this->removeFromParent();
}

bool MonsterBattleSelectLayer::onTouchBegan(Touch* touch, Event* event) {
    return true;
}
void MonsterBattleSelectLayer::onTouchMoved(Touch* touch, Event* event) {
}
void MonsterBattleSelectLayer::onTouchEnded(Touch* touch, Event* event) {
}

#pragma mark - MonsterEvolutionLayer

MonsterEvolutionLayer::MonsterEvolutionLayer()
{
}

MonsterEvolutionLayer::~MonsterEvolutionLayer()
{
    
}
MonsterEvolutionLayer *MonsterEvolutionLayer::create(ShapeCommon *shape)
{
    MonsterEvolutionLayer * layer = new MonsterEvolutionLayer();
    if(layer && layer->initWithColor(Color4B(0,0,0,150)))
    {
        layer->_shape = shape;
        layer->setImage();
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void MonsterEvolutionLayer::setImage()
{
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    auto positionListener = EventListenerTouchOneByOne::create();
    positionListener->setSwallowTouches(true);
    positionListener->onTouchBegan = CC_CALLBACK_2(MonsterEvolutionLayer::onTouchBegan, this);
    positionListener->onTouchMoved = CC_CALLBACK_2(MonsterEvolutionLayer::onTouchMoved, this);
    positionListener->onTouchEnded = CC_CALLBACK_2(MonsterEvolutionLayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(positionListener, this);
    
    Sprite *border = (Sprite *)Scale9Sprite::create("border.png");
    border->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(border);
    
    if(_shape->isLegend())
    {
        border->setContentSize(Size(500,400));
        ShapeCommon *evolution = ShapeCommon::copyShapeCommon(_shape);
        evolution->setPosition(Vec2(border->getContentSize().width/2, 100));
        border->addChild(evolution);
    }
    else
    {
        border->setContentSize(Size(900,400));
        
        LayerColor *layer = LayerColor::create();
        
        ShapeCommon *evolution = ShapeCommon::copyShapeCommon(_shape);
        evolution->_shapeData->_level->setShapeValue(1.0f);
        evolution->changeImage();
        //evolution->setPosition(Vec2(border->getContentSize().width/2,100));
        layer->addChild(evolution);
        
        Sprite *right1 = Sprite::create("right.png");
        right1->setScale(0.8);
        layer->addChild(right1);
        
        ShapeCommon *evolution2 =  ShapeCommon::copyShapeCommon(_shape);
        evolution2->_shapeData->_level->setShapeValue(SKILL_THREE);
        evolution2->changeImage();
        //evolution2->setPosition(Vec2(border->getContentSize().width/2-evolution->getVisibleContentSize().width/2-evolution2->getVisibleContentSize().width/2-100,100));
        layer->addChild(evolution2);
        
        Sprite *right2 = Sprite::create("right.png");
        right2->setScale(0.8);
        layer->addChild(right2);

        ShapeCommon *evolution3 = ShapeCommon::copyShapeCommon(_shape);
        evolution3->_shapeData->_level->setShapeValue(SKILL_FOUR);
        evolution3->changeImage();
        //evolution3->setPosition(Vec2(border->getContentSize().width/2+evolution->getVisibleContentSize().width/2+evolution3->getVisibleContentSize().width/2+100,100));
        layer->addChild(evolution3);
        
        layer->setContentSize(Size(evolution->getVisibleContentSize().width+evolution2->getVisibleContentSize().width+evolution3->getVisibleContentSize().width+200,evolution3->getVisibleContentSize().height));
        layer->ignoreAnchorPointForPosition(false);
        layer->setAnchorPoint(Vec2(0.5f,0.0f));
        layer->setPosition(Vec2(border->getContentSize().width/2, 100));
        border->addChild(layer);
        
        evolution->setPosition(Vec2(evolution->getVisibleContentSize().width/2,0));
        right1->setPosition(Vec2(evolution->getPositionX()+evolution->getVisibleContentSize().width/2+(right1->getContentSize().width/2 * right1->getScale())+10, layer->getContentSize().height/2));
        evolution2->setPosition(Vec2(evolution->getPositionX()+evolution->getVisibleContentSize().width/2+evolution2->getVisibleContentSize().width/2+100,0));
        right2->setPosition(Vec2(evolution2->getPositionX()+evolution2->getVisibleContentSize().width/2+(right2->getContentSize().width/2 * right2->getScale())+10, layer->getContentSize().height/2));
        evolution3->setPosition(Vec2(evolution2->getPositionX()+evolution2->getVisibleContentSize().width/2+evolution3->getVisibleContentSize().width/2+100,0));
        
        if(SKILL_THREE<=_shape->_shapeData->_level->getShapeValue()&&SKILL_FOUR>_shape->_shapeData->_level->getShapeValue())
        {
            evolution3->setColorShape(Color3B::BLACK);
        }
        else if(SKILL_THREE>_shape->_shapeData->_level->getShapeValue())
        {
            evolution2->setColorShape(Color3B::BLACK);
            evolution3->setColorShape(Color3B::BLACK);
        }
    }
    
    Menu *menu = Menu::create();
    MenuItem *item = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(3).c_str(), CC_CALLBACK_1(MonsterEvolutionLayer::clickExit, this));
    menu->addChild(item);
    menu->setPosition(Vec2(border->getContentSize().width/2, item->getContentSize().height/2 + 30));
    border->addChild(menu);
    
}

void MonsterEvolutionLayer::clickExit(Ref *pSender)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    this->removeFromParent();
}

bool MonsterEvolutionLayer::onTouchBegan(Touch* touch, Event* event) {
    return true;
}
void MonsterEvolutionLayer::onTouchMoved(Touch* touch, Event* event) {
}
void MonsterEvolutionLayer::onTouchEnded(Touch* touch, Event* event) {
}

#pragma mark - MosterItemListLayer

MonsterListLayer::MonsterListLayer()
{
    _index = 1;
    _count = 10;
}

MonsterListLayer::~MonsterListLayer()
{
    
}
MonsterListLayer *MonsterListLayer::create(Node *backLayer, int animationType)
{
    MonsterListLayer * layer = new MonsterListLayer();
    if(layer && layer->initWithColor(Color4B(255,255,255,255)))
    {
        layer->_backLayer = backLayer;
        layer->_player = Player::getInstance();
        layer->_animationType = animationType;
        layer->setImage();
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}
void MonsterListLayer::setImage()
{
    ignoreAnchorPointForPosition(false);
    
    if(_backLayer!=nullptr)
        _backLayer->setVisible(false);
    
    Player::getInstance()->pauseMusic();

    _border = (Sprite *)Scale9Sprite::create("border.png");
    _border->setContentSize(Size(300,550));
    _border->setPosition(CommonUtils::changePosition(Vec2(260,340)));
    addChild(_border);
    
    for(int i=1;i<10;i++)
    {
        LayerColor *line = LayerColor::create(Color4B::BLACK, 300, 5);
        line->setPosition(Vec2(0, (55*i)-5));
        _border->addChild(line);
    }
    
    refreshImage();
   
    MenuItem *left = CommonUtils::createMenuItem("left.png", CC_CALLBACK_0(MonsterListLayer::prev, this));
    left->setPosition(Vec2(_border->getPositionX()-_border->getContentSize().width/2-left->getContentSize().width/2-20,this->getContentSize().height/2+20));
    
    MenuItem *right = CommonUtils::createMenuItem("right.png", CC_CALLBACK_0(MonsterListLayer::next, this));
    right->setPosition(Vec2(_border->getPositionX()+_border->getContentSize().width/2+right->getContentSize().width/2+20,this->getContentSize().height/2+20));
    
    MenuItem *close = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(3).c_str(), Size(100,50),CC_CALLBACK_1(MonsterListLayer::close, this));
    close->setPosition(Vec2(this->getContentSize().width-80,this->getContentSize().height-60));
    
    Menu *button = Menu::create(left,right,close, NULL);
    button->setPosition(Vec2(0,0));
    this->addChild(button);
    
    _countLabel = Label::createWithTTF("",CommonUtils::getFontName(), FONT_SIZE);
    _countLabel->setPosition(CommonUtils::changePosition(Vec2(250,30)));
    _countLabel->setColor(Color3B::BLACK);
    addChild(_countLabel);
    refreshCount();
    
    _info = (Sprite *)Scale9Sprite::create("border.png");
    _info->setContentSize(Size(330,550));
    _info->setPosition(CommonUtils::changePosition(Vec2(650,340)));
    addChild(_info);
    
    Player *parent = (Player *)_player;
    if(parent->_monsterList->size()>0)
    {
        ShapeCommon *common = (ShapeCommon *)parent->_monsterList->at(0);
        refreshInfo(common);
    }
    Adaptor::hideAd();
    
}

void MonsterListLayer::refreshImage()
{
    _border->removeChild(_menu, true);
   _menu = Menu::create();
    _menu->setPosition(Vec2(0,0));
    Player *parent = (Player *)_player;
    float space = 5;
    int count = _count;
    int start = count*(_index-1);
    count = (_index*count>parent->_monsterList->size())? (int)parent->_monsterList->size():count*_index;
    
    for(int i=_count-1,j=start;j<count;i--,j++)
    {
        ShapeCommon *common = (ShapeCommon *)parent->_monsterList->at(j);
        auto normalSp = ShapeCommon::copyShapeCommonImage(common);
        CommonUtils::fitNode(normalSp, 40);
        auto selectSp = ShapeCommon::copyShapeCommonImage(common);
        CommonUtils::fitNode(selectSp, 40);
        
        LayerColor *normalLayer =  LayerColor::create(Color4B(0,0,0,0),300,50);
        normalSp->setPosition(Vec2(35, 5));
        normalLayer->addChild(normalSp);
        LayerColor *selectLayer = LayerColor::create(Color4B(0,0,0,150),300,51);
        selectSp->setPosition(Vec2(35, 5));
        selectLayer->addChild(selectSp);
        
        MenuItemSprite *button = MenuItemSprite::create(normalLayer,selectLayer, CC_CALLBACK_1(MonsterListLayer::clickInfo, this));
        button->setPosition(Vec2(_border->getContentSize().width/2, (button->getContentSize().height*i)+(space*i)+button->getContentSize().height/2));
        button->setUserObject(common);
        _menu->addChild(button);
        
        Label *contentlb = Label::createWithTTF(common->getFullName(),CommonUtils::getFontName(),FONT_SIZE);
        contentlb->setColor(Color3B::BLACK);
        contentlb->setAnchorPoint(Vec2(0,0.5f));
        contentlb->setPosition(Vec2(60, button->getContentSize().height/2));
        button->addChild(contentlb);
        
        int rank = (int)common->_shapeData->_select->getShapeValue();
        if(rank>0)
        {
            Label *selectLabel = Label::createWithTTF(__String::createWithFormat("%d",rank)->getCString(),CommonUtils::getFontName(),FONT_SIZE);
            selectLabel->setColor(Color3B::BLACK);
            selectLabel->setAnchorPoint(Vec2(1.0f,0.5f));
            selectLabel->setPosition(Vec2(button->getContentSize().width-20, button->getContentSize().height/2));
            button->addChild(selectLabel);
        }
       
    }
    _border->addChild(_menu);
}

void MonsterListLayer::refreshCount()
{
    Player *parent = (Player *)_player;
    
    int var = (parent->_monsterList->size()>0)? (parent->_monsterList->size()%_count==0)? parent->_monsterList->size()/_count:parent->_monsterList->size()/_count+1:1;
    _countLabel->setString(__String::createWithFormat("(%d/%d)",_index,var)->getCString());
}
void MonsterListLayer::clickInfo(Ref *target)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    ShapeCommon *common = (ShapeCommon *)((Node *)target)->getUserObject();
    refreshInfo(common);
}
void MonsterListLayer::refreshInfo(ShapeCommon *shape)
{
    _info->removeAllChildren();
    auto shapeSp = ShapeCommon::copyShapeCommonImage(shape);
    float positionY = 280 - shapeSp->getVisibleContentSize().height;
    positionY = (positionY/2)+100;
    shapeSp->setPosition(Vec2(_info->getContentSize().width/2, positionY));
    _info->addChild(shapeSp);
    
    ShapeObject *shapeData = shape->_shapeData;
    
    __String *contentString = __String::createWithFormat("Lv %d. %s\nHp %d/(%d + %d) \nExp %d/%d\nPower (%d+%d)\nAgility (%d+%d)\nClass : %s", (int)shapeData->_level->getShapeValue(),
                                                         shape->getFullName(),(int)shapeData->_health->getShapeValue(),
                                                         (int)shapeData->_maxHealth->getShapeValue(),(int)shapeData->_plusMaxHealth->getShapeValue(),
                                                         (int)shapeData->_exp->getShapeValue(),(int)shape->getMaxExp(), (int)shapeData->_power->getShapeValue(),
                                                        (int)shapeData->_plusPower->getShapeValue(), (int)shapeData->_agility->getShapeValue(),(int)shapeData->_plusAgility->getShapeValue(), shape->getClassAllName());
    
    Label *normalLb = Label::createWithTTF(contentString->getCString(),CommonUtils::getFontName(),FONT_SIZE);
    normalLb->setColor(Color3B::BLACK);
    normalLb->setPosition(Vec2(_info->getContentSize().width/2, _info->getContentSize().height - normalLb->getContentSize().height/2 - 15));
    _info->addChild(normalLb);

     if(dynamic_cast<ItemBagLayer *>(_backLayer))
     {
         MenuItem *useItem = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(44).c_str(), Size(100,50),CC_CALLBACK_1(MonsterListLayer::useItem, this));
         useItem->setUserObject(shape);
         Menu *button = Menu::create(useItem, NULL);
         button->setPosition(Vec2(_info->getContentSize().width/2,60));
         _info->addChild(button);
     }
    else
    {
        MenuItem *select = CommonUtils::createMenuItem("battle.png", CC_CALLBACK_1(MonsterListLayer::clickBattle, this));
        select->setUserObject(shape);
        MenuItem *remove = CommonUtils::createMenuItem("remove.png", CC_CALLBACK_1(MonsterListLayer::clickRemove, this));
        remove->setUserObject(shape);
        MenuItem *check = CommonUtils::createMenuItem("check.png", CC_CALLBACK_1(MonsterListLayer::clickEvolutionView, this));
        check->setUserObject(shape);
        Menu *button = Menu::create(select,remove, check,NULL);
        button->setPosition(Vec2(_info->getContentSize().width/2,60));
        button->alignItemsHorizontallyWithPadding(10.0f);
        _info->addChild(button);
    }
}
void MonsterListLayer::useItem(Ref *target)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    MenuItemImage *button = (MenuItemImage *)target;
    ShapeCommon *common = (ShapeCommon *)button->getUserObject();
    ShapeObject *data = common->_shapeData;
    
    switch (_animationType) {
        case ItemType::kItemTypeResorative1:
        {
            if(checkHp(data))
            {
                if(checkItem())
                {
                    data->plusHelath(250);
                    refreshInfo(common);
                }
            }
            break;
        }
        case ItemType::kItemTypeResorative2:
        {
            if(checkHp(data))
            {
                if(checkItem())
                {
                    data->plusHelath(600);
                    refreshInfo(common);
                }
            }
            break;
        }
        case ItemType::kItemTypeResorative3:
        {
            if(checkHp(data))
            {
                if(checkItem())
                {
                    data->plusHelath(1200);
                    refreshInfo(common);
                }
            }
            break;
        }
        case ItemType::kItemTypeTransResorative1:
        {
            if(checkHp(data))
            {
                if(checkItem())
                {
                    data->plusHelath((data->_maxHealth->getShapeValue()+data->_plusMaxHealth->getShapeValue())*0.3f);
                    refreshInfo(common);
                }
            }
            break;
        }
        case ItemType::kItemTypeTransResorative2:
        {
            if(checkHp(data))
            {
                if(checkItem())
                {
                    data->plusHelath((data->_maxHealth->getShapeValue()+data->_plusMaxHealth->getShapeValue())*0.6f);
                    refreshInfo(common);
                }
            }
            break;
        }
        case ItemType::kItemTypeTransResorative3:
        {
            if(checkHp(data))
            {
                if(checkItem())
                {
                    data->plusHelath((data->_maxHealth->getShapeValue()+data->_plusMaxHealth->getShapeValue()));
                    refreshInfo(common);
                }
            }
            break;
        }
        case ItemType::kItemTypePlusPower:
        {
            if(checkItem())
            {
                data->_plusPower->addShapeValue(5);
                refreshInfo(common);
            }
            break;
        }
        case ItemType::kItemTypePlusAgility:
        {
            if(checkItem())
            {
                data->_plusAgility->addShapeValue(5);
                refreshInfo(common);
            }
            break;
        }
        case ItemType::kItemTypePlusStamina:
        {
            if(checkItem())
            {
                data->_plusMaxHealth->addShapeValue(25);
                refreshInfo(common);
            }
            break;
        }
        case ItemType::kItemTypePlusTransPower:
        {
            if(checkItem())
            {
                int plusPower = data->_level->getShapeValue() * 1;
                plusPower = (plusPower>25)?25:plusPower;
                data->_plusPower->addShapeValue(plusPower);
                refreshInfo(common);
            }
            break;
        }
        case ItemType::kItemTypePlusTransAgility:
        {
            if(checkItem())
            {
                int plusAgility = data->_level->getShapeValue() * 1;
                plusAgility = (plusAgility>25)?25:plusAgility;
                data->_plusAgility->addShapeValue(plusAgility);
                refreshInfo(common);
            }
            break;
        }
        case ItemType::kItemTypePlusTransStamina:
        {
            if(checkItem())
            {
                int plusHealth = data->_level->getShapeValue() * 10;
                plusHealth = (plusHealth>250)?250:plusHealth;
                data->_plusMaxHealth->addShapeValue(plusHealth);
                refreshInfo(common);
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

void MonsterListLayer::next()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    Player *parent = (Player *)_player;
    int var = parent->_monsterList->size() % _count;
    var = (var>0)?(parent->_monsterList->size()/_count+1):parent->_monsterList->size()/_count;
    if(var<=_index)
        return;
    
    _index++;
    refreshImage();
    refreshCount();
}

void MonsterListLayer::prev()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    if(_index<2)
        return;
    
    _index--;
    refreshImage();
    refreshCount();
}

void MonsterListLayer::close(Ref *object)
{
    if(dynamic_cast<ItemBagLayer *>(_backLayer)==NULL)
    {
        Adaptor::showAd();
        Player::getInstance()->resumeMusic();
    }
    else
    {
        ItemBagLayer *layer = (ItemBagLayer *)_backLayer;
        layer->refreshImage();
        layer->refreshCount();
    }
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    _backLayer->setVisible(true);
    this->removeFromParent();
}

bool MonsterListLayer::checkItem()
{
    Player *player =  Player::getInstance();
    if(player->_itemList->isItem(_animationType))
    {
        Player::getInstance()->_itemList->minusItem(_animationType, 1);
        return true;
    }
    else
    {
        (GameScene::runningScene())->createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(45).c_str(), nullptr);
        return false;
    }
}
bool MonsterListLayer::checkHp(ShapeObject *data)
{
    if((int)data->_health->getShapeValue()>=(int)data->_maxHealth->getShapeValue()+(int)data->_plusMaxHealth->getShapeValue())
    {
        (GameScene::runningScene())->createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(46).c_str(), nullptr);
        return false;
    }
    return true;
}
void MonsterListLayer::clickBattle(Ref *target)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    (GameScene::runningScene())->addChild(MonsterBattleSelectLayer::create((ShapeCommon *)((Node *)target)->getUserObject(),this));
}
void MonsterListLayer::clickRemove(Ref *target)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    _removeMonster = (ShapeCommon *)((Node *)target)->getUserObject();
    (GameScene::runningScene())->createPopup(popUpType::kOkAndCanle, TextDb::getInstance()->getEtcText(47).c_str(), CC_CALLBACK_0(MonsterListLayer::removeMonster, this));
}
void MonsterListLayer::clickEvolutionView(Ref *target)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    (GameScene::runningScene())->addChild(MonsterEvolutionLayer::create((ShapeCommon *)((Node *)target)->getUserObject()));
}
void MonsterListLayer::removeMonster()
{
    Player *player = (Player *)_player;
    if((int)_removeMonster->_shapeData->_select->getShapeValue()==1)
    {
        (GameScene::runningScene())->createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(48).c_str(), nullptr);
    }
    else if(player->_monsterList->size()>1)
    {
        for(int i=0;i<player->_monsterList->size();i++)
        {
            ShapeCommon *common = (ShapeCommon *)player->_monsterList->at(i);
            if(common==_removeMonster)
            {
                player->_monsterList->eraseObject(_removeMonster);
                break;
            }
        }
        refreshImage();
        _info->removeAllChildren();
    }
    else
    {
        (GameScene::runningScene())->createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(49).c_str(), nullptr);
    }
}
