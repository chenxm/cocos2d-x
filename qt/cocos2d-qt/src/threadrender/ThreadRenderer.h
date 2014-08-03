#ifndef THREADRENDERER_H
#define THREADRENDERER_H

#include <QQuickItem>

class RenderThread;

class ThreadRenderer : public QQuickItem
{
    Q_OBJECT

public:
    ThreadRenderer();

public slots:
    void ready();
    void onSizeChanged();

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
private:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
#ifndef QT_NO_IM
    virtual void inputMethodEvent(QInputMethodEvent *);
#endif
    virtual void focusInEvent(QFocusEvent *);
    virtual void focusOutEvent(QFocusEvent *);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseUngrabEvent(); // XXX todo - params?
    virtual void touchUngrabEvent();
#ifndef QT_NO_WHEELEVENT
    virtual void wheelEvent(QWheelEvent *event);
#endif
    virtual void touchEvent(QTouchEvent *event);
    virtual void hoverEnterEvent(QHoverEvent *event);
    virtual void hoverMoveEvent(QHoverEvent *event);
    virtual void hoverLeaveEvent(QHoverEvent *event);
#ifndef QT_NO_DRAGANDDROP
    virtual void dragEnterEvent(QDragEnterEvent *);
    virtual void dragMoveEvent(QDragMoveEvent *);
    virtual void dragLeaveEvent(QDragLeaveEvent *);
    virtual void dropEvent(QDropEvent *);
#endif


private:
    RenderThread *m_renderThread;
};

#endif
