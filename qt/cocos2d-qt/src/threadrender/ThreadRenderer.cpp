#include "ThreadRenderer.h"
#include <QtCore/QMutex>
#include <QtCore/QThread>

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtGui/QGuiApplication>
#include <QtGui/QOffscreenSurface>

#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>
#include "cocos2d.h"
#include "Application.h"
#include "GLViewImpl.h"
#include "QtCoordinate.h"


class RenderThreadPool : public QObject
{
    Q_OBJECT
public:
    static RenderThreadPool& Instance()
    {
        if(!instance.initialized)
        {
            instance.initialized = true;
            QObject::connect(QGuiApplication::instance(),
                         SIGNAL(aboutToQuit()),
                         &RenderThreadPool::Instance(),
                         SLOT(aboutToQuit()),
                         Qt::QueuedConnection
                         );
        }
        return instance;
    }
public:
    RenderThreadPool();
    RenderThreadPool& operator<<(QThread* thread)
    {
       threads << thread;
       return *this;
    }
    void remove(QThread* thread)
    {
        threads.removeAll(thread);
    }

public slots:
   void aboutToQuit()
   {
       foreach (QThread *t, threads)
       {
           t->wait();
           delete t;
       }
       initialized = false;
   }

private:
    QList<QThread *> threads;
    bool initialized;
    static RenderThreadPool instance;
};

RenderThreadPool::RenderThreadPool() : initialized(false)
{

}

RenderThreadPool RenderThreadPool::instance;

/*
 * The render thread shares a context with the scene graph and will
 * render into two separate FBOs, one to use for display and one
 * to use for rendering
 */
class RenderThread : public QThread
{
    Q_OBJECT
public:
    RenderThread(const QSize &size)
        : surface(0)
        , context(0)
        , m_renderFbo(0)
        , m_displayFbo(0)
        , m_size(size)
    {
        RenderThreadPool::Instance() << this;
    }

    QOffscreenSurface *surface;
    QOpenGLContext *context;

public slots:
    void renderNext()
    {
        context->makeCurrent(surface);

        if (!m_renderFbo) {
            // Initialize the buffers and renderer
            QOpenGLFramebufferObjectFormat format;
            format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
            m_renderFbo = new QOpenGLFramebufferObject(m_size, format);
            m_displayFbo = new QOpenGLFramebufferObject(m_size, format);

            initializeWindow(m_size);

            cocos2d::Application::getInstance()->applicationDidFinishLaunching();
        }

        m_renderFbo->bind();
        glViewport(0, 0, m_size.width(), m_size.height());

        cocos2d::Director::getInstance()->mainLoop();


        // We need to flush the contents to the FBO before posting
        // the texture to the other thread, otherwise, we might
        // get unexpected results.
        glFlush();

        m_renderFbo->bindDefault();
        qSwap(m_renderFbo, m_displayFbo);

        emit textureReady(m_displayFbo->texture(), m_size);
    }

    void shutDown()
    {
        context->makeCurrent(surface);
        delete m_renderFbo;
        delete m_displayFbo;
        context->doneCurrent();
        delete context;

        // schedule this to be deleted only after we're done cleaning up
        surface->deleteLater();

        // Stop event processing, move the thread to GUI and make sure it is deleted.
        exit();
        moveToThread(QGuiApplication::instance()->thread());
    }

private:
    void initializeWindow(const QSizeF& size)
    {
        cocos2d::Rect windowRect(0, 0, size.width(), size.height());
        cocos2d::GLViewImpl::createWithRect("test", windowRect, ResolutionPolicy::EXACT_FIT);
    }

signals:
    void textureReady(int id, const QSize &size);

private:
    QOpenGLFramebufferObject *m_renderFbo;
    QOpenGLFramebufferObject *m_displayFbo;

    QSize m_size;
};



class TextureNode : public QObject, public QSGSimpleTextureNode
{
    Q_OBJECT

public:
    TextureNode(QQuickWindow *window)
        : m_id(0)
        , m_size(0, 0)
        , m_texture(0)
        , m_window(window)
    {
        // Our texture node must have a texture, so use the default 0 texture.
        m_texture = m_window->createTextureFromId(0, QSize(1, 1));
        setTexture(m_texture);
        setFiltering(QSGTexture::Linear);
    }

