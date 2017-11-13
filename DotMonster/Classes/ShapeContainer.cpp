//
//  ShapeContainer.cpp
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 9..
//
//

#include "ShapeContainer.h"
#include "ShapeObject.h"
#include "TextDb.h"

static ShapeNameContainer *_shapeNameContainer = NULL;
static ShapeSkillContainer *_shapeSkillContainer = NULL;

ShapeNameContainer::ShapeNameContainer()
{

    _containerShapeF = new Vector<Ref *>();
    _containerShapeW = new Vector<Ref *>();
    _containerShapeT = new Vector<Ref *>();
    _containerShapeI = new Vector<Ref *>();
    _containerShapeZ = new Vector<Ref *>();
}

ShapeNameContainer::~ShapeNameContainer()
{
    if(_containerShapeF)
    {
        delete _containerShapeF;
    }
    if(_containerShapeW)
    {
        delete _containerShapeW;
    }
    if(_containerShapeT)
    {
        delete _containerShapeT;
    }
    if(_containerShapeI)
    {
        delete _containerShapeI;
    }
    if(_containerShapeZ)
    {
        delete _containerShapeZ;
    }
}
ShapeNameContainer *ShapeNameContainer::getInstance()
{
    if(!_shapeNameContainer)
	{
		_shapeNameContainer = new ShapeNameContainer();
        _shapeNameContainer->setShapeFName();
        _shapeNameContainer->setShapeWName();
        _shapeNameContainer->setShapeTName();
        _shapeNameContainer->setShapeIName();
        _shapeNameContainer->setShapeZNmae();
	}
	return _shapeNameContainer;
}

