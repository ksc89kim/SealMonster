//
//  ItemBagLayer.h
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 6..
//
//

#ifndef __dotMonster__ItemBagLayer__
#define __dotMonster__ItemBagLayer__

#include "Player.h"

class ItemBagLayer:public LayerColor
{
    Sprite *_border;
    Node *_beforeLayer;
    Menu *_menu;
    int _index;
    int _count;
    bool _isBattle;
    Label *_countLabel;
    Sprite *_talkBorder;
    Label *_content;
    vector<string> _talkArray;
    std::string _currentTalk;
    bool _isTyping;
    int _itemIndex;
    MenuItem *_use;

public:
    ItemBagLayer();
    ~ItemBagLayer();
    Player *_player;
    static ItemBagLayer* create(Node *beforeLayer, bool isBattle);
    void next();
    void prev();
    void setImage();
    void refreshImage();
    void refreshCount();
    void useItem(Ref *pSender,Ref *object);
    void clickItem(Ref *object);
    void createUseItemPopup(Ref *object);

    void close(Ref *object);
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event *event);
    
    void nextTyping(float delayTime);
    void nextSetting();
};
#endif /* defined(__dotMonster__ItemBagLayer__) */
