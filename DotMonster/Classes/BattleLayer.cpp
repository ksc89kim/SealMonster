//
//  BattleLayer.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 10. 19..
//
//

#include "BattleLayer.h"
#include "CommonUtils.h"
#include "MapArea.h"
#include "ItemBagLayer.h"
#include "MonsterChangeLayer.h"
#include "GameScene.h"
#include "TextDb.h"
#pragma mark - Bush
Bush::Bush()
{
    _type = -1;
    _minIndex = 0;
    _maxIndex = 0;
    _minLevel = 0;
    _maxLevel = 0;
}
Bush::~Bush()
{
    
}
Bush *Bush::create(const char *bushInfo)
{
    Bush *sprite = new (std::nothrow) Bush();
    if (sprite && sprite->initWithFile("bush.png"))
    {
        sprite->setValue(bushInfo);
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}
void Bush::setValue(const char *bushInfo)
{
    std::vector<std::string> bushInfoData = (&CommonUtils::getInstance())->splits(bushInfo, "/");
    if(bushInfoData.size()==1)
    {
        _type = atoi(bushInfoData[0].c_str());
    }
    else if(bushInfoData.size()>0 && bushInfoData.size()<6)
    {
        _type = atoi(bushInfoData[0].c_str());
        _minIndex = atoi(bushInfoData[1].c_str());
        _maxIndex = atoi(bushInfoData[2].c_str());
        _minLevel = atoi(bushInfoData[3].c_str());
        _maxLevel = atoi(bushInfoData[4].c_str());
    }
}
ShapeCommon *Bush::getMonster()
{
    ShapeCommon *monster = nullptr;
    if(_type==bushType::kBushRand || _type==bushType::kBushRand20 || _type==bushType::kBushRand30)
    {
        int random = (arc4random()%3)+1;
        log("random %d", random);
        switch (random) {
            case bushType::kBushShapeF:
                monster = ShapeF::create();
                break;
            case bushType::kBushShapeW:
                monster = ShapeW::create();
                break;
            case bushType::kBushShapeT:
                monster = ShapeT::create();
                break;
            case bushType::kBushShapeI:
                monster = ShapeI::create();
                break;
            case bushType::kBushShapeZ:
                monster = ShapeZ::create();
                break;
            default:
                monster = ShapeF::create();
                break;
        }

        int playerMaxLevel = Player::getInstance()->getMaxLevelMonster();
        _minLevel = playerMaxLevel;
        switch(_type)
        {
            case bushType::kBushRand:
            {
                if(arc4random()%100==33)
                {
                    monster->setLegend(true);
                }
                else if(arc4random()%70==25)
                {
                    monster->changeFindShape(0, 0, 0);
                }
                else if(arc4random()%30==10)
                {
                    monster->changeRandShape(0, 9);
                }
                else if(arc4random()%10==5)
                {
                    monster->changeRandShape(1, 9);
                }
                else if(arc4random()%5==2)
                {
                    monster->changeRandShape(2, 9);
                }
                else
                {
                    monster->changeRandShape(3, 9);
                }
                _minLevel = playerMaxLevel;
                _maxLevel = playerMaxLevel+10;
                break;
            }
            case bushType::kBushRand20:
            {
                if(arc4random()%70==33)
                {
                    monster->setLegend(true);
                }
                else if(arc4random()%50==15)
                {
                    monster->changeFindShape(0, 0, 0);
                }
                else if(arc4random()%25==10)
                {
                    monster->changeRandShape(0, 9);
                }
                else if(arc4random()%5==2)
                {
                    monster->changeRandShape(1, 9);
                }
                else if(arc4random()%3==1)
                {
                    monster->changeRandShape(2, 9);
                }
                else
                {
                    monster->changeRandShape(3, 9);
                }
                _minLevel = playerMaxLevel+10;
                _maxLevel = playerMaxLevel+20;
                break;
            }
            case bushType::kBushRand30:
            {
                if(arc4random()%50==10)
                {
                    monster->setLegend(true);
                }
                else if(arc4random()%30==8)
                {
                    monster->changeFindShape(0, 0, 0);
                }
                else if(arc4random()%10==5)
                {
                    monster->changeRandShape(0, 9);
                }
                else if(arc4random()%5==2)
                {
                    monster->changeRandShape(1, 9);
                }
                else
                {
                    monster->changeRandShape(2, 9);
                }
                _minLevel = playerMaxLevel+20;
                _maxLevel = playerMaxLevel+30;
                break;
            }
            default:
            {
                monster->changeRandShape(3, 9);
                _maxLevel = playerMaxLevel+10;
                break;
            }
        }
    }
    else
    {
        switch (_type) {
            case bushType::kBushShapeF:
                monster = ShapeF::create();
                break;
            case bushType::kBushShapeW:
                monster = ShapeW::create();
                break;
            case bushType::kBushShapeT:
                monster = ShapeT::create();
                break;
            case bushType::kBushShapeI:
                monster = ShapeI::create();
                break;
            case bushType::kBushShapeZ:
                monster = ShapeZ::create();
                break;
            default:
                monster = ShapeF::create();
                break;
        }
        monster->changeRandShape(_minIndex, _maxIndex);
    }

    monster->_shapeData->_select->setShapeValue(1);
    if(arc4random()%50==1)
    {
        int level = arc4random()%3+10;
        monster->_shapeData->_level->setShapeValue(level);
    }
    else
    {
        int deffrent = _maxLevel-_minLevel;
        if(deffrent>0)
            monster->_shapeData->_level->setShapeValue(_minLevel+arc4random()%deffrent);
        else
            monster->_shapeData->_level->setShapeValue(arc4random()%_maxLevel);
    }
    monster->setStatus();
    monster->changeImage();
    return monster;
}
Node *Bush::createCharacterMonster(std::vector<std::string> characterMonster, int select)
{
    ShapeCommon *monster = nullptr;
    switch (atoi(characterMonster[0].c_str())) {
        case bushType::kBushShapeF:
            monster = ShapeF::create();
            break;
        case bushType::kBushShapeW:
            monster = ShapeW::create();
            break;
        case bushType::kBushShapeT:
            monster = ShapeT::create();
            break;
        case bushType::kBushShapeI:
            monster = ShapeI::create();
            break;
        case bushType::kBushShapeZ:
            monster = ShapeZ::create();
            break;
        default:
            break;
    }
    if(atoi(characterMonster[1].c_str())==9999)
    {
        monster->_shapeData->_level->setShapeValue(atoi(characterMonster[2].c_str()));
        monster->_shapeData->_select->setShapeValue(select);
        monster->setLegend(true);
    }
    else
    {
        monster->_shapeData->_level->setShapeValue(atoi(characterMonster[4].c_str()));
        monster->_shapeData->_select->setShapeValue(select);
        monster->changeFindShape(atoi(characterMonster[1].c_str()), atoi(characterMonster[2].c_str()), atoi(characterMonster[3].c_str()));
    }
    return monster;
}
#pragma mark - battleLayer

BattleLayer::BattleLayer()
{
    _delayTime = 0.0f;
    _tempScale = 0.0f;
    _isStackGame = false;
    _mapArea = nullptr;
    _player = nullptr;
    _enemy = nullptr;
    _beforeLayer = nullptr;
    _quest = nullptr;
    _playerMonSter = nullptr;
    _enemyMonSter = nullptr;
    _battleObject = nullptr;
    _enemyHp = nullptr;
    _playerHp = nullptr;
    _isPushSkill= false;
    _playMonsterPosition = Vec2::ZERO;
    _enemyMonsterPosition = Vec2::ZERO;
    _battleType = battleType::kBushType;

}
BattleLayer::~BattleLayer()
{

}

BattleLayer* BattleLayer::create(Node *beforeLayer, Node *enemy,Node *mapArea,int battleType,Node *quest)
{
    BattleLayer * layer = new BattleLayer();
    if (layer && layer->initWithColor(Color4B::WHITE))
    {
        layer->ignoreAnchorPointForPosition(false);
        layer->_player = Player::getInstance();
        layer->_enemy = enemy;
        layer->_battleType = battleType;
        layer->_mapArea = mapArea;
        layer->_beforeLayer = beforeLayer;
        layer->_quest = quest;
        layer->setStackGameImage();
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void BattleLayer::setStackGameImage()
{
    
    if(_enemy!=nullptr)
        this->addChild(_enemy);
    
    if(_beforeLayer!=nullptr)
        _beforeLayer->setVisible(false);

    
    _playMonsterPosition = CommonUtils::changePosition(Vec2(210,180));
    _enemyMonsterPosition = CommonUtils::changePosition(Vec2(750,340));
    
    _battleObject = Battle::create(CC_CALLBACK_0(BattleLayer::endStackAnimation, this));
    this->addChild(_battleObject);

    auto bar =  Sprite::create("hp.png");
    _playerHp = ProgressTimer::create(bar);
    _playerHp->setPosition(CommonUtils::changePosition(Vec2(697,254)));
    _playerHp->setType(ProgressTimer::Type::BAR);
    _playerHp->setMidpoint(Vec2(0,0));
    _playerHp->setBarChangeRate(Vec2(1, 0));
    this->addChild(_playerHp);
    
    auto bgBar = Sprite::create("playerBar.png");
    bgBar->setPosition(CommonUtils::changePosition(Vec2(675,230)));
    this->addChild(bgBar);
    
    _playerLabel = Label::createWithTTF("", CommonUtils::getFontName(), 26);
    _playerLabel->setAnchorPoint(Vec2(0,0.5f));
    _playerLabel->setPosition(Vec2(640,300));
    _playerLabel->setColor(Color3B::BLACK);
    this->addChild(_playerLabel);

    bar =  Sprite::create("hp.png");
    _enemyHp = ProgressTimer::create(bar);
    _enemyHp->setType(ProgressTimer::Type::BAR);
    _enemyHp->setMidpoint(Vec2(0,0));
    _enemyHp->setBarChangeRate(Vec2(1, 0));
    _enemyHp->setPosition(CommonUtils::changePosition(Vec2(225,557)));
    this->addChild(_enemyHp);
    
    bgBar = Sprite::create("enemyBar.png");
    bgBar->setPosition(CommonUtils::changePosition(Vec2(240,530)));
    this->addChild(bgBar);
    
    _enemyLabel = Label::createWithTTF("", CommonUtils::getFontName(), 26);
    _enemyLabel->setAnchorPoint(Vec2(0,0.5f));
    _enemyLabel->setPosition(Vec2(110,600));
    _enemyLabel->setColor(Color3B::BLACK);
    this->addChild(_enemyLabel);
    
    
    Sprite *border = (Sprite *)Scale9Sprite::create("border.png");
    border->setContentSize(Size(this->getContentSize().width-20,150));
    border->setPosition(CommonUtils::changePosition(Vec2(480,90)));
    this->addChild(border,zBorderOrder);
    
    _stackManager = SkillStackManager::create(Color4B(0,0,0,0));
    _stackManager->setPosition(Vec2(570,border->getContentSize().height/2-10));
    _stackManager->setVisible(false);
    border->addChild(_stackManager);
    
    _readyGameLayer = LayerColor::create(Color4B(0,0,0,0));
    border->addChild(_readyGameLayer);
    
    MenuItem *attackItem = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(33), Size(100,50),CC_CALLBACK_1(BattleLayer::showSkillList, this));
    MenuItem *monsterListItem = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(34), Size(100,50),CC_CALLBACK_1(BattleLayer::showMonterList, this));
    MenuItem *itemBagItem = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(35), Size(100,50),CC_CALLBACK_1(BattleLayer::showItemContainer, this));
    MenuItem *exitItem = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(3), Size(100,50),CC_CALLBACK_1(BattleLayer::exitBattle, this));
    Menu *button = Menu::create(attackItem,monsterListItem,itemBagItem, exitItem,nullptr);
    button->alignItemsHorizontallyWithPadding(50.0f);
    button->setPosition(Vec2(border->getContentSize().width/2,border->getContentSize().height/2));
    _readyGameLayer->addChild(button);
    
    _skillButtons = Menu::create();
    _skillButtons->setPosition(Vec2(border->getContentSize().width/2,border->getContentSize().height/2+20));
    border->addChild(_skillButtons);
    
    checkMonster(true);
    refreshMonsterInfo();
    
    Player::getInstance()->stopMusic();
    Player::getInstance()->playMusic(SOUND_MUSIC_BATTLE);
    Adaptor::hideAd();
}

