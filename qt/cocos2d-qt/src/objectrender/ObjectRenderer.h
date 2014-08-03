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
    RealObjectRenderer *m_renderer;
    QTimer timer;
};

#endif // OBJECTRENDERER_H
