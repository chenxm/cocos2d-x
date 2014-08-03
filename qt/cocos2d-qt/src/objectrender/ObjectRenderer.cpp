#include "ObjectRenderer.h"

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>

#include "cocos2d.h"
#include "CCApplication.h"
#include "CCGLViewImpl.h"


class RealObjectRenderer : public QObject
{
    Q_OBJECT
public:
    RealObjectRenderer();
    ~RealObjectRenderer();

    void setViewportSize(const QSize &size) { m_viewportSize = size; }

public slots:
    void paint();

private:
    QSize m_viewportSize;
};

RealObjectRenderer::RealObjectRenderer()
{
}

RealObjectRenderer::~RealObjectRenderer()
{
}

void RealObjectRenderer::paint()
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    cocos2d::GLViewImpl* glView = (cocos2d::GLViewImpl*)cocos2d::Director::getInstance()->getOpenGLView();
    glView->resetViewPort();

    cocos2d::GL::useProgram(0);
    cocos2d::Director::getInstance()->mainLoop();
}

ObjectRenderer::ObjectRenderer()
    : m_renderer(0)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(12);
}


void ObjectRenderer::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
        connect(win, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
        connect(win, SIGNAL(widthChanged(int)), this, SLOT(onWindowSpaceChanged()));
        connect(win, SIGNAL(heightChanged(int)), this, SLOT(onWindowSpaceChanged()));
//        connect(window(), SIGNAL(xChanged()), this, SLOT(onWindowSpaceChanged()));
//        connect(window(), SIGNAL(yChanged()), this, SLOT(onWindowSpaceChanged()));

        // If we allow QML to do the clearing, they would clear what we paint
        // and nothing would show.
        win->setClearBeforeRendering(false);
    }
}


void ObjectRenderer::cleanup()
{
    if (m_renderer) {
        delete m_renderer;
        m_renderer = 0;
    }
}

const cocos2d::Rect FromQtToGL(const QRectF& rect, float devicePixelRatio, int windowHeight)
{
    cocos2d::Rect windowRect(
                rect.x() * devicePixelRatio,
                (windowHeight - rect.y() - rect.height()) * devicePixelRatio,
                rect.width() * devicePixelRatio,
                rect.height() * devicePixelRatio);
    return windowRect;
}

void ObjectRenderer::initializeWindow(const QRectF& rect)
{
    cocos2d::Rect windowRect = FromQtToGL(rect, window()->devicePixelRatio(), window()->height());
    cocos2d::GLViewImpl::createWithRect("test", windowRect, ResolutionPolicy::EXACT_FIT);
}

void ObjectRenderer::onWindowSpaceChanged()
{
    CCLOG("onSizeChanged");
    if(m_renderer)
    {
        QRectF rect = boundingRect();
        rect = mapRectToScene(rect);
        cocos2d::Rect windowRect = FromQtToGL(rect, window()->devicePixelRatio(), window()->height());
        cocos2d::GLViewImpl* glView = (cocos2d::GLViewImpl*)cocos2d::Director::getInstance()->getOpenGLView();
        glView->setWindowRect(windowRect);
        glView->updateDesignResolutionSize();
    }
}

void ObjectRenderer::sync()
{
    if (!m_renderer) {
        QRectF rect = boundingRect();
        rect = mapRectToScene(rect);
        initializeWindow(rect);

        m_renderer = new RealObjectRenderer();
        connect(window(), SIGNAL(beforeRendering()), m_renderer, SLOT(paint()), Qt::DirectConnection);
        cocos2d::Application::getInstance()->applicationDidFinishLaunching();
    }
    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
}

void ObjectRenderer::update()
{
    if (window())
    {
        window()->update();
    }
}

#include "ObjectRenderer.moc"
