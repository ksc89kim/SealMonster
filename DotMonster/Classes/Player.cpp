//
//  Player.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 6..
//
//

#include "Player.h"
#include "Quest.h"
#include "Base64P.h"
#include "LoadingLayer.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

Player* Player::_player = nullptr;

Player::Player()
{
    _mapInfo = "map/map_1_1.plist";
    _currentMapPoint = 1;
    _beforeMapPoint = _currentMapPoint;
    _gold = ShapeValue::create("G", "D");
    _gold->setShapeValue(0);
    _isLoad = false;
    _isStartLoad = false;
    _mapSprite = "field/field01.png";
    _frontSprite = "field/field02.png";
    _leftSprite = "field/field03.png";
    _rightSprite = "field/field03.png";
    _backSprite = "field/field04.png";
    _isSound = UserDefault::getInstance()->getBoolForKey(SOUND_ON_OFF, true);
    _isMusic = UserDefault::getInstance()->getBoolForKey(MUSIC_ON_OFF, true);
    _isTutorial= UserDefault::getInstance()->getBoolForKey(TUTORIAL_ON_OFF, false);
}

Player::~Player()
{
    if(_gold)
        _gold->release();
}

Player *Player::getInstance()
{
    if(_player==nullptr)
    {
        _player = new Player();
        _player->setImage();
        _player->_itemList = ItemContainer::create(_player);
        _player->addChild(_player->_itemList);

    }
    return _player;
}

bool Player::isMonster()
{
    bool find = false;
    for(int i=1;i<4;i++)
    {
        for(int j=0;j<_monsterList->size();j++)
        {
            ShapeCommon *monsterShape = (ShapeCommon *)_monsterList->at(j);
            if(monsterShape->_shapeData->_select->getShapeValue()==i)
            {
                if(monsterShape->_shapeData->_health->getShapeValue()>0)
                {
                    find = true;
                    break;
                }
            }
        }
        if(find)
            break;
    }
    return find;
}

