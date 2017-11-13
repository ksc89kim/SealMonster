//
//  MapPoint.h
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 28..
//
//

#ifndef __dotMonster__MapPoint__
#define __dotMonster__MapPoint__

#include "Quest.h"
#include "Player.h"

class MapPoint:public Sprite
{

public:
    int _type;
    Character *_character;
    Quest *_quest;
    Node *_info;
    int _infoType;
    std::string _move;
    std::string _questCharacter;
    int _moveEvent;
    int _villageInfo;
    bool _isCenter;
    bool _originalVisible;
    bool _typeVisible;

    MapPoint *_top;
    MapPoint *_left;
    MapPoint *_right;
    MapPoint *_bottom;
    
    Sprite *_pointSprite;
    Node *_pointType;

    MapPoint();
    ~MapPoint();
    
    static MapPoint *create(int tag,int type, int infoType,int villageInfo,int moveEvent,const char *moveData, const char *questCharacterIndex,Character *character, Quest *quest, Node *info);
    void setValue(int type, int infoType,int villageInfo,int moveEvent,const char *moveData, const char *questCharacterIndex, Character *character, Quest *quest, Node *info);
    void checkPointSprite();
    void checkTypeSprite();
    Vec2 getMovePosition(int beforeTag, const Size& character);
    void releaseData();
    void initData();
    void setVisibleAllMap(bool isVisible);
};

#endif /* defined(__dotMonster__MapPoint__) */
