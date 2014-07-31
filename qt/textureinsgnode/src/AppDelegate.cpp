#include "AppDelegate.h"

#include "CCGLView.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate(int argc, char *argv[])
    : Application()
{
    m_nAnimationInterval = 1.0f / 60.0f * 1000.0f;
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    Director* pDirector = Director::getInstance();
    cocos2d::GLView* eglView = cocos2d::GLView::create("test");
//    cocos2d::GLView *eglView = cocos2d::GLView::createWithRect("HelloCocos2d",cocos2d::Rect(0,0,960,640));

    //    eglView->setFrameSize(960, 640);
    eglView->setDesignResolutionSize(960,640,ResolutionPolicy::NO_BORDER);
    pDirector->setOpenGLView(eglView);

    // turn on display FPS
//    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60 );
#define defx
#ifdef defx
    // create a scene. it's an autorelease object
    Scene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

#else

    // register lua engine
    LuaEngine *pEngine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(pEngine);

    LuaStack *pStack = pEngine->getLuaStack();
    lua_State* L = pStack->getLuaState();

//    // load lua extensions
//    luaopen_lua_extensions(L);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    luaopen_cocos2dx_extra_ios_iap_luabinding(L);
#endif

//    CCLOG("------------------------------------------------");
//    CCLOG("LOAD LUA FILE: %s", path.c_str());
//    CCLOG("------------------------------------------------");
//    pEngine->executeScriptFile(path.c_str());

    pEngine->executeScriptFile("src/hello.lua");

#endif
//    m_mainWindow.setCocosAppDelegate(this);
//    m_mainWindow.show();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

const char * AppDelegate::getCurrentLanguageCode()
{
    return (const char*)NULL;
}



LanguageType AppDelegate::getCurrentLanguage()
{
//    switch (QLocale::system().language())
//    {
//    case QLocale::Chinese: return LanguageType::CHINESE;
//    case QLocale::French:  return LanguageType::FRENCH;
//    case QLocale::Italian: return LanguageType::ITALIAN;
//    case QLocale::German:  return LanguageType::GERMAN;
//    case QLocale::Spanish: return LanguageType::SPANISH;
//    case QLocale::Russian: return LanguageType::RUSSIAN;
//    case QLocale::Polish:   return LanguageType::POLISH;
//    case QLocale::Norwegian:    return LanguageType::NORWEGIAN;
//    default:               return LanguageType::ENGLISH;
//    }
    return LanguageType::ENGLISH;
}

ApplicationProtocol::Platform AppDelegate::getTargetPlatform()
{
    return Platform::OS_MAC;
}

void AppDelegate::setStartupScriptFilename(const std::string& startupScriptFile)
{
    m_startupScriptFilename = startupScriptFile;
    int pos;
    while ((pos = m_startupScriptFilename.find_first_of("\\")) != std::string::npos)
    {
        m_startupScriptFilename.replace(pos, 1, "/");
    }
}

void AppDelegate::setAnimationInterval(double interval)
{
    m_nAnimationInterval = interval * 1000.0f;
}
