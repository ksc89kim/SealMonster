//
//  IntroScene.h
//  DotMonster
//
//  Created by 김선철 on 2015. 3. 29..
//
//

#ifndef __DotMonster__IntroScene__
#define __DotMonster__IntroScene__

#include "CommonScene.h"

class IntroScene : public Common
{
private:
    bool _isExitPopup;
    CommonPopUp *_eixtPopuP;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    IntroScene();
    ~IntroScene();
    CREATE_FUNC(IntroScene);
    
    void reloadSound();
    void leftImage();
    void rightImage();
    void clickNew(Ref *pSender);
    void clickLoad(Ref *pSender);
    void clickExit(Ref *pSender);
    void newGame();
    void loadGame();
    
    void onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event );
    void exitGame();
};


#endif /* defined(__DotMonster__IntroScene__) */
