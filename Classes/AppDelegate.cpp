#include "AppDelegate.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "StartScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
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
