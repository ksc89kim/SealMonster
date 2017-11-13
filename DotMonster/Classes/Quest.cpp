//
//  Quest.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 18..
//
//

#include "Quest.h"
#include "Player.h"
#include "GameScene.h"
#include "EndingLayer.h"

QuestConatiner* QuestConatiner::_questConatiner = nullptr;

Quest::Quest()
{
    _questType = 0;
    _level = 0;
    _status = 0;
    _questIndex = 0;
    _rewardType = 0;
    _removeType = 0;
}
Quest::~Quest()
{
    
}
Quest *Quest::create(QuestPackData *questPackData)
{
    return Quest::create(questPackData->_questIndex, questPackData->_level,questPackData->_questType,
                         questPackData->_status);
}
Quest *Quest::create(int questIndex,int level,int questType,int status, int rewardType, Item *rewardItem, int removeType, Item *removeItem)
{
    Quest * ret = new Quest();
    if (ret && ret->init())
    {
        ret->_questIndex = questIndex;
        ret->_level = level;
        ret->_questType = questType;
        ret->_status = status;
        ret->_rewardType = rewardType;
        ret->_rewardList.clear();
        ret->_removeType = removeType;
        ret->_removeList.clear();
        if(rewardItem != nullptr)
        {
            ret->_rewardList.pushBack(rewardItem);
            ret->addChild(rewardItem);
        }
        if(removeItem != nullptr)
        {
            ret->_removeList.pushBack(removeItem);
            ret->addChild(removeItem);
        }
       ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}
Quest *Quest::create(int questIndex,int level,int questType,int status, int rewardType,Vector<Item *> &rewardlist,
                     int removeType, Vector<Item *> &removelist)
{
    Quest * ret = new Quest();
    if (ret && ret->init())
    {
        ret->_questIndex = questIndex;
        ret->_level = level;
        ret->_questType = questType;
        ret->_status = status;
        ret->_rewardType = rewardType;
        ret->_removeType = removeType;

        ret->_rewardList.clear();
        ret->_removeList.clear();
        
        for(int i=0;i<rewardlist.size();i++)
        {
            Item *item =rewardlist.at(i);
            ret->_rewardList.pushBack(item);
            ret->addChild(item);
        }
        for(int i=0;i<removelist.size();i++)
        {
            Item *item =removelist.at(i);
            ret->_removeList.pushBack(item);
            ret->addChild(item);
        }
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}
int Quest::getStatus()
{
    return _status;
}
int Quest::getRewardType()
{
    return _rewardType;
}
int Quest::getRemoveType()
{
    return _removeType;
}
Item *Quest::rewardItem()
{
    if(_rewardList.size()>0)
        return _rewardList.at(0);
    return nullptr;
}
Item *Quest::removeItem()
{
    if(_removeList.size()>0)
        return _removeList.at(0);
    return nullptr;
}
Vector<Item *> &Quest::getRewardList()
{
    return _rewardList;
}
Vector<Item *> &Quest::getRemoveList()
{
    return _removeList;
}
int Quest::getQuestIndex()
{
    return _questIndex;
}
int Quest::getQuestLevel()
{
    return _level;
}
bool Quest::isEqualQuest(Quest *quest)
{
    if(_questIndex==quest->_questIndex)
        if(_level==quest->_level)
            return true;
    
    return false;
}
bool Quest::isCurrentQuest()
{
    if(_status==questStatus::kIng)
            return true;
    return false;
}
void Quest::setStatus(int status)
{
    _status = status;
}
int Quest::getQuestType()
{
    return _questType;
}
bool Quest::isEqualData(int questIndex, int level)
{
    if(_questIndex==questIndex&&_level==level)
        return true;
    else
        return false;
}
void Quest::questLog()
{
    log("questIndex %d, level %d, status %d, questType %d", _questIndex, _level, _status, _questType);
}
#pragma mark - QuestPack

QuestPack::QuestPack()
{
    _questList = new Vector<Quest *>();
}
QuestPack::~QuestPack()
{
    if(_questList)
        delete _questList;
}
QuestPack *QuestPack::create(int questIndex)
{
    QuestPack * ret = new QuestPack();
    if (ret && ret->init())
    {
        ret->_questIndex = questIndex;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}
void QuestPack::setQuestType(int questType)
{
    _questType = questType;
}
int QuestPack::getQuestIndex()
{
    return _questIndex;
}
int QuestPack::getQuestType()
{
    return _questType;
}
bool QuestPack::isEqualQuestIndex(int questIndex)
{
    return (questIndex==_questIndex)? true:false;
}
bool QuestPack::isEqualQuest(Quest *quest)
{
    for(int i=0;i<_questList->size();i++)
    {
        Quest *compareQuest = _questList->at(i);
        if(compareQuest->isEqualQuest(quest))
        {
            return true;
        }
    }
    return false;
}
bool QuestPack::isEqualQuestPack(QuestPack *questPack)
{
    for(int i=0;i<_questList->size();i++)
    {
        Quest *quest =  questPack->getQuest(i);
        Quest *compareQuest = _questList->at(i);
        if(compareQuest->isEqualQuest(quest))
        {
            return true;
        }
    }
    return false;
}

void QuestPack::pushQuest(Quest *quest)
{
    _questList->pushBack(quest);
}
Quest *QuestPack::getQuest(Quest *quest)
{
    for (int i=0; i<_questList->size(); i++) {
        Quest *object = _questList->at(i);
        if(object->isEqualQuest(quest)){
            return object;
        }
    }
    return nullptr;
}
Quest *QuestPack::getQuest(QuestPack *questPack)
{
    for (int i=0; i<_questList->size(); i++) {
        Quest *object = _questList->at(i);
        for(int j=0;j<questPack->size();j++)
        {
           Quest *compaerObject =questPack->getQuest(j);
            if(object->isEqualQuest(compaerObject)){
                return object;
            }
        }
    }
    return nullptr;
}
Quest *QuestPack::getQuest(int index)
{
    return _questList->at(index);
}
Quest *QuestPack::getCurrentQuest()
{
    for (int i=0; i<_questList->size(); i++) {
        Quest *object = _questList->at(i);
        if(object->isCurrentQuest())
            return object;
    }
    return nullptr;
}

void QuestPack::successQuest(Quest *quest)
{
    int nextLevel = 0;
    for (int i=0; i<_questList->size(); i++) {
        Quest *object = _questList->at(i);
        if(object->isEqualQuest(quest)){
            object->setStatus(questStatus::kSuccess);
            Vector<Item *> rewardList = object->getRewardList();
            string rewardString;
            for(int j=0;j<rewardList.size();j++)
            {
                Item *item = rewardList.at(j);
                rewardString += item->getItemName();
                if(j<rewardList.size()-1)
                    rewardString += ",";
                if(object->getRewardType()==questReward::kItem)
                {
                    Player::getInstance()->_itemList->plusItem(item);
                }
                else if(object->getRewardType()==questReward::kItemUpgrade)
                {
                    Player::getInstance()->_itemList->plusItemUpgrade(item);
                }
            }
            if(object->getRewardType()==questReward::kItem)
            {
                (GameScene::runningScene())->createPopup(popUpType::kOk, __String::createWithFormat(TextDb::getInstance()->getEtcText(52).c_str(),
                                                                                                    rewardString.c_str())->getCString() , nullptr);
            }
            else if(object->getRewardType()==questReward::kItemUpgrade)
            {
                (GameScene::runningScene())->createPopup(popUpType::kOk, __String::createWithFormat(TextDb::getInstance()->getEtcText(53).c_str(),
                                                                                                rewardString.c_str())->getCString() , nullptr);
            }
            Vector<Item *> removeList = object->getRemoveList();
            if(object->getRemoveType()==questRemove::kItem)
            {
                for(int j=0;j<removeList.size();j++)
                {
                    Item *item = removeList.at(j);
                    Player::getInstance()->_itemList->minusItem(item);
                }
            }
            nextLevel = object->getQuestLevel()+1;
            
            //ending
            if(object->getQuestIndex()==questIndex::kMainQuest && object->getQuestLevel()==59)
            {
                Director::getInstance()->getRunningScene()->addChild(EndingLayer::create());
            }
        }
    }
    for (int i=0; i<_questList->size(); i++) {
        Quest *object = _questList->at(i);
        if(object->getQuestLevel()==nextLevel)
            object->setStatus(questStatus::kIng);
        else if(nextLevel==0)
            break;
    }
}
void QuestPack::successQuestPack(QuestPack *questPack)
{
    for(int i=0;i<questPack->size();i++)
    {
        Quest *quest = questPack->getQuest(i);
        if(quest->getQuestIndex()==_questIndex)
            successQuest(quest);
    }
}
void QuestPack::changeQuestData(int level, int status)
{
    for (int i=0; i<_questList->size(); i++) {
        Quest *object = _questList->at(i);
        if(object->isEqualData(_questIndex, level))
        {
            object->setStatus(status);
        }
    }
}
int QuestPack::size()
{
    return _questList->size();
}
void QuestPack::questLog()
{
    
    log("------------quest Index %d------------------", _questIndex);
    for (int i=0; i<_questList->size(); i++) {
        Quest *object = _questList->at(i);
        object->questLog();
    }
    log("---------------------------------------------");
}
#pragma mark - QuestConatiner

QuestConatiner::QuestConatiner()
{
    _questPackList = new Vector<QuestPack *>();
}
QuestConatiner::~QuestConatiner()
{
    if(_questPackList)
        delete _questPackList;
}
QuestConatiner *QuestConatiner::sharedObject()
{
    if(_questConatiner==nullptr)
    {
        _questConatiner = new QuestConatiner();
        _questConatiner->setValue();
    }
    return _questConatiner;
}
void QuestConatiner::setValue()
{
    QuestPack *main = QuestPack::create(questIndex::kMainQuest);

    main->pushQuest(Quest::create(questIndex::kMainQuest,1,questType::kTalk,questStatus::kIng,questReward::kNot)); //촌장과의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,2,questType::kTalk,questStatus::kWait,questReward::kNot)); //촌장과의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,3,questType::kTalk,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeResorative3, 1, 1, nullptr)));  //동월과의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,4,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kQuestMulMangCho, 1, 1, nullptr))); //물망초 싸움.
    main->pushQuest(Quest::create(questIndex::kMainQuest,5,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusPower, 1, 1, nullptr))); //가온과의 싸움.
    main->pushQuest(Quest::create(questIndex::kMainQuest,6,questType::kTalk,questStatus::kWait,questReward::kNot,nullptr, questRemove::kItem,Item::create(ItemType::kQuestMulMangCho, 1, 1, nullptr))); //동월과의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,7,questType::kCharacterWin,questStatus::kWait,questReward::kNot)); //크리스탈 마스터와의 싸움.
    main->pushQuest(Quest::create(questIndex::kMainQuest,8,questType::kTalk,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemStamp, 1, 1, nullptr))); //촌장과 대화 인장 획득.
    main->pushQuest(Quest::create(questIndex::kMainQuest,9,questType::kTalk,questStatus::kWait,questReward::kNot)); //단군 어머니와의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,10,questType::kTalk,questStatus::kWait,questReward::kNot)); //미호와의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,11,questType::kTalk,questStatus::kWait,questReward::kNot)); //백단 지부 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,12,questType::kTalk,questStatus::kWait,questReward::kNot)); //이박사와의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,13,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeResorative3, 1, 1, nullptr))); //망월산 싸움1.
    main->pushQuest(Quest::create(questIndex::kMainQuest,14,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusAgility, 1, 1, nullptr))); //망월산 싸움2.
    main->pushQuest(Quest::create(questIndex::kMainQuest,15,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kQuestOnepice, 1, 1, nullptr))); //망월산 싸움3.
    main->pushQuest(Quest::create(questIndex::kMainQuest,16,questType::kTalk,questStatus::kWait,questReward::kNot,nullptr,
                                  questRemove::kItem, Item::create(ItemType::kQuestOnepice, 1, 1, nullptr))); //이박사와의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,17,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeResorative3, 1, 1, nullptr))); //유월산 싸움1.
    main->pushQuest(Quest::create(questIndex::kMainQuest,18,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusAgility, 1, 1, nullptr))); //유월산 싸움2.
    main->pushQuest(Quest::create(questIndex::kMainQuest,19,questType::kTalk,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeResorative3, 1, 1, nullptr))); //유월산 대화3.
    main->pushQuest(Quest::create(questIndex::kMainQuest,20,questType::kTalk,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusPower, 1, 1, nullptr))); //이박사와의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,21,questType::kTalk,questStatus::kWait,questReward::kNot)); //가온과의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,22,questType::kTalk,questStatus::kWait,questReward::kNot)); //치우 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,23,questType::kTalk,questStatus::kWait,questReward::kNot)); //미호 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,24,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeResorative2, 1, 1, nullptr))); //흑단 싸움1.
    main->pushQuest(Quest::create(questIndex::kMainQuest,25,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeResorative3, 1, 1, nullptr))); //흑단 싸움2.
    main->pushQuest(Quest::create(questIndex::kMainQuest,26,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusStamina, 1, 1, nullptr))); //흑단 싸움3.
    main->pushQuest(Quest::create(questIndex::kMainQuest,27,questType::kCharacterWin,questStatus::kWait,questReward::kItem, Item::create(ItemType::kItemTypeMoveFire, 1, 1, nullptr))); //몬스터싸움.
    main->pushQuest(Quest::create(questIndex::kMainQuest,28,questType::kTalk,questStatus::kWait,questReward::kNot)); //미호 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,29,questType::kCharacterWin,questStatus::kWait,questReward::kItem, Item::create(ItemType::kItemTypeMoveTree, 1, 1, nullptr))); //가온과의 싸움.
    main->pushQuest(Quest::create(questIndex::kMainQuest,30,questType::kTalk,questStatus::kWait,questReward::kNot)); //하백 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,31,questType::kTalk,questStatus::kWait,questReward::kNot)); //정체모를 위인 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,32,questType::kCharacterWin,questStatus::kWait,questReward::kItem, Item::create(ItemType::kQuestCrystal, 1, 1, nullptr))); //가더와의 대화+싸움.
    main->pushQuest(Quest::create(questIndex::kMainQuest,33,questType::kTalk,questStatus::kWait,questReward::kItemUpgrade,Item::create(ItemType::kItemStamp, 1, 1, nullptr),questRemove::kItem, Item::create(ItemType::kQuestCrystal, 1, 1, nullptr))); //하백 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,34,questType::kCharacterWin,questStatus::kWait,questReward::kNot)); //정과 미호 대화 그리고 친선시합.
    main->pushQuest(Quest::create(questIndex::kMainQuest,35,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusPower, 1, 1, nullptr))); //흑단 발전소에서 싸움1
    main->pushQuest(Quest::create(questIndex::kMainQuest,36,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeEradication, 1, 1, nullptr))); //흑단 발전소에서 싸움2
    main->pushQuest(Quest::create(questIndex::kMainQuest,37,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeResorative2, 1, 1, nullptr))); //흑단 발전소에서 싸움3
    main->pushQuest(Quest::create(questIndex::kMainQuest,38,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusAgility, 1, 1, nullptr))); //흑단 발전소에서 싸움4
    main->pushQuest(Quest::create(questIndex::kMainQuest,39,questType::kCharacterWin,questStatus::kWait,questReward::kNot)); //마웅과의 만남 그리고 싸움.
    main->pushQuest(Quest::create(questIndex::kMainQuest,40,questType::kTalk,questStatus::kWait,questReward::kNot)); //마웅과의 대화.
    main->pushQuest(Quest::create(questIndex::kMainQuest,41,questType::kTalk,questStatus::kWait,questReward::kNot)); //백단 제2의 지부에서 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,42,questType::kCharacterWin,questStatus::kWait,questReward::kItem, Item::create(ItemType::kItemTypeMoveWater, 1, 1, nullptr))); //물의신전 물의보주 얻는 싸움 (몬스터)
    Vector<Item *> rewardItem;
    Vector<Item *> removeItem;
    removeItem.pushBack(Item::create(ItemType::kItemTypeMoveFire, 1, 1, nullptr));
    removeItem.pushBack(Item::create(ItemType::kItemTypeMoveWater, 1, 1, nullptr));
    removeItem.pushBack(Item::create(ItemType::kItemTypeMoveTree, 1, 1, nullptr));
    main->pushQuest(Quest::create(questIndex::kMainQuest,43,questType::kTalk,questStatus::kWait,questReward::kNot, rewardItem,questRemove::kItem, removeItem)); //미호와의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,44,questType::kTalk,questStatus::kWait,questReward::kNot)); //박사와의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,45,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeTransResorative2, 1, 1, nullptr))); //미나티와의 싸움1
    main->pushQuest(Quest::create(questIndex::kMainQuest,46,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeTransResorative3, 1, 1, nullptr))); //미나티와의 싸움2
    main->pushQuest(Quest::create(questIndex::kMainQuest,47,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusStamina, 1, 1, nullptr))); //미나티와의 싸움3
    main->pushQuest(Quest::create(questIndex::kMainQuest,48,questType::kTalk,questStatus::kWait,questReward::kNot)); //박사와의 대화
    
    main->pushQuest(Quest::create(questIndex::kMainQuest,49,questType::kTalk,questStatus::kWait,questReward::kNot)); //가온과의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,50,questType::kTalk,questStatus::kWait,questReward::kNot)); //박사와의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,51,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeTransResorative3, 1, 1, nullptr))); //미나티와의 싸움1
    main->pushQuest(Quest::create(questIndex::kMainQuest,52,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeTransResorative2, 1, 1, nullptr))); //미나티와의 싸움2
    main->pushQuest(Quest::create(questIndex::kMainQuest,53,questType::kTalk,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusTransPower, 1, 1, nullptr))); //치우와의 대화
    main->pushQuest(Quest::create(questIndex::kMainQuest,54,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusStamina, 1, 1, nullptr))); //미호와의 싸움
    main->pushQuest(Quest::create(questIndex::kMainQuest,55,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeTransResorative2, 1, 1, nullptr))); //미나티와의 싸움3
    main->pushQuest(Quest::create(questIndex::kMainQuest,56,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusAgility, 1, 1, nullptr))); //미나티와의 싸움4
    main->pushQuest(Quest::create(questIndex::kMainQuest,57,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusTransAgility, 1, 1, nullptr))); //미나티와의 싸움5
    main->pushQuest(Quest::create(questIndex::kMainQuest,58,questType::kCharacterWin,questStatus::kWait,questReward::kNot)); //가온과의 싸움
    main->pushQuest(Quest::create(questIndex::kMainQuest,59,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusTransPower, 1, 1, nullptr))); //정과의 마지막 싸움.
    main->pushQuest(Quest::create(questIndex::kMainQuest,60,questType::kTalk,questStatus::kWait,questReward::kNot)); //스토리 끝.
    _questPackList->pushBack(main);
    
    
    QuestPack *masterQuest = QuestPack::create(questIndex::kMasterSealQuest);//마스터 싸움.
    masterQuest->pushQuest(Quest::create(questIndex::kMasterSealQuest,1,questType::kCharacterWin,questStatus::kIng,questReward::kNot));
    masterQuest->pushQuest(Quest::create(questIndex::kMasterSealQuest,2,questType::kCharacterWin,questStatus::kWait,questReward::kItemUpgrade,Item::create(ItemType::kItemStamp, 1, 1, nullptr)));
    masterQuest->pushQuest(Quest::create(questIndex::kMasterSealQuest,3,questType::kCharacterWin,questStatus::kWait,questReward::kItemUpgrade,Item::create(ItemType::kItemStamp, 1, 1, nullptr)));
    masterQuest->pushQuest(Quest::create(questIndex::kMasterSealQuest,4,questType::kCharacterWin,questStatus::kWait,questReward::kItemUpgrade,Item::create(ItemType::kItemStamp, 1, 1, nullptr)));
    masterQuest->pushQuest(Quest::create(questIndex::kMasterSealQuest,5,questType::kCharacterWin,questStatus::kWait,questReward::kNot));
    masterQuest->pushQuest(Quest::create(questIndex::kMasterSealQuest,6,questType::kCharacterWin,questStatus::kWait,questReward::kItemUpgrade,Item::create(ItemType::kItemStamp, 1, 1, nullptr)));
    masterQuest->pushQuest(Quest::create(questIndex::kMasterSealQuest,7,questType::kCharacterWin,questStatus::kWait,questReward::kItemUpgrade,Item::create(ItemType::kItemStamp, 1, 1, nullptr)));
    masterQuest->pushQuest(Quest::create(questIndex::kMasterSealQuest,8,questType::kCharacterWin,questStatus::kWait,questReward::kItemUpgrade,Item::create(ItemType::kItemStamp, 1, 1, nullptr)));
    masterQuest->pushQuest(Quest::create(questIndex::kMasterSealQuest,9,questType::kCharacterWin,questStatus::kWait,questReward::kItemUpgrade,Item::create(ItemType::kItemStamp, 1, 1, nullptr)));
    masterQuest->pushQuest(Quest::create(questIndex::kMasterSealQuest,10,questType::kCharacterWin,questStatus::kWait,questReward::kNot));
    _questPackList->pushBack(masterQuest);
    
    QuestPack *eventQuest = QuestPack::create(questIndex::kEventQuest);
    eventQuest->pushQuest(Quest::create(questIndex::kEventQuest,1,questType::kCharacterWin,questStatus::kIng,questReward::kItem,Item::create(ItemType::kItemTypePlusStamina, 1, 1, nullptr)));
    eventQuest->pushQuest(Quest::create(questIndex::kEventQuest,2,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusTransAgility, 1, 1, nullptr)));
    eventQuest->pushQuest(Quest::create(questIndex::kEventQuest,3,questType::kCharacterWin,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypePlusTransPower, 1, 1, nullptr)));
    _questPackList->pushBack(eventQuest);

    
    QuestPack *firstVillageHelpQuest = QuestPack::create(questIndex::kFirstVillageHelpQuest);
    firstVillageHelpQuest->pushQuest(Quest::create(questIndex::kFirstVillageHelpQuest,1,questType::kTalk,questStatus::kIng,questReward::kItem,Item::create(ItemType::kItemTypeResorative3, 1, 1, nullptr)));
    _questPackList->pushBack(firstVillageHelpQuest);
    
    QuestPack *firstVillageLoonQuest = QuestPack::create(questIndex::kFirstVillageLoonQuest);
    firstVillageLoonQuest->pushQuest(Quest::create(questIndex::kFirstVillageLoonQuest,1,questType::kTalk,questStatus::kIng,questReward::kNot));
    firstVillageLoonQuest->pushQuest(Quest::create(questIndex::kFirstVillageLoonQuest,2,questType::kTalk,questStatus::kWait,questReward::kItem,Item::create(ItemType::kQuestSickle, 1, 1, nullptr)));
    firstVillageLoonQuest->pushQuest(Quest::create(questIndex::kFirstVillageLoonQuest,3,questType::kTalk,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeZailLoon, 1, 1, nullptr),questRemove::kItem,Item::create(ItemType::kQuestSickle, 1, 1, nullptr)));
    _questPackList->pushBack(firstVillageLoonQuest);

    QuestPack *threeVillageLoonQuest = QuestPack::create(questIndex::kThreeVillageLoonQuest);
    threeVillageLoonQuest->pushQuest(Quest::create(questIndex::kThreeVillageLoonQuest,1,questType::kTalk,questStatus::kIng,questReward::kNot));
    threeVillageLoonQuest->pushQuest(Quest::create(questIndex::kThreeVillageLoonQuest,2,questType::kTalk,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeVailLoon, 1, 1, nullptr)));
    _questPackList->pushBack(threeVillageLoonQuest);
    
    QuestPack *fiveVillageLoonQuest = QuestPack::create(questIndex::kFiveVillageLoonQuest);
    fiveVillageLoonQuest->pushQuest(Quest::create(questIndex::kFiveVillageLoonQuest,1,questType::kTalk,questStatus::kIng,questReward::kNot));
    fiveVillageLoonQuest->pushQuest(Quest::create(questIndex::kFiveVillageLoonQuest,2,questType::kTalk,questStatus::kWait,questReward::kNot));
    fiveVillageLoonQuest->pushQuest(Quest::create(questIndex::kFiveVillageLoonQuest,3,questType::kTalk,questStatus::kWait,questReward::kNot));
    fiveVillageLoonQuest->pushQuest(Quest::create(questIndex::kFiveVillageLoonQuest,4,questType::kTalk,questStatus::kWait,questReward::kNot));
    fiveVillageLoonQuest->pushQuest(Quest::create(questIndex::kFiveVillageLoonQuest,5,questType::kTalk,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeRailLoon, 1, 1, nullptr)));
    _questPackList->pushBack(fiveVillageLoonQuest);
    
    
    QuestPack *lastLoonQuest = QuestPack::create(questIndex::kLastLoonQuest);
    lastLoonQuest->pushQuest(Quest::create(questIndex::kLastLoonQuest,1,questType::kTalk,questStatus::kIng,questReward::kItem,Item::create(ItemType::kItemTypeQailLoon, 1, 1, nullptr)));
    lastLoonQuest->pushQuest(Quest::create(questIndex::kLastLoonQuest,2,questType::kTalk,questStatus::kWait,questReward::kItem,Item::create(ItemType::kItemTypeNailLoon, 1, 1, nullptr)));
    _questPackList->pushBack(lastLoonQuest);
}
QuestPack *QuestConatiner::getQuestPack(int questIndex)
{
    for(int i=0;i<_questPackList->size();i++)
    {
        QuestPack *pack = _questPackList->at(i);
        if(pack->isEqualQuestIndex(questIndex))
            return pack;
    }
    return nullptr;
}
int QuestConatiner::getQuestStatus(int questIndex, int dataIndex)
{
    QuestPack *questPack = getQuestPack(questIndex);
    if(questPack!=nullptr)
    {
        Quest *questObject =  questPack->getQuest(dataIndex);
        if(questObject!=nullptr)
            return questObject->getStatus();
        else
            return 0;
    }
    else
    {
        return 0;
    }
}

