#include "AppDelegate.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "StartScene.h"
#include "C2DXShareSDK.h"

USING_NS_CC;
using namespace cn::sharesdk;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {

    //初始化ShareSDK
    C2DXShareSDK::open(__String::create("api20"), false);
    //初始化社交平台信息
    this -> initPlatformConfig();

    // initialize director
    Director* pDirector = Director::getInstance();
	GLView* pEGLView = pDirector->getOpenGLView();
	if (!pEGLView) {
		pEGLView = GLView::create("My Game");
        pEGLView->setFrameSize(480,320);
		pDirector->setOpenGLView(pEGLView);
	}
    pEGLView->setDesignResolutionSize(480,320,ResolutionPolicy(0));
    pDirector->setOpenGLView(pEGLView);
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //CCScene *pScene = GameLayer::scene();
	//Scene *pScene = GameScene::createWithPhysics();
	Scene *pScene = StartScene::create();
	//Scene *pScene = GameLayer::createSceneWithPhysics();
    // run
	pDirector->runWithScene(pScene);


    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::initPlatformConfig()
{
    //新浪微博
    __Dictionary *sinaConfigDict = __Dictionary::create();
    sinaConfigDict -> setObject(__String::create("568898243"), "app_key");
    sinaConfigDict -> setObject(__String::create("38a4f8204cc784f81f9f0daaf31e02e3"), "app_secret");
    sinaConfigDict -> setObject(__String::create("http://www.sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSinaWeibo, sinaConfigDict);
}