    ~TextureNode()
    {
        delete m_texture;
    }

signals:
    void textureInUse();
    void pendingNewTexture();

public slots:

    // This function gets called on the FBO rendering thread and will store the
    // texture id and size and schedule an update on the window.
    void newTexture(int id, const QSize &size) {
        m_mutex.lock();
        m_id = id;
        m_size = size;
        m_mutex.unlock();

        // We cannot call QQuickWindow::update directly here, as this is only allowed
        // from the rendering thread or GUI thread.
        emit pendingNewTexture();
    }


    // Before the scene graph starts to render, we update to the pending texture
    void prepareNode() {
        m_mutex.lock();
        int newId = m_id;
        QSize size = m_size;
        m_id = 0;
        m_mutex.unlock();
        if (newId) {
            delete m_texture;
            m_texture = m_window->createTextureFromId(newId, size);
            setTexture(m_texture);

            // This will notify the rendering thread that the texture is now being rendered
            // and it can start rendering to the other one.
            emit textureInUse();
        }
    }

private:

    int m_id;
    QSize m_size;

    QMutex m_mutex;

    QSGTexture *m_texture;
    QQuickWindow *m_window;
};

ThreadRenderer::ThreadRenderer()
    : m_renderThread(0)
{
    setAcceptedMouseButtons(Qt::AllButtons);
    connect(this, SIGNAL(widthChanged()), this, SLOT(onSizeChanged()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(onSizeChanged()));
    setFlag(ItemHasContents, true);

    m_renderThread = new RenderThread(QSize(1024, 768));
}

void ThreadRenderer::ready()
{
    m_renderThread->surface = new QOffscreenSurface();
    m_renderThread->surface->setFormat(m_renderThread->context->format());
    m_renderThread->surface->create();

    m_renderThread->moveToThread(m_renderThread);

    connect(window(), SIGNAL(sceneGraphInvalidated()), m_renderThread, SLOT(shutDown()), Qt::QueuedConnection);

    m_renderThread->start();
    update();
}

QSGNode *ThreadRenderer::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    TextureNode *node = static_cast<TextureNode *>(oldNode);

    if (!m_renderThread->context) {
        QOpenGLContext *current = window()->openglContext();
        // Some GL implementations requres that the currently bound context is
        // made non-current before we set up sharing, so we doneCurrent here
        // and makeCurrent down below while setting up our own context.
        current->doneCurrent();

        m_renderThread->context = new QOpenGLContext();
        m_renderThread->context->setFormat(current->format());
        m_renderThread->context->setShareContext(current);
        m_renderThread->context->create();
        m_renderThread->context->moveToThread(m_renderThread);

        current->makeCurrent(window());

        QMetaObject::invokeMethod(this, "ready");
        return 0;
    }

    if (!node) {
        node = new TextureNode(window());

        /* Set up connections to get the production of FBO textures in sync with vsync on the
         * rendering thread.
         *
         * When a new texture is ready on the rendering thread, we use a direct connection to
         * the texture node to let it know a new texture can be used. The node will then
         * emit pendingNewTexture which we bind to QQuickWindow::update to schedule a redraw.
         *
         * When the scene graph starts rendering the next frame, the prepareNode() function
         * is used to update the node with the new texture. Once it completes, it emits
         * textureInUse() which we connect to the FBO rendering thread's renderNext() to have
         * it start producing content into its current "back buffer".
         *
         * This FBO rendering pipeline is throttled by vsync on the scene graph rendering thread.
         */
        connect(m_renderThread, SIGNAL(textureReady(int,QSize)), node, SLOT(newTexture(int,QSize)), Qt::DirectConnection);
        connect(node, SIGNAL(pendingNewTexture()), window(), SLOT(update()), Qt::QueuedConnection);
        connect(window(), SIGNAL(beforeRendering()), node, SLOT(prepareNode()), Qt::DirectConnection);
        connect(node, SIGNAL(textureInUse()), m_renderThread, SLOT(renderNext()), Qt::QueuedConnection);

        // Get the production of FBO textures started..
        QMetaObject::invokeMethod(m_renderThread, "renderNext", Qt::QueuedConnection);
    }

    node->setRect(boundingRect());

    return node;
}

