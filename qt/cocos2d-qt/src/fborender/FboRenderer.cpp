#include "FboRenderer.h"

#include <QtGui/QOpenGLFramebufferObject>

#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>
#include "cocos2d.h"
#include "CCApplication.h"
#include "CCGLViewImpl.h"

void initializeWindow(const QRectF& rect)
{
    cocos2d::Rect windowRect(rect.x(), rect.y(), rect.width(), rect.height());
    cocos2d::GLViewImpl::createWithRect("test", windowRect, ResolutionPolicy::NO_BORDER);
}


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
    connect(this, SIGNAL(widthChanged()), this, SLOT(onSizeChanged()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(onSizeChanged()));
    QRectF rect = boundingRect();
    rect = mapRectToScene(rect);
    initializeWindow(rect);
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
