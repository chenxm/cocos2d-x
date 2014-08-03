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
    RenderThread *m_renderThread;
};

#endif
