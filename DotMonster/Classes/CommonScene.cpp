//
//  CommonScene.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 21..
//
//

#include "CommonScene.h"


bool Common::init()
{
    return init(Color4B(255,255,255,255));
}

bool Common::init(Color4B color, bool isScaleSet)
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::initWithColor(color) )
    {
        return false;
    }
    
    //setDefine();
    setScreenSizeScale(isScaleSet);
    return true;
}


void Common::setDefine()
{

    
    
}
void Common::setScreenSizeScale(bool bScale)
{
    /*
    Size size = Director::getInstance()->getWinSize();
	S_WSIZE = 960;
    S_HSIZE = 640;
	m_fScale = size.height/(640);
    log("S_WSIZE1 = %d", S_WSIZE);
    log("S_HSIZE1 = %d", S_HSIZE);
    log("scale = %f", m_fScale);

    _basePan = Sprite::create();
	//HSIZE = WSIZE*S_HSIZE/S_WSIZE;
    //WSIZE = HSIZE*S_WSIZE/S_HSIZE;
    
    CommonData::sharedInstance()->WSIZE = WSIZE;
	CommonData::sharedInstance()->HSIZE = HSIZE;
    _basePan->setContentSize(Size(WSIZE,HSIZE));
    _basePan->setPosition(Vec2(size.width/2,size.height/2));
	_basePan->setScale(m_fScale);
    this->addChild(_basePan);
	log("setScreenSizeScale");
    log("S_WSIZE2 = %f", CommonData::sharedInstance()->WSIZE);
    log("S_HSIZE2 = %f", CommonData::sharedInstance()->HSIZE);
     */
}