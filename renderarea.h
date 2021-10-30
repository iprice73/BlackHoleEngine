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
    void mousePressEvent(QMouseEvent* event) override;

private:
    ParticleSystem sys_;
    QTimer timer_;

    bool insertingBodyEnabled = false;
    bool insertingBlackHolesEnabled = false;


    void drawBlackHole(QPainter* painter) const;
    void drawParticles(QPainter* painter) const;

private slots:
    void updateSystem();
};

#endif // RENDERAREA_H
