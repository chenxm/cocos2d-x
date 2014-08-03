#ifndef OBJECTRENDERER_H
#define OBJECTRENDERER_H

#include <QtQuick/QQuickItem>
#include <QTimer>

class RealObjectRenderer;
class ObjectRenderer : public QQuickItem
{
    Q_OBJECT
public:
    ObjectRenderer();

public slots:
    void sync();
    void cleanup();
    void update();

private slots:
    void handleWindowChanged(QQuickWindow *win);
    void onWindowSpaceChanged();

private:
    void initializeWindow(const QRectF& rect);
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
    RealObjectRenderer *mRenderer;
    QTimer mTimer;
};

#endif // OBJECTRENDERER_H
