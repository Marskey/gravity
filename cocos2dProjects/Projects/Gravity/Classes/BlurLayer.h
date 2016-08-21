#include "stdafx.h"
#ifndef _BLURLAYER_H__
#define _BLURLAYER_H__

class BlurLayer : public CCSprite
{
public:
	~BlurLayer();
	static BlurLayer* create();
	bool initWithTexture(CCTexture2D* texture, const CCRect&  rect);
	void initProgram();
	void listenBackToForeground(CCObject *obj);
};
 
#endif //_BLURLAYER_H__