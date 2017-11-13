//
//  ItemContainer.h
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 6..
//
//

#ifndef __dotMonster__ItemContainer__
#define __dotMonster__ItemContainer__

#include "Item.h"

class ItemContainer:public Node
{
    Node *_player;
    Vector<Item *> *_itemList;
    ccMenuCallback _callback;
public:
    ItemContainer();
    ~ItemContainer();
    static ItemContainer* create(Node *parent);
    void plusItem(int itemType, int itemCount);
    void plusItemWithPopup(int itemType, int itemCount);
    void plusItem(Item *item);
    void plusItemWithPopup(Item *item);

    void minusItem(int itemType, int itemCount);
    void minusItem(Item *item);
    void plusItemUpgrade(int itemType, int itemCount);
    void plusItemUpgrade(Item *item);
    void chargeItem(int itemType);
    bool isItem(int itemType);
    Item *getItem(int itemType);
    int size();
    Item *getIndexItem(int index);
    void pushItem(Item *item);
    void setCallBack(const ccMenuCallback &callback);
    void clear();
};

#endif /* defined(__dotMonster__ItemContainer__) */
