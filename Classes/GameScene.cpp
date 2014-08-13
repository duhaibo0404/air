#include "GameScene.h"
#include "C2DXShareSDK.h"

 using namespace cn::sharesdk;

GameScene::GameScene(void)
{
    _gameLayer=NULL;
}

GameScene* GameScene::createWithPhysics()
{
	GameScene *ret = new GameScene();
	if (ret && ret->initWithPhysics())
	{
		ret->init();
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}
GameScene::~GameScene(void)
{
}
 
bool GameScene::init()
{
    bool bRet=false;
    do
    {
    	  CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		    
		    CCMenuItemLabel *authMenuItem = CCMenuItemLabel::create(CCLabelTTF::create("授权", "Arial", 40),
		                                                            this,
		                                                            menu_selector(HelloWorld::authMenuItemClick));
		    CCMenuItemLabel *cancelAuthMenuItem = CCMenuItemLabel::create(CCLabelTTF::create("取消授权", "Arial", 40),
		                                                                  this,
		                                                                  menu_selector(HelloWorld::cancelAuthMenuItemClick));
		    CCMenuItemLabel *hasAuthMenuItem = CCMenuItemLabel::create(CCLabelTTF::create("是否授权", "Arial", 40),
		                                                               this,
		                                                               menu_selector(HelloWorld::hasAuthMenuItemClick));
		    CCMenuItemLabel *getUserMenuItem = CCMenuItemLabel::create(CCLabelTTF::create("用户信息", "Arial", 40),
		                                                               this,
		                                                               menu_selector(HelloWorld::getUserInfoMenuItemClick));
		    CCMenuItemLabel *shareMenuItem = CCMenuItemLabel::create(CCLabelTTF::create("分享", "Arial", 40),
		                                                             this,
		                                                             menu_selector(HelloWorld::shareMenuItemClick));
		
		    CCMenu *itemsMenu = CCMenu::create(authMenuItem, cancelAuthMenuItem, hasAuthMenuItem, getUserMenuItem, shareMenuItem, NULL);
		    itemsMenu -> alignItemsHorizontallyWithPadding(20);
		    itemsMenu -> setPosition(ccp(CCDirector::sharedDirector() -> getWinSize().width / 2, 100));
		    this -> addChild(itemsMenu);
    	
        _gameLayer=GameLayer::create();
        CC_BREAK_IF(!_gameLayer);
        this->addChild(_gameLayer);
        bRet=true;
    } while (0);
 
    return bRet;
}

void authResultHandler(C2DXResponseState state, C2DXPlatType platType, __Dictionary *error)
{
    switch (state) {
        case C2DXResponseStateSuccess:
            CCLog("授权成功");
            break;
        case C2DXResponseStateFail:
            CCLog("授权失败");
            break;
        default:
            break;
    }
}

void getUserResultHandler(C2DXResponseState state, C2DXPlatType platType, __Dictionary *userInfo, __Dictionary *error)
{
    if (state == C2DXResponseStateSuccess)
    {
        //输出用户信息
        try
        {
            __Array *allKeys = userInfo -> allKeys();
			allKeys->retain();
            for (int i = 0; i < allKeys -> count(); i++)
            {
                __String *key = (__String *)allKeys -> objectAtIndex(i);
                Ref *obj = userInfo -> objectForKey(key -> getCString());
                
                log("key = %s", key -> getCString());
                if (dynamic_cast<__String *>(obj))
                {
                    log("value = %s", dynamic_cast<__String *>(obj) -> getCString());
                }
                else if (dynamic_cast<__Integer *>(obj))
                {
                    log("value = %d", dynamic_cast<__Integer *>(obj) -> getValue());
                }
                else if (dynamic_cast<__Double *>(obj))
                {
                    log("value = %f", dynamic_cast<CCDouble *>(obj) -> getValue());
                }
            }
			allKeys->release();
        }
        catch(...)
        {
            log("==============error");
        }
        
    }
}

void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, __Dictionary *shareInfo, __Dictionary *error)
{
    switch (state) {
        case C2DXResponseStateSuccess:
            CCLog("分享成功");
            break;
        case C2DXResponseStateFail:
            CCLog("分享失败");
            break;
        default:
            break;
    }
}

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void GameScene::authMenuItemClick(CCObject* pSender)
{
//    C2DXShareSDK::authorize(C2DXPlatTypeFacebook, authResultHandler);
}

void GameScene::cancelAuthMenuItemClick(CCObject* pSender)
{
//    C2DXShareSDK::cancelAuthorize(C2DXPlatTypeSinaWeibo);
}

void GameScene::hasAuthMenuItemClick(CCObject* pSender)
{
    if (C2DXShareSDK::hasAutorized(C2DXPlatTypeSinaWeibo))
    {
        CCLog("用户已授权");
    }
    else
    {
        CCLog("用户尚未授权");
    }
}

void GameScene::getUserInfoMenuItemClick(CCObject* pSender)
{
    C2DXShareSDK::getUserInfo(C2DXPlatTypeSinaWeibo, getUserResultHandler);
}

void GameScene::shareMenuItemClick(CCObject* pSender)
{
    CCDictionary *content = CCDictionary::create();
    content -> setObject(CCString::create("这是一条测试内容"), "content");
    content -> setObject(CCString::create("http://img0.bdstatic.com/img/image/shouye/systsy-11927417755.jpg"), "image");
    content -> setObject(CCString::create("测试标题"), "title");
    content -> setObject(CCString::create("测试描述"), "description");
    content -> setObject(CCString::create("http://sharesdk.cn"), "url");
    content -> setObject(CCString::createWithFormat("%d", C2DXContentTypeNews), "type");
    content -> setObject(CCString::create("http://sharesdk.cn"), "siteUrl");
    content -> setObject(CCString::create("ShareSDK"), "site");
    content -> setObject(CCString::create("http://mp3.mwap8.com/destdir/Music/2009/20090601/ZuiXuanMinZuFeng20090601119.mp3"), "musicUrl");
    content -> setObject(CCString::create("extInfo"), "extInfo");
    
    C2DXShareSDK::showShareMenu(NULL, content, CCPointMake(100, 100), C2DXMenuArrowDirectionLeft, shareResultHandler);
//    C2DXShareSDK::showShareView(C2DXPlatTypeSinaWeibo, content, shareResultHandler);
}
