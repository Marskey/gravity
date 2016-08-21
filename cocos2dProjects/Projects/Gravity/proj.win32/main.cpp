#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

USING_NS_CC;

void shotStageSceen()//½ØÍ¼,ÔÚ\devilHiding\proj.win32\Debug.win32\share.jpg
{
    CCSize frameSize = CCDirector::sharedDirector()->getOpenGLView()->getFrameSize();

    CCRenderTexture* screen = CCRenderTexture::create(frameSize.width, frameSize.height);

    screen->begin();

    CCDirector::sharedDirector()->getRunningScene()->visit();

    screen->end();
    static int count = 0;
    screen->saveToFile(CCString::createWithFormat("%d.jpg", count++)->getCString(), kCCImageFormatJPEG);
}

LRESULT Cocos2dxWndProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed)
{
    if (message == WM_KEYDOWN)
    {
        if (wParam == 'P')
        {
            shotStageSceen();
        }
    }
    return 0;
}
int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("Gravity");
    eglView->setFrameSize(320, 480);


    eglView->setWndProc(&Cocos2dxWndProc);

    return CCApplication::sharedApplication()->run();
}
