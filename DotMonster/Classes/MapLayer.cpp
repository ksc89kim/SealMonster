//
//  MapLayer.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 7..
//
//

#include "MapLayer.h"
#include "ItemBagLayer.h"
#include "MonsterListLayer.h"
#include "IntroScene.h"
#include "Setting.h"
#include "GameScene.h"
#include "TextDb.h"
#include "MiniMapLayer.h"

MapLayer::MapLayer()
:_isEventTouchEnable(true)
{
}

MapLayer::~MapLayer()
{
}

MapLayer *MapLayer::create()
{
    MapLayer * layer = new MapLayer();
    if(layer && layer->initWithColor(Color4B(255,255,255,255)))
    {
        layer->setImage();
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void MapLayer::setImage()
{
    ignoreAnchorPointForPosition(false);

    _visibleCave = LayerColor::create(Color4B::BLACK);
    _visibleCave->setOpacity(150);
    _visibleCave->setVisible(false);
    this->addChild(_visibleCave);
    
    _mapArea = MapArea::create();
    this->addChild(_mapArea);
    
    MenuItem *left = CommonUtils::createMenuItem("left.png", CC_CALLBACK_0(MapLayer::clickLeft, this));
    left->setPosition(Vec2(80,100));
    
    MenuItem *right = CommonUtils::createMenuItem("right.png", CC_CALLBACK_0(MapLayer::clickRight, this));
    right->setPosition(Vec2(300,100));

    MenuItem *top = CommonUtils::createMenuItem("top.png", CC_CALLBACK_0(MapLayer::clickTop, this));
    top->setPosition(Vec2(190,200));
    
    MenuItem *bottom =  CommonUtils::createMenuItem("bottom.png", CC_CALLBACK_0(MapLayer::clickBottom, this));
    bottom->setPosition(Vec2(190,80));
    
    MenuItem *minimap = CommonUtils::createMenuItem("minimapIcon.png", CC_CALLBACK_0(MapLayer::clickMiniMap, this));
    minimap->setPosition(CommonUtils::changePosition(Vec2(900,240)));

    MenuItem *ranking = CommonUtils::createMenuItem("ranking.png", CC_CALLBACK_0(MapLayer::clickRanking, this));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //ranking->setVisible(false);
#endif
    ranking->setPosition(CommonUtils::changePosition(Vec2(900,160)));
    
    //MenuItem *video = CommonUtils::createMenuItem("video.png", CC_CALLBACK_0(MapLayer::clickVideo, this));
    //video->setPosition(CommonUtils::changePosition(Vec2(900,160)));
    
    MenuItem *setting = CommonUtils::createMenuItem("setting.png", CC_CALLBACK_0(MapLayer::clickSetting, this));
    setting->setPosition(CommonUtils::changePosition(Vec2(900,80)));
    
    MenuItem *save = CommonUtils::createMenuItem("save.png", CC_CALLBACK_0(MapLayer::clickSave, this));
    save->setPosition(CommonUtils::changePosition(Vec2(820,80)));
    
    MenuItem *item = CommonUtils::createMenuItem("item.png", CC_CALLBACK_0(MapLayer::clickItemBag, this));
    item->setPosition(CommonUtils::changePosition(Vec2(740,80)));
    
    MenuItem *monster = CommonUtils::createMenuItem("monsterList.png", CC_CALLBACK_0(MapLayer::clickMonsterList, this));
    monster->setPosition(CommonUtils::changePosition(Vec2(660,80)));
    
    MenuItem *back = CommonUtils::createMenuItem("backButton.png", CC_CALLBACK_0(MapLayer::clickIntro, this));
    back->setPosition(CommonUtils::changePosition(Vec2(580,80)));
    
    Menu *menu = Menu::create(left,right,top,bottom,setting,save,item,monster,back,ranking,minimap,nullptr);
    menu->setPosition(Vec2(0,0));
    this->addChild(menu);
    
    _battleAnimation = LayerColor::create(Color4B::BLACK);
    _battleAnimation->setOpacity(0);
    _battleAnimation->setVisible(false);
    this->addChild(_battleAnimation);
}

void MapLayer::clickLeft()
{
    Player::getInstance()->playSound(SOUND_EFFECT_BASE_BUTTON);
    if(_isEventTouchEnable)
    {
        _mapArea->left();
    }
}

void MapLayer::clickRight()
{
    Player::getInstance()->playSound(SOUND_EFFECT_BASE_BUTTON);
    if(_isEventTouchEnable)
    {
        _mapArea->right();
    }
}

void MapLayer::clickTop()
{
    Player::getInstance()->playSound(SOUND_EFFECT_BASE_BUTTON);
    if(_isEventTouchEnable)
    {
        _mapArea->top();
    }
}

void MapLayer::clickBottom()
{
    Player::getInstance()->playSound(SOUND_EFFECT_BASE_BUTTON);
    if(_isEventTouchEnable)
    {
        _mapArea->bottom();
    }
}
void MapLayer::clickItemBag()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    if(_isEventTouchEnable)
    {
        GameScene *scene = (GameScene::runningScene());
        ItemBagLayer*layer = ItemBagLayer::create(this, false);
        layer->setPosition(Vec2(scene->getContentSize().width/2, scene->getContentSize().height/2));
        scene->addChild(layer);
    }
}
void MapLayer::clickMonsterList()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    if(_isEventTouchEnable)
    {
        GameScene *scene = (GameScene::runningScene());
        MonsterListLayer *layer = MonsterListLayer::create(this, 0);
        layer->setPosition(Vec2(scene->getContentSize().width/2, scene->getContentSize().height/2));
        scene->addChild(layer);
    }
}
void MapLayer::clickSave()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    if(_isEventTouchEnable)
    {
         Adaptor::showInterstitalAd();
        (GameScene::runningScene())->createPopup(popUpType::kOkAndCanle,
                                                 TextDb::getInstance()->getEtcText(28).c_str(),
                                                 CC_CALLBACK_0(MapLayer::save, this));
    }
}
void MapLayer::clickIntro()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    if(_isEventTouchEnable)
    {
        (GameScene::runningScene())->createPopup(popUpType::kOkAndCanle,
                                                 TextDb::getInstance()->getEtcText(29).c_str(),
                                                 CC_CALLBACK_0(MapLayer::goIntro, this));
    }
}
void MapLayer::clickSetting()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    if(_isEventTouchEnable)
    {
        GameScene *scene = (GameScene::runningScene());
        SettingLayer *layer = SettingLayer::create();
        scene->addChild(layer);
    }
}
void MapLayer::clickVideo()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    if(_isEventTouchEnable)
    {
        (GameScene::runningScene())->createPopup(popUpType::kOkAndCanle,
                                                 TextDb::getInstance()->getEtcText(30).c_str(),
                                                 CC_CALLBACK_0(MapLayer::showVideo, this));
    }
}
void MapLayer::clickRanking()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    if(_isEventTouchEnable)
    {
        string temp;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        temp = TextDb::getInstance()->getEtcText(31).c_str();
#else
        temp = TextDb::getInstance()->getEtcText(32).c_str();
#endif
        (GameScene::runningScene())->createPopup(popUpType::kOkAndCanle,
                                                 temp.c_str(),
                                                 CC_CALLBACK_0(MapLayer::ranking, this));
    }
}
void MapLayer::ranking()
{
    Adaptor::submitScore(Player::getInstance()->getMonsterScore());
    Adaptor::showLeaderBoard();
}
void MapLayer::showVideo()
{
    setEventTouchEnable(false);
    GameScene *scene = GameScene::runningScene();
    if(scene)
        scene->setVisibleLoading(true);
    Adaptor::showVedio();
}
void MapLayer::save()
{
    Player::getInstance()->save();
}
void MapLayer::goIntro()
{
    Player::getInstance()->clearData();
    Director::getInstance()->replaceScene(IntroScene::createScene());
}
MapArea *MapLayer::getMapArea()
{
    return _mapArea;
}
void MapLayer::setEventTouchEnable(bool isEnable)
{
    _isEventTouchEnable = isEnable;
    _mapArea->setTouchEnabled(isEnable);
}
void MapLayer::refreshMapArea()
{
    _mapArea->refreshLoadMap();
}
void MapLayer::clickMiniMap()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    GameScene *scene = (GameScene::runningScene());
    MiniMapLayer *miniMap = MiniMapLayer::create();
    scene->addChild(miniMap);
}

