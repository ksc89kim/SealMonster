//
//  CommonPopUp.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 26..
//
//

#include "CommonPopUp.h"
#include "CommonUtils.h"
#include "Player.h"

CommonPopUp::CommonPopUp()
{
    _type = 0;
}
CommonPopUp::~CommonPopUp()
{
    
}
CommonPopUp *CommonPopUp::create(int type, const char *content,float time,const ccMenuCallback &callback)
{
    CommonPopUp *popUp =  CommonPopUp::create(type,content,callback);
    popUp->_time = time;
    popUp->fadeOut();
    return popUp;
}

CommonPopUp *CommonPopUp::create(int type, const char *content,const ccMenuCallback &callback)
{
    CommonPopUp * layer = new CommonPopUp();
    if(layer && layer->initWithColor(Color4B(0,0,0,150)))
    {
        layer->_type = type;
        layer->ignoreAnchorPointForPosition(false);
        layer->_callbackItem = MenuItem::create(callback);
        Menu *menu  = Menu::create(layer->_callbackItem,nullptr);
        layer->addChild(menu);
        layer->setImage(content);
        layer->setValue();
        return layer;

    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void CommonPopUp::setValue()
{
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    auto positionListener = EventListenerTouchOneByOne::create();
    positionListener->setSwallowTouches(true);
    positionListener->onTouchBegan = CC_CALLBACK_2(CommonPopUp::onTouchBegan, this);
    positionListener->onTouchMoved = CC_CALLBACK_2(CommonPopUp::onTouchMoved, this);
    positionListener->onTouchEnded = CC_CALLBACK_2(CommonPopUp::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(positionListener, this);
}
void CommonPopUp::setImage(const char *content)
{

    _background = Scale9Sprite::create("border.png");
    _label = Label::createWithTTF(content,CommonUtils::getFontName(),FONT_SIZE);
    _label->setColor(Color3B::BLACK);
    switch (_type) {
        case popUpType::kDefault:
        {
            _background->setContentSize(Size(_label->getContentSize().width+FONT_SIZE,_label->getContentSize().height+FONT_SIZE));
            _label->setPosition(Vec2(_background->getContentSize().width/2, _background->getContentSize().height/2));
            break;
        }
        case popUpType::kOk:
        case popUpType::kOkAndCanle:
        {
            float baseWidth = (_label->getContentSize().width>220)?20:240;
            float baseHeight = (_label->getContentSize().width>120)?20:140;
            float padding = 20;
            MenuItem *ok = CommonUtils::createMenuItemLabel("OK", Size(100,50),CC_CALLBACK_0(CommonPopUp::ok, this));
            ok->setPosition(Vec2(0,0));
            Menu *menu = Menu::create(ok, nullptr);
            _background->addChild(menu);
            
            Size popUpSize;
            popUpSize.width = baseWidth+_label->getContentSize().width + FONT_SIZE + ok->getContentSize().width;
            popUpSize.height = baseHeight+_label->getContentSize().height + FONT_SIZE + ok->getContentSize().height+padding;
            _background->setContentSize(popUpSize);
            menu->setPosition(Vec2(_background->getContentSize().width/2,baseHeight + FONT_SIZE));
            _label->setPosition(Vec2(_background->getContentSize().width/2, menu->getPositionY()+
                                     ok->getContentSize().height/2+_label->getContentSize().height/2+padding));
            if(popUpType::kOkAndCanle==_type)
            {
                MenuItem *cancel = CommonUtils::createMenuItemLabel("Cancel", Size(100,50),CC_CALLBACK_0(CommonPopUp::cancel, this));
                menu->addChild(cancel);
                menu->alignItemsHorizontallyWithPadding(20.f);
            }
            break;
        }
        default:
            break;
    }
    _background->addChild(_label);
    _background->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(_background);
}
bool CommonPopUp::onTouchBegan(Touch* touch, Event* event) {
    return true;
}
void CommonPopUp::onTouchMoved(Touch* touch, Event* event) {
}
void CommonPopUp::onTouchEnded(Touch* touch, Event* event) {
}
void CommonPopUp::cancel()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    remove();
}
void CommonPopUp::ok()
{
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    _callbackItem->activate();
    remove();
}
void CommonPopUp::remove()
{
    this->removeFromParent();
}
void CommonPopUp::fadeOut()
{
    _background->runAction(Sequence::create(DelayTime::create(_time),FadeOut::create(0.5f), CallFunc::create(CC_CALLBACK_0(CommonPopUp::remove, this)), NULL));
}