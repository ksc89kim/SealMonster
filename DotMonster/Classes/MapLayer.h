//
//  MapLayer.h
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 7..
//
//

#ifndef __dotMonster__MapLayer__
#define __dotMonster__MapLayer__

#include "MapArea.h"
class MapLayer:public LayerColor
{
private:
    MapArea *_mapArea;
    bool _isEventTouchEnable;
public:
    MapLayer();
    ~MapLayer();
    static MapLayer *create();
    void setImage();
    void clickRight();
    void clickLeft();
    void clickTop();
    void clickBottom();
   
    void clickItemBag();
    void clickMonsterList();
    void clickSave();
    void clickIntro();
    void clickSetting();
    void clickVideo();
    void clickRanking();
    void clickMiniMap();

    void ranking();
    void save();
    void goIntro();
    void showVideo();
    MapArea *getMapArea();
    void setEventTouchEnable(bool isEnable);
    LayerColor *_battleAnimation;
    LayerColor *_visibleCave;
    
    void refreshMapArea();
};

#endif /* defined(__dotMonster__MapLayer__) */
