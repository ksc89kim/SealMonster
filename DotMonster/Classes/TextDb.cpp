#include "TextDb.h"
#include "TalkLayer.h"
TextDb* TextDb::_instance = nullptr;

TextDb::TextDb()
	:_pDB(NULL),_pStmt(NULL)
{
	log("START TEXTDB");
	int ret = -1;
    string filePath;
    LanguageType ltype = Application::getInstance()->getCurrentLanguage();
    switch (ltype) {
        case LanguageType::KOREAN:
             filePath = "GameDb";
            break;
        case LanguageType::CHINESE:
            filePath = "GameDbChina";
            break;
        default:
            filePath = "GameDbEn";
            break;
    }

	string copyFilePath =  FileUtils::getInstance()->getWritablePath() + "GameDb";
	log("copyFilePath %s", copyFilePath.c_str());
    (&CommonUtils::getInstance())->removeDirWithCopy(ret,copyFilePath, filePath,copyFilePath);
	sqlite3* db = NULL;
	sqlite3* fileDB = 0;

	ret =sqlite3_open(":memory:",&db);
	if(ret != SQLITE_OK)
	{
		log("OPEN : FAIL MEM DB");
		return;
	}

	ret = sqlite3_open(copyFilePath.c_str(), &fileDB);
	if(ret != SQLITE_OK)
	{
		log("OPEN : FAIL FILE DB (DATA MANAGER) , %s",sqlite3_errmsg(fileDB));
		return ;
	}
	sqlite3_backup* backup = sqlite3_backup_init(db,"main",fileDB,"main");
	if(backup)
	{
		sqlite3_backup_step(backup,-1);
		sqlite3_backup_finish(backup);
	}
	ret = sqlite3_errcode(db);

	if(ret == SQLITE_OK)
	{
		sqlite3_close(fileDB);
		log("DB OPEN COMPLETE");
		_pDB = db;
	}
	else
	{
		log("DB ERROR : %s",sqlite3_errmsg(db));
	}
    loadData();
	log("END TEXTDB");
}
TextDb::~TextDb()
{
	releaseData();
	if (_pStmt)
	{
		int ret = sqlite3_finalize(_pStmt);
		CCAssert(ret == SQLITE_OK, "");
	}

	sqlite3_close(_pDB);
}
TextDb *TextDb::getInstance()
{
	if ( _instance == nullptr )
	{
		_instance = new TextDb();
	}
	return _instance;
}
sqlite3_stmt* TextDb::getStmt()
{
	if (_pStmt)
	{
		int ret = sqlite3_reset(_pStmt);
		CCAssert(ret == SQLITE_OK, "");
	}

	return _pStmt;
}
void TextDb::loadData()
{
    loadVillageData();
    
    loadTalkData("chiwooTalk", characterType::kChiwoo,_chiwooTalkArray);
    loadTalkData("gaonTalk", characterType::kGaon,_gaonTalkArray);
    loadTalkData("heononeTalk", characterType::kHeonone,_heononeTalkArray);
    loadTalkData("mihoTalk", characterType::kMiho,_mihoTalkArray);
    loadTalkData("mawoongTalk", characterType::kMawoong,_mawoongTalkArray);
    loadTalkData("jungTalk", characterType::kJung,_jungTalkArray);

    loadVillageTalkData();
    loadQuestCharacterTalkData();

    talkSort(_chiwooTalkArray);
    talkSort(_gaonTalkArray);
    talkSort(_heononeTalkArray);
    talkSort(_mihoTalkArray);
    talkSort(_mawoongTalkArray);
    talkSort(_jungTalkArray);
    talkSort(_villageTalkArray);
    talkSort(_questCharacterTalkArray);
    
    loadQuestPackData("chiwooQuestPack", _chiwooQuestPackArray);
    loadQuestPackData("gaonQuestPack", _gaonQuestPackArray);
    loadQuestPackData("heononeQuestPack", _heononeQuestPackArray);
    loadQuestPackData("mihoQuestPack", _mihoQuestPackArray);
    loadQuestPackData("mawoongQuestPack", _mawoongQuestPackArray);
    loadQuestPackData("jungQuestPack", _jungQuestPackArray);
    loadVillageQuestPackData();
    loadQuestChracterQuestPackData();
    loadItemData();
    loadEtcText();
}
void TextDb::releaseData()
{
    releaseTalkData(_chiwooTalkArray);
    releaseTalkData(_gaonTalkArray);
    releaseTalkData(_heononeTalkArray);
    releaseTalkData(_mihoTalkArray);
    releaseTalkData(_mawoongTalkArray);
    releaseTalkData(_jungTalkArray);
    releaseTalkData(_villageTalkArray);
    releaseTalkData(_questCharacterTalkArray);

    releaseQuestPackData(_chiwooQuestPackArray);
    releaseQuestPackData(_gaonQuestPackArray);
    releaseQuestPackData(_heononeQuestPackArray);
    releaseQuestPackData(_mihoQuestPackArray);
    releaseQuestPackData(_mawoongQuestPackArray);
    releaseQuestPackData(_jungQuestPackArray);
    releaseQuestPackData(_villageQuestPackArray);
    releaseQuestPackData(_questCharacterQuestPackArray);
    releaseVillageData();
    releaseItemData();
    releaseEtcText();
}
void TextDb::loadTalkData(const char *talkTable, int type, std::map<unsigned int, TalkData *> &mapData)
{
    sqlite3_stmt *stmt = getStmt();
    string query = __String::createWithFormat("SELECT * FROM %s ORDER BY no", talkTable)->getCString();
    int ret = sqlite3_prepare_v2(_pDB, query.c_str(), -1, &stmt, NULL);
    CCAssert(ret == SQLITE_OK, "");
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int offset = 0;
        int no = sqlite3_column_int(stmt, offset++);
        int talkType = sqlite3_column_int(stmt, offset++);
        char *talkContent = (char *)sqlite3_column_text(stmt, offset++);
        char *talkSprite = (char *)sqlite3_column_text(stmt, offset++);
        char *questPackIndex = (char *)sqlite3_column_text(stmt, offset++);
        int talkIndex = sqlite3_column_int(stmt, offset++);
        char *talkName = (char *)sqlite3_column_text(stmt, offset++);
        mapData[no] = new TalkData(no,type,talkType,talkContent,talkSprite,questPackIndex,talkIndex,talkName);
    }
}
void TextDb::loadVillageTalkData()
{
    sqlite3_stmt *stmt = getStmt();
    string query = "SELECT * FROM villageTalk ORDER BY no";
    int ret = sqlite3_prepare_v2(_pDB, query.c_str(), -1, &stmt, NULL);
    CCAssert(ret == SQLITE_OK, "");
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int offset = 0;
        int no = sqlite3_column_int(stmt, offset++);
        int houseType = sqlite3_column_int(stmt, offset++);
        int talkType = sqlite3_column_int(stmt, offset++);
        char *talkContent = (char *)sqlite3_column_text(stmt, offset++);
        char *talkSprite = (char *)sqlite3_column_text(stmt, offset++);
        char * questPackIndex = (char *)sqlite3_column_text(stmt, offset++);
        int talkIndex = sqlite3_column_int(stmt, offset++);
        char *talkName = (char *)sqlite3_column_text(stmt, offset++);
        _villageTalkArray[no] = new TalkData(no,houseType,talkType,talkContent,talkSprite,questPackIndex,talkIndex,talkName);
    }
}

