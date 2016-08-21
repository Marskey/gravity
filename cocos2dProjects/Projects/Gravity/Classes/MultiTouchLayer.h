/************************************************************************
*  Name: MultiTouchLayer.h
*  Purpose:
*  Author: Marskey
*  time: 2015-06-08	
*  version: 1.0
/************************************************************************/
#include "stdafx.h"
#ifndef HEADER__MULTITOUCHLAYER
#define HEADER__MULTITOUCHLAYER

class MutiTouchLayer :public	CCLayer 
{
private:
	int m_touchesNum;
	double m_twoTouchesDistance;
	double m_deltaX;
	double m_deltaY;
	double m_mapPreScale;
public:
    bool init();

    virtual void registerWithTouchDispatcher(void);
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	CREATE_FUNC(MutiTouchLayer);
};
#endif // HEADER__MULTITOUCHLAYER