int QuestConatiner::getQuestStatus(Quest *quest)
{
    QuestPack *questPack = getQuestPack(quest->getQuestIndex());
    if(questPack!=nullptr)
    {
        Quest *questObject =  questPack->getQuest(quest);
        if(questObject!=nullptr)
            return questObject->getStatus();
        else
            return 0;
    }
    else
        return 0;
}

bool QuestConatiner::checkQuestCharacter(const char *questCharacterIndex)
{
    std::string quest = questCharacterIndex;
    if(!quest.compare("0"))
        return true;
    if(quest.empty())
        return false;
    
    
    std::vector<std::string> questCharacteIndex =  (&CommonUtils::getInstance())->splits(questCharacterIndex, "/");
    Quest *minQuest = Quest::create(atoi(questCharacteIndex[0].c_str()), atoi(questCharacteIndex[1].c_str()));
    Quest *maxQuest = Quest::create(atoi(questCharacteIndex[0].c_str()), atoi(questCharacteIndex[2].c_str()));
    int minStatus = getQuestStatus(minQuest);
    int maxStatus = getQuestStatus(maxQuest);
    if(minStatus>questStatus::kWait&&maxStatus<questStatus::kSuccess)
    {
        return true;
    }
    return false;
}
Quest *QuestConatiner::getCurrentQuest(int questIndex)
{
    QuestPack *questPack = getQuestPack(questIndex);
    if(questPack!=nullptr)
    {
        return questPack->getCurrentQuest();
    }
    else
        return nullptr;
}
Quest *QuestConatiner::getQuest(Quest *quest)
{
    QuestPack *questPack = getQuestPack(quest->getQuestIndex());
    if(questPack!=nullptr)
    {
        return questPack->getQuest(quest);
    }
    else
        return nullptr;
}
Quest *QuestConatiner::getQuest(int questIndex, int dataIndex)
{
    QuestPack *questPack = getQuestPack(questIndex);
    if(questPack!=nullptr)
    {
        return questPack->getQuest(dataIndex);
    }
    else
        return nullptr;
}
Quest *QuestConatiner::getQuest(QuestPack *questPack)
{
    for(int i=0;i<questPack->size();i++)
    {
        Quest *quest = questPack->getQuest(i);
        for(int j=0;j<size();j++)
        {
            QuestPack *pack = _questPackList->at(j);
            Quest *packQuest = pack->getQuest(quest);
            if(packQuest!=nullptr)
                return packQuest;
        }
    }
    return nullptr;
}
void QuestConatiner::successQuest(Quest *quest)
{
    QuestPack *questPack = getQuestPack(quest->getQuestIndex());
    if(questPack!=nullptr)
    {
        questPack->successQuest(quest);
    }
}
void QuestConatiner::successQuestPack(QuestPack *questPack)
{
    for(int i=0;i<questPack->size();i++)
    {
        Quest *quest = questPack->getQuest(i);
        QuestPack *questContainerPack = getQuestPack(quest->getQuestIndex());
        questContainerPack->successQuest(quest);
    }
    
}
void QuestConatiner::changeQuestData(int questIndex, int level, int status)
{
    QuestPack *questPack = getQuestPack(questIndex);
    if(questPack!=nullptr)
    {
        questPack->changeQuestData(level,status);
    }
}
int QuestConatiner::size()
{
    return _questPackList->size();
}
QuestPack *QuestConatiner::getQuestPackIndex(int index)
{
   return _questPackList->at(index);
}
void QuestConatiner::questLog()
{
    for(int i=0;i<size();i++)
    {
        QuestPack *questContainerPack = getQuestPackIndex(i);
        questContainerPack->questLog();
    }
}