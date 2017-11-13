//
//  Character.h
//  dotMonster
//
//  Created by 김선철 on 2014. 11. 15..
//
//

#ifndef __dotMonster__Character__
#define __dotMonster__Character__

#include "Define.h"

class Character:public Node
{
protected:
    int _characterType;
    std::string _mapSprite;
public:
    
    Vector<Ref *> *_monsterList;
    Character();
   ~Character();
    
    static Character* create();
    void setImage();
    void setValue();
    
    const char* getCharacterMapSprite();
    int getCharacterType();
    void setCharacterType(int type);
    void recoveryMonster();
    void dieRecoveryMonster();
    void initDataMonster();
    int getMaxLevelMonster();
    int getSelectMaxLevelMonster();

};

#endif /* defined(__dotMonster__Character__) */
