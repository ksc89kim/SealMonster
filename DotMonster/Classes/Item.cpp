//
//  Item.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 5..
//
//

#include "Item.h"
#include "TextDb.h"

Item::Item(){
    _itemCount = ShapeValue::create("I", "T");
    _itemCount->setShapeValue(1);
    
    _itemLevel = ShapeValue::create("I", "L");
    _itemLevel->setShapeValue(1);
}

Item::~Item(){
    if(_itemCount)
        _itemCount->release();
    if(_itemLevel)
        _itemLevel->release();
}

Item *Item::create(int itemType,float itemLevel, float itemCount,const ccMenuCallback& callback)
{
    Item *ret = new Item();
    if (ret && ret->initWithNormalImage("1pixel.png", "1pixel.png", "1pixel.png", callback))
    {
        ret->_itemType = itemType;
        ret->_itemCount->setShapeValue(itemCount);
        ret->_itemLevel->setShapeValue(itemLevel);
        ret->setValue();
        ret->refreshLabel();
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void Item::setValue()
{
    LayerColor *normalLayer = LayerColor::create(Color4B(0,0,0,0), 500, 45);
    setNormalImage(normalLayer);
    LayerColor *disabledLayer = LayerColor::create(Color4B(0,0,0,150), 500, 46);
    setDisabledImage(disabledLayer);
    LayerColor *selectedLayer = LayerColor::create(Color4B(0,0,0,150), 500, 46);
    setSelectedImage(selectedLayer);

    _label = Label::createWithTTF((__String::createWithFormat("%s x%d", getItemName(),(int)_itemCount->getShapeValue()))->getCString(),  CommonUtils::getFontName(), FONT_SIZE);
    _label->setPosition(Vec2(30, normalLayer->getContentSize().height/2));
    _label->setColor(Color3B(0, 0, 0));
    _label->setAnchorPoint(Vec2(0,0.5f));
    this->addChild(_label);
    
    log("Item Name = %s", _label->getString().c_str());
}

const char*Item::setItemSprite()
{
    ItemData *item = TextDb::getInstance()->getItemData(_itemType);
    if(item!=nullptr)
        return item->_itemSprite.c_str();
    else
        return "";
}
const char*Item::getItemName()
{
    ItemData *item = TextDb::getInstance()->getItemData(_itemType);
    return item->_itemName.c_str();
}
const char*Item::getItemContent()
{
    ItemData *item = TextDb::getInstance()->getItemData(_itemType);
    return item->_itemContent.c_str();
}
void Item::plusItem(float count)
{
    _itemCount->addShapeValue(count);
    refreshLabel();
}
void Item::minusItem(float count)
{
    _itemCount->minusShapeValue(count);
    refreshLabel();
}
void Item::setItemCount(float count)
{
    _itemCount->setShapeValue(count);
    refreshLabel();
}
void Item::plusItemUpgrade(float count)
{
    _itemLevel->addShapeValue(count);
    refreshLabel();
}

int Item::getItemCount()
{
    return _itemCount->getShapeValue();
}
int Item::getItemLevel()
{
    return _itemLevel->getShapeValue();
}
void Item::chargeItem(int itemType)
{
    if(_itemType==itemType)
    {
        _itemCount->setShapeValue(5*_itemLevel->getShapeValue());
        refreshLabel();
    }
}
void Item::refreshLabel()
{
    
    switch (_itemType) {
        case ItemType::kItemStamp:
            _label->setString((__String::createWithFormat("%s (+%d) x(%d/%d)", getItemName(), (int)_itemLevel->getShapeValue(),(int)_itemCount->getShapeValue(), 5*(int)_itemLevel->getShapeValue()))->getCString());
            break;
        case ItemType::kItemTypeVailLoon:
        case ItemType::kItemTypeRailLoon:
        case ItemType::kItemTypeZailLoon:
        case ItemType::kItemTypeQailLoon:
        case ItemType::kItemTypeNailLoon:
            _label->setString((__String::createWithFormat("%s (+%d) x%d", getItemName(), (int)_itemLevel->getShapeValue(),(int)_itemCount->getShapeValue()))->getCString());
            break;
        default:
            _label->setString((__String::createWithFormat("%s x%d", getItemName(),(int)_itemCount->getShapeValue()))->getCString());
            break;
    }

}
