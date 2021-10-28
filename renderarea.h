#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QTimer>

#include "particlesystem.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    RenderArea();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    ParticleSystem sys_;
    QTimer timer_;

    void drawBlackHole(QPainter* painter) const;
    void drawParticles(QPainter* painter) const;

private slots:
    void updateSystem() const;
};

#endif // RENDERAREA_H
