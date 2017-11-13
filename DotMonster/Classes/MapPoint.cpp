//
//  MapPoint.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 28..
//
//

#include "MapPoint.h"


#pragma mark - MapPoint
MapPoint::MapPoint()
{
    initData();
}
MapPoint::~MapPoint()
{
    releaseData();
}
MapPoint *MapPoint::create(int tag, int type, int infoType,int villageInfo,int moveEvent, const char *moveData, const char *questCharacterIndex, Character *character, Quest *quest, Node *info)
{
    MapPoint *sprite = new (std::nothrow) MapPoint();
    if (sprite && sprite->initWithFile("on.png"))
    {
        sprite->setTag(tag);
        sprite->setValue(type, infoType,villageInfo,moveEvent, moveData, questCharacterIndex,character, quest, info);
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void MapPoint::setValue(int type, int infoType,int villageInfo,int moveEvent, const char *moveData, const char *questCharacterIndex, Character *character, Quest *quest, cocos2d::Node *info)
{
    _type = type;
    _infoType = infoType;
    _villageInfo = villageInfo;
    _move = moveData;
    _character = character;
    _questCharacter = questCharacterIndex;
    _moveEvent = moveEvent;
    if(_character!=nullptr)
        _character->retain();
    _quest = quest;
    if(_quest!=nullptr)
        _quest->retain();
    _info = info;
    if(_info!=nullptr)
        _info->retain();
    
}
void MapPoint::checkPointSprite()
{
    if(_character!=nullptr)
    {
        _pointSprite = Sprite::create(_character->getCharacterMapSprite());
        if(Player::getInstance()->isLiveEnemyCharacterInfo(this))
            _pointSprite->setVisible(true);
        else
            _pointSprite->setVisible(false);
        _pointSprite->setAnchorPoint(Vec2(0.5f,0.0f));
        CommonUtils::fitNode(_pointSprite,48);
    }
    else if(_info!=nullptr)
        _pointSprite = (Sprite *)_info;
    
    
    
    if(this->getParent())
    {
        switch(_infoType)
        {
            case mapInfoType::kMapInfoQuestCharacter:
            {
                if(_pointSprite!=nullptr)
                {
                    if(QuestConatiner::sharedObject()->checkQuestCharacter(_questCharacter.c_str()))
                        _pointSprite->setVisible(true);
                    else
                        _pointSprite->setVisible(false);
                    _pointSprite->setPosition(getPosition());
                    this->getParent()->addChild(_pointSprite,layer_5);
                }
                break;
            }
            case mapInfoType::kMapInfoVillage:
            {
                _pointSprite = Sprite::create("villageMap.png");
                _pointSprite->setPosition(Vec2(getPositionX(),getPositionY()+50));
                this->getParent()->addChild(_pointSprite,layer_3);
                break;
            }
            case mapInfoType::kMapInfoMove:
            {
                _pointSprite = Sprite::create("portal.png");
                _pointSprite->setPosition(Vec2(getPositionX(),getPositionY()+50));
                this->getParent()->addChild(_pointSprite,layer_3);
                break;
            }
            case mapInfoType::kMapInfoUpgradeStore:
            {
                _pointSprite = Sprite::create("upgrade.png");
                _pointSprite->setPosition(Vec2(getPositionX(),getPositionY()+50));
                this->getParent()->addChild(_pointSprite,layer_3);
                break;
            }
            default:
            {
                if(_pointSprite!=nullptr)
                {
                    _pointSprite->setPosition(getPosition());
                    this->getParent()->addChild(_pointSprite,layer_5);
                }
                break;
            }
        }
        
        if(_info==nullptr && _pointSprite!=nullptr)
            if(_pointSprite->isVisible() && _infoType!=mapInfoType::kMapInfoVillage && _infoType!=mapInfoType::kMapInfoMove && _infoType!=mapInfoType::kMapInfoUpgradeStore )
                _isCenter = false;
    }
    if(_pointSprite!=nullptr)
        _originalVisible = _pointSprite->isVisible();

}
void MapPoint::checkTypeSprite()
{
    //_type
    switch (_type) {
        case mapType::kMapFire:
        {
            _pointType = Node::create();
            Sprite *fire = Sprite::create("fireMap.png");
            fire->setPosition(Vec2(50, 30));
            _pointType->addChild(fire);
            fire = Sprite::create("fireMap.png");
            fire->setPosition(Vec2(50, -30));
            _pointType->addChild(fire);
            fire = Sprite::create("fireMap.png");
            fire->setPosition(Vec2(-50, 30));
            _pointType->addChild(fire);
            fire = Sprite::create("fireMap.png");
            fire->setPosition(Vec2(-50, -30));
            _pointType->addChild(fire);
            break;
        }
        case mapType::kMapWater:
        {
            _pointType = Node::create();
            Sprite *warter = Sprite::create("warterMap.png");
            warter->setPosition(Vec2(50, 30));
            _pointType->addChild(warter);
            warter = Sprite::create("warterMap.png");
            warter->setPosition(Vec2(50, -30));
            _pointType->addChild(warter);
            warter = Sprite::create("warterMap.png");
            warter->setPosition(Vec2(-50, 30));
            _pointType->addChild(warter);
            warter = Sprite::create("warterMap.png");
            warter->setPosition(Vec2(-50, -30));
            _pointType->addChild(warter);
            break;
        }
        case mapType::kMapTree:
        {
            _pointType = Node::create();
            Sprite *tree = Sprite::create("treeMap.png");
            tree->setPosition(Vec2(50, 30));
            _pointType->addChild(tree);
            tree = Sprite::create("treeMap.png");
            tree->setPosition(Vec2(50, -30));
            _pointType->addChild(tree);
            tree = Sprite::create("treeMap.png");
            tree->setPosition(Vec2(-50, 30));
            _pointType->addChild(tree);
            tree = Sprite::create("treeMap.png");
            tree->setPosition(Vec2(-50, -30));
            _pointType->addChild(tree);
            break;
        }
    }
    
    if(_pointType)
    {
        _pointType->setPosition(Vec2(getPositionX(),getPositionY()));
        this->getParent()->addChild(_pointType,layer_3);
        _typeVisible = _pointType->isVisible();
    }
}
void MapPoint::initData()
{
    _isCenter = true;
    _left = nullptr;
    _right = nullptr;
    _top = nullptr;
    _bottom = nullptr;
    _character = nullptr;
    _info = nullptr;
    _quest = nullptr;
    _pointSprite = nullptr;
    _originalVisible = false;
    _pointType = nullptr;
    _typeVisible = false;
}
void MapPoint::releaseData()
{
    if(_character)
    {
        _character->release();
    }
    if(_quest)
    {
        _quest->release();
    }
    if(_info)
    {
        _info->release();
    }
}
Vec2 MapPoint::getMovePosition(int beforeTag, const Size& character)
{
    if(_left!=nullptr)
        if(beforeTag==_left->getTag())
            if(!_isCenter)
                return Vec2(this->getPositionX()-character.width/2-(_pointSprite->getContentSize().width*_pointSprite->getScaleX())/2, this->getPositionY());
    if(_right!=nullptr)
        if(beforeTag==_right->getTag())
            if(!_isCenter)
                return Vec2(this->getPositionX()+character.width/2+(_pointSprite->getContentSize().width*_pointSprite->getScaleX())/2, this->getPositionY());
    if(_top!=nullptr)
        if(beforeTag==_top->getTag())
            if(!_isCenter)
                return Vec2(getPositionX(), this->getPositionY()+character.height/2+(_pointSprite->getContentSize().height*_pointSprite->getScaleY()) /2);
    if(_bottom!=nullptr)
        if(beforeTag==_bottom->getTag())
            if(!_isCenter)
                return Vec2(getPositionX(), this->getPositionY()-character.height/2-(_pointSprite->getContentSize().height*_pointSprite->getScaleY())/2);
    return Vec2(getPositionX(), this->getPositionY());
}
void MapPoint::setVisibleAllMap(bool isVisible)
{
    if(_pointSprite)
    {
        _pointSprite->setVisible((isVisible)?_originalVisible:false);
    }
    setVisible(isVisible);
}
