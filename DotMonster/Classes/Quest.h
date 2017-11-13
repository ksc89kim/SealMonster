//
//  Quest.h
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 18..
//
//

#ifndef __dotMonster__Quest__
#define __dotMonster__Quest__

#include "Define.h"
#include "Item.h"
#include "TextDb.h"

class Quest:public Node
{
    int _rewardType;
    int _status;
    int _questType;
    int _level;
    int _questIndex;
    int _removeType;
    Vector<Item *> _rewardList;
    Vector<Item *> _removeList;
public:
    Quest();
    ~Quest();
    static Quest* create(QuestPackData *questPackData); //DB Data
    static Quest* create(int questIndex,int level,int questType=0,int status=0, int rewardType=0, Item *rewardItem = nullptr,
                         int removeType=0, Item *removeItem = nullptr);
    static Quest* create(int questIndex,int level,int questType,int status, int rewardType, Vector<Item *> &rewardlist ,
                         int removeType, Vector<Item *> &removelist);
    int getQuestType();
    int getQuestIndex();
    int getQuestLevel();
    int getStatus();
    int getRewardType();
    int getRemoveType();
    Item *rewardItem();
    Item *removeItem();
    Vector<Item *> &getRewardList();
    Vector<Item *> &getRemoveList();
    bool isEqualQuest(Quest* quest);
    bool isCurrentQuest();
    void setStatus(int status);
    bool isEqualData(int questIndex,int level);
    void questLog();
};

class QuestPack:public Node
{
    int _questIndex;
    int _questType;
    Vector<Quest *> *_questList;
public:
    QuestPack();
    ~QuestPack();
    
    int getQuestIndex();
    int getQuestType();
    int size();
    static QuestPack* create(int questIndex=0);
    void pushQuest(Quest *quest);
    Quest *getQuest(int index);
    Quest *getQuest(Quest *quest);
    Quest *getQuest(QuestPack* questPack);
    Quest *getCurrentQuest();
    bool isEqualQuestIndex(int questIndex);
    bool isEqualQuestPack(QuestPack* questPack);
    bool isEqualQuest(Quest* quest);
    void successQuest(Quest *quest);
    void successQuestPack(QuestPack *questPack);
    void changeQuestData(int level, int status);
    void questLog();
    void setQuestType(int questType);

};

class QuestConatiner:public Node
{

public:
    Vector<QuestPack *> *_questPackList;

    QuestConatiner();
    ~QuestConatiner();
    
    static QuestConatiner *_questConatiner;
    static QuestConatiner * sharedObject();

    void setValue();
    int size();
    int getQuestStatus(int questIndex, int dataIndex);
    int getQuestStatus(Quest *quest);
    QuestPack *getQuestPack(int questIndex);
    Quest *getQuest(int questIndex, int dataIndex);
    Quest *getQuest(Quest *quest);
    Quest *getQuest(QuestPack *questPack);
    QuestPack *getQuestPackIndex(int index);
    bool checkQuestCharacter(const char*questCharacterIndex);
    Quest *getCurrentQuest(int questIndex);
    void successQuest(Quest *quest);
    void successQuestPack(QuestPack *questPack);
    void changeQuestData(int questIndex,int level, int status);
    void questLog();
    
};

#endif /* defined(__dotMonster__Quest__) */