void BattleLayer::showSkillList(Ref *ref)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    _readyGameLayer->setVisible(false);
    refreshSkillButtons();
}

void BattleLayer::startStackGame()
{
    log("------Start Stack Game------");
    _stackManager->start();
    _isStackGame = true;
    this->runAction(CCSequence::create(DelayTime::create(4.0f),CallFunc::create(CC_CALLBACK_0(BattleLayer::endStackGame, this)),nullptr));
}
void BattleLayer::endStackGame()
{
    if(_isStackGame)
    {
        this->stopAllActions();
        _isStackGame = false;
        _isPushSkill = false;
        _stackManager->end();
        _battleObject->useSkill(_playerMonSter, _enemyMonSter);
    }
}
void BattleLayer::endStackAnimation()
{
    switch(checkMonster(false))
    {
        case battleCheckType::kBattle:
        {
            log("battle");
            _readyGameLayer->setVisible(true);
            break;
        }
        case battleCheckType::kChange:
        {
             log("change");
            _readyGameLayer->setVisible(true);
            refreshMonsterInfo();
            break;
        }
        case battleCheckType::kWinFinish:
        {
            log("Winfinish");
            _readyGameLayer->setVisible(true);
            ((Character *)_player)->initDataMonster();
            ((Character *)_enemy)->initDataMonster();
            
            if(_battleType==battleType::kCharacterType)
            {
                if(_mapArea!=nullptr)
                    Player::getInstance()->saveLiveEnemyCharacterInfo(false, ((MapArea *)_mapArea)->_currentPoint);
            }
            if(_quest!=nullptr)
            {
                log("quest success");
                QuestPack *questPack = (QuestPack *)_quest;
                if(questPack->getQuestType()==questType::kCharacterWin)
                    QuestConatiner::sharedObject()->successQuestPack(questPack);
            }
            reward();
            finish();
            break;
        }
        case battleCheckType::kLoseFinish:
        {
            log("Losefinish");
            ((Character *)_player)->dieRecoveryMonster();
            ((Character *)_enemy)->recoveryMonster();
            if(_mapArea!=nullptr)
            {
                ((MapArea *)_mapArea)->retunVillage();
                finish();
                if(_battleType==battleType::kCharacterType)
                    Player::getInstance()->saveLiveEnemyCharacterInfo(true, ((MapArea *)_mapArea)->_currentPoint);
            }
            break;
        }
        case battleCheckType::kEvolution:
        {
            evolution();
            break;
        }
        case battleCheckType::kLevelUp:
        {
            levelUp();
            break;
        }
    }
    log("------End Stack Game--------\n");
}

