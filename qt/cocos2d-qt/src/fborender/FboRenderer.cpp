#include "FboRenderer.h"

#include <QtGui/QOpenGLFramebufferObject>

#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>
#include "cocos2d.h"
#include "CCApplication.h"

class RealFboRenderer : public QQuickFramebufferObject::Renderer
{
public:
    RealFboRenderer()
    {
        cocos2d::Application::getInstance()->applicationDidFinishLaunching();
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
    return new RealFboRenderer();
}
