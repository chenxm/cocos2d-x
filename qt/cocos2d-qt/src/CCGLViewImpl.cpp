#include "CCGLViewImpl.h"
#include "CCApplication.h"


NS_CC_BEGIN



static bool glew_dynamic_binding()
{
	const char *gl_extensions = (const char*)glGetString(GL_EXTENSIONS);

	// If the current opengl driver doesn't have framebuffers methods, check if an extension exists
	if (glGenFramebuffers == NULL)
	{
        CCLOG("OpenGL: glGenFramebuffers is NULL, try to detect an extension\n");
		if (strstr(gl_extensions, "ARB_framebuffer_object"))
		{
            CCLOG("OpenGL: ARB_framebuffer_object is supported\n");
#ifdef Q_OS_WIN_1
			glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) wglGetProcAddress("glIsRenderbuffer");
			glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) wglGetProcAddress("glBindRenderbuffer");
			glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) wglGetProcAddress("glDeleteRenderbuffers");
			glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) wglGetProcAddress("glGenRenderbuffers");
			glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) wglGetProcAddress("glRenderbufferStorage");
			glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetRenderbufferParameteriv");
			glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) wglGetProcAddress("glIsFramebuffer");
			glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebuffer");
			glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) wglGetProcAddress("glDeleteFramebuffers");
			glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffers");
			glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) wglGetProcAddress("glCheckFramebufferStatus");
			glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) wglGetProcAddress("glFramebufferTexture1D");
			glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2D");
			glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) wglGetProcAddress("glFramebufferTexture3D");
			glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) wglGetProcAddress("glFramebufferRenderbuffer");
			glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
			glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmap");
#else
#endif
		}
		else
		if (strstr(gl_extensions, "EXT_framebuffer_object"))
		{
            CCLOG("OpenGL: EXT_framebuffer_object is supported\n");
#ifdef Q_OS_WIN_1
			glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) wglGetProcAddress("glIsRenderbufferEXT");
			glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) wglGetProcAddress("glBindRenderbufferEXT");
			glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) wglGetProcAddress("glDeleteRenderbuffersEXT");
			glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) wglGetProcAddress("glGenRenderbuffersEXT");
			glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) wglGetProcAddress("glRenderbufferStorageEXT");
			glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetRenderbufferParameterivEXT");
			glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) wglGetProcAddress("glIsFramebufferEXT");
			glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebufferEXT");
			glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) wglGetProcAddress("glDeleteFramebuffersEXT");
			glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffersEXT");
			glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) wglGetProcAddress("glCheckFramebufferStatusEXT");
			glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) wglGetProcAddress("glFramebufferTexture1DEXT");
			glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2DEXT");
			glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) wglGetProcAddress("glFramebufferTexture3DEXT");
			glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) wglGetProcAddress("glFramebufferRenderbufferEXT");
			glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) wglGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
			glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmapEXT");
#else

#endif
		}
		else
		{
            CCLOG("OpenGL: No framebuffers extension is supported\n");
            CCLOG("OpenGL: Any call to Fbo will crash!\n");
			return false;
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
// impliment GLViewImpl
//////////////////////////////////////////////////////////////////////////
//static GLViewImpl* s_pMainWindow = NULL;

//static void mouseMove(QMouseEvent *event)
//{
//    do {
//        CC_BREAK_IF(s_pMainWindow == NULL);
//        s_pMainWindow->mouseMove(event);
//    } while (false);
//    return;
//}

//static void mousePress(QMouseEvent *event)
//{
//    do {
//        CC_BREAK_IF(s_pMainWindow == NULL);
//        s_pMainWindow->mousePress(event);
//    } while (false);
//    return;
//}

//static void mouseRelease(QMouseEvent *event)
//{
//    do {
//        CC_BREAK_IF(s_pMainWindow == NULL);
//        s_pMainWindow->mouseRelease(event);
//    } while(false);
//    return;
//}

//static void viewResize(QResizeEvent *event)
//{
//    do {
//        CC_BREAK_IF(s_pMainWindow == NULL);
//        s_pMainWindow->resize(event->size().width(), event->size().height());
//    } while (false);
//    return;
//}

GLViewImpl::GLViewImpl()
    : m_bCaptured(false)
    , m_fFrameZoomFactor(1.0f)
//    , m_bSupportTouch(false)
    , m_bIsInit(false)
//    , m_window(NULL)
    , m_fScreenScaleFactor(1.0f)
//    , m_glParentWidget(NULL)
//    , GLViewWindowMode(GLVIEW_WINDOW_MODE_FIXSIZE)
{
    m_pTouch = new Touch;
    m_pSet = new std::vector<Touch*>();
}

GLViewImpl::~GLViewImpl()
{
    CC_SAFE_DELETE(m_pTouch);
    CC_SAFE_DELETE(m_pSet);
}

bool GLViewImpl::initGL()
{
    if(m_bIsInit)
    {
        return false;
    }
    // check OpenGL version at first
    const GLubyte* glVersion = glGetString(GL_VERSION);
    CCLOG("OpenGL version = %s", glVersion);
    GLenum error_code = glGetError();

    if (glVersion == NULL && error_code != GL_NO_ERROR) {
        char szMessage[256] = {0};
        ::sprintf(szMessage, "Error: %d", error_code);
        MessageBox(szMessage, "Get OpenGL version error.");
        return false;
    }

    if ( glVersion == NULL || ::atof((const char*)glVersion) < 1.5 )
    {
        char strComplain[256] = {0};
        sprintf(strComplain,
                "OpenGL 1.5 or higher is required (your version is %s).",
                glVersion);
        MessageBox(strComplain, "OpenGL version too old");
        return false;
    }

    GLenum GlewInitResult = glewInit();
    if (GLEW_OK != GlewInitResult)
    {
        MessageBox((char *)glewGetErrorString(GlewInitResult), "OpenGL error");
        return false;
    }

    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader) {
        CCLOG("Ready for GLSL");
    }
    else {
        CCLOG("Not totally ready :(");
    }

    if (glewIsSupported("GL_VERSION_2_0")) {
        CCLOG("Ready for OpenGL 2.0");
    }
    else {
        CCLOG("OpenGL 2.0 not supported");
    }

    if(glew_dynamic_binding() == false) {
        MessageBox("No OpenGL framebuffer support. Please upgrade the driver of your video card.", "OpenGL error");
		return false;
	}

    // Enable point size by default on windows.
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    m_bIsInit = true;
    return true;
}

