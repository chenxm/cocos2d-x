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
