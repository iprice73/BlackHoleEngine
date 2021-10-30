#include "renderarea.h"

#include <QPainter>
#include <QStyleOption>

constexpr int timeStep = 17;

RenderArea::RenderArea() : sys_(ParticleSystem(width(), height())), timer_(QTimer())
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

void RenderArea::mousePressEvent(QMouseEvent *event)
{

}

void RenderArea::drawBlackHole(QPainter *painter) const
{
    int bh_area = 60;
    auto bh = sys_.getBlackHole();
    QRadialGradient grad(bh->getPos(), bh_area);
    grad.setColorAt(0, QColor(0, 0, 0));
    grad.setColorAt(0.45, QColor(0, 0, 0));
    grad.setColorAt(0.50, QColor(255, 255, 255, 127));
    grad.setColorAt(1, QColor(255, 255, 255, 0));

    painter->setBrush(QBrush(grad));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(bh->getPos(), bh_area, bh_area);
}

void RenderArea::drawParticles(QPainter *painter) const
{
    auto ps = sys_.getParticles();
    painter->setBrush(QBrush(QColor(0,0,255)));
    for (const auto& body : ps) {
//        painter.drawPixmap(body.getPos().x(), body.getPos().y(), 20, 20, QPixmap(":/images/body.jpg"));
        painter->drawEllipse(body->getX(), body->getY(), 10, 10);
    }
}

void RenderArea::updateSystem()
{
    sys_.updateParticles();
    for (const auto& p : sys_.getParticles()) {
        p->updateState();
    }
    repaint();
}
