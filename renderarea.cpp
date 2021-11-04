#include "renderarea.h"

#include <QPainter>
#include <QStyleOption>

constexpr int timeStep = 17;

RenderArea::RenderArea() :
    sys_(ParticleSystem()),
    timer_(QTimer()),
    inserter_(ParticleInserter())
{
    connect(&timer_, SIGNAL(timeout()), this, SLOT(updateSystem()));
    timer_.start(timeStep);
}

void RenderArea::setInsertBody(bool state)
{
    insertingBody = state;
}

void RenderArea::setInsertBlackHole(bool state)
{
    insertingBlackHole = state;
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    drawBlackHole(&painter);
    drawParticles(&painter);
    drawSlingShot(&painter);
}

void RenderArea::mousePressEvent(QMouseEvent *event)
{
    auto pos = QWidget::mapFromGlobal(QCursor::pos());
    if (insertingBody) {
        inserter_.setBegin(pos);
    }
    if (insertingBlackHole) {
        insertBlackHole(pos);
    }
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (insertingBody) {
        inserter_.setEnd(QWidget::mapFromGlobal(QCursor::pos()));
        sys_.addParticle(inserter_.createParticle());
        inserter_.unbind();
    }
}

void RenderArea::mouseMoveEvent(QMouseEvent *event)
{
    if (insertingBody) {
        inserter_.setEnd(QWidget::mapFromGlobal(QCursor::pos()));
    }
}

void RenderArea::insertBody(const QPointF& pos)
{
    sys_.addParticle(new Particle(1, 100, pos, QPointF(2, 0)));
}

void RenderArea::insertBlackHole(const QPointF &pos)
{
    sys_.addBlackHole(new BlackHole(1, 10000, pos, 2, 2));
}

void RenderArea::drawBlackHole(QPainter *painter) const
{
    int bh_area = 30;
    auto bs = sys_.getBlackHoles();
    for (const auto* bh : bs) {
        QRadialGradient grad(bh->getPos(), bh_area);
        grad.setColorAt(0, QColor(0, 0, 0));
        grad.setColorAt(0.45, QColor(0, 0, 0));
        grad.setColorAt(0.50, QColor(255, 255, 255, 127));
        grad.setColorAt(1, QColor(255, 255, 255, 0));

        painter->setBrush(QBrush(grad));
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(bh->getPos(), bh_area, bh_area);
    }
}

void RenderArea::drawParticles(QPainter *painter) const
{
    auto ps = sys_.getParticles();
    painter->setBrush(QBrush(QColor(255,140,0)));
    for (const auto& body : ps) {
        painter->drawEllipse(body->getX(), body->getY(), 10, 10);
    }
}

void RenderArea::drawSlingShot(QPainter *painter) const
{
    painter->setPen(QPen(Qt::yellow, 2));
    painter->drawLine(inserter_.getBegin(), inserter_.getEnd());
}

void RenderArea::updateSystem()
{
    sys_.updateParticles();
    for (const auto& p : sys_.getParticles()) {
        p->updateState();
    }
    repaint();
}
