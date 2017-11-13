//
//  ItemContainer.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 6..
//
//

#include "ItemContainer.h"
#include "Player.h"
#include "GameScene.h"

ItemContainer::ItemContainer()
{
    _itemList = new Vector<Item *>();
    _callback = nullptr;
}

ItemContainer::~ItemContainer()
{
    if(_itemList){
        delete _itemList;
    }
}

ItemContainer *ItemContainer::create(Node *parent)
{
    ItemContainer * ret = new ItemContainer();
    if (ret && ret->init())
    {
        ret->_player = parent;
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
	return ret;
}

void ItemContainer::plusItem(int itemType, int itemCount)
{
    bool cheeckItem = false;
    for (int i=0; i<_itemList->size(); i++) {
        Item *item = _itemList->at(i);
        if(item->_itemType == itemType)
        {
            cheeckItem = true;
            item->plusItem(itemCount);
        }
    }
    if(!cheeckItem){
        Item *item = Item::create(itemType,1, itemCount, _callback);
        _itemList->pushBack(item);
    }
}
void ItemContainer::plusItemWithPopup(int itemType, int itemCount)
{
    plusItem(itemType,itemCount);
    GameScene *scene = GameScene::runningScene();
    Item *item = Item::create(itemType,1, itemCount, nullptr);
    __String *tempString = __String::createWithFormat(TextDb::getInstance()->getEtcText(41).c_str(), item->getItemName(), item->getItemCount());
    if(scene)
        scene->createPopup(popUpType::kOk, tempString->getCString(), nullptr);
}
void ItemContainer::plusItem(Item *item)
{
    plusItem(item->_itemType, item->getItemCount());
}
void ItemContainer::plusItemWithPopup(Item *item)
{
    plusItem(item);
    GameScene *scene = GameScene::runningScene();
    __String *tempString = __String::createWithFormat(TextDb::getInstance()->getEtcText(41).c_str(), item->getItemName(), item->getItemCount());
    if(scene)
        scene->createPopup(popUpType::kOk, tempString->getCString(), nullptr);

}
void ItemContainer::minusItem(int itemType, int itemCount)
{
    int index = -1;
    for (int i=0; i<_itemList->size(); i++) {
        Item *item = _itemList->at(i);
        if(item->_itemType == itemType)
        {
            if(item->getItemCount()-itemCount>0)
            {
                item->minusItem(itemCount);
            }
            else if(itemType==ItemType::kItemStamp)
            {
                item->setItemCount(0);
            }
            else
            {
                index = i;
            }
        }
    }
    if(index>=0)
    {
        _itemList->erase(index);
    }

}
void ItemContainer::minusItem(Item *item)
{
    minusItem(item->_itemType, item->getItemCount());
}

void ItemContainer::plusItemUpgrade(int itemType, int itemCount)
{
    for (int i=0; i<_itemList->size(); i++) {
        Item *item = _itemList->at(i);
        if(item->_itemType == itemType)
        {
            item->plusItemUpgrade(itemCount);
        }
    }
}
void ItemContainer::plusItemUpgrade(Item *item)
{
    plusItemUpgrade(item->_itemType, item->getItemCount());
}

bool ItemContainer::isItem(int itemType)
{
    bool isItem = false;
    for (int i=0; i<_itemList->size(); i++) {
        Item *item = _itemList->at(i);
        if(item->_itemType == itemType)
        {
            isItem = true;
        }
    }
    return isItem;
}

Item *ItemContainer::getItem(int itemType)
{
    for (int i=0; i<_itemList->size(); i++) {
        Item *item = _itemList->at(i);
        if(item->_itemType == itemType)
        {
            return item;
        }
    }
    return nullptr;
}
void ItemContainer::chargeItem(int itemType)
{
    for (int i=0; i<_itemList->size(); i++) {
        Item *item = _itemList->at(i);
        if(item->_itemType == itemType)
        {
            item->chargeItem(itemType);
        }
    }
}
int ItemContainer::size()
{
    return _itemList->size();
}
Item *ItemContainer::getIndexItem(int index)
{
    return _itemList->at(index);
}

void ItemContainer::setCallBack(const ccMenuCallback &callback)
{
    _callback = callback;
    for (int i=0; i<_itemList->size(); i++) {
        Item *item = _itemList->at(i);
        item->setCallback(callback);
    }
}
void ItemContainer::clear()
{
    _itemList->clear();
}
void ItemContainer::pushItem(Item *item)
{
    _itemList->pushBack(item);
}