void GLViewImpl::destroyGL()
{
}

bool GLViewImpl::isOpenGLReady()
{
    return m_bIsInit;
}

void GLViewImpl::end()
{
    CC_SAFE_DELETE(m_pSet);
    CC_SAFE_DELETE(m_pTouch);
//    CC_SAFE_DELETE(m_glParentWidget);
//    CC_SAFE_DELETE(m_window);

//    s_pMainWindow = NULL;
    delete this;
}

void GLViewImpl::swapBuffers()
{
    if (m_bIsInit)
    {
        /* Swap buffers */
//        m_window->makeCurrent();
//        m_window->swapBuffers();
    }
}


void GLViewImpl::setIMEKeyboardState(bool /*bOpen*/)
{

}

void GLViewImpl::setViewName(const std::string &pszViewName)
{
    GLView::setViewName(pszViewName);
//    if (m_glParentWidget) {
//        m_glParentWidget->setWindowTitle(getViewName().c_str());
//    }
}

//void GLViewImpl::resize(int width, int height)
//{
//    do {
//        CC_BREAK_IF(!m_window);
//        CC_BREAK_IF (Director::getInstance()->getOpenGLView() == NULL);

//        if (GLViewWindowMode == GLVIEW_WINDOW_MODE_FIXSIZE) {
//            m_window->setFixedSize(width, height);
//            m_glParentWidget->setFixedSize(width, height);
//        }
//        else {
//            setDesignResolutionSize(width, height, ResolutionPolicy::EXACT_FIT);
//        }

//    } while(false);
//    return;
//}

void GLViewImpl::setFrameZoomFactor(float fZoomFactor)
{
//    CCTRACE();
    m_fFrameZoomFactor = fZoomFactor;
//    resize(_screenSize.width * fZoomFactor, _screenSize.height * fZoomFactor);
//    centerWindow();
    Director::getInstance()->setProjection(Director::getInstance()->getProjection());
}

float GLViewImpl::getFrameZoomFactor()
{
    return m_fFrameZoomFactor;
}

void GLViewImpl::setFrameSize(float width, float height)
{
    _screenSize = Size(width, height);
}

//void GLViewImpl::centerWindow()
//{
//    CCTRACE();
//    if (m_glParentWidget && !m_glParentWidget->parent()) {
//        QDesktopWidget *w = qApp->desktop();
//        QRect rect = w->screenGeometry();
//        m_glParentWidget->move((rect.width()-m_glParentWidget->width())/2.0f
//                              ,(rect.height()-m_glParentWidget->height())/2.0f);
//    }
//}

//void GLViewImpl::moveWindow(int left, int top)
//{
//    if (m_glParentWidget && !m_glParentWidget->parent()) {
//        m_glParentWidget->move(left, top);
//    }
//}

void GLViewImpl::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint)(m_WindowOrigin.x + x * _scaleX + _viewPortRect.origin.x),
               (GLint)(m_WindowOrigin.y + y * _scaleY + _viewPortRect.origin.y),
               (GLsizei)(w * _scaleX),
               (GLsizei)(h * _scaleY));
}

void GLViewImpl::resetViewPort()
{
    setViewPortInPoints(0, 0, _designResolutionSize.width, _designResolutionSize.height);
}

void GLViewImpl::setScissorInPoints(float x , float y , float w , float h)
{
//    CCTRACE();
    GLView::setScissorInPoints(x, y, w, h);
}


