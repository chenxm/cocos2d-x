#include "FboRenderer.h"

#include <QtGui/QOpenGLFramebufferObject>

#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>
#include "cocos2d.h"
#include "CCApplication.h"
#include "CCGLViewImpl.h"
#include "QtCoordinate.h"


class RealFboRenderer : public QQuickFramebufferObject::Renderer
{
public:
    RealFboRenderer()
    {
    }

    void render() {
        glDisable(GL_DEPTH_TEST);
        glClearColor(0, 0, 0, 0);
        cocos2d::GL::useProgram(0);
        cocos2d::Director::getInstance()->mainLoop();
        update();
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setSamples(4);
        return new QOpenGLFramebufferObject(size, format);
    }

};

QQuickFramebufferObject::Renderer *FboRenderer::createRenderer() const
{
    FboRenderer* renderer = const_cast<FboRenderer*>(this);
    renderer->setAcceptedMouseButtons(Qt::AllButtons);
    connect(window(), SIGNAL(widthChanged()), this, SLOT(onSizeChanged()));
    connect(window(), SIGNAL(heightChanged()), this, SLOT(onSizeChanged()));
    renderer->resetWindowRect();
    cocos2d::Application::getInstance()->applicationDidFinishLaunching();
    return new RealFboRenderer();
}

void FboRenderer::onSizeChanged()
{
    cocos2d::GLView* glView = cocos2d::Director::getInstance()->getOpenGLView();
    if(glView != nullptr)
    {
        glView->setFrameSize(width(), height());
        ((cocos2d::GLViewImpl*)glView)->updateDesignResolutionSize();
    }

}

void FboRenderer::resetWindowRect()
{
    QRectF rect = boundingRect();
    rect = mapRectToScene(rect);
    cocos2d::Rect windowRect(rect.x(), rect.y(), rect.width(), rect.height());
    cocos2d::GLViewImpl::createWithRect("test", windowRect, ResolutionPolicy::NO_BORDER);
}

void FboRenderer::keyPressEvent(QKeyEvent *event)
{
    QQuickItem::keyPressEvent(event);
}

void FboRenderer::keyReleaseEvent(QKeyEvent *event)
{
    QQuickItem::keyReleaseEvent(event);
}

#ifndef QT_NO_IM
void FboRenderer::inputMethodEvent(QInputMethodEvent *event)
{
    QQuickItem::inputMethodEvent(event);
}
#endif

void FboRenderer::focusInEvent(QFocusEvent *event)
{
    QQuickItem::focusInEvent(event);
}

void FboRenderer::focusOutEvent(QFocusEvent *event)
{
    QQuickItem::focusOutEvent(event);
}

void FboRenderer::mousePressEvent(QMouseEvent *event)
{
    QPointF position = event->localPos();
    cocos2d::Vec2 pos = FromQtToCocos(position, window()->devicePixelRatio(), height());
    cocos2d::GLViewImpl* glView = (cocos2d::GLViewImpl*)cocos2d::Director::getInstance()->getOpenGLView();
    intptr_t id = 0;
    glView->handleTouchesBegin(1, &id, &pos.x, &pos.y);
}

void FboRenderer::mouseMoveEvent(QMouseEvent *event)
{
    QPointF position = event->localPos();
    cocos2d::Vec2 pos = FromQtToCocos(position, window()->devicePixelRatio(), height());
    cocos2d::GLViewImpl* glView = (cocos2d::GLViewImpl*)cocos2d::Director::getInstance()->getOpenGLView();
    intptr_t id = 0;
    glView->handleTouchesMove(1, &id, &pos.x, &pos.y);
}

void FboRenderer::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF position = event->localPos();
    cocos2d::Vec2 pos = FromQtToCocos(position, window()->devicePixelRatio(), height());
    cocos2d::GLViewImpl* glView = (cocos2d::GLViewImpl*)cocos2d::Director::getInstance()->getOpenGLView();
    intptr_t id = 0;
    glView->handleTouchesEnd(1, &id, &pos.x, &pos.y);
}

void FboRenderer::mouseDoubleClickEvent(QMouseEvent *event)
{
    QQuickItem::mouseDoubleClickEvent(event);
}

void FboRenderer::mouseUngrabEvent() // XXX todo - params?
{
    QQuickItem::mouseUngrabEvent();
}

void FboRenderer::touchUngrabEvent()
{
    QQuickItem::touchUngrabEvent();
}

#ifndef QT_NO_WHEELEVENT
void FboRenderer::wheelEvent(QWheelEvent *event)
{
    QQuickItem::wheelEvent(event);
}
#endif

void FboRenderer::touchEvent(QTouchEvent *event)
{
    QQuickItem::touchEvent(event);
}

void FboRenderer::hoverEnterEvent(QHoverEvent *event)
{
    QQuickItem::hoverEnterEvent(event);
}

void FboRenderer::hoverMoveEvent(QHoverEvent *event)
{
    QQuickItem::hoverMoveEvent(event);
}

void FboRenderer::hoverLeaveEvent(QHoverEvent *event)
{
    QQuickItem::hoverLeaveEvent(event);
}

#ifndef QT_NO_DRAGANDDROP
void FboRenderer::dragEnterEvent(QDragEnterEvent *event)
{
    QQuickItem::dragEnterEvent(event);
}

void FboRenderer::dragMoveEvent(QDragMoveEvent *event)
{
    QQuickItem::dragMoveEvent(event);
}

void FboRenderer::dragLeaveEvent(QDragLeaveEvent *event)
{
    QQuickItem::dragLeaveEvent(event);
}

void FboRenderer::dropEvent(QDropEvent *event)
{
    QQuickItem::dropEvent(event);
}
#endif

