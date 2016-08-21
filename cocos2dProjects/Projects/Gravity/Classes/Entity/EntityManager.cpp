#include "Entity\EntityManager.h"
#include "DBCSVService\DBCSVService.h"
#include "Global\Global_Define.h"
#include "Config.h"
//#include "Entity/EnergyBag.h"
EntityManager::EntityManager()
{
	isCameraMove = false;
	m_elapsed = 0;
}
EntityManager::~EntityManager()
{
	for (int i = 0; i < _starList.size(); ++i)
	{
		delete _starList[i];
	}
	//collectionArr->release();
}

EntityManager* EntityManager::createWithLevel(int curLevel)
{
	//---------------------------------------¹Ø¿¨´´½¨
	EntityManager* pRet = new EntityManager();
	if (pRet && pRet->initWithLevel(curLevel))
	{
		pRet->autorelease();
		return pRet;
	}
	else
		CC_SAFE_DELETE(pRet);
	return pRet;
}

bool EntityManager::initWithLevel(int curLevel)
{
	createMapWithLevel(curLevel);
	createHalo();
	scheduleUpdate();
	return true;
}


void EntityManager::createRocket()
{

}

void EntityManager::createMapWithLevel(int curLevel)
{
	CCString *sPlanetPath = CCString::createWithFormat("MAP/map_level_%d/map_level_1.ExportJson", curLevel);
	std::string sFullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(sPlanetPath->getCString());
	ui::Widget *Map = GUIReader::shareReader()->widgetFromJsonFile(sFullPath.c_str());
	this->addChild(Map);
	//------------------------------------------------------------------------
	_pRocket = Rocket::createBy(ui::UIHelper::seekWidgetByName(Map, "Image_Rocket"));
	_pRocket->setTag(kRocketTag);
	this->addChild(_pRocket);
	_pRocket->createFire();
	//------------------------------------------------------------------------collection
	collectionArr = CCArray::create();
	collectionArr->retain();
	Collection* collection = Collection::createBy(ui::UIHelper::seekWidgetByName(Map, "Image_Gem"));
	if (collection)
	{
		this->addChild(collection);
		collectionArr->addObject(collection);
	}
	//------------------------------------------------------------------------collection end
	//------------------------------------------------------------------------
	ui::UIPanel *planetGroup = dynamic_cast<ui::UIPanel*>(ui::UIHelper::seekWidgetByName(Map, "Panel_Group_Planet"));
	CCArray *container = planetGroup->getChildren();
	CCAssert(container, "container of planet should not be NULL");
	CCObject* pObj;
	CCARRAY_FOREACH(container, pObj)
	{
		Planet* p = new Planet(pObj);
		CCPoint pos = p->getPosition();
		CCAssert(p, "get nothing from json");
		_starList.push_back(p);
		_starPosList.push_back(pos);
	}
	_goalPlanetID = _starList.size() - 1;
	//---------------------------BlackHole---------------------------
	ui::UIPanel *blackholeGroup = dynamic_cast<ui::UIPanel*>(ui::UIHelper::seekWidgetByName(Map, "Panel_Group_blackHole"));
	container = blackholeGroup->getChildren();
	CCAssert(container, "container of blackhole should not be NULL");
	CCARRAY_FOREACH(container, pObj)
	{
		BlackHole* b = new BlackHole(pObj);
		CCAssert(b, "");
		_starList.push_back(b);
	}
}

void EntityManager::update(float dt)
{
	do
	{
		CC_BREAK_IF(_pRocket->isDead());
		if (_pRocket->getState() == 3)
		{
			checkMeetWithStar(dt);
		}
		collectionMeetWithStar(dt);
	} while (false);
}

void EntityManager::checkMeetWithStar(float dt)
{
	CCPoint rPos = _pRocket->getPosition();
	//for (Planet *it : _starList)
	for (std::vector<Planet*>::iterator it = _starList.begin(); it != _starList.end(); ++it)
	{
		if ((*it)->isMeetMe(rPos))
		{
			_pRocket->intoGravity(*it);
			if (dynamic_cast<BlackHole*>(*it))
			{
				_pRocket->setOnBlackHole(true);
				break;
			}
			else if ((*it) == _starList[_goalPlanetID])
			{
				_pRocket->setOnGoalPlanet(true);
				break;
			}
		}
	}
}

void EntityManager::collectionMeetWithStar(float dt)
{
	CCObject *pObj;
	CCARRAY_FOREACH(collectionArr, pObj)
	{
		Collection* collection = dynamic_cast<Collection*>(pObj);
		if (collection)
		{
			CCPoint cPos = collection->getPosition();
			//for (Planet *it : _starList)
			if (collection->getState() == 1)
				for (std::vector<Planet*>::iterator it = _starList.begin(); it != _starList.end(); ++it)
				{
					if ((*it)->isMeetMe(cPos))
					{
						collection->intoGravity(*it);
						break;
					}
				}
		}
	}
}

void EntityManager::pause()
{
	this->pauseSchedulerAndActions();
	_pRocket->pause();
	for (std::vector<Planet*>::iterator it = _starList.begin(); it != _starList.end(); ++it)
	{
		(*it)->pause();
	}
	CCObject *pObj;
	CCARRAY_FOREACH(collectionArr, pObj)
	{
		Collection* collection = dynamic_cast<Collection*>(pObj);
		collection->pauseSchedulerAndActions();
	}
}

void EntityManager::resume()
{
	this->resumeSchedulerAndActions();
	_pRocket->resume();
	for (std::vector<Planet*>::iterator it = _starList.begin(); it != _starList.end(); ++it)
	{
		(*it)->resume();
	}
	CCObject *pObj;
	CCARRAY_FOREACH(collectionArr, pObj)
	{
		Collection* collection = dynamic_cast<Collection*>(pObj);
		collection->pauseSchedulerAndActions();
	}
}

void EntityManager::setCameraClose()
{
	if (!m_elapsed && !isCameraMove)
	{
		CCAction* action = CCSequence::create(CCScaleBy::create(CLOSETODURATION, 2.0f), NULL);
		this->runAction(action);
		isCameraMove = true;
	}
}

void EntityManager::setCameraFar()
{
	if (m_elapsed > CLOSETODURATION&&isCameraMove)
	{
		isCameraMove = false;
		CCAction* action = CCSequence::create(CCSpawn::createWithTwoActions(CCScaleBy::create(CLOSETODURATION, 1 / 2.0f), CCMoveTo::create(CLOSETODURATION, ccp(0, 0))), CCCallFunc::create(this, SEL_CallFunc(&EntityManager::resetElapsion)), NULL);
		this->runAction(action);
	}
}

void EntityManager::resetElapsion()
{
	m_elapsed = 0;
}

void EntityManager::createHalo()
{
	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Halo/Halo.ExportJson");
	CCArmature* halo = CCArmature::create("Halo");
	halo->getAnimation()->play("white");
	float scale = _starList[_goalPlanetID]->getScale() * RADIO_HALOANDPLANET;
	halo->setScale(scale);
	halo->setPosition(_starList[_goalPlanetID]->getPosition());
	this->addChild(halo,-2);
	
}
void EntityManager::createSrand()
{
	cc_timeval tv;
	CCTime::gettimeofdayCocos2d(&tv, NULL);
	unsigned long reed = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	srand(reed);
}
