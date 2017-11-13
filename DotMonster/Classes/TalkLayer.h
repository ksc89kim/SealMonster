//
//  TalkLayer.h
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 15..
//
//

#ifndef __dotMonster__TalkLayer__
#define __dotMonster__TalkLayer__

#include "Quest.h"

class Talk:public Node
{

public:
    std::string _talkCotent;
    Sprite *_spriteTalk;
    int _talkType;
    Talk *_next;
    QuestPack *_questPack;
    int _talkIndex;
    std::string _talkName;
    Talk();
    ~Talk();
    static Talk *create(int talk,const char *talkCotent,const char *talkName,Sprite *spriteTalk,QuestPack *questPack = nullptr,int talkIndex=0);
};

class TalkContainer:public Node
{
    Vector<Talk *> *_talkContainer;
public:
    TalkContainer();
    ~TalkContainer();
    static TalkContainer *create();
    void addTalk(Talk *talk);
    Talk *getTalk(int index);
    Talk *getCheckTalk(int index);
    Quest *getCurrentQuest();
    Talk *getCurrentTalk();
    void linkTalk();
    Talk *getBaseTalk();
    static int changeTalkType(int index);
};

class TalkLayer:public LayerColor
{
    Sprite *_border;
    Sprite *_viewSprite;
    Sprite *_nameBorder;
    Node *_character;
    Node *_beforeLayer;
    Node *_mapArea;
    Talk *_currentTalk;
    Label *_content;
    TalkContainer *_talkContainer;
    int _characterTag;
    bool _isTyping;
    bool _isFirst;
public:
    TalkLayer();
    ~TalkLayer();
    static TalkLayer *create(Node *beforeLayer,int characterTag, Node *character=nullptr,Node *mapArea=nullptr);
    bool checkType();
    Sprite *checkTalkSpriteData(const string &data);
    void setImage();
    void setValue();
    void next();
    void nextTyping(float delayTime);
    void refreshImage();
    void refreshText();
    void finish();
    void setTalkContainer();

    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event *event);
};


#endif /* defined(__dotMonster__TalkLayer__) */
