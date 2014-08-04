#ifndef __CC_APPLICATION_H__
#define __CC_APPLICATION_H__

#include "platform/CCApplicationProtocol.h"


NS_CC_BEGIN

class CC_DLL Application : public ApplicationProtocol
{
public:
    Application();
    virtual ~Application();

    void exit(int retcode=0);

    /* override functions */
    /**
     @brief Get current language iso 639-1 code
     @return Current language iso 639-1 code
     * @js NA
     * @lua NA
     */
    virtual const char * getCurrentLanguageCode();
    virtual cocos2d::LanguageType getCurrentLanguage();


    virtual void setAnimationInterval(double interval);

    /**
     @brief Get target platform
     */
    virtual Platform getTargetPlatform();

public:
    /**
    @brief    Get current applicaiton instance.
    @return Current application instance pointer.
    */
    static Application* getInstance();

protected:
    static Application * sm_pSharedApplication;
};

NS_CC_END

#endif    // __CC_APPLICATION_H__
