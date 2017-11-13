//
//  MosterListLayer.h
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 12..
//
//

#ifndef __dotMonster__MosterListLayer__
#define __dotMonster__MosterListLayer__

#include "Define.h"
#include "ShapeCommon.h"

class MonsterListLayer;

class MonsterBattleSelectLayer: public LayerColor
{
private:
    ShapeCommon *_shape;
    MonsterListLayer *_monsterListLayer;
public:
    MonsterBattleSelectLayer();
    ~MonsterBattleSelectLayer();
    static MonsterBattleSelectLayer* create(ShapeCommon *data, MonsterListLayer *mLayer);
    void setImage();
    void click(Ref *pSender);

    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event *event);
};

class MonsterEvolutionLayer: public LayerColor
{
private:
    ShapeCommon *_shape;
public:
    MonsterEvolutionLayer();
    ~MonsterEvolutionLayer();
    static MonsterEvolutionLayer* create(ShapeCommon *data);
    void setImage();
    void clickExit(Ref *pSender);
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event *event);
};


class MonsterListLayer:public LayerColor
{
private:
    Menu *_menu;
    Sprite *_border;
    Sprite *_info;
    Node *_backLayer;
    Node *_player;
    int _index;
    int _count;
    int _animationType;
    Label *_countLabel;
    ShapeCommon *_removeMonster;
public:
    MonsterListLayer();
    ~MonsterListLayer();
    static MonsterListLayer* create(Node *backLayer, int animationType);
    void setImage();
    void refreshImage();
    void refreshCount();
    void clickInfo(Ref *target);
    void refreshInfo(ShapeCommon *shape);
    void useItem(Ref *target);
    void next();
    void prev();
    void close(Ref *object);
    bool checkItem();
    bool checkHp(ShapeObject *data);
    void clickBattle(Ref *target);
    void clickRemove(Ref *target);
    void clickEvolutionView(Ref *target);

    void removeMonster();

};


#endif /* defined(__dotMonster__MosterListLayer__) */