void ShapeNameContainer::setShapeFName()
{
    int index = 0;
    /*
    addName(shapeType::kShapeF,index++,"아","로","몬","록" ,"산더", "르","이", "프리", "트"); //1   S
    addName(shapeType::kShapeF,index++,"브","릭","툴","휴", "반", "테", "샐", "러맨", "더"); //2   S
    addName(shapeType::kShapeF,index++,"바","라","론","볼","케","이", "볼", "케이", "노"); //3   A
    addName(shapeType::kShapeF,index++,"발","락","디","브", "레", "드", "피", "닉", "스"); //4  A
    addName(shapeType::kShapeF,index++,"디","블로","아","랜", "투", "유" ,"주", "화", "작"); //5 B
    addName(shapeType::kShapeF,index++,"알","렉스","투","푸","르","미","파", "이어", "건"); //6   B
    addName(shapeType::kShapeF,index++,"헬","포","무","시","나","브", "라", "이", "드"); //7    C
    addName(shapeType::kShapeF,index++,"하","야로","비","브", "라이", "언","리", "자", "신"); //8 C
    addName(shapeType::kShapeF,index++,"파","와","우","가","우", "리","헤", "스티", "아"); //9   D
    addName(shapeType::kShapeF,index++,"퓨","리","오","바","라","몽","레", "카놀", "어"); //10   D
     */
    vector<ShapeNameData> shapeText;
    TextDb::getInstance()->runQueryShapeName(shapeType::kShapeF, shapeText);
    for(int i=0;i<shapeText.size();i++)
    {
        ShapeNameData data = shapeText.at(i);
        addName(shapeType::kShapeF,index++,data._firstName1.c_str(),data._midName1.c_str(),data._lastName1.c_str(),
                data._firstName2.c_str() ,data._midName2.c_str(), data._lastName2.c_str(),data._firstName3.c_str(), data._midName3.c_str(),
                data._lastName3.c_str());
    }
    
}
void ShapeNameContainer::setShapeWName()
{
    int index = 0;
    /*
    addName(shapeType::kShapeW,index++,"레일","랑","주","베일" ,"르", "쟝","아스", "타르", "테"); //1   S
    addName(shapeType::kShapeW,index++,"로","베리","루","나르", "줄", "송", "포", "세이", "돈"); //2   S
    addName(shapeType::kShapeW,index++,"루","비디","본","수","상","치", "이", "슈", "타르"); //3   A
    addName(shapeType::kShapeW,index++,"블","레","디","유", "수", "성", "암", "피트", "리테"); //4  A
    addName(shapeType::kShapeW,index++,"라블","로","워터","블", "랙", "핸드" ,"네레", "우", "스"); //5 B
    addName(shapeType::kShapeW,index++,"랜","디","포","매","우","몰","프루", "나", "진"); //6   B
    addName(shapeType::kShapeW,index++,"바흐","마흐","창","마일","류","호", "아", "니", "마"); //7    C
    addName(shapeType::kShapeW,index++,"워","터","볼","물", "아", "진","플루", "토", "르"); //8 C
    addName(shapeType::kShapeW,index++,"블론","베르","맨","아쿠","논", "아","테", "티", "스"); //9   D
    addName(shapeType::kShapeW,index++,"유리","우","손","호수","청","용","팔", "라이", "몬"); //10   D
    */
    vector<ShapeNameData> shapeText;
    TextDb::getInstance()->runQueryShapeName(shapeType::kShapeW, shapeText);
    for(int i=0;i<shapeText.size();i++)
    {
        ShapeNameData data = shapeText.at(i);
        addName(shapeType::kShapeW,index++,data._firstName1.c_str(),data._midName1.c_str(),data._lastName1.c_str(),
                data._firstName2.c_str() ,data._midName2.c_str(), data._lastName2.c_str(),data._firstName3.c_str(), data._midName3.c_str(),
                data._lastName3.c_str());
    }

}
void ShapeNameContainer::setShapeTName()
{
    int index = 0;
    /*
    addName(shapeType::kShapeT,index++,"클라","리세","이지","클루" ,"라이", "징","클라", "우", "드"); //1   S
    addName(shapeType::kShapeT,index++,"캐","모","마일","카이", "문", "메일", "카이", "문", "마르"); //2   S
    addName(shapeType::kShapeT,index++,"로","즈","마리","루이","마","리", "루이", "메", "리"); //3   A
    addName(shapeType::kShapeT,index++,"페","퍼","민트","페", "퍼", "맨트", "페퍼", "리", "우스"); //4  A
    addName(shapeType::kShapeT,index++,"메리","골","드","블랙", "골", "드" ,"블랜", "골", "드"); //5 B
    addName(shapeType::kShapeT,index++,"금","잔","화","금","수","화","금", "수", "혼"); //6   B
    addName(shapeType::kShapeT,index++,"어","리","연","오","루","연", "아", "랑", "연"); //7    C
    addName(shapeType::kShapeT,index++,"히","아","신스","히", "바", "신스","히", "바", "신"); //8 C
    addName(shapeType::kShapeT,index++,"칼랑","코","에","칼링","쿠", "바","칼링", "쿠", "바티"); //9   D
    addName(shapeType::kShapeT,index++,"데","이","지","데","이브","존","데", "이블", "존"); //10   D
    */
    vector<ShapeNameData> shapeText;
    TextDb::getInstance()->runQueryShapeName(shapeType::kShapeT, shapeText);
    for(int i=0;i<shapeText.size();i++)
    {
        ShapeNameData data = shapeText.at(i);
        addName(shapeType::kShapeT,index++,data._firstName1.c_str(),data._midName1.c_str(),data._lastName1.c_str(),
                data._firstName2.c_str() ,data._midName2.c_str(), data._lastName2.c_str(),data._firstName3.c_str(), data._midName3.c_str(),
                data._lastName3.c_str());
    }
}
void ShapeNameContainer::setShapeIName()
{
    
}
void ShapeNameContainer::setShapeZNmae()
{
    
}
void ShapeNameContainer::addName(int shapeType, int classNumber, const char*firstName1, const char*midName1, const char*lastName1, const char*firstName2, const char*midName2, const char*lastName2,const char*firstName3, const char*midName3, const char*lastName3)
{
    Vector<Ref *> *nameArray = getShapeArray(shapeType);
    ShapeName *object = ShapeName::create(firstName1,midName1, lastName1, classNumber);
    object->_class2 = ShapeName::create(firstName2, midName2, lastName2, classNumber);
    object->addChild(object->_class2);
    object->_class3 = ShapeName::create(firstName3,midName3, lastName3, classNumber);
    object->addChild(object->_class3);
    nameArray->pushBack(object);
}
ShapeName *ShapeNameContainer::getRandShapeName(int shapeType)
{
    Vector<Ref *> *nameArray = getShapeArray(shapeType);
    return  (ShapeName *)nameArray->at(arc4random()%nameArray->size());
}
ShapeName *ShapeNameContainer::getRandShapeName(int shapeType, int minRandLevel, int maxRandLevel)
{
    Vector<Ref *> *nameArray = getShapeArray(shapeType);
    int deffrent = maxRandLevel-minRandLevel;
    if(maxRandLevel<nameArray->size())
        if(deffrent>0)
            return  (ShapeName *)nameArray->at(minRandLevel+(arc4random()%(deffrent+1)));
        else
            return  (ShapeName *)nameArray->at(maxRandLevel);
    else
        return nullptr;

}
ShapeName *ShapeNameContainer::getFindShapeName(int shapeType, int index)
{
    Vector<Ref *> *nameArray = getShapeArray(shapeType);
    return (ShapeName *)nameArray->at(index);
}

bool ShapeNameContainer::checkFirstName(int shapeType,const char*name)
{
    Vector<Ref *> *nameArray = getShapeArray(shapeType);
    bool isCheck = false;
    for(int i=0;i<nameArray->size();i++){
        ShapeName *object = (ShapeName *)nameArray->at(i);
        if(!strcmp(object->getFirstName(), name))
        {
            isCheck = true;
            break;
        }
    }
    return isCheck;
}