int BattleLayer::checkMonster(bool isFirst)
{
    if(isFirst)
    {
        if(changeMonster(true, _player, _playerHp,_playMonsterPosition))
        {
            if(changeMonster(false, _enemy,_enemyHp,_enemyMonsterPosition))
            {
                regulateMonster();
                return battleCheckType::kChange;
            }
            else
                return battleCheckType::kWinFinish;
        }
        else
            return battleCheckType::kLoseFinish;
        
    }
    else
    {
        bool isBattle = true;
        
        if(((int)_playerMonSter->_shapeData->_health->getShapeValue())<=0)
        {
            isBattle = false;
            if(!changeMonster(true, _player, _playerHp,_playMonsterPosition))
                return battleCheckType::kLoseFinish;
            else
            {
                regulateMonster();
                return battleCheckType::kChange;
            }
        }
        if(((int)_enemyMonSter->_shapeData->_health->getShapeValue())<=0)
        {
            isBattle = false;
            switch (expUp()) {
                case battleCheckType::kEvolution:
                {
                    if(_playerMonSter->isLegend())
                        return battleCheckType::kLevelUp;
                    else
                        return battleCheckType::kEvolution;
                    break;
                }
                case battleCheckType::kLevelUp:
                    return battleCheckType::kLevelUp;
                    break;
                default:
                    break;
            }
            if(changeMonster(false, _enemy,_enemyHp,_enemyMonsterPosition))
            {
                regulateMonster();
                return battleCheckType::kChange;
            }
            else
                return battleCheckType::kWinFinish;
        }
        if(isBattle)
            return battleCheckType::kBattle;
    }
    return battleCheckType::kError;
}
bool BattleLayer::changeMonster(bool isPlayer,cocos2d::Node *user, ProgressTimer *hp,const Vec2& position)
{
    bool find = false;
    
    Character *character = (Character *)user;
    for(int i=1;i<4;i++)
    {
        for(int j=0;j<character->_monsterList->size();j++)
        {
            ShapeCommon *monsterShape = (ShapeCommon *)character->_monsterList->at(j);
            if(monsterShape->_shapeData->_select->getShapeValue()==i)
            {
                if(((int)monsterShape->_shapeData->_health->getShapeValue())>0)
                {
                    while(!monsterShape->_skillQueue.empty())
                    {
                        monsterShape->_skillQueue.pop();
                    }
                    
                    find = true;
                    if(isPlayer)
                    {
                        
                        ShapeCommon *removeMonster = _playerMonSter;
                        _playerMonSter = ShapeCommon::copyShapeCommonImage(monsterShape);
                        _playerMonSter->setFlippedXShape(true);
                        _playerMonSter->_shapeData = monsterShape->_shapeData;
                        _playerMonSter->setPosition(position);
                        _playerMonSter->setVisible(false);
                        _playerMonSter->logStatus();
                        this->addChild(_playerMonSter);
                        
                        if(removeMonster)
                        {
                            endBattleAnimation(removeMonster);
                            _playerMonSter->runAction(Sequence::create(DelayTime::create(0.2f),CallFuncN::create(CC_CALLBACK_1(BattleLayer::startBattleAnimation, this)), NULL));
                        }
                        else
                        {
                            startBattleAnimation(_playerMonSter);
                        }
                    }
                    else
                    {
                        ShapeCommon *removeMonster = _enemyMonSter;
                        _enemyMonSter = ShapeCommon::copyShapeCommonImage(monsterShape);
                        _enemyMonSter->_shapeData = monsterShape->_shapeData;
                        _enemyMonSter->setPosition(position);
                        _enemyMonSter->setVisible(false);
                        _enemyMonSter->logStatus();
                        this->addChild(_enemyMonSter);
                        if(removeMonster)
                        {
                            endBattleAnimation(removeMonster);
                            _enemyMonSter->runAction(Sequence::create(DelayTime::create(0.2f),CallFuncN::create(CC_CALLBACK_1(BattleLayer::startBattleAnimation, this)), NULL));
                        }
                        else
                        {
                            startBattleAnimation(_enemyMonSter);
                        }
                    }
                    hp->runAction(ProgressTo::create(0.2f, monsterShape->_shapeData->_health->getShapeValue()/(monsterShape->_shapeData->_maxHealth->getShapeValue()+ monsterShape->_shapeData->_plusMaxHealth->getShapeValue())*100));
                    break;
                }
            }
        }
        if(find)
            break;
    }
    if(find)
        return true;
    else
        return false;
}
bool BattleLayer::changeMonster(Ref *monster)
{
    ShapeCommon *monsterShape = (ShapeCommon *)monster;
    if(monsterShape->_shapeData->_health->getShapeValue() > 0)
    {
        ShapeCommon *removeMonster = _playerMonSter;
        _playerMonSter = ShapeCommon::copyShapeCommonImage(monsterShape);
        _playerMonSter->_shapeData = monsterShape->_shapeData;
        _playerMonSter->setFlippedXShape(true);
        _playerMonSter->setPosition(_playMonsterPosition);
        _playerMonSter->logStatus();
        _playerMonSter->setVisible(false);
        this->addChild(_playerMonSter);
        if(removeMonster)
        {
            endBattleAnimation(removeMonster);
            _playerMonSter->runAction(Sequence::create(DelayTime::create(0.2f),CallFuncN::create(CC_CALLBACK_1(BattleLayer::startBattleAnimation, this)), NULL));
        }
        else
        {
            startBattleAnimation(_playerMonSter);
        }
        _playerHp->runAction(ProgressTo::create(0.2f, monsterShape->_shapeData->_health->getShapeValue()/(monsterShape->_shapeData->_maxHealth->getShapeValue()+monsterShape->_shapeData->_plusMaxHealth->getShapeValue())*100));
        regulateMonster();
        refreshPlayMonsterInfo();
        return true;
    }
    return false;
}
void BattleLayer::regulateMonster()
{
   float levelGap =  _enemyMonSter->_shapeData->_level->getShapeValue()-_playerMonSter->_shapeData->_level->getShapeValue();
    _stackManager->levelGap(levelGap);
}
void BattleLayer::finish()
{
    Adaptor::showAd();
    Player *player = Player::getInstance();
    player->stopMusic();
    player->playMusic(SOUND_MUSIC_BASE);


    if(_mapArea!=nullptr)
        ((MapArea *)_mapArea)->refreshLoadMap();
    
    if(_beforeLayer!=nullptr)
        _beforeLayer->setVisible(true);
    
    this->removeFromParent();
}
void BattleLayer::reward()
{
    Player *player = Player::getInstance();
    switch(_battleType)
    {
        case battleType::kQuestChracterType:
        {
            player->plusGold(1000);
            break;
        }
        case battleType::kCharacterType:
        {
            if(arc4random()%3==1)
            {
                string content;
                switch(arc4random()%6)
                {
                    case 0:
                        player->_itemList->plusItemWithPopup(ItemType::kItemTypeResorative3, 1);
                        break;
                    case 4:
                        player->_itemList->plusItemWithPopup(ItemType::kItemTypeResorative1, 1);
                        break;
                    case 5:
                        player->_itemList->plusItemWithPopup(ItemType::kItemTypeResorative2, 1);
                        break;
                    case 1:
                        player->_itemList->plusItemWithPopup(ItemType::kItemTypeReturnCity, 1);
                        break;
                    case 2:
                        player->_itemList->plusItemWithPopup(ItemType::kItemTypeTransResorative2, 1);
                        break;
                    case 3:
                        player->_itemList->plusItemWithPopup(ItemType::kItemTypeEradication, 1);
                        break;
                    default:
                        player->_itemList->plusItemWithPopup(ItemType::kItemTypeResorative1, 1);
                        break;
                }
            }
            player->plusGold(1000);
            break;
        }
        case battleType::kBushType:
        {
            int enemyLevel = ((Character *)_enemy)->getSelectMaxLevelMonster();
            int playerLevel =  player->getSelectMaxLevelMonster();
            int difLevel = enemyLevel - playerLevel;
            if(arc4random()%70==21)
            {
                string content;
                switch(arc4random()%3)
                {
                    case 0:
                        player->_itemList->plusItemWithPopup(ItemType::kItemTypePlusPower, 1);
                        break;
                    case 1:
                        player->_itemList->plusItemWithPopup(ItemType::kItemTypePlusAgility, 1);
                        break;
                    case 2:
                        player->_itemList->plusItemWithPopup(ItemType::kItemTypePlusStamina, 1);
                        break;
                }
            }
            else if(difLevel<0)
            {
                player->plusGold(100);
            }
            else if(difLevel==0)
            {
                player->plusGold(200);
            }
            else if(difLevel>0&&difLevel<5)
            {
                player->plusGold(300);
            }
            else if(difLevel>4&&difLevel<10)
            {
                player->plusGold(600);
            }
            else
            {
                player->plusGold(600);
            }
            break;
        }
    }
}

