#include "Bullet.h"
#include <QtMath>
#include <QPainter>
#include <QGraphicsScene>

Bullet::Bullet(qreal angle)
        : angle(angle), speed(8), radius(5)  // радиус шара
{
    setRotation(angle);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(16); // ~60 FPS
}

QRectF Bullet::boundingRect() const
{
    return QRectF(-radius, -radius, 2 * radius, 2 * radius);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::white);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(boundingRect());
}

void Bullet::move()
{
    qreal rad = qDegreesToRadians(angle);
    QPointF delta(speed * std::sin(rad), -speed * std::cos(rad));
    setPos(pos() + delta);

    // Удаляем пулю, если вылетела за границы сцены
    if (!scene()->sceneRect().contains(pos())) {
        scene()->removeItem(this);
        deleteLater();
    }
}
