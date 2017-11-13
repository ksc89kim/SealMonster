//
//  IntroScene.cpp
//  DotMonster
//
//  Created by 김선철 on 2015. 3. 29..
//
//

#include "IntroScene.h"
#include "GameScene.h"
#include "Player.h"
#include "Base64P.h"
#include "CommonUtils.h"
#include "SimpleAudioEngine.h"
#include "CommonPopUp.h"
#include "TextDb.h"

IntroScene::IntroScene()
:_eixtPopuP(nullptr),_isExitPopup(false)
{
    
}
IntroScene::~IntroScene()
{
    if(_eixtPopuP)
        _eixtPopuP->release();
}
Scene* IntroScene::createScene()
{
    auto scene = Scene::create();
    auto layer = IntroScene::create();
    scene->addChild(layer,0,GAME_SCENE_TAG);
    return scene;
}
bool IntroScene::init()
{
    if (!Common::init()) {
        return false;
    }
    return true;
}
void IntroScene::onEnter()
{
    Common::onEnter();
   
    _eixtPopuP = CommonPopUp::create(popUpType::kOkAndCanle, TextDb::getInstance()->getEtcText(58).c_str(),CC_CALLBACK_0(IntroScene::exitGame, this));
    _eixtPopuP->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    _eixtPopuP->retain();
    
    Label *title = Label::createWithTTF("Seal Monster",CommonUtils::getFontName(), 80);
    title->enableOutline(Color4B(0,0,0,150),10);
    title->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height*0.88));
    addChild(title);
    
    Label *subTitle = Label::createWithTTF("(Polaris Version)",CommonUtils::getFontName(), 30);
    subTitle->enableOutline(Color4B(0,0,0,150),4);
    subTitle->setPosition(Vec2(title->getPositionX(), title->getPositionY()-title->getContentSize().height/2-subTitle->getContentSize().height/2));
    addChild(subTitle);
    
    leftImage();
    rightImage();
    reloadSound();
    
    MenuItem *newButton = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(59).c_str(), Size(100,50),CC_CALLBACK_1(IntroScene::clickNew, this));
    MenuItem *loadButton = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(60).c_str(), Size(100,50),CC_CALLBACK_1(IntroScene::clickLoad, this));
    MenuItem *exitButton = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(3).c_str(), Size(100,50),CC_CALLBACK_1(IntroScene::clickExit, this));

    Menu *menu = Menu::create(newButton,loadButton,exitButton,NULL);
    menu->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2-30));
    menu->alignItemsVerticallyWithPadding(25.0f);
    this->addChild(menu);
    this->setKeypadEnabled( true );


    Adaptor::showAd();
    //Adaptor::hideAd();
    Adaptor::login();

}
void IntroScene::reloadSound()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_DOTE_BUTTON);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BASE_BUTTON);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(SOUND_MUSIC_BASE);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(SOUND_MUSIC_BATTLE);
}
void IntroScene::leftImage()
{
    
    ShapeF *monster;
    monster = ShapeF::create();
    monster->_shapeData->_level->setShapeValue(17);
    monster->changeFindShape(6, 6, 6);
    monster->setFlippedXShape(true);
    monster->setPosition(Vec2(60,300));
    this->addChild(monster);
    
    monster = ShapeF::create();
    monster->_shapeData->_level->setShapeValue(17);
    monster->changeFindShape(7, 8, 9);
    monster->setFlippedXShape(true);
    monster->setPosition(CommonUtils::changePosition(Vec2(140,350)));
    this->addChild(monster);
    
    monster = ShapeF::create();
    monster->_shapeData->_level->setShapeValue(33);
    monster->changeFindShape(1, 2, 2);
    monster->setFlippedXShape(true);
    monster->setPosition(CommonUtils::changePosition(Vec2(260,230)));
    this->addChild(monster);
    
    monster = ShapeF::create();
    monster->_shapeData->_level->setShapeValue(6);
    monster->changeFindShape(5, 5, 5);
    monster->setFlippedXShape(true);
    monster->setPosition(CommonUtils::changePosition(Vec2(50,170)));
    this->addChild(monster);
    
    monster = ShapeF::create();
    monster->_shapeData->_level->setShapeValue(33);
    monster->changeFindShape(0, 1, 0);
    monster->setFlippedXShape(true);
    monster->setPosition(CommonUtils::changePosition(Vec2(130,150)));
    this->addChild(monster);
    
    monster = ShapeF::create();
    monster->_shapeData->_level->setShapeValue(33);
    monster->changeFindShape(6, 7, 8);
    monster->setFlippedXShape(true);
    monster->setPosition(CommonUtils::changePosition(Vec2(80,30)));
    this->addChild(monster);
    
    monster = ShapeF::create();
    monster->setLegend(true);
    monster->setFlippedXShape(true);
    monster->setPosition(CommonUtils::changePosition(Vec2(270,20)));
    this->addChild(monster);
    
    monster = ShapeF::create();
    monster->_shapeData->_level->setShapeValue(6);
    monster->changeFindShape(3, 4, 3);
    monster->setFlippedXShape(true);
    monster->setPosition(CommonUtils::changePosition(Vec2(190,20)));
    this->addChild(monster);
}
void IntroScene::rightImage()
{
    ShapeW *monster;
    
    monster = ShapeW::create();
    monster->_shapeData->_level->setShapeValue(33);
    monster->changeFindShape(3, 3, 3);
    monster->setPosition(CommonUtils::changePosition(Vec2(900,260)));
    this->addChild(monster);

    monster = ShapeW::create();
    monster->_shapeData->_level->setShapeValue(33);
    monster->changeFindShape(1, 2, 2);
    monster->setPosition(CommonUtils::changePosition(Vec2(760,260)));
    this->addChild(monster);
    
    monster = ShapeW::create();
    monster->_shapeData->_level->setShapeValue(33);
    monster->changeFindShape(0, 1, 0);
    monster->setPosition(CommonUtils::changePosition(Vec2(850,150)));
    this->addChild(monster);
    
    monster = ShapeW::create();
    monster->_shapeData->_level->setShapeValue(6);
    monster->changeFindShape(5, 5, 5);
    monster->setPosition(CommonUtils::changePosition(Vec2(700,210)));
    this->addChild(monster);
    
    monster = ShapeW::create();
    monster->_shapeData->_level->setShapeValue(33);
    monster->changeFindShape(6, 7, 8);
    monster->setPosition(CommonUtils::changePosition(Vec2(890,30)));
    this->addChild(monster);
    
    monster = ShapeW::create();
    monster->_shapeData->_level->setShapeValue(6);
    monster->setLegend(true);
    monster->setPosition(CommonUtils::changePosition(Vec2(680,30)));
    this->addChild(monster);
    
    monster = ShapeW::create();
    monster->_shapeData->_level->setShapeValue(6);
    monster->changeFindShape(3, 4, 3);
    monster->setPosition(CommonUtils::changePosition(Vec2(850,0)));
    this->addChild(monster);
}
void IntroScene::clickNew(Ref *pSender)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    newGame();
}
void IntroScene::clickLoad(Ref *pSender)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    bool isLoadData = UserDefault::getInstance()->getBoolForKey("isLoadData", false);
    if(isLoadData)
    {
        loadGame();
    }
    else
    {
        CommonPopUp *popuP = CommonPopUp::create(popUpType::kOk, TextDb::getInstance()->getEtcText(61).c_str(), nullptr);
        popuP->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
        this->addChild(popuP, 100000);
    }
}
void IntroScene::clickExit(Ref *pSender)
{
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
void IntroScene::newGame()
{
    //AdmobHelper::showVedio();
    
    Player *player = Player::getInstance();
    ShapeF *monster =  ShapeF::create();
    monster->_shapeData->_level->setShapeValue(5);
    monster->_shapeData->_select->setShapeValue(1);
    monster->changeFindShape(7, 7, 7);
    //monster->setLegend(true);
    monster->logStatus();
    player->_monsterList->pushBack(monster);
    
    /*
    monster =  ShapeW::create();
    monster->_shapeData->_level->setShapeValue(16);
    monster->_shapeData->_select->setShapeValue(2);
    monster->changeFindShape(3, 3, 3);
    monster->logStatus();
    player->_monsterList->pushBack(monster);

    
    monster =  ShapeW::create();
    monster->_shapeData->_level->setShapeValue(32);
    monster->_shapeData->_select->setShapeValue(3);
    monster->changeFindShape(3, 3, 3);
    monster->logStatus();
    player->_monsterList->pushBack(monster);
    
    for(int i=0;i<20;i++)
    {
        monster =  ShapeW::create();
        monster->_shapeData->_level->setShapeValue(32);
        monster->changeRandShape(1,6);
        monster->logStatus();
        player->_monsterList->pushBack(monster);
    }
    */
    
    player->_isLoad = false;
    player->_isStartLoad = false;

    /*
    player->_itemList->plusItem(ItemType::kItemTypeResorative1,500);
    player->_itemList->plusItem(ItemType::kItemTypePlusAgility,500);
    player->_itemList->plusItem(ItemType::kItemTypePlusPower,500);
    player->_itemList->plusItem(ItemType::kItemTypePlusStamina,500);
     */
    
    player->_itemList->plusItem(ItemType::kItemTypeResorative1,3);
    player->plusGold(5000);
    Director::getInstance()->replaceScene(GameScene::createScene());
    
}

void IntroScene::loadGame()
{
    Player *player = Player::getInstance();
    player->_isStartLoad = true;
    Director::getInstance()->replaceScene(GameScene::createScene());
}

void IntroScene::onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event )
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK || keycode == EventKeyboard::KeyCode::KEY_F1) {
        clickExit(nullptr);
    }
}
void IntroScene::exitGame()
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}