int BattleLayer::expUp()
{
    int diff = _enemyMonSter->_shapeData->_level->getShapeValue() - _playerMonSter->_shapeData->_level->getShapeValue();
    int exp = _enemyMonSter->_shapeData->_level->getShapeValue() * 3;
    Item *item = Player::getInstance()->_itemList->getItem(ItemType::kItemTypeVailLoon);
    if(item!=nullptr)
    {
        float calExp =  exp*((item->getItemLevel() * 0.1f)+0.1f);
        exp = exp+calExp;
    }
    int anotherExp = ((exp/2)>0)?exp/2:0;
    Player::getInstance()->anotherExpUp(anotherExp, (int)_playerMonSter->_shapeData->_select->getShapeValue());
    if(diff>10)
    {
        exp = exp * 7.0f;
    }
    else if(diff>6)
    {
        exp = exp * 5.0f;
    }
    else if(diff>0)
    {
        exp = exp * 3.0f;
    }
    else
    if(_playerMonSter->expUp(exp))
    {
        switch((int)_playerMonSter->_shapeData->_level->getShapeValue())
        {
            case SKILL_THREE:
            case SKILL_FOUR:
                return battleCheckType::kEvolution;
                break;
        }
        return battleCheckType::kLevelUp;
    }
    return battleCheckType::kExp;
}
void BattleLayer::evolution()
{
    Player *plyer = Player::getInstance();
    
    ShapeCommon *evShape;
    for(int j=0;j<plyer->_monsterList->size();j++)
    {
        ShapeCommon *monsterShape = (ShapeCommon *)plyer->_monsterList->at(j);
        if(monsterShape->_shapeData->_select->getShapeValue()==_playerMonSter->_shapeData->_select->getShapeValue())
        {
            evShape = monsterShape;
            evShape->_shapeData = monsterShape->_shapeData;
            break;
        }
    }
    ShapeCommon *evolutionSp =  ShapeCommon::copyShapeCommon(evShape);
    evolutionSp->setPosition(_playerMonSter->getPosition());
    evolutionSp->setFlippedXShape(true);
    evolutionSp->_shapeData = evShape->_shapeData;
    
    _playerMonSter->_imageMid->runAction(Sequence::create(DelayTime::create(0.1f),FadeOut::create(0.2f),FadeIn::create(0.2f),FadeOut::create(0.2f),FadeIn::create(0.2f),FadeOut::create(0.2f), NULL));
    _playerMonSter->_imageTop->runAction(Sequence::create(DelayTime::create(0.1f),FadeOut::create(0.2f),FadeIn::create(0.2f),FadeOut::create(0.2f),FadeIn::create(0.2f), FadeOut::create(0.2f),NULL));
    _playerMonSter->runAction(Sequence::create(DelayTime::create(0.1f),FadeOut::create(0.2f),FadeIn::create(0.2f),FadeOut::create(0.2f),FadeIn::create(0.2f), FadeOut::create(0.2f),NULL));
    
    evolutionSp->setOpacityShape(0);
    evolutionSp->_imageMid->runAction(Sequence::create(DelayTime::create(0.1f),FadeIn::create(0.2f),FadeOut::create(0.2f),FadeIn::create(0.2f),FadeOut::create(0.2f), FadeIn::create(0.2f),NULL));
    evolutionSp->_imageTop->runAction(Sequence::create(DelayTime::create(0.1f),FadeIn::create(0.2f),FadeOut::create(0.2f),FadeIn::create(0.2f),FadeOut::create(0.2f), FadeIn::create(0.2f),NULL));
    evolutionSp->runAction(Sequence::create(DelayTime::create(0.1f),FadeIn::create(0.2f),FadeOut::create(0.2f),FadeIn::create(0.2f),FadeOut::create(0.2f), FadeIn::create(0.2f),DelayTime::create(0.6), CallFuncN::create(CC_CALLBACK_1(BattleLayer::endEvolution, this)),NULL));
    refreshPlayMonsterInfo();
    this->addChild(evolutionSp);
}

