//
//  GameScene.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 21..
//
//

#include "GameScene.h"
#include "Player.h"
#include "BattleLayer.h"
#include "ItemBagLayer.h"
#include "TalkLayer.h"
#include "VillageLayer.h"

GameScene::GameScene()
:_eixtPopuP(nullptr),_isExitPopup(false),_map(nullptr)
{
    
}
GameScene::~GameScene()
{
    if(_eixtPopuP)
        _eixtPopuP->release();
    if(_loadinglayer)
        _loadinglayer->release();
}
Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer,0,GAME_SCENE_TAG);
    return scene;
}
bool GameScene::init()
{
    if (!Common::init()) {
        return false;
    }
    
    _eixtPopuP = CommonPopUp::create(popUpType::kOkAndCanle, TextDb::getInstance()->getEtcText(56).c_str(),CC_CALLBACK_0(GameScene::exitGame, this));
    _eixtPopuP->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    _eixtPopuP->retain();
    
    return true;


}
void GameScene::onEnter()
{
    Common::onEnter();
    
    _map = MapLayer::create();
    _map->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(_map);
    
    Player::getInstance()->load();
    
    Player::getInstance()->stopMusic();
    Player::getInstance()->playMusic(SOUND_MUSIC_BASE);
    
    if(!Player::getInstance()->_isLoad)
    {
        VillageLayer *villageLayer = VillageLayer::create(_map, 1);
        villageLayer->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
        this->addChild(villageLayer);
        
        TalkLayer *talkLayer = TalkLayer::create(villageLayer, 1000);
        talkLayer->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
        this->addChild(talkLayer);
    }
    else
    {
        this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create(CC_CALLBACK_0(GameScene::showInterstitalAd, this)),NULL));
    }
    _map->refreshMapArea();
    this->setKeypadEnabled( true );
    

    _loadinglayer = LoadingLayer::create();
    _loadinglayer->setVisible(false);
    _loadinglayer->retain();
}
void GameScene::createPopup(int type, const char *text,const ccMenuCallback &callback)
{
    CommonPopUp *popuP = CommonPopUp::create(type, text,callback);
    popuP->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(popuP, 100000);
}
GameScene* GameScene::runningScene()
{
	GameScene* scene =  dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene()->getChildByTag(GAME_SCENE_TAG));
    if (scene)
		return scene;
	else
		return NULL;
}
void GameScene::onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event )
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK || keycode == EventKeyboard::KeyCode::KEY_F1) {
        Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
        if(!_isExitPopup)
        {
            this->addChild(_eixtPopuP, 900000);
            _isExitPopup = true;
        }
        else
        {
            this->removeChild(_eixtPopuP);
            _isExitPopup = false;
            
        }
    }
}
MapLayer *GameScene::getMapLayer()
{
    if(_map)
        return _map;
    return nullptr;
}
void GameScene::videoSuccess()
{
    this->schedule(schedule_selector(GameScene::schedulVideoSucces),0.5f);
}
void GameScene::schedulVideoSucces(float df)
{
    if(_map)
        _map->setEventTouchEnable(true);
    setVisibleLoading(false);
    
    if(arc4random()%7==1)
    {
        switch (arc4random()%2) {
            case 0:
                Player::getInstance()->_itemList->plusItemWithPopup(ItemType::kItemTypePlusTransPower, 1);
                break;
            case 1:
                Player::getInstance()->_itemList->plusItemWithPopup(ItemType::kItemTypePlusTransAgility, 1);
                break;
            default:
                Player::getInstance()->_itemList->plusItemWithPopup(ItemType::kItemTypePlusTransStamina, 1);
                break;
        }
    }
    else
    {
        switch (arc4random()%3) {
            case 0:
                Player::getInstance()->_itemList->plusItemWithPopup(ItemType::kItemTypePlusPower, 1);
                break;
            case 1:
                Player::getInstance()->_itemList->plusItemWithPopup(ItemType::kItemTypePlusAgility, 1);
                break;
            case 2:
                Player::getInstance()->_itemList->plusItemWithPopup(ItemType::kItemTypePlusStamina, 1);
                break;
            default:
                Player::getInstance()->_itemList->plusItemWithPopup(ItemType::kItemTypePlusAgility, 1);
                break;
        }
    }
    this->unschedule(schedule_selector(GameScene::schedulVideoSucces));
}
void GameScene::videoFail()
{
    if(_map)
        _map->setEventTouchEnable(true);
    setVisibleLoading(false);
}
void GameScene::videoNotContent()
{
    this->schedule(schedule_selector(GameScene::schedulNotContent),0.5f);
}
void GameScene::schedulNotContent(float df)
{
    if(_map)
        _map->setEventTouchEnable(true);
    setVisibleLoading(false);
    createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(57).c_str(),nullptr);
    this->unschedule(schedule_selector(GameScene::schedulNotContent));
}
void GameScene::exitGame()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void GameScene::setVisibleLoading(bool isLoading)
{
    if(isLoading&&!_loadinglayer->isVisible())
    {
        _loadinglayer->setVisible(isLoading);
        _loadinglayer->startLoading();
        this->addChild(_loadinglayer);
    }
    else if(_loadinglayer->isVisible() && !isLoading)
    {
        _loadinglayer->setVisible(isLoading);
        _loadinglayer->stopLoading();
        this->removeChild(_loadinglayer);
    }
}
void GameScene::showInterstitalAd()
{
    Adaptor::showInterstitalAd();
}