void TextDb::loadQuestCharacterTalkData()
{
    sqlite3_stmt *stmt = getStmt();
    string query = "SELECT * FROM questCharacterTalk ORDER BY no";
    int ret = sqlite3_prepare_v2(_pDB, query.c_str(), -1, &stmt, NULL);
    CCAssert(ret == SQLITE_OK, "");
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int offset = 0;
        int no = sqlite3_column_int(stmt, offset++);
        int characterType = sqlite3_column_int(stmt, offset++);
        int talkType = sqlite3_column_int(stmt, offset++);
        char *talkContent = (char *)sqlite3_column_text(stmt, offset++);
        char *talkSprite = (char *)sqlite3_column_text(stmt, offset++);
        char * questPackIndex = (char *)sqlite3_column_text(stmt, offset++);
        int talkIndex = sqlite3_column_int(stmt, offset++);
        char *talkName = (char *)sqlite3_column_text(stmt, offset++);
        _questCharacterTalkArray[no] = new TalkData(no,characterType,talkType,talkContent,talkSprite,questPackIndex,talkIndex,talkName);
    }
}

void TextDb::loadQuestPackData(const char *talkTable, std::map<unsigned int, QuestPackData *> &mapData)
{
    sqlite3_stmt *stmt = getStmt();
    string query = __String::createWithFormat("SELECT * FROM %s ORDER BY no", talkTable)->getCString();
    int ret = sqlite3_prepare_v2(_pDB, query.c_str(), -1, &stmt, NULL);
    CCAssert(ret == SQLITE_OK, "");
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int offset = 0;
        int no = sqlite3_column_int(stmt, offset++);
        int questIndex = sqlite3_column_int(stmt, offset++);
        int level = sqlite3_column_int(stmt, offset++);
        int questType = sqlite3_column_int(stmt, offset++);
        int status = sqlite3_column_int(stmt, offset++);
        mapData[no] = new QuestPackData(no,0,questIndex,level,questType,status);
    }
}
void TextDb::loadVillageQuestPackData()
{
    sqlite3_stmt *stmt = getStmt();
    string query = "SELECT * FROM villageQuestPack ORDER BY no";
    int ret = sqlite3_prepare_v2(_pDB, query.c_str(), -1, &stmt, NULL);
    CCAssert(ret == SQLITE_OK, "");
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int offset = 0;
        int no = sqlite3_column_int(stmt, offset++);
        int villageType = sqlite3_column_int(stmt, offset++);
        int questIndex = sqlite3_column_int(stmt, offset++);
        int level = sqlite3_column_int(stmt, offset++);
        int questType = sqlite3_column_int(stmt, offset++);
        int status = sqlite3_column_int(stmt, offset++);
        _villageQuestPackArray[no] = new QuestPackData(no,villageType,questIndex,level,questType,status);
    }
}
void TextDb::loadQuestChracterQuestPackData()
{
    sqlite3_stmt *stmt = getStmt();
    string query = "SELECT * FROM questCharacterQuestPack ORDER BY no";
    int ret = sqlite3_prepare_v2(_pDB, query.c_str(), -1, &stmt, NULL);
    CCAssert(ret == SQLITE_OK, "");
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int offset = 0;
        int no = sqlite3_column_int(stmt, offset++);
        int characterType = sqlite3_column_int(stmt, offset++);
        int questIndex = sqlite3_column_int(stmt, offset++);
        int level = sqlite3_column_int(stmt, offset++);
        int questType = sqlite3_column_int(stmt, offset++);
        int status = sqlite3_column_int(stmt, offset++);
        _questCharacterQuestPackArray[no] = new QuestPackData(no,characterType,questIndex,level,questType,status);
    }
}

