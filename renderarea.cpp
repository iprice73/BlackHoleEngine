#include "renderarea.h"

#include <QPainter>
#include <QStyleOption>
#include <QLineF>
#include <QMouseEvent>
#include <QtMath>
#include <QDebug>

constexpr int timeStep = 2;

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

void RenderArea::setDrawingTrace(bool state)
{
    drawingTrace = state;
}

void RenderArea::setDrawingRays(bool state) {
    drawingRays = state;
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
    if (!sys_.getBlackHoles().empty()) {
        drawRay(&painter, sys_.getBlackHoles()[0]);
    }
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

    if (drawingRays) {
        rayPoint_.setX(QWidget::mapFromGlobal(QCursor::pos()).x());
        rayPoint_.setY(QWidget::mapFromGlobal(QCursor::pos()).y());
        repaint();
    }
}

void RenderArea::insertBlackHole(const QPointF &pos)
{
    sys_.addBlackHole(new BlackHole(1, 1e9, pos, 2, 2));
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
    painter->setPen(QPen(QColor(255,140,0)));
    for (const auto& body : ps) {
        painter->drawEllipse(body->getX(), body->getY(), 10, 10);
        if (drawingTrace) {
            painter->drawLines(body->getTrace());
        }
    }
}

void RenderArea::drawSlingShot(QPainter *painter) const
{
    painter->setPen(QPen(Qt::yellow, 2));
    painter->drawLine(inserter_.getBegin(), inserter_.getEnd());
}

void RenderArea::drawRay(QPainter *painter, BlackHole* bh) const
{
    painter->setPen(QPen(Qt::yellow, 1));
    painter->drawEllipse(rayPoint_, 10, 10);
    QVector<QLineF> rays;

    if (bh) {
        auto bh_point = bh->getPos();
        qsizetype rayLength = 100;
        qreal theta = 90;
        auto start_point = rayPoint_;
        for (qsizetype i = 0; i < rayLength; i++) {
            QLineF angleLine;
            angleLine.setP1(start_point);
            angleLine.setLength(10);
            auto angle = atan2f(start_point.x() - bh_point.x(), start_point.y() - bh_point.y()) / M_PI * 180;
            theta += 350 / sqrt(pow(bh_point.x() - start_point.x(), 2) + pow(bh_point.y() - start_point.y(), 2));
            angleLine.setAngle(theta);
            start_point = angleLine.p2();
            rays << angleLine;
        }
    }

    painter->drawLines(rays);






//    QLineF angleLine1, angleLine2;
//    angleLine1.setP1(rayPoint_);
//    angleLine1.setAngle(0);
//    angleLine1.setLength(200);
//    angleLine2.setP1(angleLine1.p2());
//    angleLine2.setAngle(30);
//    angleLine2.setLength(200);
//    painter->drawLine(angleLine1);
//    rays << angleLine1 << angleLine2;
//    painter->drawLines(rays);
}

void RenderArea::updateSystem()
{
    sys_.updateParticles();
    for (const auto& p : sys_.getParticles()) {
        p->updateState();
    }
    repaint();
}
