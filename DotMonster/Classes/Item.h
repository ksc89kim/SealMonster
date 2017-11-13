//
//  Item.h
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 5..
//
//

#ifndef __dotMonster__Item__
#define __dotMonster__Item__

#include "Define.h"
#include "ShapeValue.h"

class Item:public MenuItemImage
{
    ShapeValue *_itemCount;
    ShapeValue * _itemLevel;
    Label *_label;
    Sprite *_ItemImage;
public:
    Item();
    ~Item();
    int _itemType;

    static Item* create(int itemType, float itemLevel, float itemCount, const ccMenuCallback& callback);
    void setValue();
    const char*setItemSprite();
    const char*getItemName();
    const char*getItemContent();

    void plusItem(float count);
    void minusItem(float count);
    void setItemCount(float count);
    void plusItemUpgrade(float count);
    void chargeItem(int itemType);
    int getItemCount();
    int getItemLevel();
    void refreshLabel();
};

#endif /* defined(__dotMonster__Item__) */
