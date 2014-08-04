#include "ObjectRenderer.h"

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>

#include "cocos2d.h"
#include "Application.h"
#include "GLViewImpl.h"
#include "QtCoordinate.h"


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
    cocos2d::GLViewImpl* glView = (cocos2d::GLViewImpl*)cocos2d::Director::getInstance()->getOpenGLView();
    if(glView == nullptr)
    {
        return;
    }
    glClearColor(0, 0, 0, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glView->resetViewPort();

    cocos2d::GL::useProgram(0);
    cocos2d::Director::getInstance()->mainLoop();
}

ObjectRenderer::ObjectRenderer()
    : mRenderer(0)
{
    setAcceptedMouseButtons(Qt::AllButtons);
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(update()));
    mTimer.start(12);
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
    if (mRenderer) {
        delete mRenderer;
        mRenderer = 0;
    }
}

void ObjectRenderer::resetWindowRect()
{
    QRectF rect = boundingRect();
    rect = mapRectToScene(rect);
    cocos2d::Rect windowRect = FromQtToGL(rect, window()->devicePixelRatio(), window()->height());
    cocos2d::GLViewImpl::createWithRect("test", windowRect, ResolutionPolicy::EXACT_FIT);
}

void ObjectRenderer::onWindowSpaceChanged()
{
    CCLOG("onSizeChanged");
    if(mRenderer)
    {
        QRectF rect = boundingRect();
        rect = mapRectToScene(rect);
        cocos2d::Rect windowRect = FromQtToGL(rect, window()->devicePixelRatio(), window()->height());
        cocos2d::GLViewImpl* glView = (cocos2d::GLViewImpl*)cocos2d::Director::getInstance()->getOpenGLView();
        glView->setViewportRect(windowRect);
        glView->updateDesignResolutionSize();
    }
}

void ObjectRenderer::sync()
{
    if (!mRenderer) {
        resetWindowRect();
        mRenderer = new RealObjectRenderer();
        connect(window(), SIGNAL(beforeRendering()), mRenderer, SLOT(paint()), Qt::DirectConnection);
        cocos2d::Application::getInstance()->applicationDidFinishLaunching();
    }
    mRenderer->setViewportSize(window()->size() * window()->devicePixelRatio());
}

void ObjectRenderer::update()
{
    if (window())
    {
        window()->update();
    }
}

void ObjectRenderer::keyPressEvent(QKeyEvent *event)
{
    QQuickItem::keyPressEvent(event);
}

void ObjectRenderer::keyReleaseEvent(QKeyEvent *event)
{
    QQuickItem::keyReleaseEvent(event);
}

#ifndef QT_NO_IM
void ObjectRenderer::inputMethodEvent(QInputMethodEvent *event)
{
    QQuickItem::inputMethodEvent(event);
}
#endif

void ObjectRenderer::focusInEvent(QFocusEvent *event)
{
    QQuickItem::focusInEvent(event);
}

void ObjectRenderer::focusOutEvent(QFocusEvent *event)
{
    QQuickItem::focusOutEvent(event);
}

void ObjectRenderer::mousePressEvent(QMouseEvent *event)
{
    QPointF position = event->localPos();
    cocos2d::Vec2 pos = FromQtToCocos(position, window()->devicePixelRatio(), height());
    cocos2d::GLViewImpl* glView = (cocos2d::GLViewImpl*)cocos2d::Director::getInstance()->getOpenGLView();
    intptr_t id = 0;
    glView->handleTouchesBegin(1, &id, &pos.x, &pos.y);
}

void ObjectRenderer::mouseMoveEvent(QMouseEvent *event)
{
    QPointF position = event->localPos();
    cocos2d::Vec2 pos = FromQtToCocos(position, window()->devicePixelRatio(), height());
    cocos2d::GLViewImpl* glView = (cocos2d::GLViewImpl*)cocos2d::Director::getInstance()->getOpenGLView();
    intptr_t id = 0;
    glView->handleTouchesMove(1, &id, &pos.x, &pos.y);
}

void ObjectRenderer::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF position = event->localPos();
    cocos2d::Vec2 pos = FromQtToCocos(position, window()->devicePixelRatio(), height());
    cocos2d::GLViewImpl* glView = (cocos2d::GLViewImpl*)cocos2d::Director::getInstance()->getOpenGLView();
    intptr_t id = 0;
    glView->handleTouchesEnd(1, &id, &pos.x, &pos.y);
}

void ObjectRenderer::mouseDoubleClickEvent(QMouseEvent *event)
{
    QQuickItem::mouseDoubleClickEvent(event);
}

void ObjectRenderer::mouseUngrabEvent() // XXX todo - params?
{
    QQuickItem::mouseUngrabEvent();
}

void ObjectRenderer::touchUngrabEvent()
{
    QQuickItem::touchUngrabEvent();
}

#ifndef QT_NO_WHEELEVENT
void ObjectRenderer::wheelEvent(QWheelEvent *event)
{
    QQuickItem::wheelEvent(event);
}
#endif

void ObjectRenderer::touchEvent(QTouchEvent *event)
{
    QQuickItem::touchEvent(event);
}

void ObjectRenderer::hoverEnterEvent(QHoverEvent *event)
{
    QQuickItem::hoverEnterEvent(event);
}

void ObjectRenderer::hoverMoveEvent(QHoverEvent *event)
{
    QQuickItem::hoverMoveEvent(event);
}

void ObjectRenderer::hoverLeaveEvent(QHoverEvent *event)
{
    QQuickItem::hoverLeaveEvent(event);
}

#ifndef QT_NO_DRAGANDDROP
void ObjectRenderer::dragEnterEvent(QDragEnterEvent *event)
{
    QQuickItem::dragEnterEvent(event);
}

void ObjectRenderer::dragMoveEvent(QDragMoveEvent *event)
{
    QQuickItem::dragMoveEvent(event);
}

void ObjectRenderer::dragLeaveEvent(QDragLeaveEvent *event)
{
    QQuickItem::dragLeaveEvent(event);
}

void ObjectRenderer::dropEvent(QDropEvent *event)
{
    QQuickItem::dropEvent(event);
}
#endif


#include "ObjectRenderer.moc"
