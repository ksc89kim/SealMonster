//
//  MiniMapLayer.cpp
//  DotMonster
//
//  Created by 김선철 on 2016. 3. 7..
//
//

#include "MiniMapLayer.h"
#include "TextDb.h"
#include "Player.h"

MiniMapLayer *MiniMapLayer::create()
{
    MiniMapLayer *ret = new (std::nothrow) MiniMapLayer();
    if (ret && ret->initWithColor(Color4B(0,0,0,0)))
    {
        ret->setClickRemove(false);
        ret->setClickVisible(false);
        ret->setImage();
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

void MiniMapLayer::setImage()
{
    _scroll = ScrollView::create(this->getContentSize());
    _scroll->setBounceable(false);
    _container = Sprite::create("minimap.png");
    _scroll->setContainer(_container);
    this->addChild(_scroll);
    
    Sprite *sprite = Sprite::create("field/field01.png");
    sprite->setPosition(Vec2(0,0));
    sprite->setAnchorPoint(Vec2(0.5f,0));
    sprite->setScale(0.7f);
    _container->addChild(sprite);
    
    MiniMapData data= MiniMapData(0,"",0,0);
    string mapName = Player::getInstance()->_mapInfo.c_str();
    vector<string> mapInfo = (&CommonUtils::getInstance())->splits(mapName, "/");
    if(mapInfo.size()>1)
    {
        TextDb::getInstance()->runQueryMiniMapData(mapInfo[1], data);
        sprite->setPosition(Vec2(data._positionX,data._positionY));
    }
    log("minimapData %s,%d,%d", data._mapName.c_str(), data._positionX, data._positionY);
    
    float WSIZE = _scroll->getViewSize().width;
    float HSIZE = _scroll->getViewSize().height;
    
    Vec2 position;
    position.x = -sprite->getPosition().x+(WSIZE/2);
    position.x = (0<=position.x)? 0:-sprite->getPosition().x+(WSIZE/2);
    if(position.x<0)
        position.x = (position.x<=-_scroll->getContentSize().width+WSIZE)? -_scroll->getContentSize().width+WSIZE:-sprite->getPosition().x+(WSIZE/2);
    
    position.y = -sprite->getPosition().y+(HSIZE/2);
    position.y = (0<=position.y)? 0:-sprite->getPosition().y+(HSIZE/2);
    if(position.y<0)
        position.y = (position.y<=-_scroll->getContentSize().height+HSIZE)? -_scroll->getContentSize().height+HSIZE:-sprite->getPosition().y+(HSIZE/2);
    
    _scroll->setContentOffset(position);
    
    Menu *menu = Menu::create();
    menu->setPosition(Vec2(0,0));
    MenuItem *close = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(3), CC_CALLBACK_0(MiniMapLayer::clickClose, this));
    close->setPosition(Vec2(this->getContentSize().width-close->getContentSize().width/2-20,this->getContentSize().height-close->getContentSize().height/2-20));
    menu->addChild(close);
    this->addChild(menu);
    
    Player::getInstance()->pauseMusic();
}

void MiniMapLayer::clickClose()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    Player::getInstance()->resumeMusic();
    this->removeFromParent();
}