bool Player::isLiveEnemyCharacterInfo(cocos2d::Node *mapPoint)
{
    std::vector<std::string> mapInfo = (&CommonUtils::getInstance())->splits(Player::getInstance()->_mapInfo, "_");
    std::vector<std::string> data = (&CommonUtils::getInstance())->splits(mapInfo[2].c_str(), ".");
    __String *key = __String::createWithFormat("%s_%s_%d", mapInfo[1].c_str(), data[0].c_str(), mapPoint->getTag());
    if(getEnemyCharacterInfo(key->getCString()))
        return true;
    else
        return false;
}
void Player::saveLiveEnemyCharacterInfo(bool isLive,cocos2d::Node *mapPoint)
{
    std::vector<std::string> mapInfo = (&CommonUtils::getInstance())->splits(Player::getInstance()->_mapInfo, "_");
    std::vector<std::string> data = (&CommonUtils::getInstance())->splits(mapInfo[2].c_str(), ".");
    __String *key = __String::createWithFormat("%s_%s_%d", mapInfo[1].c_str(), data[0].c_str(), mapPoint->getTag());
    ValueMap::iterator iter = _enemyCharactersInfo.find(key->getCString());
    if(iter != _enemyCharactersInfo.end())
    {
        _enemyCharactersInfo.erase(key->getCString());
        Value liveData(EncryptUtil::Encrypt(isLive));
        _enemyCharactersInfo.insert(std::map<std::string,Value>::value_type(key->getCString(),liveData));
    }else
    {
        Value liveData(EncryptUtil::Encrypt(isLive));
        _enemyCharactersInfo.insert(std::map<std::string,Value>::value_type(key->getCString(),liveData));
    }
}
bool Player::getEnemyCharacterInfo(std::string key)
{
    ValueMap::iterator iter = _enemyCharactersInfo.find(key.c_str());
    if(iter != _enemyCharactersInfo.end())
    {
        return EncryptUtil::DecryptInt(_enemyCharactersInfo.at(key.c_str()).asString());
    }
    else
        return true;
}
void Player::save()
{
    log("------------------------------save----------------------------");
    LoadingLayer *layer = LoadingLayer::create();
    layer->startLoading();
    Director::getInstance()->getRunningScene()->addChild(layer);
    UserDefault::getInstance()->setStringForKey("mapInfo", Base64P::enCode(_mapInfo));
    UserDefault::getInstance()->setStringForKey("currentMapPoint", Base64P::enCode(_currentMapPoint));
    UserDefault::getInstance()->setStringForKey("beforeMapPoint", Base64P::enCode(_beforeMapPoint));
    GameScene *scene = GameScene::runningScene();
    if(scene)
    {
        MapArea *mapArea = scene->getMapLayer()->getMapArea();
        UserDefault::getInstance()->setStringForKey("eradicationItem", Base64P::enCode(mapArea->getEradicationItem()));
        UserDefault::getInstance()->setStringForKey("temptationItem", Base64P::enCode(mapArea->getTemptationItem()));
        UserDefault::getInstance()->setStringForKey("visibleCaveItem", Base64P::enCode(mapArea->getVisibleCaveItem()));
    }
    UserDefault::getInstance()->setStringForKey("gold", Base64P::enCode(_gold->getShapeValue()));
    UserDefault::getInstance()->setStringForKey("monsterListSize", Base64P::enCode((int)_monsterList->size()));
    for(int i=0;i<_monsterList->size();i++)
    {
        ShapeCommon *monsterShape = (ShapeCommon *)_monsterList->at(i);
        ShapeObject *shapeData = monsterShape->_shapeData;

        __String *key = __String::createWithFormat("monster_%d_type", i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(shapeData->_type->getShapeValue()));
        key->initWithFormat("monster_%d_health",i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(shapeData->_health->getShapeValue()));
        key->initWithFormat("monster_%d_classNumber_1",i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(shapeData->_name->getFirstNumber()));
        key->initWithFormat("monster_%d_classNumber_2",i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(shapeData->_name->getMidNumber()));
        key->initWithFormat("monster_%d_classNumber_3",i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(shapeData->_name->getLastNumber()));
        
        key->initWithFormat("monster_%d_level",i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(shapeData->_level->getShapeValue()));
        key->initWithFormat("monster_%d_exp",i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(shapeData->_exp->getShapeValue()));
        key->initWithFormat("monster_%d_select",i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(shapeData->_select->getShapeValue()));
        key->initWithFormat("monster_%d_legend",i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(shapeData->_isLegend->getShapeValue()));
        key->initWithFormat("monster_%d_plusPower",i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(shapeData->_plusPower->getShapeValue()));
        key->initWithFormat("monster_%d_plusMaxHealth",i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(shapeData->_plusMaxHealth->getShapeValue()));
        key->initWithFormat("monster_%d_plusAgility",i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(shapeData->_plusAgility->getShapeValue()));

    }
    UserDefault::getInstance()->setStringForKey("itemListSize", Base64P::enCode(_itemList->size()));
    for(int i=0;i<_itemList->size();i++)
    {
        Item *item = _itemList->getIndexItem(i);
        __String *key = __String::createWithFormat("item_%d_type", i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(item->_itemType));
        key->initWithFormat("item_%d_level",i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(item->getItemLevel()));
        key->initWithFormat("item_%d_count",i);
        UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(item->getItemCount()));
    }
    for(int i=0;i<QuestConatiner::sharedObject()->size();i++)
    {
        QuestPack *questPack = QuestConatiner::sharedObject()->getQuestPackIndex(i);
        for(int j=0;j<questPack->size();j++)
        {
            Quest *quest = questPack->getQuest(j);
            quest->questLog();
            __String *key = __String::createWithFormat("quest_%d_index_%d", i,j);
            UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(quest->getQuestIndex()));
            key->initWithFormat("quest_%d_level_%d",i,j);
            UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(quest->getQuestLevel()));
            key->initWithFormat("quest_%d_status_%d",i,j);
            UserDefault::getInstance()->setStringForKey(key->getCString(), Base64P::enCode(quest->getStatus()));
        }
    }
    UserDefault::getInstance()->setBoolForKey("isLoadData", true);
    UserDefault::getInstance()->flush();
    FileUtils::getInstance()->writeToFile(_enemyCharactersInfo, FileUtils::getInstance()->getWritablePath()+ENEMY_FILE_PATH);
    layer->stopLoading();
    Director::getInstance()->getRunningScene()->removeChild(layer);
    log("------------------------------save----------------------------");
}
void Player::load()
{
    if(!_isStartLoad) return;
    
    log("------------------------------load----------------------------");
    log("file Path = %s", UserDefault::getInstance()->getXMLFilePath().c_str());
    
    LoadingLayer *layer = LoadingLayer::create();
    layer->startLoading();
    Director::getInstance()->getRunningScene()->addChild(layer);

    _mapInfo = Base64P::deCode(UserDefault::getInstance()->getStringForKey("mapInfo"));
    //_mapInfo = "map/map_5_6.plist"; //sc
    _currentMapPoint = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey("currentMapPoint"));
    //_currentMapPoint = 60; //sc
    _beforeMapPoint = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey("beforeMapPoint"));
    //_beforeMapPoint = 60; //sc
    
    GameScene *scene = GameScene::runningScene();
    if(scene)
    {
        MapArea *mapArea = scene->getMapLayer()->getMapArea();
       int eradicationItem = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey("eradicationItem"));
        int temptationItem = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey("temptationItem"));
        int visibleCaveItem = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey("visibleCaveItem"));
        mapArea->setEradicationItem((eradicationItem>0)?true:false);
        mapArea->setTemptationItem((temptationItem>0)?true:false);
        mapArea->setVisibleCaveItem((visibleCaveItem>0)?true:false);
    }
    
    _gold->setShapeValue(Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey("gold")));
    //_gold->setShapeValue(999999);
    int size = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey("monsterListSize"));
    _monsterList->clear();
    for(int i=0;i<size;i++)
    {
        __String *key = __String::createWithFormat("monster_%d_type", i);
        int type = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString()));
        ShapeCommon *shape;
        switch (type) {
            case bushType::kBushShapeF:
                shape = ShapeF::create();
                break;
            case bushType::kBushShapeW:
                shape = ShapeW::create();
                break;
            case bushType::kBushShapeT:
                shape = ShapeT::create();
                break;
            case bushType::kBushShapeI:
                shape = ShapeI::create();
                break;
            case bushType::kBushShapeZ:
                shape = ShapeZ::create();
                break;
            default:
                break;
        }
        ShapeObject *shapeData = shape->_shapeData;
        
        key->initWithFormat("monster_%d_level",i);
        shapeData->_level->setShapeValue(Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString())));
        //shapeData->_level->setShapeValue(9999);//sc
        key->initWithFormat("monster_%d_exp",i);
        shapeData->_exp->setShapeValue(Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString())));
        key->initWithFormat("monster_%d_select",i);
        shapeData->_select->setShapeValue(Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString())));
        
        key->initWithFormat("monster_%d_classNumber_1",i);
        int classNumber1 = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString()));
        key->initWithFormat("monster_%d_classNumber_2",i);
        int classNumber2 = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString()));
        key->initWithFormat("monster_%d_classNumber_3",i);
        int classNumber3 = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString()));
        shape->changeFindShape(classNumber1, classNumber2, classNumber3);
        
        key->initWithFormat("monster_%d_legend",i);
        bool isLegend = (Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString()))>0)? true:false;
        //isLegend = true; //sc
        if(isLegend)
        {
            shape->setLegend(isLegend);
        }
        
        key->initWithFormat("monster_%d_health",i);
        shapeData->_health->setShapeValue(Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString())));
        
        key->initWithFormat("monster_%d_plusPower",i);
        shapeData->_plusPower->setShapeValue(Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString())));
        key->initWithFormat("monster_%d_plusMaxHealth",i);
        shapeData->_plusMaxHealth->setShapeValue(Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString())));
        key->initWithFormat("monster_%d_plusAgility",i);
        shapeData->_plusAgility->setShapeValue(Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString())));
        shape->logStatus();
        _monsterList->pushBack(shape);
    }

    size = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey("itemListSize"));
    _itemList->clear();
    for(int i=0;i<size;i++)
    {
        __String *key = __String::createWithFormat("item_%d_type", i);
        int type = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString()));
        key->initWithFormat("item_%d_level",i);
        int level = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString()));
        key->initWithFormat("item_%d_count",i);
        int count = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString()));
        _itemList->pushItem(Item::create(type, level, count,nullptr));
    }
    /*
    _itemList->pushItem(Item::create(ItemType::kItemTypePlusTransPower, 5, 1, nullptr)); //sc
    _itemList->pushItem(Item::create(ItemType::kItemTypePlusTransAgility, 5, 1, nullptr)); //sc
    _itemList->pushItem(Item::create(ItemType::kItemTypePlusTransStamina, 5, 1, nullptr)); //sc
     */
    /*
    _itemList->pushItem(Item::create(ItemType::kItemStamp, 1, 1, nullptr));
    _itemList->pushItem(Item::create(ItemType::kItemTypeRailLoon, 1, 1, nullptr));
    _itemList->pushItem(Item::create(ItemType::kItemTypeVailLoon, 2, 1, nullptr));
    _itemList->pushItem(Item::create(ItemType::kItemTypeQailLoon, 3, 1, nullptr));
    _itemList->pushItem(Item::create(ItemType::kItemTypeZailLoon, 4, 1, nullptr));
    _itemList->pushItem(Item::create(ItemType::kItemTypeNailLoon, 1, 1, nullptr));
    */
    
    for(int i=0;i<QuestConatiner::sharedObject()->size();i++)
    {
        QuestPack *questPack = QuestConatiner::sharedObject()->getQuestPackIndex(i);
        for(int j=0;j<questPack->size();j++)
        {
            __String *key = __String::createWithFormat("quest_%d_index_%d", i,j);
            int questIndex = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString()));
            key->initWithFormat("quest_%d_level_%d",i,j);
            int questlevel = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString()));
            key->initWithFormat("quest_%d_status_%d",i,j);
            int queststatus = Base64P::deCodeInt(UserDefault::getInstance()->getStringForKey(key->getCString()));
            /*
            if(questIndex==questIndex::kMasterSealQuest)
            {
                if(questlevel<=5)
                {
                    queststatus = questStatus::kSuccess;
                }
                else if(questlevel==6)
                {
                    queststatus = questStatus::kIng;
                }
            }*/ //sc
            QuestConatiner::sharedObject()->changeQuestData(questIndex, questlevel, queststatus);
        }
    }
    if(FileUtils::getInstance()->isFileExist(FileUtils::getInstance()->getWritablePath()+ENEMY_FILE_PATH))
    {
        _enemyCharactersInfo = FileUtils::getInstance()->getValueMapFromFile(FileUtils::getInstance()->getWritablePath()+ENEMY_FILE_PATH);
    }
    
    _isLoad = true;
    layer->stopLoading();
    Director::getInstance()->getRunningScene()->removeChild(layer);

    log("------------------------------load----------------------------");
}
void Player::pushMonster(ShapeCommon *monster)
{
    log("getSelectMonsterIndex() %d",getSelectMonsterIndex());
    monster->_shapeData->_select->setShapeValue(getSelectMonsterIndex());
    _monsterList->pushBack(ShapeCommon::copyShapeCommon(monster));
}
int Player::getSelectMonsterIndex()
{
    int selectIndex = 0;
    for(int i=0;i<_monsterList->size();i++)
    {
        ShapeCommon *monster = (ShapeCommon *)_monsterList->at(i);
        if(monster->_shapeData->_select->getShapeValue()>selectIndex)
        {
            selectIndex = monster->_shapeData->_select->getShapeValue();
        }
        if(selectIndex>=3)
            break;
    }
    if(selectIndex>=0&&selectIndex<3)
    {
        return selectIndex+1;
    }
    return 0;
}

