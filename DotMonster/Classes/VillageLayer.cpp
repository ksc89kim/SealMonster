//
//  VillageLayer.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 22..
//
//

#include "VillageLayer.h"
#include "GameScene.h"
#include "TalkLayer.h"
#include "StampCharge.h"
#include "Hospital.h"
#include "CommonUtils.h"
#include "ItemShop.h"

VillageLayer::VillageLayer()
{
    
}

VillageLayer::~VillageLayer()
{
    
}

VillageLayer *VillageLayer::create(cocos2d::Node *beforeLayer, int villageTag)
{
    VillageLayer * layer = new VillageLayer();
    if(layer && layer->initWithColor(Color4B(255,255,255,255)))
    {
        layer->ignoreAnchorPointForPosition(false);
        layer->_beforeLayer = beforeLayer;
        layer->_villageTag = villageTag;
        layer->setValue();
        layer->setImage();
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}
void VillageLayer::setValue()
{
    _beforeLayer->setVisible(false);
}
void VillageLayer::setImage()
{
    float beginningX = 100;
    float increase = 50;
    float x = beginningX;
    float y = 0;

    Player::getInstance()->playMusic(SOUND_MUSIC_CITY);
    Menu *menu = Menu::create();
    menu->setPosition(Vec2(0,0));
    
    MenuItem *hospital = CommonUtils::createMenuItem("hospital.png", CC_CALLBACK_0(VillageLayer::clickHospital, this));
    y = this->getContentSize().height-hospital->getContentSize().height;
    hospital->setPosition(Vec2(x,y));
    menu->addChild(hospital);
    
    Label *villageContent = Label::createWithTTF(TextDb::getInstance()->getEtcText(8).c_str(),CommonUtils::getFontName(),FONT_SIZE);
    villageContent->setPosition(Vec2(hospital->getContentSize().width/2, -FONT_SIZE));
    villageContent->setColor(Color3B(0,0,0));
    CommonUtils::setLabelAutoSize(villageContent, FONT_SIZE, Size(hospital->getContentSize().width+25,25));
    hospital->addChild(villageContent);
    
    MenuItem *charge = CommonUtils::createMenuItem("chageShop.png", CC_CALLBACK_0(VillageLayer::clickCharge, this));
    x += increase+charge->getContentSize().width;
    charge->setPosition(Vec2(x,y));
    menu->addChild(charge);

    villageContent = Label::createWithTTF(TextDb::getInstance()->getEtcText(54).c_str(),CommonUtils::getFontName(),FONT_SIZE);
    villageContent->setPosition(Vec2(charge->getContentSize().width/2, -FONT_SIZE));
    villageContent->setColor(Color3B(0,0,0));
    CommonUtils::setLabelAutoSize(villageContent, FONT_SIZE, Size(charge->getContentSize().width+25,25));
    charge->addChild(villageContent);
    
    MenuItem *itemShop = CommonUtils::createMenuItem("itemShop.png", CC_CALLBACK_0(VillageLayer::clickItemShop, this));
    x += increase+itemShop->getContentSize().width;
    itemShop->setPosition(Vec2(x,y));
    menu->addChild(itemShop);

    villageContent = Label::createWithTTF(TextDb::getInstance()->getEtcText(16).c_str(),CommonUtils::getFontName(),FONT_SIZE);
    villageContent->setPosition(Vec2(itemShop->getContentSize().width/2, -FONT_SIZE));
    villageContent->setColor(Color3B(0,0,0));
    CommonUtils::setLabelAutoSize(villageContent, FONT_SIZE, Size(itemShop->getContentSize().width+25,25));
    itemShop->addChild(villageContent);
    
    log(" _villageTag = %d", _villageTag);
    
    std::map<unsigned int,VillageData *> _villageInfo = TextDb::getInstance()->getVillageDataMap();
    for(int i=1;i<_villageInfo.size();i++)
    {
        VillageData *data =  _villageInfo[i];
        if(data->_villageType==_villageTag)
        {
            MenuItem *house = CommonUtils::createMenuItem("house.png", CC_CALLBACK_1(VillageLayer::click, this));
            house->setTag(data->_houseType);
            
            if(x+house->getContentSize().width+increase>=this->getContentSize().width)
            {
                x = beginningX;
                y -= (increase+house->getContentSize().height);
            }
            else
                x += increase+charge->getContentSize().width;
            
            house->setPosition(Vec2(x,y));
            menu->addChild(house);
            
            villageContent = Label::createWithTTF(data->_houseName.c_str(),CommonUtils::getFontName(),FONT_SIZE);
            villageContent->setPosition(Vec2(house->getContentSize().width/2, -FONT_SIZE));
            villageContent->setColor(Color3B(0,0,0));
            CommonUtils::setLabelAutoSize(villageContent, FONT_SIZE, Size(house->getContentSize().width+25,25));
            house->addChild(villageContent);
        }
    }
    
    MenuItem *exit = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(3).c_str(), Size(100,50),CC_CALLBACK_0(VillageLayer::exit, this));
    exit->setPosition(CommonUtils::changePosition(Vec2(900,50)));
    menu->addChild(exit);
    this->addChild(menu);
}

void VillageLayer::clickHospital()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    log("click Hospital");
    GameScene *currentScene =  GameScene::runningScene();
    HospitalLayer *stamp = HospitalLayer::create(this);
    currentScene->addChild(stamp);
    
}
void VillageLayer::clickCharge()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    log("click Charge");
    GameScene *currentScene =  GameScene::runningScene();
    StampChargeLayer *stamp = StampChargeLayer::create(this);
    currentScene->addChild(stamp);
}
void VillageLayer::clickItemShop()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    log("click Itemshop");
    GameScene *currentScene =  GameScene::runningScene();
    ItemShopLayer *shop = ItemShopLayer::create(this);
    currentScene->addChild(shop);
}
void VillageLayer::click(cocos2d::Ref *object)
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    log("click");
    GameScene *currentScene =  GameScene::runningScene();
    MenuItemImage *character = (MenuItemImage *)object;
    TalkLayer *talkLyaer = TalkLayer::create(this, character->getTag());
    talkLyaer->setPosition(Vec2(this->getContentSize().width/2,this->getContentSize().height/2));
    currentScene->addChild(talkLyaer);

}
void VillageLayer::exit()
{
    Player::getInstance()->playMusic(SOUND_MUSIC_BASE);
    //초반 나가기 막기.
    Quest *quest = QuestConatiner::sharedObject()->getCurrentQuest(questIndex::kMainQuest);
    if(quest!=nullptr)
    {
        if(quest->getQuestLevel()<3)
        {
            (GameScene::runningScene())->createPopup(popUpType::kOk, TextDb::getInstance()->getEtcText(55).c_str(), nullptr);
            return;
        }
    }
    Player::getInstance()->resumeMusic();
    _beforeLayer->setVisible(true);
    this->removeFromParent();
    log("exit");
}