void BattleLayer::endEvolution(Ref *ref)
{
    this->removeChild(_playerMonSter);
    _playerMonSter = (ShapeCommon *)ref;
    _playerHp->runAction(ProgressTo::create(0.2f, _playerMonSter->_shapeData->_health->getShapeValue()/(_playerMonSter->_shapeData->_maxHealth->getShapeValue()+_playerMonSter->_shapeData->_plusMaxHealth->getShapeValue())*100));
    
    endEvolutinOrLevelUpData();
}

void BattleLayer::levelUp()
{
    Player::getInstance()->playSound(SOUND_EFFECT_LEVELUP);
    refreshHp();
    refreshPlayMonsterInfo();
    this->runAction(Sequence::create(DelayTime::create(0.7f),CallFuncN::create(CC_CALLBACK_1(BattleLayer::endLevelUp, this)),NULL));
}

void BattleLayer::endLevelUp(Ref *ref)
{
    endEvolutinOrLevelUpData();
}

void BattleLayer::endEvolutinOrLevelUpData()
{
    if(changeMonster(false, _enemy,_enemyHp,_enemyMonsterPosition))
    {
        //battleCheckType::kChange
        regulateMonster();
        _readyGameLayer->setVisible(true);
        refreshMonsterInfo();
    }
    else
    {
        //battleCheckType::kWinFinish
        _readyGameLayer->setVisible(true);
        ((Character *)_player)->initDataMonster();
        ((Character *)_enemy)->initDataMonster();
        
        if(_battleType==battleType::kCharacterType)
        {
            if(_mapArea!=nullptr)
                Player::getInstance()->saveLiveEnemyCharacterInfo(false, ((MapArea *)_mapArea)->_currentPoint);
        }
        if(_quest!=nullptr)
        {
            log("quest success");
            QuestPack *questPack = (QuestPack *)_quest;
            if(questPack->getQuestType()==questType::kCharacterWin)
                QuestConatiner::sharedObject()->successQuestPack(questPack);
        }
        finish();
    }
}
void BattleLayer::exitBattle(Ref *ref)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    if(arc4random()%3==1)
    {
        finish();
    }
    else
    {
        (GameScene::runningScene())->createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(36).c_str(), CC_CALLBACK_1(BattleLayer::failExit,this));
    }
}
void BattleLayer::failExit(Ref *ref)
{
    attackEnemy();
}
void BattleLayer::attackEnemy()
{
    _readyGameLayer->setVisible(false);
    _battleObject->useSkill(_playerMonSter, _enemyMonSter,false);
}
 int BattleLayer::catchMonster()
{
    if(_battleType==battleType::kCharacterType || _battleType==battleType::kQuestChracterType)
    {
        (GameScene::runningScene())->createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(37).c_str(), nullptr);
        return catchType::kError;
    }
    else
    {
        float hpPercent = _enemyMonSter->_shapeData->_health->getShapeValue()/(_enemyMonSter->_shapeData->_maxHealth->getShapeValue()+_enemyMonSter->_shapeData->_plusMaxHealth->getShapeValue())*100;
        _enemyMonSter->_shapeData->_select->setShapeValue(0);
        Item *item = Player::getInstance()->_itemList->getItem(ItemType::kItemStamp);
        if(item!=nullptr)
        {
            float compare =  9 -  _enemyMonSter->getClassAll();
            bool isLegend =  _enemyMonSter->getLegendValue();
            if(isLegend)
            {
                if(hpPercent<=10)
                {
                    if(arc4random()%10000==25)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }
                else if(hpPercent<=5)
                {
                    if(arc4random()%1000==25)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }
                else if(hpPercent<=1)
                {
                    if(arc4random()%100==25)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }

            }
            else if(_enemyMonSter->getClassAll()>=0&&_enemyMonSter->getClassAll()<3)
            {
                if(hpPercent<=10)
                {
                    if(arc4random()%30==1)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }
                if(hpPercent<=20)
                {
                    if(arc4random()%50==1)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }
                else
                {
                    if(arc4random()%50==2)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }

            }
            else if(item->getItemLevel() >= compare)
            {
                if(hpPercent<=10)
                {
                    if(arc4random()%2==1)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }
                if(hpPercent<=30)
                {
                    if(arc4random()%3==1)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }
                else if(hpPercent<=50)
                {
                    if(arc4random()%5==1)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }
                else if(hpPercent<=80)
                {
                    if(arc4random()%10==5)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }
                else
                {
                    if(arc4random()%20==5)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }
            }
            else
            {
                if(hpPercent<=10)
                {
                    if(arc4random()%10==5)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }
                else if(hpPercent<=30)
                {
                    if(arc4random()%20==5)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }
                else if(hpPercent<=50)
                {
                    if(arc4random()%30==5)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }
                else if(hpPercent<=80)
                {
                    if(arc4random()%50==5)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }
                else
                {
                    if(arc4random()%70==5)
                    {
                        Player::getInstance()->pushMonster(_enemyMonSter);
                        return catchType::kCatch;
                    }
                }
            }
            
        }
        
    }
    return catchType::kFail;
}
void BattleLayer::catchMonsterAnimation()
{
    _tempScale = _enemyMonSter->getScale();
    _enemyMonSter->runAction(Sequence::create(ScaleTo::create(0.3f, 0.0f), CallFunc::create(CC_CALLBACK_0(BattleLayer::endCatchMonsterAnimation, this)),NULL));
}
void BattleLayer::endCatchMonsterAnimation()
{
    Label *label = Label::createWithTTF("Catch!",CommonUtils::getFontName(),50);
    label->setColor(Color3B::BLACK);
    label->setScale(0.0f);
    label->setPosition(Vec2(_enemyMonsterPosition.x,_enemyMonsterPosition.y+50));
    label->runAction(Sequence::create(EaseSineInOut::create(ScaleTo::create(0.2f, 1.0f)),DelayTime::create(0.3f), CallFunc::create(CC_CALLBACK_0(BattleLayer::finish, this)),NULL));
    this->addChild(label);
}
void BattleLayer::catchFailMonsterAnimation()
{
    _tempScale = _enemyMonSter->getScale();
    _enemyMonSter->runAction(Sequence::create(ScaleTo::create(0.3f, 0.0f), EaseSineInOut::create(ScaleTo::create(0.3f, _tempScale)),CallFunc::create(CC_CALLBACK_0(BattleLayer::endCatchFailMonsterAnimation, this)),NULL));
}
void BattleLayer::endCatchFailMonsterAnimation()
{
    _enemyMonSter->catchFailAnimation();
}

