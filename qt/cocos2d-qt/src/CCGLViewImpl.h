#ifndef __CC_GLVIEW_IMPL_H__
#define __CC_GLVIEW_IMPL_H__
#include <vector>
#include "GL/glew.h"
#include "cocos2d.h"
#include "CCStdC.h"
#include "platform/CCCommon.h"
#include "platform/CCGLView.h"


NS_CC_BEGIN

class CC_DLL GLViewImpl : public GLView, public Ref
{
public:
    explicit GLViewImpl();
    virtual ~GLViewImpl();

private:
    /* override functions */
    virtual bool isOpenGLReady();
    virtual void end();
    virtual void swapBuffers();
    virtual void setFrameSize(float width, float height);
    virtual void setIMEKeyboardState(bool bOpen);
    virtual void setViewName(const std::string& pszViewName);
    virtual void setViewPortInPoints(float x , float y , float w , float h);
    virtual void setScissorInPoints(float x , float y , float w , float h);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    virtual HWND getWin32Window() {return 0;}
#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    virtual id getCocoaWindow(){return 0;}
#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) */

public:
    // static function
    /**
    @brief    get the shared main open gl window
    */
    static GLViewImpl* createWithRect(const std::string& viewName, const Rect& rect, ResolutionPolicy resolutionPolicy);

public:
    void setViewportRect(const Rect& rect);
    void setViewportOrigin(const Vec2& point);
    void initializeDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy);
    void updateDesignResolutionSize();
    void resetViewPort();

    /*
     * Set zoom factor for frame. This method is for debugging big resolution (e.g.new ipad) app on desktop.
     */
    void setFrameZoomFactor(float fZoomFactor);
    float getFrameZoomFactor();
    
private:
    bool initGL();
    void destroyGL();

private:
    bool mIsInitialed;
    float mFrameZoomFactor;
    Vec2 mViewportOrigin;

};

NS_CC_END

#endif    // __CC_GLVIEW_IMPL_H__
