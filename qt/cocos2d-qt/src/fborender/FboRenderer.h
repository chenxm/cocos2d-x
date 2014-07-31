#ifndef FBORENDERER_H
#define FBORENDERER_H

#include <QtQuick/QQuickFramebufferObject>

class FboRenderer : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    Renderer *createRenderer() const;
};

#endif //FBORENDERER_H