void TextDb::loadItemData()
{
    sqlite3_stmt *stmt = getStmt();
    string query = "SELECT * FROM Item ORDER BY no";
    int ret = sqlite3_prepare_v2(_pDB, query.c_str(), -1, &stmt, NULL);
    CCAssert(ret == SQLITE_OK, "");
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int offset = 0;
        int no = sqlite3_column_int(stmt, offset++);
        int itemType = sqlite3_column_int(stmt, offset++);
        char *itemName = (char *)sqlite3_column_text(stmt, offset++);
        char *itemSprite = (char *)sqlite3_column_text(stmt, offset++);
        int isShop = sqlite3_column_int(stmt, offset++);
        int itemUseType = sqlite3_column_int(stmt, offset++);
        char *itemContent = (char *)sqlite3_column_text(stmt, offset++);
        int isLoon = sqlite3_column_int(stmt, offset++);

        log("--------itemType-------");
        log("no = %d,",no);
        log("itemType = %d,",itemType);
        log("itemName = %s,",itemName);
        log("itemSprite = %s,",itemSprite);
        log("--------itemType-------");
        _itemArray[no] = new ItemData(no,itemType,itemName,itemSprite,itemContent,isShop,itemUseType,isLoon);
    }
}
void TextDb::loadVillageData()
{
    sqlite3_stmt *stmt = getStmt();
    string query = "SELECT * FROM village ORDER BY no";
    int ret = sqlite3_prepare_v2(_pDB, query.c_str(), -1, &stmt, NULL);
    CCAssert(ret == SQLITE_OK, "");
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int offset = 0;
        int no = sqlite3_column_int(stmt, offset++);
        int villageType = sqlite3_column_int(stmt, offset++);
        int houseType = sqlite3_column_int(stmt, offset++);
        char *houseName = (char *)sqlite3_column_text(stmt, offset++);
        _villageArray[no] = new VillageData(no,villageType,houseType,houseName);
    }
}
void TextDb::loadEtcText()
{
    sqlite3_stmt *stmt = getStmt();
    string query = "SELECT * FROM etcText ORDER BY no";
    int ret = sqlite3_prepare_v2(_pDB, query.c_str(), -1, &stmt, NULL);
    CCAssert(ret == SQLITE_OK, "");
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int offset = 0;
        int no = sqlite3_column_int(stmt, offset++);
        char *etcText = (char *)sqlite3_column_text(stmt, offset++);
        _etcTextArray[no] = new EtcTextData(no,etcText);
    }
}
void TextDb::releaseTalkData(std::map<unsigned int, TalkData *> &mapData)
{
    for (std::map<unsigned int, TalkData*>::iterator it = mapData.begin(); it != mapData.end(); it++)
    {
        delete it->second;
    }
    mapData.clear();
}
void TextDb::releaseQuestPackData(std::map<unsigned int, QuestPackData *> &mapData)
{
    for (std::map<unsigned int, QuestPackData*>::iterator it = mapData.begin(); it != mapData.end(); it++)
    {
        delete it->second;
    }
    mapData.clear();
}
void TextDb::releaseVillageData()
{
    for (std::map<unsigned int, VillageData*>::iterator it = _villageArray.begin(); it != _villageArray.end(); it++)
    {
        delete it->second;
    }
    _villageArray.clear();
}
void TextDb::releaseItemData()
{
    for (std::map<unsigned int, ItemData*>::iterator it = _itemArray.begin(); it != _itemArray.end(); it++)
    {
        delete it->second;
    }
    _itemArray.clear();
}
void TextDb::releaseEtcText()
{
    for (std::map<unsigned int, EtcTextData*>::iterator it = _etcTextArray.begin(); it != _etcTextArray.end(); it++)
    {
        delete it->second;
    }
    _etcTextArray.clear();
}
void TextDb::runQueryShapeName(int type, std::vector<ShapeNameData> &shapeData)
{
    sqlite3_stmt *stmt = getStmt();
    string query = __String::createWithFormat("SELECT * FROM shapeName WHERE changeType = %d",type)->getCString();
    int ret = sqlite3_prepare_v2(_pDB, query.c_str(), -1, &stmt, NULL);
    CCAssert(ret == SQLITE_OK, "");
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int offset = 0;
        int no = sqlite3_column_int(stmt, offset++);
        int type = sqlite3_column_int(stmt, offset++);
        char *firsttName1 = (char *)sqlite3_column_text(stmt, offset++);
        char *midName1 = (char *)sqlite3_column_text(stmt, offset++);
        char *lastName1 = (char *)sqlite3_column_text(stmt, offset++);
        char *firsttName2 = (char *)sqlite3_column_text(stmt, offset++);
        char *midName2 = (char *)sqlite3_column_text(stmt, offset++);
        char *lastName2 = (char *)sqlite3_column_text(stmt, offset++);
        char *firsttName3 = (char *)sqlite3_column_text(stmt, offset++);
        char *midName3 = (char *)sqlite3_column_text(stmt, offset++);
        char *lastName3 = (char *)sqlite3_column_text(stmt, offset++);
        shapeData.push_back(ShapeNameData(no,type,firsttName1,midName1,lastName1,
                                          firsttName2,midName2,lastName2,
                                          firsttName3,midName3,lastName3));
    }
}
void TextDb::runQueryShapeName(int type, ShapeNameData &shapeData)
{
    sqlite3_stmt *stmt = getStmt();
    string query = __String::createWithFormat("SELECT * FROM shapeName WHERE changeType = %d",type)->getCString();
    int ret = sqlite3_prepare_v2(_pDB, query.c_str(), -1, &stmt, NULL);
    CCAssert(ret == SQLITE_OK, "");
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int offset = 0;
        int no = sqlite3_column_int(stmt, offset++);
        int type = sqlite3_column_int(stmt, offset++);
        char *firsttName1 = (char *)sqlite3_column_text(stmt, offset++);
        char *midName1 = (char *)sqlite3_column_text(stmt, offset++);
        char *lastName1 = (char *)sqlite3_column_text(stmt, offset++);
        char *firsttName2 = (char *)sqlite3_column_text(stmt, offset++);
        char *midName2 = (char *)sqlite3_column_text(stmt, offset++);
        char *lastName2 = (char *)sqlite3_column_text(stmt, offset++);
        char *firsttName3 = (char *)sqlite3_column_text(stmt, offset++);
        char *midName3 = (char *)sqlite3_column_text(stmt, offset++);
        char *lastName3 = (char *)sqlite3_column_text(stmt, offset++);
        shapeData._no = no;
        shapeData._type = type;
        shapeData._firstName1 = firsttName1;
        shapeData._firstName2 = firsttName2;
        shapeData._firstName3 = firsttName3;
        shapeData._midName1 = midName1;
        shapeData._midName2 = midName2;
        shapeData._midName3 = midName3;
        shapeData._lastName1 = lastName1;
        shapeData._lastName2 = lastName2;
        shapeData._lastName3 = lastName3;
        break;
    }
}

