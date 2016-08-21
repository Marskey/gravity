#include "BlurLayer.h"


BlurLayer::~BlurLayer()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_COME_TO_FOREGROUND);
}



BlurLayer* BlurLayer::create()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRenderTexture* pRender = CCRenderTexture::create(visibleSize.width, visibleSize.height);
	pRender->begin();
	CCDirector::sharedDirector()->getRunningScene()->visit();
	pRender->end();
	BlurLayer* pRet = new BlurLayer();
	if (pRet && pRet->initWithTexture(pRender->getSprite()->getTexture(), pRender->getSprite()->getTextureRect()))
	{
		pRet->setFlipY(true);
		pRet->autorelease();
	}
	else
		CC_SAFE_DELETE(pRet);
	return pRet;
}
void BlurLayer::listenBackToForeground(CCObject *obj)
{
	setShaderProgram(NULL);
	initProgram();
}

bool BlurLayer::initWithTexture(CCTexture2D* texture, const CCRect& rect)
{
	if (CCSprite::initWithTexture(texture, rect))
	{
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
			callfuncO_selector(BlurLayer::listenBackToForeground),
			EVENT_COME_TO_FOREGROUND,
			NULL);


		//this->initProgram();
	
		return true;
	}

	return false;
}

void BlurLayer::initProgram()
{
	GLchar * fragSource = (GLchar*)CCString::createWithContentsOfFile(
		CCFileUtils::sharedFileUtils()->fullPathForFilename("Shaders/example_Blur.fsh").c_str())->getCString();
	CCGLProgram* pProgram = new CCGLProgram();
	pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
	setShaderProgram(pProgram);
	pProgram->release();

	CHECK_GL_ERROR_DEBUG();

	getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	
	CHECK_GL_ERROR_DEBUG();

	getShaderProgram()->link();

	CHECK_GL_ERROR_DEBUG();

	getShaderProgram()->updateUniforms();

	CHECK_GL_ERROR_DEBUG();

	GLuint	sizeLocation = glGetUniformLocation(getShaderProgram()->getProgram(), "resolution");
	CCSize s = getTexture()->getContentSizeInPixels();	
	getShaderProgram()->setUniformLocationWith2f(sizeLocation, s.width, s.height);
	GLuint blurRadiusLocation = glGetUniformLocation(getShaderProgram()->getProgram(), "blurRadius");
	getShaderProgram()->setUniformLocationWith1f(blurRadiusLocation, 15.0f);
	GLuint sampleNumLocation = glGetUniformLocation(getShaderProgram()->getProgram(), "sampleNum");
	getShaderProgram()->setUniformLocationWith1f(sampleNumLocation, 8.0f);
	CHECK_GL_ERROR_DEBUG();
}


