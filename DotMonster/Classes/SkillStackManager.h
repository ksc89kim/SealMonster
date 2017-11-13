//
//  SkillStackManager.h
//  dotMonster
//
//  Created by 김선철 on 2014. 10. 20..
//
//

#ifndef __dotMonster__SkillStackManager__
#define __dotMonster__SkillStackManager__

#include "Define.h"
#include "MoveObject.h"
#include "StackObject.h"

class SkillStackManager:public LayerColor
{
private:
    float _dt;
public:
    Vector<StackObject *> *_stackImages;
    MoveObject *_moveStackCharacter;
    Sprite *_button;
    bool _missStackLevel;
    ProgressTimer *_stackTimer;
    
    Label *_skill1;
    Label *_skill2;
    Label *_skill3;
    Label *_skill4;
    
    SkillStackManager();
    ~SkillStackManager();
    
    static SkillStackManager* create(const Color4B& color);

    void setStackImage();
    void batchStack(float dt);
    void collisionCheck(Ref *ref);
    void randOneBatch(StackObject *object, int index);
    void start();
    void end();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    void levelGap(float gap);
    void addSkill(int level);
    void resetSkill();
};

#endif /* defined(__dotMonster__SkillStackManager__) */
