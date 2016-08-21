#ifndef _GameScene_H_
#define _GameScene_H_
#include "UI\UIDialog.h"
#include "Entity\EntityManager.h"
#include "BlurLayer.h"

class GameScene : public UIDialog 
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();
	void update(float dt);
	void pause();
	void resume(CCObject* pSender);
private:
	ui::UIButton *pPauseBtn;
	//ui::UILabelAtlas *pMin;
	//ui::UILabelAtlas *pColon;
	ui::UILabelAtlas *pSec;
	ui::UIImageView *pClock;
	ui::UILoadingBar *pEnergyBar;
	ui::UILabelAtlas *pCoreGet;
	ui::UIImageView *pCoreIcon;
	EntityManager *pEntities;
	BlurLayer *blur;
	int _time;
	CCPoint WIN_SIZE;
	bool gameState;/*true is running,false is over*/

	double m_twoTouchesDistance;
	double m_deltaX;
	double m_deltaY;
	double m_mapPreScale;
	int m_touchesNum;
	int m_CoreGetNum;
	CCString *temp;
	std::vector<CCPoint> touchPos;
private:
	//pause the game
	void gameOver(CCObject *pSender);
	void gameWin(float dt);
	void gameLose(float dt);
	void countTime(float dt);
	float calculateEvaluation();
	void setFireOnRocket();
	void addCoreNum(CCObject*pSender);
	void onPauseBtn(CCObject* pSender, ui::TouchEventType type); 
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);



};
#endif // _GameScreen_H_