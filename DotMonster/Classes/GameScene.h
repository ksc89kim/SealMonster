//
//  GameScene.h
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 21..
//
//

#ifndef __dotMonster__GameScene__
#define __dotMonster__GameScene__

#include "CommonScene.h"
#include "MapLayer.h"
#include "LoadingLayer.h"
class GameScene : public Common
{
private:
    bool _isExitPopup;
    CommonPopUp *_eixtPopuP;
    MapLayer *_map;
    LoadingLayer *_loadinglayer;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    static GameScene* runningScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void onEnter();
    void createPopup(int type,const char *text,const ccMenuCallback &callback);
    
    GameScene();
    ~GameScene();
    
    void onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event );
    void exitGame();
    MapLayer *getMapLayer();
    void videoSuccess();
    void schedulVideoSucces(float df);
    void videoNotContent();
    void schedulNotContent(float df);
    void videoFail();
    void setVisibleLoading(bool isLoading);
    void showInterstitalAd();
    CREATE_FUNC(GameScene);
};


#endif /* defined(__dotMonster__GameScene__) */
