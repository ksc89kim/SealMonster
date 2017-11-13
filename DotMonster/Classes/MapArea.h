//
//  MapArea.h
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 5..
//
//

#ifndef __dotMonster__MapArea__
#define __dotMonster__MapArea__

#include "MapPoint.h"

class MapArea:public ScrollView
{
private:
    ValueMap _mapImageData;
    ValueMap _mapData;
    LayerColor *_background;
    float _width;
    float _height;
    float _space;
    bool _isTouch;
    float _moveDelay;
    int _moveEventPoint;
    Sprite *_playerImage;
    bool _isEradicationItem;
    bool _isTemptationItem;
    bool _isVisibleCaveItem;
public:
    MapArea();
    ~MapArea();
    
    MapPoint *_currentPoint;

    
    static MapArea *create();
    void setImage();
    void setImageMap(const char*file);
    void setPlayer();
    void refreshLoadMap();
    
    int getIntMapData(ValueMap &map, const char*key);
    std::string getStringMapData(ValueMap &map, const char*key);
    Character *getCharacterData(ValueMap &map);
    Node *getBushData(ValueMap &map);
    Quest *getQuestData(ValueMap &map);
    
    void endWalk();
    void right();
    void left();
    void top();
    void bottom();
    
    void movePlayer(const Vec2 &movePosition);
    void checkMapData();
    void checkBattleData();
    bool checkMoveStop(MapPoint *point);
    bool checkInfoStop(MapPoint *point);
    void visibleCave();
    void retunVillage();
    
    void decryptMap(const char *file); //현재 사용하지 않음.
    void decryptData(const char *key, const char *index); //현재 사용하지 않음.
    
    void decodeMap(const char *file);
    void decodeBase64p(ValueMap &map,const char *key, const char *index);

    void loadMapSprite(const char *file);
    void loadMapSpriteMake(int type,ValueMap &map);
    
    void startBattleAnimation();
    void endBattleAnimation();

    void setEradicationItem(bool isEradication);
    void setTemptationItem(bool isTemptation);
    void setVisibleCaveItem(bool isVisibleCave);
    
    bool getEradicationItem();
    bool getTemptationItem();
    bool getVisibleCaveItem();
    
};

#endif /* defined(__dotMonster__MapArea__) */
