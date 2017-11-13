#ifndef __TEXT_DB_H__
#define __TEXT_DB_H__

#include "sqlite3/sqlite3.h"
#include "CocosHeader.h"
#include "Define.h"


class QuestPackData:public Ref
{
public:
    int _no,_type,_questIndex
    , _level,_questType,_status;

    QuestPackData(int no, int type,
                  int questIndex, int level,
                  int questType, int status)
    :_no(no),_type(type),_questIndex(questIndex),
    _level(level),_questType(questType),_status(status)
    {}
};
class TalkData:public Ref
{
public:
    int _no, _type, _talkType,_talkIndex;
    string _talkContent, _talkSprite,_questPackIndex, _talkName;
    TalkData(int no, int type,int talkType, const char *talkContent, const char *talkSprite, const char *questPackIndex, int talkIndex, const char *talkName)
    :_no(no),_type(type),_talkType(talkType),_talkContent(talkContent),_talkSprite(talkSprite),_questPackIndex(questPackIndex), _talkIndex(talkIndex), _talkName(talkName)
    {}
};

class VillageData:public Ref
{
public:
    int _no, _villageType, _houseType;
    string _houseName;
    VillageData(int no, int villageType, int houseType, const char*houseName)
    :_no(no),_villageType(villageType),_houseType(houseType), _houseName(houseName)
    {}
    
};
class EtcTextData:public Ref
{
public:
    int _no;
    string _etcText;
    EtcTextData(int no, const char *etcText)
    :_no(no),_etcText(etcText)
    {}
};
class MiniMapData:public Ref
{
public:
    int _no, _positionX,_positionY;
    string _mapName;
    MiniMapData(int no, const char *mapName, int positionX, int positionY)
    :_no(no),_mapName(mapName),_positionX(positionX),_positionY(positionY)
    {}
};
class ShapeNameData:public Ref
{
public:
    int _no;
    int _type;
    string _firstName1;
    string _firstName2;
    string _firstName3;
    string _midName1;
    string _midName2;
    string _midName3;
    string _lastName1;
    string _lastName2;
    string _lastName3;

    ShapeNameData(int no, int type,const char *firstName1,const char *midName1,const char *lastName1
                  ,const char *firstName2,const char *midName2,const char *lastName2
                  ,const char *firstName3,const char *midName3,const char *lastName3)
    :_no(no),_type(type), _firstName1(firstName1),_midName1(midName1),_lastName1(lastName1),
    _firstName2(firstName2),_midName2(midName2),_lastName2(lastName2),
    _firstName3(firstName3),_midName3(midName3),_lastName3(lastName3)
    {}
};
class ShapeSkillData:public Ref
{
public:
    int _no;
    int _type;
    string _skill1;
    string _skill2;
    string _skill3;
    string _skill4;

    ShapeSkillData(int no, int type,const char *skill1,const char *skill2,const char *skill3,const char *skill4)
    :_no(no),_type(type), _skill1(skill1),_skill2(skill2),_skill3(skill3),_skill4(skill4)
    {}
};
class ItemData:public Ref
{
public:
    enum
    {
        kNotUseType,
        kMapUseType,
        kBattleUseType,
        kAllUseType,
    };
    int _no, _itemType, _itemUseType,_isShop,_isLoon;
    string _itemName;
    string _itemSprite;
    string _itemContent;

    ItemData(int no, int itemType, char *itemName, char *itemSprite, const char *itemContent, int isShop, int itemUseType, int isLoon)
    :_no(no),_itemType(itemType),_itemName(itemName), _itemSprite(itemSprite), _itemContent(itemContent), _isLoon(isLoon)
    ,_isShop(isShop),_itemUseType(itemUseType)
    {}
};

class TextDb:public Node
{
public:
	TextDb();
	~TextDb();
	static TextDb *getInstance();
	static TextDb *_instance;

	string getText(int no);
    string getEtcText(int no);
    VillageData *getVillageData(int type);
    TalkData *getTalkData(int no, int type);
    QuestPackData *getQuestData(int no, int type);
    std::map<unsigned int,TalkData *> &getTalkMap(int type);
    std::map<unsigned int,QuestPackData *> &getQuestPackMap(int type);
    std::map<unsigned int,VillageData *> &getVillageDataMap();
    ItemData *getItemData(int type);
    std::map<unsigned int,ItemData *> &getItemDataMap();
    void runQueryShapeName(int type, std::vector<ShapeNameData> &shapeData);
    void runQueryShapeName(int type, ShapeNameData &shapeData);

    void runQueryShapeSkill(int type, std::vector<ShapeSkillData> &shapeData);
    void runQueryMiniMapData(const string& mapName, MiniMapData &mapData);

private:
	sqlite3 *_pDB;
	sqlite3_stmt *_pStmt;
	sqlite3_stmt* getStmt();

    void loadData();
    void releaseData();
    
    //load data
    void loadTalkData(const char*talkTable, int type, std::map<unsigned int,TalkData *> &mapData);
    void loadVillageTalkData();
    void loadQuestCharacterTalkData();
    void loadQuestPackData(const char*talkTable, std::map<unsigned int,QuestPackData *> &mapData);
    void loadVillageQuestPackData();
    void loadQuestChracterQuestPackData();
    
    void loadItemData();
    void loadVillageData();
    void loadEtcText();

    //releaseData
	void releaseTalkData(std::map<unsigned int,TalkData *> &mapData);
    void releaseQuestPackData(std::map<unsigned int,QuestPackData *> &mapData);
    
    void releaseVillageData();
    void releaseItemData();
    void releaseEtcText();


    //talk Sort
    void talkSort(std::map<unsigned int,TalkData *> &array);

    //Item Data
    std::map<unsigned int,ItemData *> _itemArray;
    
    //Village Data
    std::map<unsigned int,VillageData *> _villageArray;
    
    //Talk Data
    std::map<unsigned int,TalkData *> _chiwooTalkArray;
    std::map<unsigned int,TalkData *> _gaonTalkArray;
    std::map<unsigned int,TalkData *> _heononeTalkArray;
    std::map<unsigned int,TalkData *> _mawoongTalkArray;
    std::map<unsigned int,TalkData *> _mihoTalkArray;
    std::map<unsigned int,TalkData *> _jungTalkArray;
    std::map<unsigned int,TalkData *> _villageTalkArray;
    std::map<unsigned int,TalkData *> _questCharacterTalkArray;
    //Quest Pack Data
    std::map<unsigned int,QuestPackData *> _chiwooQuestPackArray;
    std::map<unsigned int,QuestPackData *> _gaonQuestPackArray;
    std::map<unsigned int,QuestPackData *> _heononeQuestPackArray;
    std::map<unsigned int,QuestPackData *> _mawoongQuestPackArray;
    std::map<unsigned int,QuestPackData *> _mihoQuestPackArray;
    std::map<unsigned int,QuestPackData *> _jungQuestPackArray;
    std::map<unsigned int,QuestPackData *> _villageQuestPackArray;
    std::map<unsigned int,QuestPackData *> _questCharacterQuestPackArray;
    //etc Text
    std::map<unsigned int,EtcTextData *> _etcTextArray;

};

#endif
