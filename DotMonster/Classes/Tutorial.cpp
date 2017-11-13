//
//  Tutorial.cpp
//  DotMonster
//
//  Created by 김선철 on 2016. 3. 9..
//
//

#include "Tutorial.h"
#include "TextDb.h"
#include "Player.h"
#include "BattleLayer.h"
#include "GameScene.h"

Tutorial *Tutorial::create(Node *beforeLayer, Node *enemy,Node *mapArea)
{
    Tutorial *ret = new (std::nothrow) Tutorial();
    if (ret && ret->initWithColor(Color4B(0,0,0,0)))
    {
        ret->_mapArea = mapArea;
        ret->_beforeLayer = beforeLayer;
        ret->_enemy = enemy;
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

void Tutorial::setImage()
{
    if(_enemy!=nullptr)
        this->addChild(_enemy);
    
    if(_beforeLayer!=nullptr)
        _beforeLayer->setVisible(false);
    
    
    _tutorial1 = Sprite::create("tutorial.png");
    _tutorial1->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    CommonUtils::fitNode(_tutorial1, this->getContentSize());
    this->addChild(_tutorial1);
    
    auto label = Label::createWithTTF(TextDb::getInstance()->getEtcText(63), CommonUtils::getFontName(), 15);
    label->setPosition(Vec2(316,194));
    label->setAnchorPoint(Vec2(0.5f,0));
    _tutorial1->addChild(label);
    
    label = Label::createWithTTF(TextDb::getInstance()->getEtcText(64), CommonUtils::getFontName(), 15);
    label->setPosition(Vec2(498,246));
    label->setAnchorPoint(Vec2(0.5f,0));
    _tutorial1->addChild(label);
    
    label = Label::createWithTTF(TextDb::getInstance()->getEtcText(65), CommonUtils::getFontName(), 15);
    label->setPosition(Vec2(673,192));
    label->setAnchorPoint(Vec2(0.5f,0));
    _tutorial1->addChild(label);
    
    _tutorial2 = Sprite::create("tutorial2.png");
    _tutorial2->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    _tutorial2->setVisible(false);
    CommonUtils::fitNode(_tutorial2, this->getContentSize());
    this->addChild(_tutorial2);
    
    label = Label::createWithTTF(TextDb::getInstance()->getEtcText(66), CommonUtils::getFontName(), 15);
    label->setPosition(Vec2(311,193));
    label->setAnchorPoint(Vec2(0.5f,0));
    _tutorial2->addChild(label);
    
    label = Label::createWithTTF(TextDb::getInstance()->getEtcText(67), CommonUtils::getFontName(), 15);
    label->setPosition(Vec2(442,292));
    label->setAnchorPoint(Vec2(0.5f,0));
    _tutorial2->addChild(label);
    
    label = Label::createWithTTF(TextDb::getInstance()->getEtcText(68), CommonUtils::getFontName(), 15);
    label->setPosition(Vec2(576,400));
    label->setAnchorPoint(Vec2(0.5f,0));
    _tutorial2->addChild(label);
    
    label = Label::createWithTTF(TextDb::getInstance()->getEtcText(69), CommonUtils::getFontName(), 15);
    label->setPosition(Vec2(700,255));
    label->setAnchorPoint(Vec2(0.5f,0));
    _tutorial2->addChild(label);
    
    _tutorial3 = Sprite::create("tutorial3.png");
    _tutorial3->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    _tutorial3->setVisible(false);
    CommonUtils::fitNode(_tutorial3, this->getContentSize());
    this->addChild(_tutorial3);
    
    label = Label::createWithTTF(TextDb::getInstance()->getEtcText(70), CommonUtils::getFontName(), 15);
    label->setPosition(Vec2(564,320));
    label->setAnchorPoint(Vec2(0.5f,0));
    _tutorial3->addChild(label);
    
    _tutorial4 = Sprite::create("tutorial4.png");
    _tutorial4->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    CommonUtils::fitNode(_tutorial4, this->getContentSize());
    _tutorial4->setVisible(false);
    this->addChild(_tutorial4);
    
    label = Label::createWithTTF(TextDb::getInstance()->getEtcText(71), CommonUtils::getFontName(), 15);
    label->setPosition(Vec2(180,396));
    label->setAnchorPoint(Vec2(0.5f,0));
    _tutorial4->addChild(label);
    
    label = Label::createWithTTF(TextDb::getInstance()->getEtcText(72), CommonUtils::getFontName(), 15);
    label->setPosition(Vec2(300,314));
    label->setAnchorPoint(Vec2(0.5f,0));
    _tutorial4->addChild(label);
    
    label = Label::createWithTTF(TextDb::getInstance()->getEtcText(73), CommonUtils::getFontName(), 15);
    label->setPosition(Vec2(395,206));
    label->setAnchorPoint(Vec2(0.5f,0));
    _tutorial4->addChild(label);
    
    label = Label::createWithTTF(TextDb::getInstance()->getEtcText(74), CommonUtils::getFontName(), 15);
    label->setPosition(Vec2(641,263));
    label->setAnchorPoint(Vec2(0.5f,0));
    _tutorial4->addChild(label);
    
    label = Label::createWithTTF(TextDb::getInstance()->getEtcText(75), CommonUtils::getFontName(), 15);
    label->setPosition(Vec2(1000,269));
    label->setAnchorPoint(Vec2(0.5f,0));
    _tutorial4->addChild(label);
    
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    auto positionListener = EventListenerTouchOneByOne::create();
    positionListener->setSwallowTouches(true);
    positionListener->onTouchBegan = CC_CALLBACK_2(Tutorial::onTouchBegan, this);
    positionListener->onTouchMoved = CC_CALLBACK_2(Tutorial::onTouchMoved, this);
    positionListener->onTouchEnded = CC_CALLBACK_2(Tutorial::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(positionListener, this);
    
    Player::getInstance()->pauseMusic();
}

bool Tutorial::onTouchBegan(Touch* touch, Event* event) {
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    return true;
}
void Tutorial::onTouchMoved(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    
}
void Tutorial::onTouchEnded(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    if(_tutorial1->isVisible())
    {
        _tutorial1->setVisible(false);
        _tutorial2->setVisible(true);
    }
    else if(_tutorial2->isVisible())
    {
        _tutorial2->setVisible(false);
        _tutorial3->setVisible(true);
    }
    else if(_tutorial3->isVisible())
    {
        _tutorial3->setVisible(false);
        _tutorial4->setVisible(true);
    }
    else
    {
        Character * enemy = ((Character *)_enemy);
        ShapeCommon *monster = ShapeF::create();
        if(enemy->_monsterList->size()>0)
        {
           monster = (ShapeCommon *)enemy->_monsterList->at(0);
        }
        Character *spaceCharacter = Character::create();
        if(monster!=nullptr)
            spaceCharacter->_monsterList->pushBack(monster);
        
        GameScene* currentScene = GameScene::runningScene();
        BattleLayer *battleLayer = BattleLayer::create(_beforeLayer,spaceCharacter, _mapArea);
        battleLayer->setPosition(Vec2(currentScene->getContentSize().width/2,currentScene->getContentSize().height/2));
        currentScene->addChild(battleLayer);
        
        Player::getInstance()->setTutorial(true);
        Player::getInstance()->resumeMusic();
        this->removeFromParent();
    }
}