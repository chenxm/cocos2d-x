#include "GLViewQtImpl.h"


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
GLViewQtImpl::GLViewQtImpl()
    : mIsInitialed(false)
    , mFrameZoomFactor(1.0f)
{
}

GLViewQtImpl::~GLViewQtImpl()
{
}

bool GLViewQtImpl::initGL()
{
    if(mIsInitialed)
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

    mIsInitialed = true;
    return true;
}

void GLViewQtImpl::destroyGL()
{
}

bool GLViewQtImpl::isOpenGLReady()
{
    return mIsInitialed;
}

void GLViewQtImpl::end()
{
    delete this;
}

void GLViewQtImpl::swapBuffers()
{
    if (mIsInitialed)
    {
        /* Swap buffers */
    }
}


void GLViewQtImpl::setIMEKeyboardState(bool /*bOpen*/)
{

}

void GLViewQtImpl::setViewName(const std::string &pszViewName)
{
    GLView::setViewName(pszViewName);
}

void GLViewQtImpl::setFrameZoomFactor(float fZoomFactor)
{
    mFrameZoomFactor = fZoomFactor;
}

float GLViewQtImpl::getFrameZoomFactor()
{
    return mFrameZoomFactor;
}

void GLViewQtImpl::setFrameSize(float width, float height)
{
    _screenSize = Size(width, height);
}

void GLViewQtImpl::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint)(mViewportOrigin.x + x * _scaleX + _viewPortRect.origin.x),
               (GLint)(mViewportOrigin.y + y * _scaleY + _viewPortRect.origin.y),
               (GLsizei)(w * _scaleX),
               (GLsizei)(h * _scaleY));
}

void GLViewQtImpl::resetViewPort()
{
    setViewPortInPoints(0, 0, _designResolutionSize.width, _designResolutionSize.height);
}

void GLViewQtImpl::setScissorInPoints(float x , float y , float w , float h)
{
    GLView::setScissorInPoints(x, y, w, h);
}


GLViewQtImpl* GLViewQtImpl::createWithRect(const std::string &viewName, const Rect& rect, ResolutionPolicy resolutionPolicy)
{
    // initialize director
    cocos2d::Director* pDirector = cocos2d::Director::getInstance();
    GLViewQtImpl* glView = new GLViewQtImpl;
    if(!glView->initGL()) {
        delete glView;
        glView = nullptr;
    }
    glView->setViewportRect(rect);
    glView->initializeDesignResolutionSize(rect.size.width, rect.size.height, resolutionPolicy);
    pDirector->setOpenGLView(glView);
    return glView;
}

void GLViewQtImpl::initializeDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy)
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

void GLViewQtImpl::updateDesignResolutionSize()
{
    GLView::updateDesignResolutionSize();
}

void GLViewQtImpl::setViewportRect(const Rect& rect)
{
    setViewportOrigin(rect.origin);
    setFrameSize(rect.size.width, rect.size.height);
}

void GLViewQtImpl::setViewportOrigin(const Vec2& point)
{
    mViewportOrigin = point;
}

NS_CC_END
