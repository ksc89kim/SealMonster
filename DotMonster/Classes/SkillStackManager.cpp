//
//  SkillStackManager.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 10. 20..
//
//

#include "SkillStackManager.h"
#include "BattleLayer.h"


SkillStackManager::SkillStackManager()
{
    _stackImages = new Vector<StackObject *>();
}

SkillStackManager::~SkillStackManager()
{
    if(_stackImages){
        delete _stackImages;
    }
}

SkillStackManager * SkillStackManager::create(const Color4B& color)
{
    SkillStackManager * layer = new SkillStackManager();
    if(layer && layer->initWithColor(color))
    {
        layer->_dt = 0;
        layer->setStackImage();
        layer->autorelease();
        layer->ignoreAnchorPointForPosition(false);
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void SkillStackManager::setStackImage()
{
    //테스트용...
    ShapeSkill *skillData = ShapeSkill::create();
    StackObject *so = StackObject::create(skillData);
    
    
    //move object
    _moveStackCharacter = MoveObject::create("moveStack.png");
    this->addChild(_moveStackCharacter);
    
    
    auto stackTimeBg = Scale9Sprite::create("stackTime2.png");
    stackTimeBg->setContentSize(this->getContentSize());
    _stackTimer = ProgressTimer::create((Sprite *)stackTimeBg->getSprite());
    _stackTimer->setType(ProgressTimer::Type::BAR);
    _stackTimer->setMidpoint(Vec2(0,0));
    _stackTimer->setBarChangeRate(Vec2(1, 0));
    _stackTimer->setPercentage(100.0f);
    this->addChild(_stackTimer);
    
    //stackObject
    
    float padding = 10.0f;
    int x = so->getContentSize().width+padding/2;
    int clearance = _moveStackCharacter->getContentSize().width;
    int spriteSize = 0;

    for(int i=0; i<SKILL_BATCH_COUNT; i++)
    {
        ShapeSkill *skillData = ShapeSkill::create();
        StackObject *so = StackObject::create(skillData);
        so->setVisible(false);
        spriteSize = so->getContentSize().width;
        this->setContentSize(Size(x,so->getContentSize().height+padding));
        so->setPosition(Vec2(x - so->getContentSize().width/2, this->getContentSize().height/2));
        x += so->getContentSize().width + clearance;
        this->addChild(so);
        _stackImages->pushBack(so);
    }
    
    this->setContentSize(Size(this->getContentSize().width+padding,this->getContentSize().height));
    
    auto bg = Scale9Sprite::create("stackBorder.png");
    bg->setContentSize(this->getContentSize());
    bg->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(bg);
    
    _stackTimer->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    
    Sprite *skill1 = Sprite::create("stackSkill1.png");
    skill1->setScale(0.5f);
    skill1->setPosition(Vec2(-90, -8));
    this->addChild(skill1);
    
    _skill1 = Label::createWithTTF("0", CommonUtils::getFontName(), FONT_SIZE);
    _skill1->setPosition(Vec2(skill1->getPositionX()+
                              (skill1->getContentSize().width*skill1->getScale())+10,skill1->getPositionY()));
    _skill1->setAnchorPoint(Vec2(0,0.5f));
    _skill1->setTag(0);
    _skill1->setColor(Color3B::BLACK);
    this->addChild(_skill1);
    
    Sprite *skill2 = Sprite::create("stackSkill2.png");
    skill2->setScale(0.5f);
    skill2->setPosition(Vec2(-90, 27));
    this->addChild(skill2);
    
    _skill2 = Label::createWithTTF("0", CommonUtils::getFontName(), FONT_SIZE);
    _skill2->setPosition(Vec2(skill2->getPositionX()+
                              (skill2->getContentSize().width*skill2->getScale())+10,skill2->getPositionY()));
    _skill2->setAnchorPoint(Vec2(0,0.5f));
    _skill2->setTag(0);
    _skill2->setColor(Color3B::BLACK);
    this->addChild(_skill2);
    
    Sprite *skill3 = Sprite::create("stackSkill3.png");
    skill3->setScale(0.5f);
    skill3->setPosition(Vec2(-90, 62));
    this->addChild(skill3);
    
    _skill3 = Label::createWithTTF("0", CommonUtils::getFontName(), FONT_SIZE);
    _skill3->setPosition(Vec2(skill3->getPositionX()+
                              (skill3->getContentSize().width*skill3->getScale())+10,skill3->getPositionY()));
    _skill3->setAnchorPoint(Vec2(0,0.5f));
    _skill3->setTag(0);
    _skill3->setColor(Color3B::BLACK);
    this->addChild(_skill3);
    
    Sprite *skill4 = Sprite::create("stackSkill4.png");
    skill4->setScale(0.5f);
    skill4->setPosition(Vec2(-90, 97));
    this->addChild(skill4);
    
    _skill4 = Label::createWithTTF("0", CommonUtils::getFontName(), FONT_SIZE);
    _skill4->setPosition(Vec2(skill4->getPositionX()+
                              (skill4->getContentSize().width*skill4->getScale())+10,skill4->getPositionY()));
    _skill4->setAnchorPoint(Vec2(0,0.5f));
    _skill4->setColor(Color3B::BLACK);
    _skill4->setTag(0);
    this->addChild(_skill4);
    
    Sprite *info = Sprite::create("stackInfo.png");
    info->setPosition(Vec2(-140,this->getContentSize().height/2+10));
    this->addChild(info);
    
    
    //button
    _button = CommonUtils::createLabelBorder("TOUCH",Size(120,120));
    _button->setPosition(Vec2(this->getContentSize().width+_button->getContentSize().width/2+20, this->getContentSize().height/2+10));
    this->addChild(_button);
    
    //touch
    
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    auto positionListener = EventListenerTouchOneByOne::create();
    positionListener->setSwallowTouches(true);
    positionListener->onTouchBegan = CC_CALLBACK_2(SkillStackManager::onTouchBegan, this);
    dispatcher->addEventListenerWithSceneGraphPriority(positionListener, this);
    
}

void SkillStackManager::start()
{
    _stackTimer->setPercentage(100.0f);
    setVisible(true);
    _moveStackCharacter->setMoveRange(this);
    batchStack(0);
    _moveStackCharacter->move();
    _stackTimer->runAction(ProgressTo::create(4.0f, 0.0f));

}
void SkillStackManager::end()
{
    resetSkill();
    setVisible(false);
    _moveStackCharacter->stopAllActions();
}

void SkillStackManager::collisionCheck(Ref *ref)
{

    bool checkCollision = false;
    for(int i=0;i<_stackImages->size();i++)
    {
        StackObject *object =  _stackImages->at(i);
        
        if(object->isVisible())
        {
           
            Rect stackObjectRect = object->getBoundingBox();
            Rect moveCharacterRect = _moveStackCharacter->getBoundingBox();
            if(stackObjectRect.intersectsRect(moveCharacterRect))
            {
                BattleLayer *parent = (BattleLayer *) this->getParent()->getParent();
                if(!parent->_battleObject->doPushSkill(parent->_playerMonSter, object->_skillData))
                {
                    BattleLayer *parent = (BattleLayer *) this->getParent()->getParent();
                    parent->endStackGame();
                }
                addSkill(object->_skillData->_skillLevel);
                object->setVisible(false);
                randOneBatch(object, i);
                checkCollision = true;
            }

        }
    }
    
    if(!checkCollision)
    {
        BattleLayer *parent = (BattleLayer *) this->getParent()->getParent();
        parent->endStackGame();
    }

}
void SkillStackManager::randOneBatch(StackObject *object,int index)
{
    
    int i=0;
    int probability = 5;
    while(i==0){
        for(int j=0;j<_stackImages->size();j++)
        {
            StackObject *stackImage = _stackImages->at(j);
            if(!stackImage->isVisible() && index!=j)
            {
                if(arc4random()%probability==1)
                {
                    stackImage->changeSkillData(object->_skillData);
                    stackImage->setVisible(true);
                    i++;
                    break;
                }
            }
        }
    }
}

void SkillStackManager::batchStack(float dt)
{
    int batchPosition[SKILL_BATCH_COUNT] = {0,0,0,0,0,0,0,0};
    BattleLayer *parent = (BattleLayer *) this->getParent()->getParent();
    
    if(parent->_playerMonSter->_shapeData->_level->getShapeValue()>=SKILL_FOUR)
    {
        int temp[SKILL_MAX_BATCH_COUNT][SKILL_BATCH_COUNT]= {{1,3,1,0,2,0,2,4},{2,1,0,1,3,0,4,1},{4,0,1,0,2,3,0,1},{1,0,2,0,4,3,0,1},{1,3,0,1,2,0,4,2},
            {2,3,0,0,4,0,1,1},{0,1,2,0,4,0,3,1},{3,0,1,2,1,0,4,0},{1,4,0,2,0,3,2,1},{2,4,1,3,0,0,1,1},
            {4,0,1,0,2,0,1,3},{3,1,0,0,2,0,4,1},{2,4,0,1,0,3,0,1},{3,0,4,1,0,0,1,2},{2,0,1,4,1,0,0,3},
            {2,0,0,0,1,3,1,4},{2,4,0,0,0,1,1,3},{1,2,0,0,3,0,4,1},{2,3,1,0,4,1,0,2},{1,0,2,0,4,0,3,1},
            {1,0,2,0,0,1,3,4},{3,1,0,0,2,0,1,4},{1,0,1,2,4,0,3,0},{1,2,4,0,1,0,2,3},{3,1,0,4,0,1,0,2},
            {4,2,1,0,1,3,2,0},{1,4,1,3,0,1,0,2},{3,2,1,2,0,4,1,0},{4,2,1,0,3,1,0,2},{2,1,0,3,0,1,0,4}};
        int index = arc4random()%SKILL_MAX_BATCH_COUNT;
        for(int i=0;i<SKILL_BATCH_COUNT;i++)
        {
            batchPosition[i] = temp[index][i];
        }
    }
    else if(parent->_playerMonSter->_shapeData->_level->getShapeValue()>=SKILL_THREE)
    {
        int temp[SKILL_MAX_BATCH_COUNT][SKILL_BATCH_COUNT]= {{1,3,1,0,2,0,0,1,},{2,1,0,1,0,0,2,3},{2,0,1,0,1,3,0,2},{1,2,0,0,0,3,0,1},{1,3,0,0,2,0,0,1},
            {2,3,0,0,0,0,1,1},{0,1,2,0,0,3,0,1},{3,0,1,0,1,0,2,0},{1,2,0,0,0,3,0,1},{0,0,1,2,0,0,3,1},
            {3,0,1,0,2,0,0,1},{3,1,0,0,0,1,0,2},{2,0,0,1,0,1,3,0},{3,0,0,1,0,0,1,2},{2,2,0,3,1,0,0,1},
            {2,0,0,0,1,3,1,2},{2,1,0,0,0,1,2,3},{2,2,0,0,3,0,1,1},{0,3,1,0,2,1,0,2},{2,0,2,0,1,0,3,1},
            {1,3,2,0,0,0,1,2},{3,1,2,0,2,1,0,0},{3,0,1,2,0,1,1,0},{1,3,0,0,1,0,2,1},{3,0,1,0,0,1,0,2},
            {2,0,1,0,1,3,2,0},{1,0,1,3,0,1,0,2},{1,2,1,2,0,0,1,3},{0,2,1,0,3,1,0,2},{2,1,0,3,0,1,0,0}};
        int index = arc4random()%SKILL_MAX_BATCH_COUNT;
        for(int i=0;i<SKILL_BATCH_COUNT;i++)
        {
            batchPosition[i] = temp[index][i];
        }
    }
    else if(parent->_playerMonSter->_shapeData->_level->getShapeValue()>=SKILL_TWO)
    {
        int temp[SKILL_MAX_BATCH_COUNT][SKILL_BATCH_COUNT]= {{1,0,1,0,2,0,0,0},{2,1,0,1,0,2,0,0},{0,0,1,0,1,0,0,2},{1,0,0,2,0,1,0,0},{1,0,0,0,2,0,0,1},
            {2,0,1,0,0,0,1,0},{0,1,2,0,0,0,0,1},{2,0,1,0,1,0,2,0},{1,0,0,0,2,0,1,1},{2,0,1,2,0,0,0,1},
            {2,0,1,0,2,0,0,1},{0,1,0,0,0,0,1,2},{2,0,0,1,0,1,0,0},{0,1,0,1,0,0,0,2},{2,0,0,0,1,1,0,0},
            {2,0,0,0,1,0,1,0},{2,0,1,0,0,1,0,0},{0,2,0,0,1,0,0,1},{0,0,1,0,0,1,0,2},{0,0,2,0,1,0,0,1},
            {1,0,2,0,0,0,1,0},{0,1,0,0,2,0,0,1},{1,0,1,2,0,0,1,0},{0,0,0,0,1,0,2,1},{1,0,0,0,0,1,0,2},
            {0,0,1,0,1,0,2,0},{1,0,1,0,0,1,0,2},{1,2,1,2,0,0,1,0},{0,2,1,0,0,1,0,2},{2,1,0,0,0,1,0,1}};
        int index = arc4random()%SKILL_MAX_BATCH_COUNT;
        for(int i=0;i<SKILL_BATCH_COUNT;i++)
        {
            batchPosition[i] = temp[index][i];
        }
    }
    else if(parent->_playerMonSter->_shapeData->_level->getShapeValue()>=SKILL_FIRST)
    {
        int temp[SKILL_MAX_BATCH_COUNT][SKILL_BATCH_COUNT]= {{1,0,1,0,0,0,0,0},{0,1,0,1,0,0,0,0},{0,0,1,0,1,0,0,0},{1,0,0,0,0,1,0,0},{1,0,0,0,0,1,0,0},
            {0,1,0,0,0,0,1,0},{0,1,0,0,0,0,0,1},{0,0,1,0,1,0,0,0},{1,0,0,0,0,0,0,1},{0,0,1,0,0,0,0,1},
        {0,0,1,0,0,1,0,0},{0,1,0,0,0,0,1,0},{0,0,0,1,0,1,0,0},{0,0,0,1,0,0,0,1},{0,0,0,0,1,1,0,0},
        {0,0,1,0,1,0,1,0},{0,0,1,0,0,1,0,0},{0,0,0,1,0,1,0,1},{0,0,1,0,0,1,0,0},{0,0,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0},{0,1,0,0,0,0,0,1},{0,0,1,0,0,0,1,0},{0,0,0,0,1,0,0,1},{0,1,0,0,0,0,0,1},
        {0,0,1,0,1,0,1,0},{1,0,1,0,0,1,0,0},{1,0,1,0,0,0,1,0},{0,0,1,0,0,1,0,0},{0,1,0,0,0,1,1,0}};
        int index = arc4random()%SKILL_MAX_BATCH_COUNT;
        for(int i=0;i<SKILL_BATCH_COUNT;i++)
        {
            batchPosition[i] = temp[index][i];
        }
    }
    
  
    

  
    for (int i=0; i<_stackImages->size(); i++) {
        StackObject *stackImage = _stackImages->at(i);
        if(batchPosition[i]>0)
        {
            switch (batchPosition[i]) {
                case 1:
                    stackImage->changeSkillData(parent->_playerMonSter->_shapeData->_skill1);
                    break;
                case 2:
                    stackImage->changeSkillData(parent->_playerMonSter->_shapeData->_skill2);
                    break;
                case 3:
                    stackImage->changeSkillData(parent->_playerMonSter->_shapeData->_skill3);
                    break;
                case 4:
                    stackImage->changeSkillData(parent->_playerMonSter->_shapeData->_skill4);
                    break;
                default:
                    break;
            }
            stackImage->setVisible(true);
        }
        else
        {
            stackImage->setVisible(false);
        }
        
    }

}
void SkillStackManager::levelGap(float gap)
{
    _moveStackCharacter->_gap = gap;
}
void SkillStackManager::addSkill(int level)
{
    switch(level)
    {
        case 1:
            _skill1->setString(__String::createWithFormat("%d", _skill1->getTag()+1)->getCString());
            _skill1->setTag(_skill1->getTag()+1);
            break;
        case 2:
            _skill2->setString(__String::createWithFormat("%d", _skill2->getTag()+1)->getCString());
            _skill2->setTag(_skill2->getTag()+1);
            break;
        case 3:
            _skill3->setString(__String::createWithFormat("%d", _skill3->getTag()+1)->getCString());
            _skill3->setTag(_skill3->getTag()+1);
            break;
        case 4:
            _skill4->setString(__String::createWithFormat("%d", _skill4->getTag()+1)->getCString());
            _skill4->setTag(_skill4->getTag()+1);
            break;
    }
}
void SkillStackManager::resetSkill()
{
    _skill1->setString("0");
    _skill1->setTag(0);

    _skill2->setString("0");
    _skill2->setTag(0);

    _skill3->setString("0");
    _skill3->setTag(0);

    _skill4->setString("0");
    _skill4->setTag(0);
}
bool SkillStackManager::onTouchBegan(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    Rect boundingBox = _button->getBoundingBox();
    
    
    if(boundingBox.containsPoint(location)){
        if(isVisible())
        {
            Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
            collisionCheck(NULL);
        }
    }
    return true;
}