void BattleLayer::showMonterList(Ref *ref)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    GameScene *scene = (GameScene::runningScene());
    MonsterChangeLayer *layer = MonsterChangeLayer::create(this,0);
    layer->setPosition(Vec2(scene->getContentSize().width/2, scene->getContentSize().height/2));
    scene->addChild(layer);
}
void BattleLayer::showItemContainer(Ref *ref)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    GameScene *scene = (GameScene::runningScene());
    ItemBagLayer*layer = ItemBagLayer::create(this, true);
    layer->setPosition(Vec2(scene->getContentSize().width/2, scene->getContentSize().height/2));
    scene->addChild(layer);
}
void BattleLayer::refreshHp()
{
    ShapeObject *shapeData =  _playerMonSter->_shapeData;
    _playerHp->runAction(ProgressTo::create(0.2f, shapeData->_health->getShapeValue()/(shapeData->_maxHealth->getShapeValue()+shapeData->_plusMaxHealth->getShapeValue())*100));
}

void BattleLayer::refreshMonsterInfo()
{
    auto temp = __String::createWithFormat("Lv %d  %s  C:%s", (int)_playerMonSter->_shapeData->_level->getShapeValue(), _playerMonSter->getFullName(), _playerMonSter->getClassAllName());
    _playerLabel->setString(temp->getCString());
    temp = __String::createWithFormat("Lv %d  %s  C:%s", (int)_enemyMonSter->_shapeData->_level->getShapeValue(), _enemyMonSter->getFullName(),_enemyMonSter->getClassAllName());
    _enemyLabel->setString(temp->getCString());
}
void BattleLayer::refreshPlayMonsterInfo()
{
    auto temp = __String::createWithFormat("Lv %d  %s  C:%s", (int)_playerMonSter->_shapeData->_level->getShapeValue(), _playerMonSter->getFullName(),_playerMonSter->getClassAllName());
    _playerLabel->setString(temp->getCString());
}
void BattleLayer::refreshSkillButtons()
{
    _skillButtons->removeAllChildren();
    int level = (int)_playerMonSter->_shapeData->_level->getShapeValue();
    createSkillButton("skill1.png", _playerMonSter->_shapeData->_skill1->_skillName.c_str(),level<SKILL_FIRST,SKILL_FIRST);
    createSkillButton("skill2.png",  _playerMonSter->_shapeData->_skill2->_skillName.c_str(),level<SKILL_TWO,SKILL_TWO);
    createSkillButton("skill3.png",  _playerMonSter->_shapeData->_skill3->_skillName.c_str(),level<SKILL_THREE,SKILL_THREE);
    createSkillButton("skill4.png",  _playerMonSter->_shapeData->_skill4->_skillName.c_str(),level<SKILL_FOUR,SKILL_FOUR);
    MenuItem *skill = CommonUtils::createMenuItem("skillExit.png", CC_CALLBACK_1(BattleLayer::clickSkillExit,this));
    _skillButtons->addChild(skill);
    _skillButtons->alignItemsHorizontallyWithPadding(30.0f);

}
void BattleLayer::createSkillButton(const char*skillButton, const char *skillName,  bool isLock, int index)
{
    MenuItem *skill;
    if(isLock)
    {
        skill = CommonUtils::createMenuItem("lock.png", nullptr);
        _skillButtons->addChild(skill);
    }
    else
    {
        skill = CommonUtils::createMenuItem(skillButton, CC_CALLBACK_1(BattleLayer::clickSkill,this));
        skill->setTag(index);
        _skillButtons->addChild(skill);
    }
    
    Label *skillNameLabel = Label::createWithTTF(skillName, CommonUtils::getFontName(), 20);
    CommonUtils::setLabelAutoSize(skillNameLabel,20, Size(skill->getContentSize().width+15,25));
    skillNameLabel->setPosition(Vec2(skill->getContentSize().width/2, -skillNameLabel->getContentSize().height/2));
    skillNameLabel->setColor(Color3B::BLACK);
    skill->addChild(skillNameLabel);
}
void BattleLayer::clickSkill(Ref *ref)
{
    if(!_isPushSkill)
    {
        _isPushSkill = true;
        Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
        int index = ((Node *)ref)->getTag();
        _skillButtons->removeAllChildren();
        _battleObject->initBattleData();
        _stackManager->resetSkill();
        switch (index) {
            case SKILL_FIRST:
                _battleObject->doPushSkill(_playerMonSter, _playerMonSter->_shapeData->_skill1);
                _stackManager->addSkill(1);
                break;
            case SKILL_TWO:
                _battleObject->doPushSkill(_playerMonSter, _playerMonSter->_shapeData->_skill2);
                _stackManager->addSkill(2);
                break;
            case SKILL_THREE:
                _battleObject->doPushSkill(_playerMonSter, _playerMonSter->_shapeData->_skill3);
                _stackManager->addSkill(3);
                break;
            case SKILL_FOUR:
                _battleObject->doPushSkill(_playerMonSter, _playerMonSter->_shapeData->_skill4);
                _stackManager->addSkill(4);
                break;
            default:
                break;
        }
        startStackGame();
    }
}
void BattleLayer::clickSkillExit(Ref *ref)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    _skillButtons->removeAllChildren();
    _readyGameLayer->setVisible(true);
}

void BattleLayer::startBattleAnimation(Node *target)
{
    _tempScale = target->getScale();
    target->setScale(0.0f);
    target->setVisible(true);
    target->runAction(ScaleTo::create(0.2f, _tempScale));
}
void BattleLayer::endBattleAnimation(Node *target)
{
    target->runAction(Sequence::create(ScaleTo::create(0.2f, 0.0f), CallFuncN::create(CC_CALLBACK_1(BattleLayer::removeNode, this)),NULL));
}
void BattleLayer::removeNode(Node *target)
{
    target->removeFromParent();
}

