//
//  BattleLayer.h
//  dotMonster
//
//  Created by 김선철 on 2014. 10. 19..
//
//

#ifndef __dotMonster__BattleLayer__
#define __dotMonster__BattleLayer__

#include "Battle.h"
#include "SkillStackManager.h"
#include "ShapeCommon.h"
#include "Player.h"

class Bush:public Sprite
{
    int _type;
    int _minIndex;
    int _maxIndex;
    int _minLevel;
    int _maxLevel;
public:

    Bush();
    ~Bush();
    static Bush *create(const char *bushInfo);
    ShapeCommon *getMonster();
    void setValue(const char *bushInfo);
    static Node *createCharacterMonster(std::vector<std::string> characterMonster, int select);
};

class BattleLayer:public LayerColor
{
    enum
    {
        zCatchOrder = 10,
        zBorderOrder,
    };
private:
    float _delayTime;
    SkillStackManager *_stackManager;
    Node *_player;
    Node *_mapArea;
    Node *_enemy;
    Node *_beforeLayer;
    Node *_quest;
    bool _isStackGame;
    bool _isPushSkill;
    LayerColor *_readyGameLayer;
    Vec2 _playMonsterPosition;
    Vec2 _enemyMonsterPosition;
    float _tempScale;
    Label *_playerLabel;
    Label *_enemyLabel;
    Menu *_skillButtons;
public:
    BattleLayer();
    ~BattleLayer();
    
    Battle *_battleObject;
    ShapeCommon *_playerMonSter;
    ShapeCommon *_enemyMonSter;
    ProgressTimer *_playerHp;
    ProgressTimer *_enemyHp;
    
    static BattleLayer* create(Node *beforeLayer,Node *enemy,Node *mapArea=nullptr, int battleType = battleType::kBushType, Node *quest=nullptr);
    void setStackGameImage();
    void showSkillList(Ref *ref);
    void startStackGame();
    void stackGame(float dt);
    void endStackGame();
    void endStackAnimation();
    
    int checkMonster(bool isFirst);
    bool changeMonster(bool isPlayer, Node *user, ProgressTimer *hp,const Vec2& position);
    bool changeMonster(Ref *monster);
    void regulateMonster();
    void finish();
    void reward();

    int expUp();
    void evolution();
    void endEvolution(Ref *ref);
    
    void levelUp();
    void endLevelUp(Ref *ref);
    void endEvolutinOrLevelUpData();
    
    void exitBattle(Ref *ref);
    void failExit(Ref *ref);
    void attackEnemy();
    int catchMonster();
    void catchMonsterAnimation();
    void endCatchMonsterAnimation();
    void catchFailMonsterAnimation();
    void endCatchFailMonsterAnimation();

    void showMonterList(Ref *ref);
    void showItemContainer(Ref *ref);

    void refreshHp();
    void refreshMonsterInfo();
    void refreshPlayMonsterInfo();
    void refreshSkillButtons();
    void createSkillButton(const char*skillButton, const char *skillName, bool isLock, int index);
    void clickSkill(Ref *ref);
    void clickSkillExit(Ref *ref);
    
    void startBattleAnimation(Node *target);
    void endBattleAnimation(Node *target);

    void removeNode(Node *target);
    int _battleType;
};

#endif /* defined(__dotMonster__BattleLayer__) */