GLViewImpl* GLViewImpl::createWithRect(const std::string &viewName, const Rect& rect, ResolutionPolicy resolutionPolicy)
{
    // initialize director
    cocos2d::Director* pDirector = cocos2d::Director::getInstance();
    GLViewImpl* glView = new GLViewImpl;
    if(!glView->initGL()) {
        delete glView;
        glView = nullptr;
    }
    glView->setWindowRect(rect);
    glView->initializeDesignResolutionSize(rect.size.width, rect.size.height, resolutionPolicy);
    pDirector->setOpenGLView(glView);
    return glView;
}

void GLViewImpl::initializeDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy)
{
    CCASSERT(resolutionPolicy != ResolutionPolicy::UNKNOWN, "should set resolutionPolicy");

    if (width == 0.0f || height == 0.0f)
    {
        return;
    }

    _designResolutionSize.setSize(width, height);
    _resolutionPolicy = resolutionPolicy;

    if (_screenSize.width > 0 && _screenSize.height > 0
        && _designResolutionSize.width > 0 && _designResolutionSize.height > 0)
    {
        _scaleX = (float)_screenSize.width / _designResolutionSize.width;
        _scaleY = (float)_screenSize.height / _designResolutionSize.height;

        if (_resolutionPolicy == ResolutionPolicy::NO_BORDER)
        {
            _scaleX = _scaleY = MAX(_scaleX, _scaleY);
        }

        else if (_resolutionPolicy == ResolutionPolicy::SHOW_ALL)
        {
            _scaleX = _scaleY = MIN(_scaleX, _scaleY);
        }

        else if ( _resolutionPolicy == ResolutionPolicy::FIXED_HEIGHT) {
            _scaleX = _scaleY;
            _designResolutionSize.width = ceilf(_screenSize.width/_scaleX);
        }

        else if ( _resolutionPolicy == ResolutionPolicy::FIXED_WIDTH) {
            _scaleY = _scaleX;
            _designResolutionSize.height = ceilf(_screenSize.height/_scaleY);
        }

        // calculate the rect of viewport
        float viewPortW = _designResolutionSize.width * _scaleX;
        float viewPortH = _designResolutionSize.height * _scaleY;

        _viewPortRect.setRect((_screenSize.width - viewPortW) / 2, (_screenSize.height - viewPortH) / 2, viewPortW, viewPortH);

    }
}

void GLViewImpl::updateDesignResolutionSize()
{
    GLView::updateDesignResolutionSize();
}

void GLViewImpl::mouseMove(QMouseEvent *event)
{
    if (/*! m_pDelegate || */! m_pTouch)
        return;

    if (! m_bCaptured)
        return;

    m_pTouch->setTouchInfo(0, (float)(event->x()) / m_fScreenScaleFactor, (float)(event->y()) / m_fScreenScaleFactor);

    intptr_t id = m_pTouch->getID();
    float x = m_pTouch->getLocationInView().x;
    float y = m_pTouch->getLocationInView().y;
    this->handleTouchesMove(1, &id, &x, &y);

    return;
}

void GLViewImpl::setWindowRect(const Rect& rect)
{
    m_WindowOrigin = rect.origin;
    setFrameSize(rect.size.width, rect.size.height);
}

void GLViewImpl::mousePress(QMouseEvent *event)
{
    if (/*! m_pDelegate ||*/ ! m_pTouch)
        return;

    if (event->button() != Qt::LeftButton)
        return;

    m_bCaptured = true;

    m_pTouch->setTouchInfo(0, (float)(event->x()) / m_fScreenScaleFactor,
        (float)(event->y()) / m_fScreenScaleFactor);
    m_pSet->push_back(m_pTouch);

    intptr_t id = m_pTouch->getID();
    float x = m_pTouch->getLocationInView().x;
    float y = m_pTouch->getLocationInView().y;
    this->handleTouchesBegin(1, &id, &x, &y);

    return;
}

void GLViewImpl::mouseRelease(QMouseEvent *event)
{
    if (/*! m_pDelegate || */! m_pTouch)
        return;

    if (event->button() != Qt::LeftButton)
        return;

    m_bCaptured = false;

    m_pTouch->setTouchInfo(0, (float)(event->x()) / m_fScreenScaleFactor,
        (float)(event->y()) / m_fScreenScaleFactor);

    intptr_t id = m_pTouch->getID();
    float x = m_pTouch->getLocationInView().x;
    float y = m_pTouch->getLocationInView().y;
    this->handleTouchesEnd(1, &id, &x, &y);

    /// remove the touch info from m_pSet
    for( std::vector<Touch*>::iterator iteEachTouch = m_pSet->begin();
         iteEachTouch != m_pSet->end();
         ++iteEachTouch)
    {
        if (*iteEachTouch == m_pTouch) {
            m_pSet->erase(iteEachTouch);
            break;
        }
    }

    return;
}

void GLViewImpl::setAccelerometerKeyHook(ACCEL_PTRFUN func)
{
//    if (m_window)
//        m_window->setKeyEventFunc(func);
}

//QWidget *GLViewImpl::getGLWidget(void)
//{
//    return m_window;
//}

NS_CC_END
