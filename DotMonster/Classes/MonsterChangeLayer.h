//
//  MonsterChangeLayer.h
//  DotMonster
//
//  Created by 김선철 on 2016. 1. 5..
//
//

#ifndef __DotMonster__MonsterChangeLayer__
#define __DotMonster__MonsterChangeLayer__

#include "Define.h"
#include "ShapeCommon.h"

class MonsterChangeLayer:public LayerColor
{
    int _index;
    int _animationType;
    Node *_backLayer;
    Node *_player;
    ShapeCommon *_monster;
    LayerColor *_monsterList;
    LayerColor *_selectMonsterList;
public:
    MonsterChangeLayer();
    ~MonsterChangeLayer();
    static MonsterChangeLayer* create(Node *backLayer, int animationType);
    void setImage();
    void close(Ref *pSender);
    void clickMonster(Ref *monster);
    void refreshImage();
    bool checkItem();
    bool checkHp(ShapeObject *data);
};

#endif /* defined(__DotMonster__MonsterChangeLayer__) */
