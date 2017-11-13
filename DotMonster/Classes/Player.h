//
//  Player.h
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 6..
//
//

#ifndef __dotMonster__Player__
#define __dotMonster__Player__

#include "ItemContainer.h"
#include "Character.h"
#include "ShapeCommon.h"
#include "ShapeF.h"
#include "ShapeT.h"
#include "ShapeW.h"
#include "ShapeZ.h"
#include "ShapeI.h"

class Player:public Character
{
private:
    ShapeValue *_gold;
    std::string _frontSprite;
    std::string _backSprite;
    std::string _leftSprite;
    std::string _rightSprite;
    bool _isSound;
    bool _isMusic;
    bool _isTutorial;
public:
    Player();
    ~Player();
    
    ItemContainer *_itemList;
    std::string _mapInfo;
    int _currentMapPoint;
    int _beforeMapPoint;
    ValueMap _enemyCharactersInfo;
    bool _isLoad;
    bool _isStartLoad;

    static Player *_player;
    static Player* getInstance();
    bool isMonster();
    
    bool isLiveEnemyCharacterInfo(Node *mapPoint); //맵에 대한 적 정보들.
    bool getEnemyCharacterInfo(std::string key);
    void saveLiveEnemyCharacterInfo(bool isLive,Node *mapPoint); //맵에 대한 적 정보들.
    void save();
    void load();
    void pushMonster(ShapeCommon *monster);
    int getSelectMonsterIndex();
    void setSelectMonster(ShapeCommon *monster, int index);
    
    void anotherExpUp(int exp, int selectNum);
    void plusGold(float gold);
    void minusGold(float gold);
    float getGold();
    
    const char* getCharacterFrontSprite();
    const char* getCharacterBackSprite();
    const char* getCharacterLeftSprite();
    const char* getCharacterRightSprite();
    
    void clearData();
    void playSound(const std::string &name);
    void playMusic(const std::string &name);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
    
    void setSound(bool isSound);
    void setMusic(bool isMusic);
    bool getSound();
    bool getMusic();
    int getMonsterScore();
    
    void setTutorial(bool tutorial);
    bool getTutorial();
};
#endif /* defined(__dotMonster__Player__) */
