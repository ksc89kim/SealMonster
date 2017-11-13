
//  Battle.cpp
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 19..
//
//

#include "Battle.h"
#include "BattleLayer.h"

Battle::Battle()
{
    
}
Battle::~Battle()
{
    if(_skillLevelCount)
        _skillLevelCount->release();
    if(_count)
        _count->release();
    if(_skillDamage)
        _skillDamage->release();
    if(_skillTurn)
        _skillTurn->release();
}

Battle* Battle::create(const std::function<void()> function)
{
    Battle * ret = new Battle();
    if (ret && ret->init())
    {
        ret->_skillLevelCount = ShapeValue::create("S", "T");
        ret->_count = ShapeValue::create("C", "T");
        ret->_skillDamage = ShapeValue::create("S", "D");
        ret->_skillTurn = ShapeValue::create("S", "N");
        ret->_func = function;
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
	return ret;
}
void Battle::initBattleData()
{
    _skillLevelCount->setShapeValue(0);
    _count->setShapeValue(0);
    _skillDamage->setShapeValue(0);
    _skillTurn->setShapeValue(0);
}

#pragma mark - Battle Data and Animation


bool Battle::doPushSkill(Ref *target, ShapeSkill *skill)
{
    ShapeCommon *self = (ShapeCommon *)target;
    if(skill->_skillLevel>=_skillLevelCount->getShapeValue())
    {
        ShapeSkill *skillData = ShapeSkill::create(skill);
        skillData->retain();
        self->_skillQueue.push(skillData);
        _skillLevelCount->setShapeValue(skill->_skillLevel);
        return true;
    }
    else
    {
        _skillLevelCount->setShapeValue(0);
        return false;
    }

}

void Battle::useSkill(Ref *target,Ref *enemy, bool enemyTime)
{
    ShapeCommon *self = (ShapeCommon *)target;
    ShapeCommon *enemyShape = (ShapeCommon *)enemy;
    ShapeObject *selfData = self->_shapeData;
    ShapeObject *enemyShapeData = enemyShape->_shapeData;
    
    if(enemyShapeData->_health->getShapeValue()<=0)
    {
        _func();
        while(!self->_skillQueue.empty())
        {
            self->_skillQueue.pop();
        }
    }
    else
    {
        if(!self->_skillQueue.empty())
        {

            float attributeDamage = calAttribute(self, enemy);
            float baseDamage = calBase(self,enemy);
            float diffLevelDamage = calLevel(self,enemy);
            ShapeSkill *skill = self->_skillQueue.front();
            
            self->_skillQueue.pop();
            
            if(skill->_skillLevel>_count->getShapeValue())
            {
                _count->setShapeValue(skill->_skillLevel);
                switch (skill->_skillType) {
                    case animationType::kAttack:
                        _skillDamage->setShapeValue(((selfData->_power->getShapeValue()+selfData->_plusPower->getShapeValue()-selfData->_debufPower->getShapeValue())*getAttackSkillPerCent(skill->_skillLevel)*baseDamage)*diffLevelDamage);
                        break;
                    case animationType::kAttributeAttack:
                        _skillDamage->setShapeValue((((selfData->_power->getShapeValue()+selfData->_plusPower->getShapeValue()-selfData->_debufPower->getShapeValue())*getAttackSkillPerCent(skill->_skillLevel)) *attributeDamage)*diffLevelDamage);
                        break;
                    case animationType::kDebufTurn:
                        _skillTurn->setShapeValue(getTurnSkillPerCent(skill->_skillLevel));
                        break;
                    case animationType::kReflect:
                        _skillTurn->setShapeValue(getTurnSkillPerCent(skill->_skillLevel));
                        break;
                    case animationType::kStopTurn:
                        _skillTurn->setShapeValue(getTurnSkillPerCent(skill->_skillLevel));
                        break;
                    default:
                        break;
                }
                calSkill(self, enemy,enemyTime,skill);
            }
            else if(skill->_skillLevel==_count->getShapeValue())
            {
                switch (skill->_skillType) {
                    case animationType::kAttack:
                        _skillDamage->addShapeValue(((((selfData->_power->getShapeValue()+selfData->_plusPower->getShapeValue()-selfData->_debufPower->getShapeValue())*getAttackSkillPerCent(skill->_skillLevel))*baseDamage)*diffLevelDamage) * 0.2f);
                        break;
                    case animationType::kAttributeAttack:
                        _skillDamage->addShapeValue(((((selfData->_power->getShapeValue()+selfData->_plusPower->getShapeValue()-selfData->_debufPower->getShapeValue())*getAttackSkillPerCent(skill->_skillLevel)) *attributeDamage)*diffLevelDamage)*0.2f);
                        break;
                    case animationType::kReflect:
                    case animationType::kStopTurn:
                        _skillTurn->addShapeValue(getTurnSkillPerCent(skill->_skillLevel)*0.2f);
                        break;
                    case animationType::kDebufTurn:
                        _skillTurn->addShapeValue(getTurnSkillPerCent(skill->_skillLevel)*1.0f);
                        break;
                    default:
                        break;
                }
                calSkill(self, enemy,enemyTime,skill);
            }
            skill->release();
        }
        else
        {
            initBattleData();
            if(!enemyTime)
            {
                if(enemyShapeData->_health->getShapeValue()>0)
                    enemyAi(self, enemy);
                else
                    _func();
            }
            else
            {
                _func();
            }
            
        }
    }
}
float Battle::calAttribute(Ref *target, cocos2d::Ref *enemy)
{
    ShapeF *myShapeF = dynamic_cast<ShapeF *>(target);
    ShapeW *myShapeW = dynamic_cast<ShapeW *>(target);
    ShapeT *myShapeT = dynamic_cast<ShapeT *>(target);
    ShapeI *myShapeI = dynamic_cast<ShapeI *>(target);
    ShapeZ *myShapeZ = dynamic_cast<ShapeZ *>(target);
    
    ShapeF *enemyShapeF = dynamic_cast<ShapeF *>(enemy);
    ShapeW *enemyShapeW = dynamic_cast<ShapeW *>(enemy);
    ShapeT *enemyShapeT = dynamic_cast<ShapeT *>(enemy);
    ShapeI *enemyShapeI = dynamic_cast<ShapeI *>(enemy);
    ShapeZ *enemyShapeZ = dynamic_cast<ShapeZ *>(enemy);
    
    if(myShapeF!=nullptr) //fire
    {
        if(enemyShapeW!=nullptr)
        {
            return 0.5f;
        }
        else if(enemyShapeT!=nullptr)
        {
            return 1.8f;
        }
    }
    else if(myShapeW!=nullptr) //water
    {
        if(enemyShapeF!=nullptr)
        {
            return 1.8f;
        }
        else if(enemyShapeT!=nullptr)
        {
            return 0.5f;
        }
    }
    else if(myShapeT!=nullptr) //tree
    {
        if(enemyShapeF!=nullptr)
        {
            return 0.5f;
        }
        else if(enemyShapeW!=nullptr)
        {
            return 1.8f;
        }
    }
    else if(myShapeI!=nullptr) //
    {
        if(enemyShapeF!=nullptr)
        {
            return 1.8f;
        }
        else if(enemyShapeW!=nullptr)
        {
            return 1.8f;
        }
        else if(enemyShapeT!=nullptr)
        {
            return 1.8f;
        }
        else if(enemyShapeZ!=nullptr)
        {
            return 0.5f;
        }
    }
    else if(myShapeZ!=nullptr) //
    {
        if(enemyShapeI!=nullptr)
        {
            return 1.8f;
        }
    }
    return 1.0f;
}
float Battle::calBase(Ref *target, Ref *enemy)
{
    ShapeF *myShapeF = dynamic_cast<ShapeF *>(target);
    ShapeW *myShapeW = dynamic_cast<ShapeW *>(target);
    ShapeT *myShapeT = dynamic_cast<ShapeT *>(target);
    ShapeI *myShapeI = dynamic_cast<ShapeI *>(target);
    ShapeZ *myShapeZ = dynamic_cast<ShapeZ *>(target);
    
    ShapeF *enemyShapeF = dynamic_cast<ShapeF *>(enemy);
    ShapeW *enemyShapeW = dynamic_cast<ShapeW *>(enemy);
    ShapeT *enemyShapeT = dynamic_cast<ShapeT *>(enemy);
    ShapeI *enemyShapeI = dynamic_cast<ShapeI *>(enemy);
    ShapeZ *enemyShapeZ = dynamic_cast<ShapeZ *>(enemy);
    
    if(myShapeF!=nullptr) //fire
    {
        if(enemyShapeW!=nullptr)
        {
            return 0.8f;
        }
        else if(enemyShapeT!=nullptr)
        {
            return 1.3f;
        }
    }
    else if(myShapeW!=nullptr) //water
    {
        if(enemyShapeF!=nullptr)
        {
            return 0.8f;
        }
        else if(enemyShapeT!=nullptr)
        {
            return 1.3f;
        }
    }
    else if(myShapeT!=nullptr) //tree
    {
        if(enemyShapeF!=nullptr)
        {
            return 0.8f;
        }
        else if(enemyShapeW!=nullptr)
        {
            return 1.3f;
        }
    }
    else if(myShapeI!=nullptr) //
    {
        if(enemyShapeF!=nullptr)
        {
            return 1.3f;
        }
        else if(enemyShapeW!=nullptr)
        {
            return 1.3f;
        }
        else if(enemyShapeT!=nullptr)
        {
            return 1.3f;
        }
        else if(enemyShapeZ!=nullptr)
        {
            return 0.8f;
        }
    }
    else if(myShapeZ!=nullptr) //
    {
        if(enemyShapeI!=nullptr)
        {
            return 1.3f;
        }
    }
    return 1.0f;
}
float Battle::calLevel(Ref *target, Ref *enemy)
{
    ShapeCommon *self = (ShapeCommon *)target;
    ShapeCommon *enemyShape = (ShapeCommon *)enemy;
    ShapeObject *selfData = self->_shapeData;
    ShapeObject *enemyShapeData = enemyShape->_shapeData;
    float diffLevel = (int)enemyShapeData->_level->getShapeValue() - (int)selfData->_level->getShapeValue();
    diffLevel = (diffLevel>0)?diffLevel:0;
    float damage = 1.0f;
    if(diffLevel>=9)
    {
        damage = 0.7f;
    }
    else if(diffLevel>3&&diffLevel<9)
    {
        damage = 0.8f;
    }
    else if(diffLevel>0&&diffLevel<4)
    {
        damage = 0.9f;
    }
    return damage;
}
float Battle::getAttackSkillPerCent(int level)
{
    float percent = 1.0;
    switch (level) {
        case 3:
            percent=1.5f;
            break;
        case 4:
            percent=2.5f;
        default:
            break;
    }
    if(level>4)
    {
        for(int i=1;i<=level;i++)
        {
            percent += 0.5f;
        }
    }
    return percent;
}
float Battle::getTurnSkillPerCent(int level)
{
    float percent = 0;
    for(int i=1;i<level;i++)
    {
        percent += 1.0f;
    }
    return percent;
}

void Battle::createAnimation(Node *target, Ref *skill,bool enemyTime, float delayTime,bool isBuf)
{
    log("create Animation!!@!@!");
    ShapeSkill *skillData = (ShapeSkill *)skill;

    if(skillData->_animationFileName.compare(""))
    {
        log("make Animation!!@!@! %s",skillData->_animationFileName.c_str());

        float aniTime=0.5f;
        char frameName[128];
        Sprite *animationSprite = Sprite::create();
        animationSprite->setAnchorPoint(Vec2(0.5f,0.0f));
        //animationSprite->setScale(target->getScale());
        
        if(enemyTime)
            animationSprite->setFlippedX(true);
        else
            animationSprite->setFlippedX(false);
        
        BattleLayer *parent = (BattleLayer *)this->getParent();
        animationSprite->setScale(target->getScale());
        animationSprite->setPosition(target->getPosition());
        parent->addChild(animationSprite,50000);
        
        Animation *animation = Animation::create();
        animation->setDelayPerUnit(aniTime/3);
        for(int i = 1; i <= 5; ++i)
        {
            memset(frameName, 0, 128);
            sprintf(frameName, ("%s%d.png"), skillData->_animationFileName.c_str(),i);
            animation->addSpriteFrameWithFile(frameName);
        }

        animation->addSpriteFrameWithFile("1pixel.png");
        Animate *animate = Animate::create(animation);
        if(delayTime>0)
        {
            animationSprite->runAction(Sequence::create(DelayTime::create(delayTime),animate,CallFuncN::create(CC_CALLBACK_1(Battle::removeAnimation, this)),NULL));
            if(!isBuf)
                ((ShapeCommon *)target)->damageAnimation(delayTime);
        }
        else
        {
            animationSprite->runAction(Sequence::create(animate,CallFuncN::create(CC_CALLBACK_1(Battle::removeAnimation, this)),NULL));
            if(!isBuf)
               ((ShapeCommon *)target)->damageAnimation();
        }
        
    }
    
}
void Battle::removeAnimation(Node *target)
{
    target->removeFromParent();
}
void Battle::startAnimation(Ref *target, Ref *enemy, bool enemyTime,Ref *skill, bool isEnemyAnimation)
{
    ShapeSkill *skillData = (ShapeSkill *)skill;
    float delayTime = 0;
    switch (skillData->_skillType) {
        case animationType::kMiss:
        {
            ((ShapeCommon *)enemy)->missAnimation();
            break;
        }
        case animationType::kAttack:
        {
            log("attack animation!");
            createAnimation((Node *)enemy,skill,enemyTime);
            break;
        }
        case animationType::kAttributeAttack:
        {
            log("attribute attack animation!");
            createAnimation((Node *)enemy,skill,enemyTime);
            break;
        }
        case animationType::kDebufTurn:
        {
            log("debuf animation!");
            createAnimation((Node *)enemy,skill,enemyTime);
            ((ShapeCommon *)enemy)->debufAnimation(0.5f);
            break;
        }
        case animationType::kReflect:
        {
            if (isEnemyAnimation) {
                log("enemy reflect animation!");
                delayTime = 0.1f;
                createAnimation((Node *)target,skill,false,delayTime);
                ShapeCommon *enemyShape = (ShapeCommon *)enemy;
                ShapeSkill *reflectSkill = ShapeSkill::create(enemyShape->_shapeData->_reflectSkill);
                createAnimation((Node *)enemy,reflectSkill,false,0.0f,true);
            }
            else
            {
                log("reflect animation!");
                createAnimation((Node *)target,skill,false,0.0f,true);
            }
            break;
        }
        case animationType::kStopTurn:
        {
            log("stop animation!");
            if (isEnemyAnimation) {
                ((ShapeCommon *)target)->stopAnimation();
            }
            else
            {
                createAnimation((Node *)enemy,skill,enemyTime);
            }
            break;
        }
        default:
        break;
    }
    
    this->setUserData((void *)enemyTime);
    this->setUserObject(target);
    this->runAction(Sequence::create(DelayTime::create(0.6f+delayTime),CallFuncN::create(CC_CALLBACK_1(Battle::endAnimation, this, enemy)), nullptr));
    
}
void Battle::endAnimation(Node *pSender, Ref* enemy)
{
    bool enemyTime = pSender->getUserData();
    Ref *target = pSender->getUserObject();

    BattleLayer *parent = (BattleLayer *)this->getParent();
    ShapeCommon *shapeTarget = (ShapeCommon *)target;
    ShapeCommon *enemyShape = (ShapeCommon *)enemy;
    if(enemyTime)
    {
        
        parent->_playerHp->runAction(ProgressTo::create(0.2f, enemyShape->_shapeData->_health->getShapeValue()/(enemyShape->_shapeData->_maxHealth->getShapeValue()+ enemyShape->_shapeData->_plusMaxHealth->getShapeValue())*100));
        parent->_enemyHp->runAction(ProgressTo::create(0.2f, shapeTarget->_shapeData->_health->getShapeValue()/(shapeTarget->_shapeData->_maxHealth->getShapeValue()+shapeTarget->_shapeData->_plusMaxHealth->getShapeValue())*100));
    }
    else
    {
        parent->_playerHp->runAction(ProgressTo::create(0.2f, shapeTarget->_shapeData->_health->getShapeValue()/(shapeTarget->_shapeData->_maxHealth->getShapeValue()+shapeTarget->_shapeData->_plusMaxHealth->getShapeValue())*100));
        parent->_enemyHp->runAction(ProgressTo::create(0.2f, enemyShape->_shapeData->_health->getShapeValue()/(enemyShape->_shapeData->_maxHealth->getShapeValue()+ enemyShape->_shapeData->_plusMaxHealth->getShapeValue())*100));
    }
    
    this->setUserData((void *)enemyTime);
    this->setUserObject(target);
    this->runAction(Sequence::create(DelayTime::create(0.2f),CallFuncN::create(CC_CALLBACK_1(Battle::endHpAnimation, this, enemy)), nullptr));
}
void Battle::endHpAnimation(Node *pSender, Ref* enemy)
{
    bool enemyTime = pSender->getUserData();
    Ref *target = pSender->getUserObject();
    useSkill(target, enemy, enemyTime);
}
void Battle::calSkill(cocos2d::Ref *target, cocos2d::Ref *enemy,bool enemyTime, Ref *skill)
{
    ShapeCommon *self = (ShapeCommon *)target;
    if(!self->_skillQueue.empty())
    {
        ShapeSkill *nextSkill = self->_skillQueue.front();
        if(nextSkill->_skillLevel>_count->getShapeValue()){
            resultSkillData(self,enemy,enemyTime,skill);
        }
        else
        {
            useSkill(self, enemy,enemyTime);
        }
    }
    else
    {
        resultSkillData(self,enemy,enemyTime,skill);
    }
}
void Battle::resultSkillData(cocos2d::Ref *target, cocos2d::Ref *enemy,bool enemyTime, Ref *skill)
{
    
    ShapeCommon *self = (ShapeCommon *)target;
    ShapeObject *selfData = self->_shapeData;
    ShapeCommon *enemyShape = (ShapeCommon *)enemy;
    ShapeObject *enemyShapeData = enemyShape->_shapeData;
    ShapeSkill *skillData = (ShapeSkill *)skill;
    
    if(checkDebufTurn(self))
    {
        selfData->_debufTurn->minusShapeValue(1);
    }
    else
    {
        self->stopDebufAnimation();
        selfData->_debufPower->setShapeValue(0);
        selfData->_debufAgility->setShapeValue(0);
    }
    if(checkMiss(selfData->_agility->getShapeValue()+selfData->_plusAgility->getShapeValue()-
                 selfData->_debufAgility->getShapeValue(), enemyShapeData->_agility->getShapeValue(), enemyShapeData->_level->getShapeValue()))
    {
        log("Miss Attack");
        skillData->_skillType = animationType::kMiss;
        startAnimation(self, enemyShape, enemyTime,skill);
    }
    else if(checkStopTurn(self))
    {
        log("Stop Turn");
        selfData->_stopTurn->minusShapeValue(1);
        skillData->_skillType = animationType::kStopTurn;
        startAnimation(self,enemyShape,enemyTime,skill,true);

    }
    else if(checkReflectTurn(enemy, skillData->_skillType))
    {
        log("Reflect Turn");
        enemyShapeData->_reflectCount->minusShapeValue(1);
        self->logStatus();
        log("self -skill Damage = %f", _skillDamage->getShapeValue());
        selfData->minusHelath(_skillDamage->getShapeValue());
        self->logStatus();
        skillData->_skillType = animationType::kReflect;
        startAnimation(self,enemyShape,enemyTime,skill,true);
    }
    else
    {
        switch (skillData->_skillType) {
            case animationType::kAttack:
            case animationType::kAttributeAttack:
            {
                log("skill Damage = %f", _skillDamage->getShapeValue());
                enemyShapeData->minusHelath(_skillDamage->getShapeValue());
            }
                break;
            case animationType::kDebufTurn:
            {
                if(enemyShapeData->_power>enemyShapeData->_agility)
                {
                    enemyShapeData->_debufPower->setShapeValue(enemyShapeData->_power->getShapeValue()*0.4f);
                }
                else
                {
                    enemyShapeData->_debufAgility->setShapeValue(enemyShapeData->_agility->getShapeValue()*0.4f);
                }
                enemyShapeData->_debufTurn->setShapeValue(_skillTurn->getShapeValue());
                break;
            }
            case animationType::kReflect:
            {
                selfData->_reflectSkill->changeSkillData(skillData);
                selfData->_reflectCount->setShapeValue(_skillTurn->getShapeValue());
                break;
            }
            case animationType::kStopTurn:
            {
                enemyShapeData->_stopSkill->changeSkillData(skillData);
                enemyShapeData->_stopTurn->setShapeValue(_skillTurn->getShapeValue());
                break;
            }
            default:
                break;
        }
        startAnimation(self, enemyShape, enemyTime,skill);
    }

}

bool Battle::checkMiss(float selfAgility, float enemyAgility, float enemyLevel)
{
    
    int rand = arc4random() % 5;
    switch (rand) {
        case 0:
        case 1:
        case 2:
        {
           float temp  = enemyAgility- selfAgility;
           if(temp>0)
           {
               int cal = ((5 * enemyLevel)*3);
               rand = arc4random() % cal;
               if(rand<=temp)
                   return true;
           }
            return false;
        }
            break;
        default:
            break;
    }
    return false;
}
bool Battle::checkStopTurn(cocos2d::Ref *target)
{
    ShapeCommon *self = (ShapeCommon *)target;
    ShapeObject *selfData = self->_shapeData;
    if(selfData->_stopTurn->getShapeValue()>0)
    {
        return true;
    }
    return false;
}
bool Battle::checkDebufTurn(cocos2d::Ref *target)
{
    ShapeCommon *self = (ShapeCommon *)target;
    ShapeObject *selfData = self->_shapeData;
    if(selfData->_debufTurn->getShapeValue()>0)
    {
        return true;
    }
    return false;
}
bool Battle::checkReflectTurn(cocos2d::Ref *enemy, int animationType)
{
    ShapeCommon *enemyShape = (ShapeCommon *)enemy;
    ShapeObject *enemyShapeData = enemyShape->_shapeData;
    if(enemyShapeData->_reflectCount->getShapeValue()>0 && animationType==animationType::kAttack)
    {
        return true;
    }
    return false;
}


void Battle::enemyAi(cocos2d::Ref *target, cocos2d::Ref *enemy)
{
    log("--------------enemyTime-------------");
    ShapeCommon *enemyShape = (ShapeCommon *)enemy;
    int percent = enemyShape->_shapeData->_health->getShapeValue()/(enemyShape->_shapeData->_maxHealth->getShapeValue()+ enemyShape->_shapeData->_plusMaxHealth->getShapeValue())*100;
    BattleLayer *parent = (BattleLayer *)this->getParent();
    switch (parent->_battleType) {
        case battleType::kQuestChracterType:
        case battleType::kCharacterType:
        {
            if(percent>50)
            {
                enemyTwoLevel(target, enemy);
            }
            else
            {
                enemyThreeLevel(target, enemy);
            }
            break;
        }
        default:
        {
            if(percent>60)
            {
                enemyFirstLevel(target, enemy);
            }
            else
            {
                enemyTwoLevel(target, enemy);
            }
            break;
        }
    }
    useSkill(enemy, target, true);
}

void Battle::enemyFirstLevel(Ref *target,Ref *enemy)
{
    ShapeCommon *enemyShape = (ShapeCommon *)enemy;
    
    if(enemyShape->_shapeData->_level->getShapeValue()>=SKILL_FOUR)
    {
        if(arc4random()%3==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill4);
            doPushSkill(enemy, enemyShape->_shapeData->_skill4);
        }
        else if(arc4random()%5==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
        }
        else
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill4);
            doPushSkill(enemy, enemyShape->_shapeData->_skill4);
        }
    }
    else if(enemyShape->_shapeData->_level->getShapeValue()>=SKILL_THREE)
    {
        if(arc4random()%3==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
        }
        else if(arc4random()%5==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill2);
        }
        else
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
        }
        
    }
    else if(enemyShape->_shapeData->_level->getShapeValue()>=SKILL_TWO)
    {
        if(arc4random()%3==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
        }
        else
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill2);
        }
    }
    else if(enemyShape->_shapeData->_level->getShapeValue()>=SKILL_FIRST)
    {
        if(arc4random()%3==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
        }
        else
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
        }
    }
    else
    {
        doPushSkill(enemy, enemyShape->_shapeData->_skill1);
        doPushSkill(enemy, enemyShape->_shapeData->_skill1);
    }
}
void Battle::enemyTwoLevel(Ref *target,Ref *enemy)
{
    ShapeCommon *enemyShape = (ShapeCommon *)enemy;
    if(enemyShape->_shapeData->_level->getShapeValue()>=SKILL_FOUR)
    {
        if(arc4random()%3==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill2);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
        }
        else if(arc4random()%5==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
            doPushSkill(enemy, enemyShape->_shapeData->_skill4);
        }
        else
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill2);
            doPushSkill(enemy, enemyShape->_shapeData->_skill4);
        }
    }
    else if(enemyShape->_shapeData->_level->getShapeValue()>=SKILL_THREE)
    {
        if(arc4random()%3==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
        }
        else if(arc4random()%5==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill2);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
        }
        else
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
        }
        
    }
    else if(enemyShape->_shapeData->_level->getShapeValue()>=SKILL_TWO)
    {
        if(arc4random()%3==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill2);
        }
        else if(arc4random()%5==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill2);
        }
        else
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
        }
    }
    else if(enemyShape->_shapeData->_level->getShapeValue()>=SKILL_FIRST)
    {
        if(arc4random()%3==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
        }
        else
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
        }
    }
    else
    {
        doPushSkill(enemy, enemyShape->_shapeData->_skill1);
        doPushSkill(enemy, enemyShape->_shapeData->_skill1);
        doPushSkill(enemy, enemyShape->_shapeData->_skill1);
    }
}
void Battle::enemyThreeLevel(Ref *target,Ref *enemy)
{
    ShapeCommon *enemyShape = (ShapeCommon *)enemy;
    if(enemyShape->_shapeData->_level->getShapeValue()>=SKILL_FOUR)
    {
        if(arc4random()%3==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill2);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
            doPushSkill(enemy, enemyShape->_shapeData->_skill4);
        }
        else if(arc4random()%5==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill2);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
            doPushSkill(enemy, enemyShape->_shapeData->_skill4);
            doPushSkill(enemy, enemyShape->_shapeData->_skill4);
        }
        else
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
            doPushSkill(enemy, enemyShape->_shapeData->_skill4);
            doPushSkill(enemy, enemyShape->_shapeData->_skill4);
        }
    }
    else if(enemyShape->_shapeData->_level->getShapeValue()>=SKILL_THREE)
    {
        if(arc4random()%3==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill2);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
        }
        else if(arc4random()%5==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
        }
        else
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
            doPushSkill(enemy, enemyShape->_shapeData->_skill3);
        }
        
    }
    else if(enemyShape->_shapeData->_level->getShapeValue()>=SKILL_TWO)
    {
        if(arc4random()%3==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill2);
        }
        else if(arc4random()%5==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill2);
        }
        else
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill2);
        }
    }
    else if(enemyShape->_shapeData->_level->getShapeValue()>=SKILL_FIRST)
    {
        if(arc4random()%3==1)
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
        }
        else
        {
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
            doPushSkill(enemy, enemyShape->_shapeData->_skill1);
        }
    }
    else
    {
        doPushSkill(enemy, enemyShape->_shapeData->_skill1);
        doPushSkill(enemy, enemyShape->_shapeData->_skill1);
        doPushSkill(enemy, enemyShape->_shapeData->_skill1);
        doPushSkill(enemy, enemyShape->_shapeData->_skill1);
    }
}
