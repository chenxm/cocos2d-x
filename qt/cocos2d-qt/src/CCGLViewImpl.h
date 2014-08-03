#ifndef __CC_GLVIEW_H__
#define __CC_GLVIEW_H__
#include "GL/glew.h"
#include "cocos2d.h"

#include <QMouseEvent>
#include <vector>
#include "CCStdC.h"
#include "platform/CCCommon.h"
#include "platform/CCGLView.h"

typedef enum {
    GLVIEW_WINDOW_MODE_FIXSIZE = 0,     // GL window with the fixed windows size
    GLVIEW_WINDOW_MODE_RESIZABLE,       // resizable GL window
}   GLViewWindowModeType;

typedef void(*ACCEL_PTRFUN)(QKeyEvent *event);

class GLWidget;

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
    void setWindowRect(const Rect& rect);
    void initializeDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy);
    void updateDesignResolutionSize();
    void resetViewPort();

    /*
     * Set zoom factor for frame. This method is for debugging big resolution (e.g.new ipad) app on desktop.
     */
    void setFrameZoomFactor(float fZoomFactor);
    float getFrameZoomFactor();
    
    // Qt
    void mouseMove(QMouseEvent *event);
    void mousePress(QMouseEvent *event);
    void mouseRelease(QMouseEvent *event);
    void setAccelerometerKeyHook(ACCEL_PTRFUN func);

private:
    bool initGL();
    void destroyGL();

private:
    bool m_bIsInit;
    bool m_bCaptured;
//    bool m_bSupportTouch;
    float m_fFrameZoomFactor;
    float m_fScreenScaleFactor;
    Vec2 m_WindowOrigin;

    std::vector<Touch*> * m_pSet;
    Touch * m_pTouch;
};

NS_CC_END

#endif    // __CC_GLVIEW_H__
