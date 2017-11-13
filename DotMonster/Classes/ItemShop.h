//
//  ItemButton.h
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 10..
//
//

#ifndef __dotMonster__ItemShop__
#define __dotMonster__ItemShop__

#include "Define.h"
#include "Player.h"

class ItemShopLayer:public LayerColor
{
private:
    Node *_beforeLayer;
    Label *_content;
    std::string _currentTalk;
    bool _isTyping;
    vector<string> _talkArray;
    int _index;
    bool _isExit;
    Sprite *_talkBorder;
    Sprite *_itemButtonBorder;
    Sprite *_itemListBorder;
    Player *_player;
    int _itemIndex;
    int _count;
    Label *_countLabel;
    Label *_goldLabel;
    std::vector<ItemData *> _shopList;
    std::map<unsigned int,ShapeValue *> _shopPriceList;
    Menu *_menu;
    MenuItem *_buy;
public:
    static ItemShopLayer *create(Node *beforeLayer);
    void setImage();
    void nextTyping(float delayTime);
    void nextSetting();
    void setItemLayer();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event *event);
    void clickBuy(Ref *pSender);
    void clickItem(Ref *pSender);
    void clickExit(Ref *pSender);
    void next();
    void prev();
    void refreshCount();
    void refreshImage();
    int isPrice(int itemType);
};

#endif /* defined(__dotMonster__ItemShop__) */