void TextDb::runQueryShapeSkill(int type, std::vector<ShapeSkillData> &shapeData)
{
    sqlite3_stmt *stmt = getStmt();
    string query = __String::createWithFormat("SELECT * FROM skillName WHERE type = %d",type)->getCString();
    int ret = sqlite3_prepare_v2(_pDB, query.c_str(), -1, &stmt, NULL);
    CCAssert(ret == SQLITE_OK, "");
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int offset = 0;
        int no = sqlite3_column_int(stmt, offset++);
        int type = sqlite3_column_int(stmt, offset++);
        char *skill1 = (char *)sqlite3_column_text(stmt, offset++);
        char *skill2 = (char *)sqlite3_column_text(stmt, offset++);
        char *skill3 = (char *)sqlite3_column_text(stmt, offset++);
        char *skill4 = (char *)sqlite3_column_text(stmt, offset++);
        shapeData.push_back(ShapeSkillData(no,type,skill1,skill2,skill3,skill4));
    }
}

void TextDb::runQueryMiniMapData(const string& mapName, MiniMapData &mapData)
{
    sqlite3_stmt *stmt = getStmt();
    string query = __String::createWithFormat("SELECT * FROM miniMapData WHERE mapName = \"%s\"",mapName.c_str())->getCString();
    int ret = sqlite3_prepare_v2(_pDB, query.c_str(), -1, &stmt, NULL);
    CCAssert(ret == SQLITE_OK, "");
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int offset = 0;
        int no = sqlite3_column_int(stmt, offset++);
        char *mapNameData = (char *)sqlite3_column_text(stmt, offset++);
        int positionX = sqlite3_column_int(stmt, offset++);
        int positionY = sqlite3_column_int(stmt, offset++);
        mapData._no = no;
        mapData._mapName = mapNameData;
        mapData._positionX = positionX;
        mapData._positionY = positionY;
        break;
    }
}
string TextDb::getEtcText(int no)
{
    EtcTextData *ret = nullptr;
    std::map<unsigned int, EtcTextData*>::iterator it = _etcTextArray.find(no);
    if (it != _etcTextArray.end())
    {
        ret = _etcTextArray[no];
    }
    if(ret)
        return ret->_etcText;
    return "";
}
TalkData *TextDb::getTalkData(int no ,int type)
{
    TalkData *ret = nullptr;
    std::map<unsigned int, TalkData*> array = getTalkMap(type);
    std::map<unsigned int, TalkData*>::iterator it = array.find(no);
    if (it != array.end())
    {
        ret = array[no];
    }
    return ret;
}
QuestPackData *TextDb::getQuestData(int no, int type)
{
    QuestPackData *ret = nullptr;
    std::map<unsigned int, QuestPackData*> array = getQuestPackMap(type);
    std::map<unsigned int, QuestPackData*>::iterator it = array.find(no);
    if (it != array.end())
    {
        ret = array[no];
    }
    return ret;
}
VillageData *TextDb::getVillageData(int type)
{
    for(int i=1;i<_villageArray.size();i++)
    {
        VillageData *data = _villageArray[i];
        if(type==data->_houseType)
        {
            return data;
        }
    }
    return nullptr;
}

