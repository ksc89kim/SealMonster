//
//  CommonData.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 21..
//
//

#include "CommonData.h"

CommonData* CommonData::_instance = NULL;


CommonData* CommonData::sharedInstance()
{
	if ( _instance == NULL )
	{
		_instance = new CommonData();
	}
	return _instance;
}