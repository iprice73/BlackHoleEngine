#ifndef PARTICLE_H
#define PARTICLE_H

#include <QList>
#include <QLineF>
#include <QtMath>

#include "stellarobject.h"

class Particle : public StellarObject
{
public:
    Particle(int id, float mass, const QPointF& pos, QPointF init_vel = QPointF(0.0f, 0.0f));

    QPointF getVel() const { return vel_; }
    QPointF getAcc() const { return acc_; }
    QList<QPointF> getTrace() const { return trace_; }

    float getSphericalR(const QPointF& bh) const { return sqrt(pow((pos_.x() - bh.x()), 2) + pow((pos_.y() - bh.y()), 2)); }
    float getSphericalRho(const QPointF& bh) const { return qAtan((pos_.y() - bh.y()) / (pos_.x() - bh.x())); }

    void updateState();
    void setAcceleration(const QPointF& acc);
    void adjustAcc(const QPointF& acc);

private:
    QPointF vel_;
    QPointF acc_;

    QList<QPointF> trace_;

    void updatePosition();
    void updateVelocity();
    void updateTrace();
};

#endif // PARTICLE_H