std::map<unsigned int,TalkData *> &TextDb::getTalkMap(int type)
{
    switch(type)
    {
        case characterType::kChiwoo:
            return _chiwooTalkArray;
            break;
        case characterType::kGaon:
            return _gaonTalkArray;
            break;
        case characterType::kHeonone:
            return _heononeTalkArray;
            break;
        case characterType::kMiho:
            return _mihoTalkArray;
            break;
        case characterType::kMawoong:
            return _mawoongTalkArray;
            break;
        case characterType::kJung:
            return _jungTalkArray;
            break;
        default:
        {
            if(9999<type) //type 10000 이상 퀘스트 캐릭터.
            {
                return _questCharacterTalkArray;
            }
            else
            {
                return _villageTalkArray;
            }
        }
            break;
    }
    std::map<unsigned int, TalkData*> array;
    return array;
}
std::map<unsigned int,QuestPackData *> &TextDb::getQuestPackMap(int type)
{
    switch(type)
    {
        case characterType::kChiwoo:
             return _chiwooQuestPackArray;
            break;
        case characterType::kHeonone:
            return _heononeQuestPackArray;
            break;
        case characterType::kGaon:
            return _gaonQuestPackArray;
            break;
        case characterType::kMiho:
            return _mihoQuestPackArray;
            break;
        case characterType::kMawoong:
             return _mawoongQuestPackArray;
            break;
        case characterType::kJung:
            return _jungQuestPackArray;
            break;
        default:
        {
            if(9999<type) //type 10000 이상 퀘스트 캐릭터
            {
                return _questCharacterQuestPackArray;
            }
            else
            {
                return _villageQuestPackArray;
            }
        }
            break;
    }
    std::map<unsigned int,QuestPackData *> array;
    return array;
}
std::map<unsigned int,VillageData *> &TextDb::getVillageDataMap()
{
    return _villageArray;
}
ItemData *TextDb::getItemData(int type)
{
    for(int i=1;i<=_itemArray.size();i++)
    {
        ItemData *data = _itemArray[i];
        if(type==data->_itemType)
        {
            return data;
        }
    }
    return nullptr;
}
std::map<unsigned int,ItemData *> &TextDb::getItemDataMap()
{
    return _itemArray;
}
void TextDb::talkSort(std::map<unsigned int,TalkData *> &array)
{
    std::map<unsigned int,TalkData *> sortTalkContainer;
    int maxIndex = 0;
    for(int i=1;i<=array.size();i++)
    {
        TalkData *talk = array[i];
        if(talk->_talkIndex>maxIndex)
            maxIndex = talk->_talkIndex;
    }
    int index = 1;
    for(int i=1;i<=maxIndex;i++)
    {
        for(int v=talkType::ktalkStart;v<=talkType::ktalkBaseFinish;v++)
        {
            int type = TalkContainer::changeTalkType(v);
            for(int j=1;j<=array.size();j++)
            {
                TalkData *talk = array[j];
                if(type==talk->_talkType && i == talk->_talkIndex)
                {
                    sortTalkContainer[index] = talk;
                    index++;
                }
            }
        }
    }
    array.clear();
    for(int i=1;i<=sortTalkContainer.size();i++)
    {
        array[i] = sortTalkContainer[i];
    }
}


