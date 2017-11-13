//
//  MapArea.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 5..
//
//

#include "MapArea.h"
#include "BattleLayer.h"
#include "TalkLayer.h"
#include "VillageLayer.h"
#include "Base64P.h"
#include "MapLayer.h"
#include "GameScene.h"
#include "Tutorial.h"
#include "UpgradeLoonShop.h"

MapArea::MapArea()
{
    _isTouch = false;
    _space = 130;
    _moveDelay = 0.3f;
    _width = (_space*MAP_WIDTH)+(83*MAP_WIDTH);//83 imageWidth
    _height = (_space*MAP_HEIGHT)+(60*MAP_HEIGHT); //60 imageHeight
    _moveEventPoint = 0;
    _isEradicationItem = false;
    _isTemptationItem = false;
    _isVisibleCaveItem = false;
}

MapArea::~MapArea()
{
    
}

MapArea *MapArea::create()
{
    MapArea* pRet = new MapArea();
    if (pRet && pRet->initWithViewSize(Director::getInstance()->getWinSize()))
    {
        pRet->setImage();
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}
void MapArea::setImage()
{
    _background=LayerColor::create(Color4B(200,255,200,0),_width,_height);
    setContainer(_background);
    setBounceable(false);
    refreshLoadMap();
}
void MapArea::decryptMap(const char *file)
{
    _mapData.clear();
    _mapData = FileUtils::getInstance()->getValueMapFromFile(file);
    
    for (int i=1;i<=MAP_HEIGHT*MAP_WIDTH;i++) {
        ValueMap mapData = _mapData.at(__String::createWithFormat("%d", i)->getCString()).asValueMap();
        const char *key = __String::createWithFormat("%d", i)->getCString();
        if(mapData.at("isSelected").asInt())
        {
            decryptData("mapType",key);
            decryptData("mapInfoType",key);
            decryptData("bushInfo",key);
            decryptData("characterType",key);
            decryptData("characterMonster1",key);
            decryptData("characterMonster2",key);
            decryptData("characterMonster3",key);
            decryptData("questCharacterIndex",key);
            decryptData("questIndex",key);
            decryptData("questLevel",key);
            decryptData("mapMove",key);
            decryptData("village",key);
        }
    }
}
void MapArea::decryptData(const char *key, const char *index)
{

    ValueMap mapData = _mapData.at(index).asValueMap();
    if(mapData.at(key).asString().compare(""))
    {
        log("==============decryptData=================");
        log("key %s", key);
        log("index %s", index);
        log("mapData.at(key).asString() %s",mapData.at(key).asString().c_str());
        std::string temp = EncryptUtil::Decrypt(mapData.at(key).asString());
        log("temp %s", temp.c_str());
        mapData[key] = temp;
        _mapData[index] = mapData;

    }
}

void MapArea::decodeMap(const char *file)
{
    _mapData.clear();
    _mapData = FileUtils::getInstance()->getValueMapFromFile(file);
    
    for (int i=1;i<=MAP_HEIGHT*MAP_WIDTH;i++) {
        ValueMap mapData = _mapData.at(__String::createWithFormat("%d", i)->getCString()).asValueMap();
        const char *key = __String::createWithFormat("%d", i)->getCString();
        if(mapData.at("isSelected").asInt())
        {
            decodeBase64p(_mapData,"mapType",key);
            decodeBase64p(_mapData,"mapInfoType",key);
            decodeBase64p(_mapData,"bushInfo",key);
            decodeBase64p(_mapData,"characterType",key);
            decodeBase64p(_mapData,"characterMonster1",key);
            decodeBase64p(_mapData,"characterMonster2",key);
            decodeBase64p(_mapData,"characterMonster3",key);
            decodeBase64p(_mapData,"questCharacterIndex",key);
            decodeBase64p(_mapData,"questIndex",key);
            decodeBase64p(_mapData,"questLevel",key);
            decodeBase64p(_mapData,"mapMove",key);
            decodeBase64p(_mapData,"village",key);
        }
    }

}
void MapArea::decodeBase64p(ValueMap &map,const char *key, const char *index)
{
    ValueMap mapData = map.at(index).asValueMap();
    if(mapData.at(key).asString().compare(""))
    {
        std::string temp = mapData.at(key).asString();
        mapData[key] =  Base64P::deCode(temp);
        map[index] = mapData;
    }
}

void MapArea::setImageMap(const char *file)
{
    decodeMap(file);
    int tag = 1;
    for (int i=0; i<MAP_HEIGHT; i++) {
        for (int j=0; j<MAP_WIDTH; j++) {
            ValueMap mapData = _mapData.at(__String::createWithFormat("%d", tag)->getCString()).asValueMap();
            if(mapData.at("isSelected").asInt())
            {
                int mapType = getIntMapData(mapData, "mapType");
                int mapInfoType = getIntMapData(mapData, "mapInfoType");
                int villageInfo = getIntMapData(mapData, "village");
                std::string moveData = getStringMapData(mapData, "mapMove");
                Quest *quest = getQuestData(mapData);
                Node *bush = getBushData(mapData);
                std::string questCharacter = getStringMapData(mapData, "questCharacterIndex");
                int moveEvent = getIntMapData(mapData, "moveEvent");
                MapPoint *mapPoint = MapPoint::create(tag,mapType, mapInfoType,villageInfo,moveEvent, moveData.c_str(),questCharacter.c_str(),getCharacterData(mapData),quest,bush);
                mapPoint->setPosition(Vec2((mapPoint->getContentSize().width*j)+(_space*(j+1)),_height-((mapPoint->getContentSize().height*i)+(_space*(i+1)))));
                _background->addChild(mapPoint,layer_3);
                mapPoint->checkPointSprite();
                mapPoint->checkTypeSprite();
            }
            tag++;
        }
    }
    for(int i=1;i<=MAP_HEIGHT*MAP_WIDTH;i++)
    {
        ValueMap mapData = _mapData.at(__String::createWithFormat("%d", i)->getCString()).asValueMap();
        if(mapData.at("isSelected").asInt())
        {
           MapPoint *mapPoint = (MapPoint *)_background->getChildByTag(i);
            int left = mapData.at("left").asInt();
            int right  = mapData.at("right").asInt();
            int top  = mapData.at("top").asInt();
            int bottom  = mapData.at("bottom").asInt();
            bool isRightEnd = (i%MAP_WIDTH==0)?true:false;
            bool isLeftEnd = (i%MAP_WIDTH==1)?true:false;
            if(left&&!isLeftEnd)
               mapPoint->_left = (MapPoint *)_background->getChildByTag(left);
            if(right&&!isRightEnd)
                mapPoint->_right = (MapPoint *)_background->getChildByTag(right);
            if(top)
                mapPoint->_top = (MapPoint *)_background->getChildByTag(top);
            if(bottom)
                mapPoint->_bottom = (MapPoint *)_background->getChildByTag(bottom);
        }
    }
    loadMapSprite(file);
}
void MapArea::loadMapSprite(const char *file)
{
    std::vector<std::string> mapFile = (&CommonUtils::getInstance())->splits(file, ".");
    if(mapFile.size()>0)
    {
        std::string spriteFileName = mapFile[0];
        spriteFileName = spriteFileName + "_sprite.plist";
        if(FileUtils::getInstance()->isFileExist(spriteFileName))
        {
            _mapImageData = FileUtils::getInstance()->getValueMapFromFile(spriteFileName);
            ValueMap mapData = _mapImageData.at("1").asValueMap();
            loadMapSpriteMake(layer_1, mapData);
            mapData = _mapImageData.at("2").asValueMap();
            loadMapSpriteMake(layer_2, mapData);
            mapData = _mapImageData.at("4").asValueMap();
            loadMapSpriteMake(layer_4, mapData);
            mapData = _mapImageData.at("5").asValueMap();
            loadMapSpriteMake(layer_5, mapData);
        }
    }
}
void MapArea::loadMapSpriteMake(int type, ValueMap &map)
{
    for(int i=0;i<map.size();i++)
    {
        ValueMap mapData = map.at(__String::createWithFormat("%d", i)->getCString()).asValueMap();
        std::string images = mapData.at("image").asString();
        std::string position = mapData.at("position").asString();
        Vec2 point =  PointFromString(position);
                Sprite *createSprite = Sprite::create(images.c_str());
        createSprite->setPosition(point);
        _background->addChild(createSprite, type);
    }
}
void MapArea::setPlayer()
{
    log("current %d", Player::getInstance()->_currentMapPoint);
    MapPoint *mapPoint = (MapPoint *)_background->getChildByTag(Player::getInstance()->_currentMapPoint);
    if(mapPoint->_isCenter)
        _currentPoint = mapPoint;
    else
    {
        mapPoint = (MapPoint *)_background->getChildByTag(Player::getInstance()->_beforeMapPoint);
        _currentPoint = mapPoint;
        Player::getInstance()->_currentMapPoint = Player::getInstance()->_beforeMapPoint;
    }
    _playerImage = Sprite::create(Player::getInstance()->getCharacterMapSprite());
    _playerImage->setAnchorPoint(Vec2(0.5f,0));
    _playerImage->setPosition(mapPoint->getPosition());
    _background->addChild(_playerImage,layer_4);

    float WSIZE = this->getViewSize().width;
    float HSIZE = this->getViewSize().height;
    
    Vec2 position;
    position.x = -_currentPoint->getPosition().x+(WSIZE/2);
    position.x = (0<=position.x)? 0:-_currentPoint->getPosition().x+(WSIZE/2);
    if(position.x<0)
        position.x = (position.x<=-getContentSize().width+WSIZE)? -getContentSize().width+WSIZE:-_currentPoint->getPosition().x+(WSIZE/2);
    
    position.y = -_currentPoint->getPosition().y+(HSIZE/2);
    position.y = (0<=position.y)? 0:-_currentPoint->getPosition().y+(HSIZE/2);
    if(position.y<0)
        position.y = (position.y<=-getContentSize().height+HSIZE)? -getContentSize().height+HSIZE:-_currentPoint->getPosition().y+(HSIZE/2);
    
    setContentOffset(position);

}
void MapArea::refreshLoadMap()
{
    QuestConatiner::sharedObject()->questLog();
    _isTouch = false;
    _background->removeAllChildren();
    log("Player::sharedObject()->_mapInfo.c_str() %s", Player::getInstance()->_mapInfo.c_str());
    setImageMap(Player::getInstance()->_mapInfo.c_str());
    setPlayer();
    visibleCave();
}
Character *MapArea::getCharacterData(ValueMap &map)
{
    int characterType = getIntMapData(map, "characterType");
    if(characterType)
    {
        Character *character = Character::create();
        character->setCharacterType(characterType);
        for(int i=1;i<=3;i++)
        {
            string checkMapString = getStringMapData(map, __String::createWithFormat("%s%d", "characterMonster",i)->getCString());
            if(checkMapString.compare(""))
            {
                std::vector<std::string> characterMonster1 = (&CommonUtils::getInstance())->splits(checkMapString, "/");
                Node *monsterNode =  Bush::createCharacterMonster(characterMonster1,1);
                character->_monsterList->pushBack(monsterNode);
            }
        }
        return character;
    }
    return nullptr;
}
Node *MapArea::getBushData(ValueMap &map)
{
    std::string bushInfo =  getStringMapData(map, "bushInfo");
    if(bushInfo.compare(""))
    {
        return Bush::create(bushInfo.c_str());
    }
    return nullptr;
}
Quest *MapArea::getQuestData(ValueMap &map)
{
    int questIndex = getIntMapData(map, "questIndex");
    if(questIndex)
        return Quest::create(questIndex, getIntMapData(map, "questLevel"));
    return nullptr;
}

int MapArea::getIntMapData(ValueMap &map, const char *key)
{
    if(map.at(key).asString().compare(SPACE_MAP_DATA_STRING))
    {
        return map.at(key).asInt();
    }
    return 0;
}
std::string MapArea::getStringMapData(ValueMap &map, const char *key)
{
    if(map.at(key).asString().compare(SPACE_MAP_DATA_STRING))
    {
        return map.at(key).asString();
    }
    return "";
}

void MapArea::right()
{
    if(!_isTouch)
    {
        if(_currentPoint->_right!=nullptr)
        {
            _isTouch = true;
            if(checkMoveStop(_currentPoint->_right))
            {
                _playerImage->setFlippedX(true);
                _playerImage->setSpriteFrame(Sprite::create(Player::getInstance()->getCharacterRightSprite())->getSpriteFrame());
                movePlayer(_currentPoint->_right->getMovePosition(_currentPoint->getTag(), _playerImage->getContentSize()));
                _currentPoint = _currentPoint->_right;
            }
            else
                _isTouch = false;
        }
    }

}
void MapArea::left()
{
    if(!_isTouch)
    {
        if(_currentPoint->_left!=nullptr)
        {
            _isTouch = true;
            if(checkMoveStop(_currentPoint->_left))
            {
                _playerImage->setSpriteFrame(Sprite::create(Player::getInstance()->getCharacterLeftSprite())->getSpriteFrame());
                movePlayer(_currentPoint->_left->getMovePosition(_currentPoint->getTag(), _playerImage->getContentSize()));
                _currentPoint = _currentPoint->_left;
            }
            else
                _isTouch = false;
        }
    }
}
void MapArea::top()
{
    if(!_isTouch)
    {
        if(_currentPoint->_top!=nullptr)
        {
            _isTouch = true;
            if(checkMoveStop(_currentPoint->_top))
            {
                _playerImage->setSpriteFrame(Sprite::create(Player::getInstance()->getCharacterBackSprite())->getSpriteFrame());
                movePlayer(_currentPoint->_top->getMovePosition(_currentPoint->getTag(), _playerImage->getContentSize()));
                _currentPoint = _currentPoint->_top;
            }
            else
                _isTouch = false;
        }
    }
}
void MapArea::bottom()
{
    if(!_isTouch)
    {
        if(_currentPoint->_bottom!=nullptr)
        {
            _isTouch = true;
            if(checkMoveStop(_currentPoint->_bottom))
            {
                _playerImage->setSpriteFrame(Sprite::create(Player::getInstance()->getCharacterFrontSprite())->getSpriteFrame());
                movePlayer(_currentPoint->_bottom->getMovePosition(_currentPoint->getTag(), _playerImage->getContentSize()));
                _currentPoint = _currentPoint->_bottom;
            }
            else
                _isTouch = false;
        }
    }
}
void MapArea::movePlayer(const Vec2 &movePosition)
{
    _playerImage->runAction(MoveTo::create(_moveDelay, movePosition));
    this->runAction(Sequence::create(DelayTime::create(_moveDelay), CallFunc::create(CC_CALLBACK_0(MapArea::endWalk, this)), nullptr));
    
    Vec2 position;
    position.x = -movePosition.x+(this->getViewSize().width/2);
    position.x = (0<=position.x)? 0:-movePosition.x+(this->getViewSize().width/2);
    if(position.x<0)
        position.x = (position.x<=-getContentSize().width+this->getViewSize().width)? -getContentSize().width+this->getViewSize().width:-movePosition.x+(this->getViewSize().width/2);
    
    position.y = -movePosition.y+(this->getViewSize().height/2);
    position.y = (0<=position.y)? 0:-movePosition.y+(this->getViewSize().height/2);
    if(position.y<0)
        position.y = (position.y<=-getContentSize().height+this->getViewSize().height)? -getContentSize().height+this->getViewSize().height:-movePosition.y+(this->getViewSize().height/2);
    setContentOffsetInDuration(position, _moveDelay);

}
void MapArea::endWalk()
{
    //change player Image
    switch (_currentPoint->_infoType) {
        case mapInfoType::kMapInfoCharacter:
        case mapInfoType::kMapInfoQuestCharacter:
            if(!_currentPoint->_pointSprite->isVisible())
            {
                _playerImage->setFlippedX(false);
                _playerImage->setSpriteFrame(Sprite::create(Player::getInstance()->getCharacterMapSprite())->getSpriteFrame());
            }
            break;
        default:
            _playerImage->setFlippedX(false);
            _playerImage->setSpriteFrame(Sprite::create(Player::getInstance()->getCharacterMapSprite())->getSpriteFrame());
            break;
    }
    
    checkMapData();
    visibleCave();
}

void MapArea::checkMapData()
{
    Player::getInstance()->_beforeMapPoint = Player::getInstance()->_currentMapPoint;
    Player::getInstance()->_currentMapPoint = _currentPoint->getTag();
    
    GameScene* currentScene = GameScene::runningScene();
    log("map Point %d", Player::getInstance()->_currentMapPoint);
    log("_currentPoint->_infoType %d", _currentPoint->_infoType);
    switch(_currentPoint->_infoType)
    {
        case mapInfoType::kMapInfoVillage:
        {
            VillageLayer *village = VillageLayer::create(this->getParent(), _currentPoint->_villageInfo);
            village->setPosition(Vec2(currentScene->getContentSize().width/2,currentScene->getContentSize().height/2));
            currentScene->addChild(village);
            _isTouch = false;
            break;
        }
        case mapInfoType::kMapInfoMove:
        {
            std::vector<std::string> mapData = (&CommonUtils::getInstance())->splits(_currentPoint->_move, "_");
            Player::getInstance()->_mapInfo = __String::createWithFormat("map/%s_%s_%s.plist", mapData[0].c_str(),mapData[1].c_str(),mapData[2].c_str())->getCString();
            Player::getInstance()->_currentMapPoint = atoi(mapData[3].c_str());
            refreshLoadMap();
            _isEradicationItem = false;
            _isTemptationItem = false;
            _isVisibleCaveItem = false;
            _isTouch = false;
            break;
        }
        case mapInfoType::kMapInfoMonster:
        {
            if(Player::getInstance()->isMonster())
            {
                if(_isEradicationItem)
                {
                    _isTouch = false;
                }
                else if(_isTemptationItem)
                {
                    startBattleAnimation();
                }
                else
                {
                    if(arc4random()%4==1)
                    {
                        startBattleAnimation();
                    }
                    else
                        _isTouch = false;
                }
            }
            else
                _isTouch = false;

            break;
        }
        case mapInfoType::kMapInfoCharacter:
        case mapInfoType::kMapInfoQuestCharacter:
        {
            if(Player::getInstance()->isMonster())
            {
                if(_currentPoint->_pointSprite->isVisible())
                {
                  startBattleAnimation();
                }
                else
                    _isTouch = false;
            }
            else
                _isTouch = false;

            break;
        }
        case mapInfoType::kMapInfoMoveEvent:
        {
           if(_currentPoint->_moveEvent)
           {
               _moveEventPoint = _currentPoint->getTag();
           }
           else
           {
               Player::getInstance()->_currentMapPoint = _moveEventPoint;
               Player::getInstance()->_beforeMapPoint = _moveEventPoint;
               refreshLoadMap();

           }
            _isTouch = false;

            break;
        }
        case mapInfoType::kMapInfoUpgradeStore:
        {
            UpgradeLoonShop *upgradeShop = UpgradeLoonShop::create(this);
            currentScene->addChild(upgradeShop);
            _isTouch = false;
            break;
        }
        default:
            _isTouch = false;
            break;

    }
}


bool MapArea::checkMoveStop(MapPoint *point)
{
    int needItemType = 0;
    switch (point->_type) {
        case mapType::kMapFire:
            needItemType = ItemType::kItemTypeMoveFire;
            break;
        case mapType::kMapWater:
            needItemType = ItemType::kItemTypeMoveWater;
            break;
        case mapType::kMapTree:
            needItemType = ItemType::kItemTypeMoveTree;
            break;
        default:
            break;
    }
    if(needItemType>0)
    {
        if(Player::getInstance()->_itemList->isItem(needItemType))
            return checkInfoStop(point);
        else
            return false;
    }
    else
    {
        return checkInfoStop(point);
    }
    
    
    return true;
    
}
bool MapArea::checkInfoStop(MapPoint *point)
{
    if(point->_infoType==mapInfoType::kMapInfoStopMove)
    {
        if(QuestConatiner::sharedObject()->getQuestStatus((Quest *)point->_quest)==questStatus::kSuccess)
            return true;
        else
            return false;
    }
    else
        return true;
}
void MapArea::visibleCave()
{
    MapLayer *map = (MapLayer *)this->getParent();
    if(_currentPoint->_type==mapType::kMapCave && (!_isVisibleCaveItem))
    {
        if(map!=NULL)
        {
            map->_visibleCave->setVisible(true);
        }
        for(int i=1;i<=MAP_HEIGHT*MAP_WIDTH;i++)
        {
            ValueMap mapData = _mapData.at(__String::createWithFormat("%d", i)->getCString()).asValueMap();
            
            if(mapData.at("isSelected").asInt())
            {
                MapPoint *mapPoint = (MapPoint *)_background->getChildByTag(i);
                int current = _currentPoint->getTag();
                int left = (_currentPoint->_left!=nullptr)? _currentPoint->_left->getTag():-1;
                int right = (_currentPoint->_right!=nullptr)? _currentPoint->_right->getTag():-1;
                int top = (_currentPoint->_top!=nullptr)? _currentPoint->_top->getTag():-1;
                int bottom = (_currentPoint->_bottom!=nullptr)? _currentPoint->_bottom->getTag():-1;;
                if(i==current||i==left||i==right||i==top||i==bottom)
                    mapPoint->setVisibleAllMap(true);
                else
                    mapPoint->setVisibleAllMap(false);

            }
        }
    }
    else
    {
        if(map!=NULL)
        {
            map->_visibleCave->setVisible(false);
        }
        for(int i=1;i<=MAP_HEIGHT*MAP_WIDTH;i++)
        {
            ValueMap mapData = _mapData.at(__String::createWithFormat("%d", i)->getCString()).asValueMap();
            
            if(mapData.at("isSelected").asInt())
            {
                MapPoint *mapPoint = (MapPoint *)_background->getChildByTag(i);
                
                mapPoint->setVisible(true);
                
            }
        }
    }
   
}
void MapArea::retunVillage()
{
    std::vector<std::string> mapInfo = (&CommonUtils::getInstance())->splits(Player::getInstance()->_mapInfo, "_");
    Player::getInstance()->_mapInfo = (__String::createWithFormat("map/map_%s_1.plist", mapInfo[1].c_str()))->getCString();
    decodeMap(Player::getInstance()->_mapInfo.c_str());
    
    for(int i=1;i<=MAP_HEIGHT*MAP_WIDTH;i++)
    {
        ValueMap mapData = _mapData.at(__String::createWithFormat("%d", i)->getCString()).asValueMap();
        if(mapData.at("isSelected").asInt())
        {
            int mapInfoType = getIntMapData(mapData, "mapInfoType");
            if(mapInfoType==mapInfoType::kMapInfoVillage)
            {
                log("log i = %d", i);
                Player::getInstance()->_beforeMapPoint = i;
                Player::getInstance()->_currentMapPoint = i;
            }
        }
    }
    _isEradicationItem = false;
    _isTemptationItem = false;
    _isVisibleCaveItem = false;
    refreshLoadMap();
}
void MapArea::startBattleAnimation()
{
    _isTouch = true;
    Player::getInstance()->playSound(SOUND_EFFECT_FIND);
    MapLayer *map = (MapLayer *)this->getParent();
    map->setEventTouchEnable(false);
    map->_battleAnimation->setVisible(true);
    map->_battleAnimation->runAction(Sequence::create(FadeIn::create(0.2f),FadeOut::create(0.2f),
                                                      FadeIn::create(0.2f),FadeOut::create(0.2f)
                                                      ,FadeIn::create(0.2f),FadeOut::create(0.2f),
                                                      FadeIn::create(0.2f),FadeOut::create(0.2f),
                                                      FadeIn::create(0.2f),FadeOut::create(0.2f),
                                                      CallFunc::create(CC_CALLBACK_0(MapArea::endBattleAnimation, this)),NULL));
}
void MapArea::endBattleAnimation()
{
    checkBattleData();
    _isTouch = false;
    MapLayer *map = (MapLayer *)this->getParent();
    map->_battleAnimation->setVisible(false);
    map->_battleAnimation->setOpacity(0);
    map->setEventTouchEnable(true);
}

void MapArea::checkBattleData()
{
    GameScene* currentScene = GameScene::runningScene();
    switch (_currentPoint->_infoType) {
        case mapInfoType::kMapInfoMonster:
        {
            
            Character *spaceCharacter = Character::create();
            ShapeCommon *monster = ((Bush *)_currentPoint->_info)->getMonster();
            if(monster!=nullptr)
            {
                spaceCharacter->_monsterList->pushBack(monster);
                
                if(!Player::getInstance()->getTutorial())
                {
                    Tutorial *tutorial = Tutorial::create(this->getParent(),spaceCharacter, this);
                    currentScene->addChild(tutorial);
                }
                else
                {
                    BattleLayer *battleLayer = BattleLayer::create(this->getParent(),spaceCharacter, this);
                    battleLayer->setPosition(Vec2(currentScene->getContentSize().width/2,currentScene->getContentSize().height/2));
                    currentScene->addChild(battleLayer);
                }
            }
            break;
            
        }
        case mapInfoType::kMapInfoCharacter:
        {
            
            BattleLayer *battleLayer = BattleLayer::create(this->getParent(),_currentPoint->_character,this, battleType::kCharacterType);
            battleLayer->setPosition(Vec2(currentScene->getContentSize().width/2,currentScene->getContentSize().height/2));
            currentScene->addChild(battleLayer);
            break;
        }
        case mapInfoType::kMapInfoQuestCharacter:
        {
            
            TalkLayer *talkLayer = TalkLayer::create(this->getParent(),_currentPoint->_character->getCharacterType(),_currentPoint->_character, this);
            talkLayer->setPosition(Vec2(currentScene->getContentSize().width/2,currentScene->getContentSize().height/2));
            currentScene->addChild(talkLayer);
            break;
        }
    }
}
void MapArea::setEradicationItem(bool isEradication)
{
    _isEradicationItem = isEradication;
}
void MapArea::setTemptationItem(bool isTemptation)
{
    _isTemptationItem = isTemptation;
}
void MapArea::setVisibleCaveItem(bool isVisibleCave)
{
    _isVisibleCaveItem = isVisibleCave;
}
bool MapArea::getEradicationItem()
{
    return _isEradicationItem;
}
bool MapArea::getTemptationItem()
{
    return _isTemptationItem;
}
bool MapArea::getVisibleCaveItem()
{
    return _isVisibleCaveItem;
}