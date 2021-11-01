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

    bool insertingBody = false;
    bool insertingBlackHoles = false;

    void insertBody(const QPointF& pos);
    void insertBlackHole(const QPointF& pos);

    void drawBlackHole(QPainter* painter) const;
    void drawParticles(QPainter* painter) const;
    void drawSlingShot(QPainter* painter) const;

private slots:
    void updateSystem();
};

#endif // RENDERAREA_H
