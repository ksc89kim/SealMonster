//
//  Define.h
//  ShapeMaster
//
//  Created by 김선철 on 2014. 2. 23..
//
//

#ifndef __ShapeMaster__Define__
#define __ShapeMaster__Define__

#include "CommonUtils.h"
#include "CommonData.h"
#include "CommonPopUp.h"
#include "EncryptUtil.h"
#include "Adaptor.h"

#define GAME_SCENE_TAG 7777
#define SKILL_FIRST 1
#define SKILL_TWO 6
#define SKILL_THREE 16
#define SKILL_FOUR 32
#define SKILL_BATCH_COUNT 8
#define SKILL_MAX_BATCH_COUNT 30
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define SPACE_MAP_DATA_INT 0
#define SPACE_MAP_DATA_STRING ""
#define ENEMY_FILE_PATH "enemyFile.plist"

#define SOUND_ON_OFF "SOUND_KEY"
#define MUSIC_ON_OFF "MUSIC_KEY"
#define TUTORIAL_ON_OFF "TUTORIAL_KEY"

#define SOUND_EFFECT_DOTE_BUTTON "sound/dotbutton.wav"
#define SOUND_EFFECT_BASE_BUTTON "sound/button.wav"
#define SOUND_EFFECT_FIND "sound/find.wav"
#define SOUND_EFFECT_LEVELUP "sound/levelup.wav"

#define SOUND_MUSIC_BASE "sound/background.wav"
#define SOUND_MUSIC_BATTLE "sound/battle.wav"
#define SOUND_MUSIC_CITY "sound/sunny-walking.wav"

namespace ItemType {
    enum{
        kItemTypeResorative1=1,
        kItemTypeResorative2,
        kItemTypeResorative3,
        kItemTypePlusPower,
        kItemTypePlusAgility,
        kItemTypePlusStamina,
        kItemTypeReturnCity,
        kItemTypeMoveFire,
        kItemTypeMoveWater,
        kItemTypeMoveTree,
        kItemStamp,
        kItemTypeEradication,
        kItemTypeTemptation,
        kItemTypeVisibleCave,
        kItemTypeTransResorative1,
        kItemTypeTransResorative2,
        kItemTypeTransResorative3,
        kItemTypePlusTransPower,
        kItemTypePlusTransAgility,
        kItemTypePlusTransStamina,
        kItemTypeRailLoon, //골드
        kItemTypeVailLoon, //경험치
        kItemTypeZailLoon, //레벨업 체력
        kItemTypeQailLoon, //레벨업 민첩
        kItemTypeNailLoon, //레벨업 힘
        kQuestMulMangCho=1000, //물망초
        kQuestOnepice, //흑령의조각
        kQuestCrystal,//크리스탈 씨앗
        kQuestSickle,//낫
    };
}

namespace animationType {
    enum
    {
        kAttack,
        kAttributeAttack,
        kStopTurn,
        kDebufTurn,
        kReflect,
        kMiss,
        
    };
}
namespace battleCheckType {
    enum
    {
        kBattle,
        kChange,
        kWinFinish,
        kLoseFinish,
        kEvolution,
        kLevelUp,
        kExp,
        kError
    };
}

namespace questType{
    enum{
        kDefault,
        kItem,
        kMap,
        kTalk,
        kMonster,
        kMonsterKill,
        kCharacterWin,
    };
}
namespace questReward{
    enum{
        kNot,
        kItem,
        kGold,
        kItemUpgrade
    };
}
namespace questRemove{
    enum{
        kNot,
        kItem,
    };
}
namespace questStatus{
    enum{
        kFail=1,
        kWait,
        kIng,
        kSuccess,
    };
}
namespace questIndex{
    enum{
        kNotQuest=0,
        kMainQuest=1,
        kMasterSealQuest,
        kEventQuest,
        kFirstVillageHelpQuest,
        kFirstVillageLoonQuest,
        kThreeVillageLoonQuest,
        kFiveVillageLoonQuest,
        kLastLoonQuest,
    };
}
namespace bushType{
    enum{
        kBushRand30 = -2,
        kBushRand20 = -1,
        kBushRand=0,
        kBushShapeF=1,
        kBushShapeW,
        kBushShapeT,
        kBushShapeZ,
        kBushShapeI
    };
}
namespace mapType {
    enum{
        kMapDefault=1,
        kMapFire,
        kMapWater,
        kMapTree,
        kMapCave,
    };
}
namespace mapInfoType{
    enum{
        kMapInfoMove=1,
        kMapInfoVillage,
        kMapInfoMonster,
        kMapInfoStopMove,
        kMapInfoCharacter,
        kMapInfoQuestCharacter,
        kMapInfoMoveEvent,
        kMapInfoUpgradeStore,
    };
}
namespace talkType{
    enum{
        ktalkStart,
        ktalkNext,
        ktalkFinish,
        ktalkBaseStart,
        ktalkBaseNext,
        ktalkBaseFinish,
    };
}

namespace characterType{
    enum{
        kChiwoo=1, //주인공 형
        kGaon, //주인공 라이벌
        kHeonone, //주인공 라이벌 아버지.
        kMiho, //치호의 친구. 여캐 미호
        kMawoong, //치호의 친구. 남캐 마웅
        kJung,//끝판왕
        kHuntingCharacter1=100000,
        kHuntingCharacter2,
        kHuntingCharacter3,
        kHuntingCharacter4,
        kHuntingCharacter5,
        kHuntingCharacter6,
        kHuntingCharacter7,
    };
}

namespace statusType {
    enum{
        kBaseHealth,
        kBaseAgility,
        kBasePower,
        kHealth,
        kAgility,
        kPower
    };
}
namespace catchType
{
    enum
    {
        kError,
        kCatch,
        kFail
    };
}
namespace battleType
{
    enum
    {
        kBushType = 0,
        kCharacterType = 1,
        kQuestChracterType = 2
    };
}

enum{
    layer_1, //background
    layer_2, //point back
    layer_3, //point
    layer_4, //point front
    layer_5,  //front front
    layer_6  //front front

};

#endif /* defined(__ShapeMaster__Define__) */
