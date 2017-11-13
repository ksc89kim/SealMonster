//
//  Setting.cpp
//  DotMonster
//
//  Created by 김선철 on 2016. 2. 3..
//
//

#include "Setting.h"
#include "Player.h"
#include "TextDb.h"

SettingLayer *SettingLayer::create()
{
    SettingLayer *ret = new (std::nothrow) SettingLayer();
    if (ret && ret->initWithColor(Color4B(0,0,0,150)))
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
void SettingLayer::setImage()
{
    Sprite *border = (Sprite *)Scale9Sprite::create("border.png");
    border->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(border);
    
    
    Menu *menu = Menu::create();
    _sound= (MenuItemSprite *)CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(24),CC_CALLBACK_0(SettingLayer::clickSound, this));
    menu->addChild(_sound);
    _music= (MenuItemSprite *)CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(26), CC_CALLBACK_0(SettingLayer::clickMusic, this));
    menu->addChild(_music);
    MenuItem *close = CommonUtils::createMenuItemLabel(TextDb::getInstance()->getEtcText(3), CC_CALLBACK_0(SettingLayer::clickClose, this));
    menu->addChild(close);
    menu->alignItemsVerticallyWithPadding(10.0f);
    border->setContentSize(Size(_music->getContentSize().width+35,_sound->getContentSize().height+_music->getContentSize().height+close->getContentSize().height+60));

    menu->setPosition(Vec2(border->getContentSize().width/2, border->getContentSize().height/2));
    border->addChild(menu);
    

    setSound(Player::getInstance()->getSound(),true);
    setMusic(Player::getInstance()->getMusic(),true);

}
void SettingLayer::setSound(bool isSound, bool isFirst)
{
    if(isSound)
    {
        CommonUtils::setMenuItemLabel(_sound, TextDb::getInstance()->getEtcText(24));
        _sound->setTag(1);
    }
    else
    {
        CommonUtils::setMenuItemLabel(_sound, TextDb::getInstance()->getEtcText(25));
        _sound->setTag(0);
    }
    if(!isFirst)
        Player::getInstance()->setSound(isSound);

}
void SettingLayer::setMusic(bool isMusic, bool isFirst)
{
    Player::getInstance()->setMusic(isMusic);
    if(isMusic)
    {
        CommonUtils::setMenuItemLabel(_music, TextDb::getInstance()->getEtcText(26));
        _music->setTag(1);
        if(!isFirst)
            Player::getInstance()->playMusic(SOUND_MUSIC_BASE);
    }
    else
    {
        CommonUtils::setMenuItemLabel(_music, TextDb::getInstance()->getEtcText(27));
        _music->setTag(0);
        if(!isFirst)
            Player::getInstance()->stopMusic();
    }

}

void SettingLayer::clickSound()
{
    setSound((_sound->getTag()==1)?false:true,false);
}
void SettingLayer::clickMusic()
{
    setMusic((_music->getTag()==1)?false:true,false);
}
void SettingLayer::clickClose()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    this->removeFromParent();
}