void Player::setSelectMonster(ShapeCommon *monster, int index)
{
    for(int i=0;i<_monsterList->size();i++)
    {
        ShapeCommon *catchMonster = (ShapeCommon *)_monsterList->at(i);
        if(catchMonster!=monster&&index==((int)catchMonster->_shapeData->_select->getShapeValue()))
        {
            catchMonster->_shapeData->_select->setShapeValue(0);
        }
        else if(catchMonster==monster)
        {
            catchMonster->_shapeData->_select->setShapeValue(index);
        }
    }
}

void Player::anotherExpUp(int exp, int selectNum)
{
    for(int i=1;i<=3;i++)
    {
        for(int j=0;j<_monsterList->size();j++)
        {
            ShapeCommon *monster = (ShapeCommon *)_monsterList->at(j);
            int select = (int)monster->_shapeData->_select->getShapeValue();
            if(select==i && selectNum!=select)
            {
                monster->expUp(exp);
                break;
            }
        }
    }
}
void Player::plusGold(float gold)
{
    Item *item = _itemList->getItem(ItemType::kItemTypeRailLoon);
    if(item!=nullptr)
    {
        float calGold =  gold*((item->getItemLevel() * 0.1f)+0.1f);
        _gold->addShapeValue(gold+calGold);
    }
    else
        _gold->addShapeValue(gold);
}
void Player::minusGold(float gold)
{
    _gold->minusShapeValue(gold);
}
float Player::getGold()
{
    return _gold->getShapeValue();
}

