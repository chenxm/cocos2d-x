#include "Application.h"
#include <QCoreApplication>


NS_CC_BEGIN

// sharedApplication pointer
Application * Application::sm_pSharedApplication = 0;

Application::Application()
{
    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

Application::~Application()
{
    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = NULL;
}

void Application::exit(int retcode)
{
    qApp->exit(retcode);
}

const char * Application::getCurrentLanguageCode()
{
    return (const char*)NULL;
}



LanguageType Application::getCurrentLanguage()
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

ApplicationProtocol::Platform Application::getTargetPlatform()
{
    return Platform::OS_MAC;
}

void Application::setAnimationInterval(double interval)
{
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
Application* Application::getInstance()
{
    CC_ASSERT(sm_pSharedApplication);
    return sm_pSharedApplication;
}

NS_CC_END