bool ShapeNameContainer::checkMidName(int shapeType,const char*name)
{
    Vector<Ref *> *nameArray = getShapeArray(shapeType);
    bool isCheck = false;
    for(int i=0;i<nameArray->size();i++){
        ShapeName *object = (ShapeName *)nameArray->at(i);
        if(!!strcmp(object->getMidName(), name))
        {
            isCheck = true;
            break;
        }
    }
    return isCheck;
}
bool ShapeNameContainer::checkLastName(int shapeType,const char*name)
{
    Vector<Ref *> *nameArray = getShapeArray(shapeType);
    bool isCheck = false;
    for(int i=0;i<nameArray->size();i++){
        ShapeName *object = (ShapeName *)nameArray->at(i);
        if(!!strcmp(object->getLastName(), name))
        {
            isCheck = true;
            break;
        }
    }
    return isCheck;
}
Vector<Ref *> *ShapeNameContainer::getShapeArray(int shapeType)
{
    //    Vector<Ref *> empty;
    switch (shapeType) {
        case shapeType::kShapeF:
            return _containerShapeF;
            break;
        case shapeType::kShapeW:
            return _containerShapeW;
            break;
        case shapeType::kShapeT:
            return _containerShapeT;
            break;
        case shapeType::kShapeZ:
            return _containerShapeZ;
            break;
        case shapeType::kShapeI:
            return _containerShapeI;
            break;
        default:
            break;
    }
    //    return empty;
}



//skill

ShapeSkillContainer *ShapeSkillContainer::getInstance()
{
    if(!_shapeSkillContainer)
	{
		_shapeSkillContainer= new ShapeSkillContainer();
        _shapeSkillContainer->setShapeFSkill();
        _shapeSkillContainer->setShapeWSkill();
        _shapeSkillContainer->setShapeTSkill();
        _shapeSkillContainer->setShapeISkill();
        _shapeSkillContainer->setShapeZSkill();
	}
	return _shapeSkillContainer;
}

void ShapeSkillContainer::addSkill(int shapeType, std::string skillName1, std::string animationName1, int skillType1, std::string skillName2, std::string animationName2, int skillType2, std::string skillName3, std::string animationName3, int skillType3, std::string skillName4,std::string animationName4, int skillType4)
{
    Vector<Ref *> *skillArray = getShapeArray(shapeType);
    ShapeObject *skillObject = ShapeObject::create();
    skillObject->_skill1 = ShapeSkill::create(skillType1, 1, skillName1,animationName1);
    skillObject->addChild(skillObject->_skill1);
    skillObject->_skill2 = ShapeSkill::create(skillType2, 2, skillName2,animationName2);
    skillObject->addChild(skillObject->_skill2);
    skillObject->_skill3 = ShapeSkill::create(skillType3, 3, skillName3,animationName3);
    skillObject->addChild(skillObject->_skill3);
    skillObject->_skill4 = ShapeSkill::create(skillType4, 4, skillName4,animationName4);
    skillObject->addChild(skillObject->_skill4);
    skillArray->pushBack(skillObject);
}
ShapeSkillContainer::ShapeSkillContainer()
{
    _containerShapeSkillF = new Vector<Ref *>();
    _containerShapeSkillW = new Vector<Ref *>();
    _containerShapeSkillT = new Vector<Ref *>();
    _containerShapeSkillI = new Vector<Ref *>();
    _containerShapeSkillZ = new Vector<Ref *>();

}

