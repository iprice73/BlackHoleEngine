#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QTimer>

#include "particleinserter.h"
#include "particlesystem.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    RenderArea();

    void setInsertBody(bool state);
    void setInsertBlackHole(bool state);
    void setDrawingTrace(bool state);
    void setDrawingRays(bool state);

    ParticleSystem& getSystem() { return sys_; }

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    ParticleSystem sys_;
    QTimer timer_;
    ParticleInserter inserter_;
    QPointF rayPoint_;

    bool insertingBody = false;
    bool insertingBlackHole = false;
    bool drawingTrace = false;
    bool drawingRays = false;

    void insertBlackHole(const QPointF& pos);

    void drawBlackHole(QPainter* painter) const;
    void drawParticles(QPainter* painter) const;
    void drawSlingShot(QPainter* painter) const;
    void drawRay(QPainter* painter, BlackHole* bh = nullptr) const;

private slots:
    void updateSystem();
};

#endif // RENDERAREA_H
