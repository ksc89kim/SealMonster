//
//  TalkLayer.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 15..
//
//

#include "TalkLayer.h"
#include "Character.h"
#include "BattleLayer.h"
#include "MapArea.h"
#include "TextDb.h"
#include "GameScene.h"

#pragma mark - Talk
Talk::Talk()
{
    _questPack = nullptr;
    _next = nullptr;
    _spriteTalk = nullptr;
}
Talk::~Talk()
{
    if(_spriteTalk)
        _spriteTalk->release();
}
Talk *Talk::create(int talk,const char *talkCotent,const char *talkName,Sprite *spriteTalk,QuestPack *questPack,int talkIndex)
{
    Talk * ret = new Talk();
    if (ret && ret->init())
    {
        ret->_talkType = talk;
        ret->_talkCotent = talkCotent;
        ret->_spriteTalk = spriteTalk;
        ret->_spriteTalk->retain();
        ret->_questPack = questPack;
        ret->_talkIndex = talkIndex;
        ret->_talkName = talkName;
        if(ret->_questPack != nullptr)
            ret->addChild(ret->_questPack);
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}
#pragma mark - TalkContainer
TalkContainer::TalkContainer()
{
    _talkContainer = new Vector<Talk *>();
}
TalkContainer::~TalkContainer()
{
    if(_talkContainer)
        delete _talkContainer;
}
TalkContainer *TalkContainer::create()
{
    TalkContainer * ret = new TalkContainer();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}
void TalkContainer::addTalk(Talk *talk)
{
    _talkContainer->pushBack(talk);
}
Talk *TalkContainer::getTalk(int index)
{
   return _talkContainer->at(index);
}
Quest *TalkContainer::getCurrentQuest()
{
    Talk *checkTalk = getCurrentTalk();
    if(checkTalk!=nullptr && checkTalk->_talkType!=talkType::ktalkBaseStart)
        return QuestConatiner::sharedObject()->getQuest(checkTalk->_questPack);
    
    return nullptr;
}
Talk *TalkContainer::getCheckTalk(int index)
{
    Quest *currentTalk = QuestConatiner::sharedObject()->getCurrentQuest(index);
    if(currentTalk!=nullptr)
    {
        for(int i=0;i<_talkContainer->size();i++)
        {
            Talk *talk = _talkContainer->at(i);
            if(talk->_questPack!=nullptr)
            {
                if(talk->_talkType == talkType::ktalkStart || talk->_talkType == talkType::ktalkBaseStart)
                    if(talk->_questPack->isEqualQuest(currentTalk))
                        return talk;
            }
        }
    }
    return nullptr;
}
Talk *TalkContainer::getBaseTalk()
{
    for(int i=0;i<_talkContainer->size();i++)
    {
        Talk *talk = _talkContainer->at(i);
        if(talk->_talkType==talkType::ktalkBaseStart)
            return talk;
    }
    return nullptr;
}
Talk *TalkContainer::getCurrentTalk()
{
    Talk *talk = getCheckTalk(questIndex::kMainQuest);
    if(talk==nullptr)
    {
        talk = getCheckTalk(questIndex::kMasterSealQuest);
    }
    if(talk==nullptr)
    {
        talk = getCheckTalk(questIndex::kEventQuest);
    }
    if(talk==nullptr)
    {
        talk = getCheckTalk(questIndex::kFirstVillageHelpQuest);
    }
    if(talk==nullptr)
    {
        talk = getCheckTalk(questIndex::kFirstVillageLoonQuest);
    }
    if(talk==nullptr)
    {
        talk = getCheckTalk(questIndex::kThreeVillageLoonQuest);
    }
    if(talk==nullptr)
    {
        talk = getCheckTalk(questIndex::kFiveVillageLoonQuest);
    }
    if(talk==nullptr)
    {
        talk = getCheckTalk(questIndex::kLastLoonQuest);
    }
    if(talk==nullptr)
    {
        talk = getBaseTalk();
    }
    return talk;
}
int TalkContainer::changeTalkType(int index)
{
    int type = talkType::ktalkBaseStart;
    switch(index)
    {
        case 0:
            type = talkType::ktalkBaseStart;
            break;
        case 1:
            type = talkType::ktalkBaseNext;
            break;
        case 2:
            type = talkType::ktalkBaseFinish;
            break;
        case 3:
            type = talkType::ktalkStart;
            break;
        case 4:
            type = talkType::ktalkNext;
            break;
        case 5:
            type = talkType::ktalkFinish;
            break;
    }
    return type;
}
void TalkContainer::linkTalk()
{
    Talk *beforeTalk = nullptr;
    for(int i=0;i<_talkContainer->size();i++)
    {
        Talk *talk = _talkContainer->at(i);
        if(talk->_talkType==talkType::ktalkStart)
            beforeTalk = talk;
        else if(talk->_talkType==talkType::ktalkNext || talk->_talkType==talkType::ktalkFinish)
        {
            beforeTalk->_next = talk;
            talk->_questPack = beforeTalk->_questPack;
            beforeTalk = talk;
        }
        
        if(talk->_talkType==talkType::ktalkBaseStart)
            beforeTalk = talk;
        else if(talk->_talkType==talkType::ktalkBaseNext || talk->_talkType==talkType::ktalkBaseFinish)
        {
            beforeTalk->_next = talk;
            talk->_questPack = beforeTalk->_questPack;
            beforeTalk = talk;
        }
    }
}
#pragma mark - TalkLayer
TalkLayer::TalkLayer()
{
    _isFirst = true;
    _isTyping = false;
    _characterTag = 0;
    _currentTalk = nullptr;
    _content = nullptr;
    _beforeLayer = nullptr;
    _character = nullptr;
    _mapArea = nullptr;
    _viewSprite = nullptr;
}

TalkLayer::~TalkLayer()
{

}

TalkLayer *TalkLayer::create(Node *beforeLayer,int characterTag, Node *character,Node *mapArea)
{
    TalkLayer * layer = new TalkLayer();
    if(layer && layer->initWithColor(Color4B(255,255,255,255)))
    {
        layer->ignoreAnchorPointForPosition(false);
        layer->_beforeLayer = beforeLayer;
        layer->_characterTag = characterTag;
        layer->_character = character;
        layer->_mapArea = mapArea;
        layer->setValue();
        layer->setImage();
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void TalkLayer::setImage()
{
    
    if(_beforeLayer!=nullptr)
        _beforeLayer->setVisible(false);

    Player::getInstance()->pauseMusic();
    Adaptor::hideAd();
    
    _currentTalk = _talkContainer->getCurrentTalk();

    if(_currentTalk!=nullptr)
    {

        _border=  (Sprite *)Scale9Sprite::create("border.png");
        _border->setContentSize(Size(this->getContentSize().width-50,250));
        _border->setPosition(Vec2(this->getContentSize().width/2,this->getContentSize().height*0.25));
        _border->ignoreAnchorPointForPosition(false);
        _content = Label::createWithTTF("",CommonUtils::getFontName(),FONT_SIZE);
        _content->setDimensions(_border->getContentSize().width-40, _border->getContentSize().height-40);
        _content->setVerticalAlignment(TextVAlignment::CENTER);
        _content->setHorizontalAlignment(TextHAlignment::LEFT);
        _content->setColor(Color3B(0,0,0));
        _content->setPosition(Vec2(_border->getContentSize().width/2,_border->getContentSize().height/2));
        _border->addChild(_content);
        this->addChild(_border);
        
        _nameBorder = CommonUtils::createLabelBorder(_currentTalk->_talkName);
        _nameBorder->setAnchorPoint(Vec2(0,0.5f));
        CommonUtils::setLabelBorderAncorPoint(_nameBorder, Vec2(0,0.5f));
        CommonUtils::setLabelBorderPoint(_nameBorder, Vec2(10,_nameBorder->getContentSize().height/2));
        _nameBorder->setPosition(Vec2(0, _border->getContentSize().height+30));
        _border->addChild(_nameBorder);
        
        next();
        
        refreshImage();
    }
    else
        log("null ptr");
    

    
//    CommonPopUp *p = CommonPopUp::create(CC_CALLBACK_0(TalkLayer::setImage, this));
//    this->addChild(p);

}
void TalkLayer::refreshImage()
{
    this->removeChild(_viewSprite);
    _viewSprite = _currentTalk->_spriteTalk;
    if(dynamic_cast<ShapeCommon *>(_viewSprite))
    {
        ShapeCommon *shape = (ShapeCommon *)_viewSprite;
        _viewSprite->setPosition(Vec2(this->getContentSize().width/2,_border->getPositionY()+_border->getContentSize().height/2+50));
        
    }
    else
    {
        _viewSprite->setAnchorPoint(Vec2(0.5f,0.5f));
        _viewSprite->setPosition(Vec2(this->getContentSize().width/2,_border->getPositionY()+_border->getContentSize().height/2+
                                      (_viewSprite->getContentSize().height+_viewSprite->getScale())/2+50));
    }
    CommonUtils::setLabelBorderContent(_nameBorder, _currentTalk->_talkName);
    
    this->addChild(_viewSprite);
    
}
void TalkLayer::refreshText()
{
    _content->setString(_currentTalk->_talkCotent.c_str());
}
void TalkLayer::setValue()
{
    setTalkContainer();
    
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    auto positionListener = EventListenerTouchOneByOne::create();
    positionListener->setSwallowTouches(true);
    positionListener->onTouchBegan = CC_CALLBACK_2(TalkLayer::onTouchBegan, this);
    positionListener->onTouchMoved = CC_CALLBACK_2(TalkLayer::onTouchMoved, this);
    positionListener->onTouchEnded = CC_CALLBACK_2(TalkLayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(positionListener, this);
}

bool TalkLayer::onTouchBegan(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());
    return true;
}
void TalkLayer::onTouchMoved(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Point location = target->convertToNodeSpace(touch->getLocation());

}
void TalkLayer::onTouchEnded(Touch* touch, Event* event) {
    auto target = event->getCurrentTarget();
    Player::getInstance()->playSound(SOUND_EFFECT_DOTE_BUTTON);
    Point location = target->convertToNodeSpace(touch->getLocation());
    next();
}
bool TalkLayer::checkType()
{
    if(_isTyping)
    {
        this->unschedule(schedule_selector(TalkLayer::nextTyping));
        _isFirst = false;
        _isTyping = false;
        refreshText();
        return true;
    }
    return false;

}
Sprite *TalkLayer::checkTalkSpriteData(const string &data)
{
    std::vector<std::string> spriteData = (&CommonUtils::getInstance())->splits(data, "/");
    if(spriteData.size()>1 && spriteData.size()<6)
    {
        ShapeCommon *monster=nullptr;
        int bushType = atoi(spriteData[0].c_str());
        int firstIndex = atoi(spriteData[1].c_str());
        int midIndex = atoi(spriteData[2].c_str());
        int lastIndex = atoi(spriteData[3].c_str());
        int level = atoi(spriteData[4].c_str());
        switch(bushType)
        {
            case bushType::kBushShapeF:
                monster = ShapeF::create();
                break;
            case bushType::kBushShapeT:
                monster = ShapeT::create();
                break;
            case bushType::kBushShapeW:
                monster = ShapeW::create();
                break;
            case bushType::kBushShapeI:
                monster = ShapeI::create();
                break;
            case bushType::kBushShapeZ:
                monster = ShapeZ::create();
                break;
        }
        if(monster!=nullptr)
        {
            monster->_shapeData->_level->setShapeValue(level);
            monster->changeFindShape(firstIndex, midIndex, lastIndex);
        }
        return (Sprite *)monster;
    }
    
    string imageFile = "talk/" + data;
    Sprite *sprite =Sprite::create(imageFile);
    sprite->setAnchorPoint(Vec2(0.5f,0.0f));
    return sprite;
}
void TalkLayer::next()
{
    if(_currentTalk!=nullptr)
    {
        if(_currentTalk->_next!=nullptr)
        {
            if(!checkType())
            {
                _isTyping = true;
                _content->setString("");
                if(_isFirst)
                    _isFirst = false;
                else
                    _currentTalk = _currentTalk->_next;
                refreshImage();
                this->schedule(schedule_selector(TalkLayer::nextTyping));
            }
            
        }
        else
        {
            if(_isFirst)
            {
                if(!checkType())
                {
                    _isTyping = true;
                    _content->setString("");
                    refreshImage();
                    this->schedule(schedule_selector(TalkLayer::nextTyping));
                }
            }
            else
            {
                if(!checkType())
                {
                    finish();
                }
            }
        }
    }
}
void TalkLayer::nextTyping(float delayTime)
{

    if(_content->getString().size()<_currentTalk->_talkCotent.size())
    {
        string temp;
        for(int i=1;i<=3;i++) //한글 버전.
        {
            if((_currentTalk->_talkCotent.at(_content->getString().size()+i-1) & 0x80)==0x80)
            {
                temp += _currentTalk->_talkCotent.at(_content->getString().size()+i-1);
            }
            else
            {
                temp = _currentTalk->_talkCotent.at(_content->getString().size()+i-1);
                break;
            }
        }
        _content->setString(_content->getString()+temp);
    }
    else
    {
        next();
    }
}

void TalkLayer::finish()
{
    Adaptor::showAd();
    if(_currentTalk->_questPack!=nullptr)
    {
        for(int i=0;i<_currentTalk->_questPack->size();i++)
        {
            Quest *quest = _currentTalk->_questPack->getQuest(i);
            if(quest->getQuestType()==questType::kTalk)
                if(quest->getStatus()==questStatus::kSuccess)
                {
                    quest->questLog();
                    QuestConatiner::sharedObject()->successQuest(quest);
                    QuestConatiner::sharedObject()->questLog();

                }
        }
    }
    
    if(_beforeLayer!=nullptr)
    {
        _beforeLayer->setVisible(true);
        if(_currentTalk->_questPack!=nullptr)
        {
            QuestPack *pack = QuestPack::create();
            pack->setQuestType(questType::kCharacterWin);
            for(int i=0;i<_currentTalk->_questPack->size();i++)
            {
                Quest *quest =  _currentTalk->_questPack->getQuest(i);
                if(quest->getQuestType()==questType::kCharacterWin)
                {
                    pack->pushQuest(QuestConatiner::sharedObject()->getQuest(quest));
                }
            }
            if(pack->size()>0 && _mapArea!=nullptr)
            {
                GameScene *currentScene =  GameScene::runningScene();
                BattleLayer *battleLayer = BattleLayer::create(_beforeLayer,_character,_mapArea,battleType::kQuestChracterType,pack);
                battleLayer->setPosition(Vec2(currentScene->getContentSize().width/2,currentScene->getContentSize().height/2));
                currentScene->addChild(battleLayer);
            }
            else if(_mapArea!=nullptr)
            {
                ((MapArea *)_mapArea)->refreshLoadMap();
            }
        }
        else if(_mapArea!=nullptr)
        {
            ((MapArea *)_mapArea)->refreshLoadMap();
        }
    }
    Player::getInstance()->resumeMusic();

    this->removeFromParent();
}

void TalkLayer::setTalkContainer()
{
    _talkContainer = TalkContainer::create();
    this->addChild(_talkContainer);
    std::map<unsigned int,TalkData *> talkArray = TextDb::getInstance()->getTalkMap(_characterTag);
    for(int i=1;i<=talkArray.size();i++)
    {
        TalkData *talkData = talkArray[i];
        if(_characterTag>0)
        {
            if(_characterTag==talkData->_type)
            {
                if(talkData->_talkType==talkType::ktalkStart&&talkData->_questPackIndex.length()>0)
                {
                    QuestPack *questPack = QuestPack::create();
                    std::vector<std::string> questInfo = (&CommonUtils::getInstance())->splits(talkData->_questPackIndex, "/");
                    for(int i=0; i<questInfo.size();i++)
                    {
                        int questPackIndex = atoi(questInfo[i].c_str());
                        Quest *quest = Quest::create(TextDb::getInstance()->getQuestData(questPackIndex, _characterTag));
                        questPack->pushQuest(quest);
                        
                    }
                    _talkContainer->addTalk(Talk::create(talkData->_talkType, talkData->_talkContent.c_str(),talkData->_talkName.c_str(),checkTalkSpriteData(talkData->_talkSprite), questPack, talkData->_talkIndex));
                    
                }
                else
                {
                    _talkContainer->addTalk(Talk::create(talkData->_talkType, talkData->_talkContent.c_str(),talkData->_talkName.c_str(), checkTalkSpriteData(talkData->_talkSprite),nullptr, talkData->_talkIndex));
                }
            }
        }
        else
        {
            _talkContainer->addTalk(Talk::create(talkData->_talkType, talkData->_talkContent.c_str(),talkData->_talkName.c_str(), checkTalkSpriteData(talkData->_talkSprite),nullptr, talkData->_talkIndex));
        }
        
    }
    _talkContainer->linkTalk();
}