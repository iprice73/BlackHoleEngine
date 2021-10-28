#include "renderarea.h"

#include <QPainter>
#include <QStyleOption>

constexpr int timeStep = 17;

RenderArea::RenderArea() : sys_(ParticleSystem()), timer_(QTimer())
{
    connect(&timer_, SIGNAL(timeout()), this, SLOT(updateSystem()));
    timer_.start(timeStep);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    drawBlackHole(&painter);
    drawParticles(&painter);
}

void RenderArea::drawBlackHole(QPainter *painter) const
{
//    QPointF center(width() / 2, height() / 2);
//    QRadialGradient grad(center, bh->get_rs() / 20);
//    grad.setColorAt(0.000, QColor(0, 0, 0, 255));
//    grad.setColorAt(0.9, QColor(0, 0, 0, 255));
//    grad.setColorAt(1.000, QColor(0, 0, 0, 0.000));
    painter->setBrush(QBrush(QColor(0,0,0)));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(200, 200, 50, 50);
}

void RenderArea::drawParticles(QPainter *painter) const
{

}

void RenderArea::updateSystem() const
{

}
