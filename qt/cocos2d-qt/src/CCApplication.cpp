#include "CCApplication.h"


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

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
Application* Application::getInstance()
{
    CC_ASSERT(sm_pSharedApplication);
    return sm_pSharedApplication;
}

NS_CC_END

