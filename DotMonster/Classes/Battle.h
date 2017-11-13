//
//  Battle.h
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 19..
//
//

#ifndef __ShapeMaster__Battle__
#define __ShapeMaster__Battle__

#include "Define.h"
#include "ShapeSkill.h"
#include "ShapeValue.h"


class Battle:public Node
{
    std::function<void()> _func;
public:
    ShapeValue *_skillLevelCount;
    ShapeValue *_count;
    ShapeValue *_skillDamage;
    ShapeValue *_skillTurn;
    Battle();
    ~Battle();
    static Battle* create(std::function<void()> function);
    //Battle Data or animation (skill)
    void initBattleData(); //배틀 초기화
    bool doPushSkill(Ref *target,ShapeSkill *skill); //스킬 쌓기
    void useSkill(Ref *target, Ref *enemy, bool enemyTime = false); //사용 스킬 player
    float calAttribute(Ref *target, Ref *enemy); //속성 스킬 계산
    float calBase(Ref *target, Ref *enemy); //기본 스킬 속성 계산
    float calLevel(Ref *target, Ref *enemy); //레벨 차이별 데미지 계산.
    float getAttackSkillPerCent(int level); // 스킬 레벨별 데미지
    float getTurnSkillPerCent(int level); //턴제 계산
    void startAnimation(Ref *target, Ref *enemy,bool enemyTime, Ref *skill, bool isEnemyAnimation = false); //스킬 애니메이션
    void endAnimation(Node *pSender, Ref* enemy);//스킬 애니메이션
    void calSkill(Ref *target, Ref *enemy,bool enemyTime, Ref *skill); //스킬 사용여부 계산
    void resultSkillData(Ref *target, Ref *enemy,bool enemyTime, Ref *skill); //스킬데이터 처리.
    bool checkMiss(float selfAgility, float enemyAgility, float enemyLevel); //회피 계산
    bool checkStopTurn(Ref *target); //정지 스킬 계산
    bool checkDebufTurn(Ref *target); //디버프 스킬 계산
    bool checkReflectTurn(Ref *enemy, int animationType); //반사 스킬 계산
    
    //적 Ai
    void enemyAi(Ref *target,Ref *enemy);
    void enemyFirstLevel(Ref *target,Ref *enemy);
    void enemyTwoLevel(Ref *target,Ref *enemy);
    void enemyThreeLevel(Ref *target,Ref *enemy);
    //Hp 애니메이션
    void endHpAnimation(Node *pSender, Ref* enemy);
    void createAnimation(Node *target, Ref *skill, bool enemyTime,  float delayTime=0.0f,bool isBuf = false); //스킬 애니메이션 생성 (이미지용)
    void removeAnimation(Node *target); //스킬 애니메이션 삭제(이미지용)
};

#endif /* defined(__ShapeMaster__Battle__) */
