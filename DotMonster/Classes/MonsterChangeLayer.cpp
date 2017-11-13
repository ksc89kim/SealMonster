//
//  MonsterChangeLayer.cpp
//  DotMonster
//
//  Created by 김선철 on 2016. 1. 5..
//
//

#include "MonsterChangeLayer.h"
#include "Player.h"
#include "ItemBagLayer.h"
#include "BattleLayer.h"
#include "GameScene.h"


MonsterChangeLayer::MonsterChangeLayer()
{
    _index = 0;
    
}

MonsterChangeLayer::~MonsterChangeLayer()
{
    
}
MonsterChangeLayer *MonsterChangeLayer::create(Node *backLayer, int animationType)
{
    MonsterChangeLayer * layer = new MonsterChangeLayer();
    if(layer && layer->initWithColor(Color4B(255,255,255,255)))
    {
        layer->ignoreAnchorPointForPosition(false);
        layer->_animationType = animationType;
        layer->_backLayer = backLayer;
        layer->_player = Player::getInstance();
        layer->setImage();
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void MonsterChangeLayer::setImage()
{
    if(_backLayer!=nullptr)
        _backLayer->setVisible(false);
    
    Player::getInstance()->pauseMusic();

    Player *player = (Player *)_player;
    Menu *menu = Menu::create();
    for(int i=1;i<4;i++)
    {
        for(int j=0;j<player->_monsterList->size();j++)
        {
            ShapeCommon *monsterShape = (ShapeCommon *)player->_monsterList->at(j);
            if(monsterShape!=nullptr)
            {
                if(monsterShape->_shapeData->_select->getShapeValue()==i)
                {
                    
                    MenuItem *button = CommonUtils::createMenuItemLabel("", Size(330,480),CC_CALLBACK_1(MonsterChangeLayer::clickMonster, this));
                    button->setUserObject(monsterShape);
                    menu->addChild(button);
                    
                    auto normalSp = ShapeCommon::copyShapeCommonImage(monsterShape);
                    float positionY = 280 - normalSp->getVisibleContentSize().height;
                    positionY = (positionY/2)+50;
                    normalSp->setPosition(Vec2(button->getContentSize().width/2, positionY));
                    auto selectSp = ShapeCommon::copyShapeCommonImage(monsterShape);
                    selectSp->setPosition(Vec2(button->getContentSize().width/2, positionY));
                    CommonUtils::menuItemSpriteAddChild((MenuItemSprite *)button, normalSp,selectSp);
                    
                    
                    ShapeObject *shapeData = monsterShape->_shapeData;
                    
                    __String *contentString = __String::createWithFormat("Lv %d. %s\nHp %d/(%d + %d) \nExp %d/%d\nClass : %s", (int)shapeData->_level->getShapeValue(),
                                                                         monsterShape->getFullName(),(int)shapeData->_health->getShapeValue(),
                                                                         (int)shapeData->_maxHealth->getShapeValue(),(int)shapeData->_plusMaxHealth->getShapeValue(),
                                                                         (int)shapeData->_exp->getShapeValue(),(int)monsterShape->getMaxExp(), monsterShape->getClassAllName());
                    
                    Label *normalLb = Label::createWithTTF(contentString->getCString(),CommonUtils::getFontName(),FONT_SIZE);
                    normalLb->setColor(Color3B::BLACK);
                    normalLb->setPosition(Vec2(button->getContentSize().width/2, button->getContentSize().height - normalLb->getContentSize().height/2 - 20));
                    Label *selectLb = Label::createWithTTF(contentString->getCString(),CommonUtils::getFontName(),FONT_SIZE);
                    selectLb->setColor(Color3B::BLACK);
                    selectLb->setPosition(Vec2(button->getContentSize().width/2, button->getContentSize().height - selectLb->getContentSize().height/2 - 20));
                    CommonUtils::menuItemSpriteAddChild((MenuItemSprite *)button, normalLb,selectLb);
                }
            }
        }
    }
    menu->alignItemsHorizontallyWithPadding(50.0f);
    menu->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2-50));
    this->addChild(menu);
    
    
    MenuItem *close = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(3).c_str(), Size(100,50),CC_CALLBACK_1(MonsterChangeLayer::close, this));
    close->setPosition(Vec2(this->getContentSize().width-80,this->getContentSize().height-60));
    
    Menu *buttonClose = Menu::create(close, NULL);
    buttonClose->setPosition(Vec2(0,0));
    this->addChild(buttonClose);
    
    Label *contentLabel = Label::createWithTTF(TextDb::getInstance()->getEtcText(50).c_str(),CommonUtils::getFontName(),28);
    contentLabel->setColor(Color3B::BLACK);
    contentLabel->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height- contentLabel->getContentSize().height/2 - 30));
    this->addChild(contentLabel);
}

void MonsterChangeLayer::close(Ref *pSender)
{
    Player::getInstance()->resumeMusic();
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    this->removeFromParent();
    _backLayer->setVisible(true);
}
void MonsterChangeLayer::clickMonster(Ref *monster)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    MenuItemImage *button = (MenuItemImage *)monster;
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
                    refreshImage();
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
                    refreshImage();
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
                    refreshImage();
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
                    refreshImage();
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
                    refreshImage();
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
                    refreshImage();
                }
            }
            break;
        }
        default:
        {
            BattleLayer *battle = dynamic_cast<BattleLayer *>(_backLayer);
            if(battle)
            {
                if(battle->changeMonster(common))
                {
                    battle->setVisible(true);
                    battle->attackEnemy();
                    Player::getInstance()->resumeMusic();
                    this->removeFromParent();
                }
                else
                {
                    (GameScene::runningScene())->createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(51).c_str(), nullptr);
                }
            }
            break;
        }
    }
}
void MonsterChangeLayer::refreshImage()
{
    ItemBagLayer *layer = dynamic_cast<ItemBagLayer *>(_backLayer);
    if(layer)
    {
        layer->refreshImage();
    }
    this->removeAllChildren();
    setImage();
}
bool MonsterChangeLayer::checkItem()
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
bool MonsterChangeLayer::checkHp(ShapeObject *data)
{
    if((int)data->_health->getShapeValue()>=(int)data->_maxHealth->getShapeValue()+(int)data->_plusMaxHealth->getShapeValue())
    {
        (GameScene::runningScene())->createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(46).c_str(), nullptr);
        return false;
    }
    return true;
}