ShapeSkillContainer::~ShapeSkillContainer()
{
   
    if(_containerShapeSkillF)
    {
        delete _containerShapeSkillF;
    }
    if(_containerShapeSkillW)
    {
        delete _containerShapeSkillW;
    }
    if(_containerShapeSkillT)
    {
        delete _containerShapeSkillT;
    }
    if(_containerShapeSkillI)
    {
        delete _containerShapeSkillI;
    }
    if(_containerShapeSkillZ)
    {
        delete _containerShapeSkillZ;
    }

}
void ShapeSkillContainer::setShapeFSkill()
{
    /*
    addSkill(shapeType::kShapeF,"돌격",getShapeFile(shapeType::kShapeF,"FS1-1-"),animationType::kAttack,"반사",getShapeFile(shapeType::kShapeF,"FS1-2-"),animationType::kReflect,"불의용",
             getShapeFile(shapeType::kShapeF,"FS1-3-"),animationType::kAttributeAttack,"주작의분노",getShapeFile(shapeType::kShapeF,"FS1-4-"),animationType::kAttributeAttack); //1   S
    addSkill(shapeType::kShapeF,"돌격",getShapeFile(shapeType::kShapeF,"FS2-1-"),animationType::kAttack,"불꽃뿌리기",getShapeFile(shapeType::kShapeF,"FS2-2-"),animationType::kStopTurn,
             "불의시작",getShapeFile(shapeType::kShapeF,"FS2-3-"),animationType::kAttributeAttack,"헬파이어",getShapeFile(shapeType::kShapeF,"FS2-4-"),animationType::kAttributeAttack); //2   S
    
    addSkill(shapeType::kShapeF,"돌격",getShapeFile(shapeType::kShapeF,"FS3-1-"),animationType::kAttack,"불의인장",getShapeFile(shapeType::kShapeF,"FS3-2-"),animationType::kDebufTurn,
             "아홉가지의 불",getShapeFile(shapeType::kShapeF,"FS3-3-"),animationType::kAttributeAttack,"메테오",getShapeFile(shapeType::kShapeF,"FS3-4-"),animationType::kAttributeAttack); //3   A
    
    addSkill(shapeType::kShapeF,"돌격",getShapeFile(shapeType::kShapeF,"FS4-1-"),animationType::kAttack,"흔들기",getShapeFile(shapeType::kShapeF,"FS4-2-"),animationType::kDebufTurn,
             "불꽃회오리",getShapeFile(shapeType::kShapeF,"FS4-3-"),animationType::kAttributeAttack,"용암의힘",getShapeFile(shapeType::kShapeF,"FS4-4-"),animationType::kAttributeAttack); //4  A
    
    addSkill(shapeType::kShapeF,"돌격",getShapeFile(shapeType::kShapeF,"FS5-1-"),animationType::kAttack,"소리치기",getShapeFile(shapeType::kShapeF,"FS5-2-"),animationType::kStopTurn,
             "불꽃손톱",getShapeFile(shapeType::kShapeF,"FS5-3-"),animationType::kAttributeAttack,"불의바램",getShapeFile(shapeType::kShapeF,"FS5-4-"),animationType::kAttributeAttack); //5 B
    
    addSkill(shapeType::kShapeF,"박치기",getShapeFile(shapeType::kShapeF,"FS6-1-"),animationType::kAttack,"최면술",getShapeFile(shapeType::kShapeF,"FS6-2-"),animationType::kStopTurn,
             "불꽃발톱",getShapeFile(shapeType::kShapeF,"FS6-3-"),animationType::kAttributeAttack,"불의악몽",getShapeFile(shapeType::kShapeF,"FS6-4-"),animationType::kAttributeAttack); //6   B
    
    addSkill(shapeType::kShapeF,"박치기",getShapeFile(shapeType::kShapeF,"FS7-1-"),animationType::kAttack,"반사",getShapeFile(shapeType::kShapeF,"FS7-2-"),animationType::kReflect,
             "불의일격",getShapeFile(shapeType::kShapeF,"FS7-3-"),animationType::kAttributeAttack,"불의소용돌이",getShapeFile(shapeType::kShapeF,"FS7-4-"),animationType::kAttributeAttack); //7    C
    
    addSkill(shapeType::kShapeF,"박치기",getShapeFile(shapeType::kShapeF,"FS8-1-"),animationType::kAttack,"깜짝 기습",getShapeFile(shapeType::kShapeF,"FS8-2-"),animationType::kDebufTurn,
             "불꽃씨앗",getShapeFile(shapeType::kShapeF,"FS8-3-"),animationType::kAttributeAttack,"불의눈물",getShapeFile(shapeType::kShapeF,"FS8-4-"),animationType::kAttributeAttack); //8 C
    
    addSkill(shapeType::kShapeF,"박치기",getShapeFile(shapeType::kShapeF,"FS9-1-"),animationType::kAttack,"숨쉬는 불",getShapeFile(shapeType::kShapeF,"FS9-2-"),animationType::kDebufTurn,
             "불의손길",getShapeFile(shapeType::kShapeF,"FS9-3-"),animationType::kAttributeAttack,"불의폭격",getShapeFile(shapeType::kShapeF,"FS9-4-"),animationType::kAttributeAttack); //9   D
    
    addSkill(shapeType::kShapeF,"박치기",getShapeFile(shapeType::kShapeF,"FS10-1-"),animationType::kAttack,"보이지 않는 손",getShapeFile(shapeType::kShapeF,"FS10-2-"),animationType::kDebufTurn,
             "불의눈길",getShapeFile(shapeType::kShapeF,"FS10-3-"),animationType::kAttributeAttack,"불의기적",getShapeFile(shapeType::kShapeF,"FS10-4-"),animationType::kAttributeAttack); //10   D
    */
    
    vector<ShapeSkillData> shapeText;
    TextDb::getInstance()->runQueryShapeSkill(shapeType::kShapeF, shapeText);
    for(int i=0;i<shapeText.size();i++)
    {
        ShapeSkillData data = shapeText.at(i);
        string skillImageFirst = __String::createWithFormat("FS%d-1-",i+1)->getCString();
        string skillImageTwo = __String::createWithFormat("FS%d-2-",i+1)->getCString();
        string skillImageThree = __String::createWithFormat("FS%d-3-",i+1)->getCString();
        string skillImageFour = __String::createWithFormat("FS%d-4-",i+1)->getCString();

        switch (i+1) {
            case 1:
            case 7:
            {
                addSkill(shapeType::kShapeF,data._skill1.c_str(),getShapeFile(shapeType::kShapeF,skillImageFirst.c_str()),animationType::kAttack,data._skill2.c_str(),getShapeFile(shapeType::kShapeF,skillImageTwo.c_str()),animationType::kReflect,data._skill3.c_str(), getShapeFile(shapeType::kShapeF,skillImageThree.c_str()),animationType::kAttributeAttack,data._skill4.c_str(),getShapeFile(shapeType::kShapeF,skillImageFour.c_str()),animationType::kAttributeAttack); //1
                break;
            }
            case 2:
            case 5:
            case 6:
            {
                addSkill(shapeType::kShapeF,data._skill1.c_str(),getShapeFile(shapeType::kShapeF,skillImageFirst.c_str()),animationType::kAttack,data._skill2.c_str(),getShapeFile(shapeType::kShapeF,skillImageTwo.c_str()),animationType::kStopTurn,data._skill3.c_str(), getShapeFile(shapeType::kShapeF,skillImageThree.c_str()),animationType::kAttributeAttack,data._skill4.c_str(),getShapeFile(shapeType::kShapeF,skillImageFour.c_str()),animationType::kAttributeAttack); //1
                break;
            }
            default:
            {
                addSkill(shapeType::kShapeF,data._skill1.c_str(),getShapeFile(shapeType::kShapeF,skillImageFirst.c_str()),animationType::kAttack,data._skill2.c_str(),getShapeFile(shapeType::kShapeF,skillImageTwo.c_str()),animationType::kDebufTurn,data._skill3.c_str(), getShapeFile(shapeType::kShapeF,skillImageThree.c_str()),animationType::kAttributeAttack,data._skill4.c_str(),getShapeFile(shapeType::kShapeF,skillImageFour.c_str()),animationType::kAttributeAttack); //1
                break;
            }
        }
        
    }
    
}
void ShapeSkillContainer::setShapeWSkill()
{
    /*
    addSkill(shapeType::kShapeW,"돌격",getShapeFile(shapeType::kShapeW,"WS1-1-"),animationType::kAttack,"반사",getShapeFile(shapeType::kShapeW,"WS1-2-"),animationType::kReflect,
             "수룡의힘",getShapeFile(shapeType::kShapeW,"WS1-3-"),animationType::kAttributeAttack,"해일",getShapeFile(shapeType::kShapeW,"WS1-4-"),animationType::kAttributeAttack); //1   S
    addSkill(shapeType::kShapeW,"돌격",getShapeFile(shapeType::kShapeW,"WS2-1-"),animationType::kAttack,"물의장막",getShapeFile(shapeType::kShapeW,"WS2-2-"),animationType::kStopTurn,
             "홍수",getShapeFile(shapeType::kShapeW,"WS2-3-"),animationType::kAttributeAttack,"레비아탄의 분노",getShapeFile(shapeType::kShapeW,"WS2-4-"),animationType::kAttributeAttack); //2   S
    addSkill(shapeType::kShapeW,"돌격",getShapeFile(shapeType::kShapeW,"WS3-1-"),animationType::kAttack,"물의저주",getShapeFile(shapeType::kShapeW,"WS3-2-"),animationType::kDebufTurn,
             "워터 스워드",getShapeFile(shapeType::kShapeW,"WS3-3-"),animationType::kAttributeAttack,"용오름",getShapeFile(shapeType::kShapeW,"WS3-4-"),animationType::kAttributeAttack); //3   A
    addSkill(shapeType::kShapeW,"돌격",getShapeFile(shapeType::kShapeW,"WS4-1-"),animationType::kAttack,"물치기",getShapeFile(shapeType::kShapeW,"WS4-2-"),animationType::kDebufTurn,
             "강의유속",getShapeFile(shapeType::kShapeW,"WS4-3-"),animationType::kAttributeAttack,"신의눈물",getShapeFile(shapeType::kShapeW,"WS4-4-"),animationType::kAttributeAttack); //4  A
    addSkill(shapeType::kShapeW,"돌격",getShapeFile(shapeType::kShapeW,"WS5-1-"),animationType::kAttack,"소리치기",getShapeFile(shapeType::kShapeW,"WS5-2-"),animationType::kStopTurn,
             "물의정성",getShapeFile(shapeType::kShapeW,"WS5-3-"),animationType::kAttributeAttack,"물의바램",getShapeFile(shapeType::kShapeW,"WS5-4-"),animationType::kAttributeAttack); //5 B
    addSkill(shapeType::kShapeW,"박치기",getShapeFile(shapeType::kShapeW,"WS6-1-"),animationType::kAttack,"물감옥",getShapeFile(shapeType::kShapeW,"WS6-2-"),animationType::kStopTurn,
             "날카로운 파도",getShapeFile(shapeType::kShapeW,"WS6-3-"),animationType::kAttributeAttack,"물의악몽",getShapeFile(shapeType::kShapeW,"WS6-4-"),animationType::kAttributeAttack); //6   B
    addSkill(shapeType::kShapeW,"박치기",getShapeFile(shapeType::kShapeW,"WS7-1-"),animationType::kAttack,"반사",getShapeFile(shapeType::kShapeW,"WS7-2-"),animationType::kReflect,
             "파도치기",getShapeFile(shapeType::kShapeW,"WS7-3-"),animationType::kAttributeAttack,"워터 노바",getShapeFile(shapeType::kShapeW,"WS7-4-"),animationType::kAttributeAttack); //7    C
    addSkill(shapeType::kShapeW,"박치기",getShapeFile(shapeType::kShapeW,"WS8-1-"),animationType::kAttack,"깜짝 기습",getShapeFile(shapeType::kShapeW,"WS8-2-"),animationType::kDebufTurn,
             "아쿠아 블라스트",getShapeFile(shapeType::kShapeW,"WS8-3-"),animationType::kAttributeAttack,"물의진화",getShapeFile(shapeType::kShapeW,"WS8-4-"),animationType::kAttributeAttack); //8 C
    addSkill(shapeType::kShapeW,"박치기",getShapeFile(shapeType::kShapeW,"WS9-1-"),animationType::kAttack,"워터링",getShapeFile(shapeType::kShapeW,"WS9-2-"),animationType::kDebufTurn,
             "물의화살",getShapeFile(shapeType::kShapeW,"WS9-3-"),animationType::kAttributeAttack,"워터 빔",getShapeFile(shapeType::kShapeW,"WS9-4-"),animationType::kAttributeAttack); //9   D
    addSkill(shapeType::kShapeW,"박치기",getShapeFile(shapeType::kShapeW,"WS10-1-"),animationType::kAttack,"수중효과",getShapeFile(shapeType::kShapeW,"WS10-2-"),animationType::kDebufTurn,
             "물기둥",getShapeFile(shapeType::kShapeW,"WS10-3-"),animationType::kAttributeAttack,"강산성비",getShapeFile(shapeType::kShapeW,"WS10-4-"),animationType::kAttributeAttack); //10   D
    */
    
    vector<ShapeSkillData> shapeText;
    TextDb::getInstance()->runQueryShapeSkill(shapeType::kShapeW, shapeText);
    for(int i=0;i<shapeText.size();i++)
    {
        ShapeSkillData data = shapeText.at(i);
        string skillImageFirst = __String::createWithFormat("WS%d-1-",i+1)->getCString();
        string skillImageTwo = __String::createWithFormat("WS%d-2-",i+1)->getCString();
        string skillImageThree = __String::createWithFormat("WS%d-3-",i+1)->getCString();
        string skillImageFour = __String::createWithFormat("WS%d-4-",i+1)->getCString();
        
        switch (i+1) {
            case 1:
            case 7:
            {
                addSkill(shapeType::kShapeW,data._skill1.c_str(),getShapeFile(shapeType::kShapeW,skillImageFirst.c_str()),animationType::kAttack,data._skill2.c_str(),getShapeFile(shapeType::kShapeW,skillImageTwo.c_str()),animationType::kReflect,data._skill3.c_str(), getShapeFile(shapeType::kShapeW,skillImageThree.c_str()),animationType::kAttributeAttack,data._skill4.c_str(),getShapeFile(shapeType::kShapeW,skillImageFour.c_str()),animationType::kAttributeAttack); //1
                break;
            }
            case 2:
            case 5:
            case 6:
            {
                addSkill(shapeType::kShapeW,data._skill1.c_str(),getShapeFile(shapeType::kShapeW,skillImageFirst.c_str()),animationType::kAttack,data._skill2.c_str(),getShapeFile(shapeType::kShapeW,skillImageTwo.c_str()),animationType::kStopTurn,data._skill3.c_str(), getShapeFile(shapeType::kShapeW,skillImageThree.c_str()),animationType::kAttributeAttack,data._skill4.c_str(),getShapeFile(shapeType::kShapeW,skillImageFour.c_str()),animationType::kAttributeAttack); //1
                break;
            }
            default:
            {
                addSkill(shapeType::kShapeW,data._skill1.c_str(),getShapeFile(shapeType::kShapeW,skillImageFirst.c_str()),animationType::kAttack,data._skill2.c_str(),getShapeFile(shapeType::kShapeW,skillImageTwo.c_str()),animationType::kDebufTurn,data._skill3.c_str(), getShapeFile(shapeType::kShapeW,skillImageThree.c_str()),animationType::kAttributeAttack,data._skill4.c_str(),getShapeFile(shapeType::kShapeW,skillImageFour.c_str()),animationType::kAttributeAttack); //1
                break;
            }
        }
    }
}
void ShapeSkillContainer::setShapeTSkill()
{
    /*
    addSkill(shapeType::kShapeT,"돌격",getShapeFile(shapeType::kShapeT,"LS1-1-"),animationType::kAttack,"반사",getShapeFile(shapeType::kShapeT,"LS1-2-"),animationType::kReflect,"생명의 힘",getShapeFile(shapeType::kShapeT,"LS1-3-"),animationType::kAttributeAttack,"태양광선",getShapeFile(shapeType::kShapeT,"LS1-4-"),animationType::kAttributeAttack); //1   S
    addSkill(shapeType::kShapeT,"돌격",getShapeFile(shapeType::kShapeT,"LS2-1-"),animationType::kAttack,"옭아매기",getShapeFile(shapeType::kShapeT,"LS2-2-"),animationType::kStopTurn,"빛의 인도",getShapeFile(shapeType::kShapeT,"LS2-3-"),animationType::kAttributeAttack,"독뱀",getShapeFile(shapeType::kShapeT,"LS2-4-"),animationType::kAttributeAttack); //2   S
addSkill(shapeType::kShapeT,"돌격",getShapeFile(shapeType::kShapeT,"LS3-1-"),animationType::kAttack,"나무의저주",getShapeFile(shapeType::kShapeT,"LS3-2-"),animationType::kDebufTurn,"앤트의 분노",getShapeFile(shapeType::kShapeT,"LS3-3-"),animationType::kAttributeAttack,"앤트의 계시",getShapeFile(shapeType::kShapeT,"LS3-4-"),animationType::kAttributeAttack); //3   A
    addSkill(shapeType::kShapeT,"돌격",getShapeFile(shapeType::kShapeT,"LS4-1-"),animationType::kAttack,"덩쿨치기",getShapeFile(shapeType::kShapeT,"LS4-2-"),animationType::kDebufTurn,"다크 플라워",getShapeFile(shapeType::kShapeT,"LS4-3-"),animationType::kAttributeAttack,"벚꽃흩날리기",getShapeFile(shapeType::kShapeT,"LS4-4-"),animationType::kAttributeAttack); //4  A
    addSkill(shapeType::kShapeT,"돌격",getShapeFile(shapeType::kShapeT,"LS5-1-"),animationType::kAttack,"소리치기",getShapeFile(shapeType::kShapeT,"LS5-2-"),
             animationType::kStopTurn,"재앙의나무",getShapeFile(shapeType::kShapeT,"LS5-3-"),animationType::kAttributeAttack,"드레인",getShapeFile(shapeType::kShapeT,"LS5-4-"),animationType::kAttributeAttack); //5 B
    addSkill(shapeType::kShapeT,"박치기",getShapeFile(shapeType::kShapeT,"LS6-1-"),animationType::kAttack,"수면가루",getShapeFile(shapeType::kShapeT,"LS6-2-"),animationType::kStopTurn,"꽃잎주먹",getShapeFile(shapeType::kShapeT,"LS6-3-"),animationType::kAttributeAttack,"꽃잎의 파도",getShapeFile(shapeType::kShapeT,"LS6-4-"),animationType::kAttributeAttack); //6   B
    addSkill(shapeType::kShapeT,"박치기",getShapeFile(shapeType::kShapeT,"LS7-1-"),animationType::kAttack,"반사",getShapeFile(shapeType::kShapeT,"LS7-2-"),animationType::kReflect,"꽃잎회오리",getShapeFile(shapeType::kShapeT,"LS7-3-"),animationType::kAttributeAttack,"꽃보라",getShapeFile(shapeType::kShapeT,"LS7-4-"),animationType::kAttributeAttack); //7    C
    addSkill(shapeType::kShapeT,"박치기",getShapeFile(shapeType::kShapeT,"LS8-1-"),animationType::kAttack,"나무의저주",getShapeFile(shapeType::kShapeT,"LS8-2-"),animationType::kDebufTurn,"씨폭탄",getShapeFile(shapeType::kShapeT,"LS8-3-"),animationType::kAttributeAttack,"독구름",getShapeFile(shapeType::kShapeT,"LS8-4-"),animationType::kAttributeAttack); //8 C
    addSkill(shapeType::kShapeT,"박치기",getShapeFile(shapeType::kShapeT,"LS9-1-"),animationType::kAttack,"덫",getShapeFile(shapeType::kShapeT,"LS9-2-"),animationType::kDebufTurn,"개미군단의소환",getShapeFile(shapeType::kShapeT,"LS9-3-"),animationType::kAttributeAttack,"덩쿨가르기",getShapeFile(shapeType::kShapeT,"LS9-4-"),animationType::kAttributeAttack); //9   D
    addSkill(shapeType::kShapeT,"박치기",getShapeFile(shapeType::kShapeT,"LS10-1-"),animationType::kAttack,"씨뿌리기",getShapeFile(shapeType::kShapeT,"LS10-2-"),animationType::kDebufTurn,"잎날가르기",getShapeFile(shapeType::kShapeT,"LS10-3-"), animationType::kAttributeAttack,"목검찌르기",getShapeFile(shapeType::kShapeT,"LS10-4-"),animationType::kAttributeAttack); //10   D
    */
    
    vector<ShapeSkillData> shapeText;
    TextDb::getInstance()->runQueryShapeSkill(shapeType::kShapeT, shapeText);
    for(int i=0;i<shapeText.size();i++)
    {
        ShapeSkillData data = shapeText.at(i);
        string skillImageFirst = __String::createWithFormat("LS%d-1-",i+1)->getCString();
        string skillImageTwo = __String::createWithFormat("LS%d-2-",i+1)->getCString();
        string skillImageThree = __String::createWithFormat("LS%d-3-",i+1)->getCString();
        string skillImageFour = __String::createWithFormat("LS%d-4-",i+1)->getCString();
        switch (i+1) {
            case 1:
            case 7:
            {
                addSkill(shapeType::kShapeT,data._skill1.c_str(),getShapeFile(shapeType::kShapeT,skillImageFirst.c_str()),animationType::kAttack,data._skill2.c_str(),getShapeFile(shapeType::kShapeT,skillImageTwo.c_str()),animationType::kReflect,data._skill3.c_str(), getShapeFile(shapeType::kShapeT,skillImageThree.c_str()),animationType::kAttributeAttack,data._skill4.c_str(),getShapeFile(shapeType::kShapeT,skillImageFour.c_str()),animationType::kAttributeAttack); //1
                break;
            }
            case 2:
            case 5:
            case 6:
            {
                addSkill(shapeType::kShapeT,data._skill1.c_str(),getShapeFile(shapeType::kShapeT,skillImageFirst.c_str()),animationType::kAttack,data._skill2.c_str(),getShapeFile(shapeType::kShapeT,skillImageTwo.c_str()),animationType::kStopTurn,data._skill3.c_str(), getShapeFile(shapeType::kShapeT,skillImageThree.c_str()),animationType::kAttributeAttack,data._skill4.c_str(),getShapeFile(shapeType::kShapeT,skillImageFour.c_str()),animationType::kAttributeAttack); //1
                break;
            }
            default:
            {
                addSkill(shapeType::kShapeT,data._skill1.c_str(),getShapeFile(shapeType::kShapeT,skillImageFirst.c_str()),animationType::kAttack,data._skill2.c_str(),getShapeFile(shapeType::kShapeT,skillImageTwo.c_str()),animationType::kDebufTurn,data._skill3.c_str(), getShapeFile(shapeType::kShapeT,skillImageThree.c_str()),animationType::kAttributeAttack,data._skill4.c_str(),getShapeFile(shapeType::kShapeT,skillImageFour.c_str()),animationType::kAttributeAttack); //1
                break;
            }
        }
        
    }
}
void ShapeSkillContainer::setShapeISkill()
{
    
}
void ShapeSkillContainer::setShapeZSkill()
{
    
}
Vector<Ref *> *ShapeSkillContainer::getShapeArray(int shapeType)
{
    switch (shapeType) {
        case shapeType::kShapeF:
            return _containerShapeSkillF;
            break;
        case shapeType::kShapeW:
            return _containerShapeSkillW;
            break;
        case shapeType::kShapeT:
            return _containerShapeSkillT;
            break;
        case shapeType::kShapeZ:
            return _containerShapeSkillZ;
            break;
        case shapeType::kShapeI:
            return _containerShapeSkillI;
            break;
        default:
            break;
    }
}
const char *ShapeSkillContainer::getShapeFile(int shapeType,const char *skillName)
{
    switch (shapeType) {
        case shapeType::kShapeF:
            return __String::createWithFormat("%s/%s", "skillF",skillName)->getCString();
            break;
        case shapeType::kShapeW:
            return __String::createWithFormat("%s/%s", "skillW",skillName)->getCString();
            break;
        case shapeType::kShapeT:
            return __String::createWithFormat("%s/%s", "skillT",skillName)->getCString();
            break;
        case shapeType::kShapeZ:
            return __String::createWithFormat("%s/%s", "skillI",skillName)->getCString();
            break;
        case shapeType::kShapeI:
            return __String::createWithFormat("%s/%s", "skillZ",skillName)->getCString();
            break;
        default:
            break;
    }
    return "";
}