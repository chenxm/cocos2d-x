#ifndef QTCOORDINATE_H
#define QTCOORDINATE_H
#include "cocos2d.h"
#include <QtCore>

const cocos2d::Rect FromQtToGL(const QRectF& rect, float devicePixelRatio, int windowHeight)
{
    cocos2d::Rect windowRect(
                rect.x() * devicePixelRatio,
                (windowHeight - rect.y() - rect.height()) * devicePixelRatio,
                rect.width() * devicePixelRatio,
                rect.height() * devicePixelRatio);
    return windowRect;
}

const cocos2d::Vec2 FromQtToGL(const QPointF& point, float devicePixelRatio, int windowHeight)
{
    cocos2d::Vec2 vec2(
                    point.x() * devicePixelRatio,
                    (windowHeight - point.y()) * devicePixelRatio
                );
    return vec2;
}

const cocos2d::Vec2 FromQtToCocos(const QPointF& point, float devicePixelRatio, int windowHeight)
{
    cocos2d::Vec2 vec2(
                    point.x() * devicePixelRatio,
                    point.y() * devicePixelRatio
                );
    return vec2;
}



#endif // QTCOORDINATE_H
