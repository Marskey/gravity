/************************************************************************
*  Name: MultiTouchLayer.cpp
*  Purpose:
*  Author: Marskey
*  time: 2015-06-08	
*  version: 1.0
/************************************************************************/

#include "MultiTouchLayer.h"

bool MutiTouchLayer::init()
{
    if (CCLayer::init())
    {
        setTouchEnabled(true);
		setTouchMode(kCCTouchesAllAtOnce);
		m_touchesNum = 0;
        return true;
    }
    return false;
}

void MutiTouchLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	m_touchesNum += pTouches->count();
	CCLog("touches == %d", m_touchesNum);
}

void MutiTouchLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

}
void MutiTouchLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	//m_touchesNum -= pTouches->count();
}
void MutiTouchLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
}

void MutiTouchLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}