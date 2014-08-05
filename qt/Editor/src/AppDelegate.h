#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  AppDelegate : public cocos2d::Application
{
public:
    AppDelegate(int argc, char *argv[]);
    virtual ~AppDelegate();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    * @js NA
    * @lua NA
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  This function will be called when the application enters background.
    * @js NA
    * @lua NA
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  This function will be called when the application enters foreground.
    * @js NA
    * @lua NA
    */
    virtual void applicationWillEnterForeground();

    /**
     @brief Get current language iso 639-1 code
     @return Current language iso 639-1 code
     * @js NA
     * @lua NA
     */
    virtual const char * getCurrentLanguageCode();


    /* override functions */
    virtual void setAnimationInterval(double interval);
    virtual cocos2d::LanguageType getCurrentLanguage();

    /**
     @brief Get target platform
     */
    virtual Platform getTargetPlatform();

    const std::string& getStartupScriptFilename(void) {
        return m_startupScriptFilename;
    }
    void setStartupScriptFilename(const std::string& startupScriptFile);


private:
    long long           m_nAnimationInterval;
    std::string         m_startupScriptFilename;
};

#endif // _APP_DELEGATE_H_

