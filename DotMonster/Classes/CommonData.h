//
//  CommonData.h
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 21..
//
//

#ifndef __dotMonster__CommonData__
#define __dotMonster__CommonData__

#include "CocosHeader.h"

class CommonData : public Node
{
public:
    static CommonData* _instance;
    static CommonData* sharedInstance();


};
#endif /* defined(__dotMonster__CommonData__) */