void ThreadRenderer::onSizeChanged()
{
    CCLOG("onSizeChanged");
}

void ThreadRenderer::keyPressEvent(QKeyEvent *event)
{
    QQuickItem::keyPressEvent(event);
}

void ThreadRenderer::keyReleaseEvent(QKeyEvent *event)
{
    QQuickItem::keyReleaseEvent(event);
}

#ifndef QT_NO_IM
void ThreadRenderer::inputMethodEvent(QInputMethodEvent *event)
{
    QQuickItem::inputMethodEvent(event);
}
#endif

void ThreadRenderer::focusInEvent(QFocusEvent *event)
{
    QQuickItem::focusInEvent(event);
}

void ThreadRenderer::focusOutEvent(QFocusEvent *event)
{
    QQuickItem::focusOutEvent(event);
}

void ThreadRenderer::mousePressEvent(QMouseEvent *event)
{
    QPointF position = event->localPos();
    cocos2d::Vec2 pos = FromQtToCocos(position, window()->devicePixelRatio(), height());
    cocos2d::GLViewImpl* glView = (cocos2d::GLViewImpl*)cocos2d::Director::getInstance()->getOpenGLView();
    intptr_t id = 0;
    glView->handleTouchesBegin(1, &id, &pos.x, &pos.y);
}

void ThreadRenderer::mouseMoveEvent(QMouseEvent *event)
{
    QPointF position = event->localPos();
    cocos2d::Vec2 pos = FromQtToCocos(position, window()->devicePixelRatio(), height());
    cocos2d::GLViewImpl* glView = (cocos2d::GLViewImpl*)cocos2d::Director::getInstance()->getOpenGLView();
    intptr_t id = 0;
    glView->handleTouchesMove(1, &id, &pos.x, &pos.y);
}

void ThreadRenderer::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF position = event->localPos();
    cocos2d::Vec2 pos = FromQtToCocos(position, window()->devicePixelRatio(), height());
    cocos2d::GLViewImpl* glView = (cocos2d::GLViewImpl*)cocos2d::Director::getInstance()->getOpenGLView();
    intptr_t id = 0;
    glView->handleTouchesEnd(1, &id, &pos.x, &pos.y);
}

void ThreadRenderer::mouseDoubleClickEvent(QMouseEvent *event)
{
    QQuickItem::mouseDoubleClickEvent(event);
}

void ThreadRenderer::mouseUngrabEvent() // XXX todo - params?
{
    QQuickItem::mouseUngrabEvent();
}

void ThreadRenderer::touchUngrabEvent()
{
    QQuickItem::touchUngrabEvent();
}

#ifndef QT_NO_WHEELEVENT
void ThreadRenderer::wheelEvent(QWheelEvent *event)
{
    QQuickItem::wheelEvent(event);
}
#endif

void ThreadRenderer::touchEvent(QTouchEvent *event)
{
    QQuickItem::touchEvent(event);
}

void ThreadRenderer::hoverEnterEvent(QHoverEvent *event)
{
    QQuickItem::hoverEnterEvent(event);
}

void ThreadRenderer::hoverMoveEvent(QHoverEvent *event)
{
    QQuickItem::hoverMoveEvent(event);
}

void ThreadRenderer::hoverLeaveEvent(QHoverEvent *event)
{
    QQuickItem::hoverLeaveEvent(event);
}

#ifndef QT_NO_DRAGANDDROP
void ThreadRenderer::dragEnterEvent(QDragEnterEvent *event)
{
    QQuickItem::dragEnterEvent(event);
}

void ThreadRenderer::dragMoveEvent(QDragMoveEvent *event)
{
    QQuickItem::dragMoveEvent(event);
}

void ThreadRenderer::dragLeaveEvent(QDragLeaveEvent *event)
{
    QQuickItem::dragLeaveEvent(event);
}

void ThreadRenderer::dropEvent(QDropEvent *event)
{
    QQuickItem::dropEvent(event);
}
#endif


#include "ThreadRenderer.moc"
