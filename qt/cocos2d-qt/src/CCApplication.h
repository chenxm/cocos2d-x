#ifndef __CC_APPLICATION_H__
#define __CC_APPLICATION_H__

#include "CCApplicationProtocol.h"


NS_CC_BEGIN

class CC_DLL Application : public ApplicationProtocol
{
public:
    Application();
    virtual ~Application();

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
