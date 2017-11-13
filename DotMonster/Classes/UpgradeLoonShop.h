//
//  UpgradeLoonShop.hpp
//  DotMonster
//
//  Created by 김선철 on 2016. 3. 13..
//
//

#ifndef UpgradeLoonShop_h
#define UpgradeLoonShop_h

#include "Define.h"
#include "Player.h"

class UpgradeLoonShop:public LayerColor
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
    std::vector<Item *> _itemList;
    Menu *_menu;
    MenuItem *_upgrade;
public:
    static UpgradeLoonShop *create(Node *beforeLayer);
    void setImage();
    void nextTyping(float delayTime);
    void nextSetting();
    void setItemLayer();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event *event);
    void clickUpgrade(Ref *pSender);
    void clickItem(Ref *pSender);
    void clickExit(Ref *pSender);
    void next();
    void prev();
    void refreshCount();
    void refreshImage();
};


#endif /* UpgradeLoonShop_h */