const char* Player::getCharacterFrontSprite()
{
    return _frontSprite.c_str();
}
const char* Player::getCharacterBackSprite()
{
    return _backSprite.c_str();
}
const char* Player::getCharacterLeftSprite()
{
    return _leftSprite.c_str();
}
const char* Player::getCharacterRightSprite()
{
    return _rightSprite.c_str();
}
void Player::clearData()
{
    _gold->setShapeValue(0);
    _isLoad = false;
    _isStartLoad = false;
    _mapInfo = "map/map_1_1.plist";
    _currentMapPoint = 1;
    _beforeMapPoint = _currentMapPoint;
    _monsterList->clear();
    _itemList->clear();
    QuestConatiner::sharedObject()->_questPackList->clear();
    QuestConatiner::sharedObject()->setValue();
    _enemyCharactersInfo.clear();
}


void Player::playSound(const std::string &name)
{
    if(_isSound)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(name.c_str());
    }
}
void Player::playMusic(const std::string &name)
{
    if(_isMusic)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(name.c_str(),true);
    }
}
void Player::stopMusic()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
void Player::pauseMusic()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void Player::resumeMusic()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void Player::setSound(bool isSound)
{
    _isSound = isSound;
    UserDefault::getInstance()->setBoolForKey(SOUND_ON_OFF, isSound);
    UserDefault::getInstance()->flush();
}
void Player::setMusic(bool isMusic)
{
    _isMusic = isMusic;
    UserDefault::getInstance()->setBoolForKey(MUSIC_ON_OFF, isMusic);
    UserDefault::getInstance()->flush();
}
bool Player::getSound()
{
    return _isSound;
}
bool Player::getMusic()
{
    return _isMusic;
}
int Player::getMonsterScore()
{
    int score = 0;
    for(int i=1;i<=3;i++)
    {
        for(int j=0;j<_monsterList->size();j++)
        {
            ShapeCommon *monster = (ShapeCommon *)_monsterList->at(j);
            int select = (int)monster->_shapeData->_select->getShapeValue();
            ShapeObject *shapeData = monster->_shapeData;
            if(select==i)
            {
                score += ((int)shapeData->_power->getShapeValue()) * 15;
                score += ((int)shapeData->_agility->getShapeValue()) * 15;
                score += ((int)shapeData->_plusPower->getShapeValue()) * 15;
                score += ((int)shapeData->_plusAgility->getShapeValue()) * 10;
                score += ((int)shapeData->_plusMaxHealth->getShapeValue());
                ShapeObject *tempObject = monster->getStatusObject(shapeData->_name->getLastNumber());
                score += ((int)tempObject->_power->getShapeValue()) * 15;;
                break;
            }
        }
    }
    
    return score;
}
void Player::setTutorial(bool tutorial)
{
    _isTutorial = tutorial;
    UserDefault::getInstance()->setBoolForKey(TUTORIAL_ON_OFF, _isTutorial);
    UserDefault::getInstance()->flush();
}
bool Player::getTutorial()
{
    return _isTutorial;
}