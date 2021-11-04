#ifndef PARTICLE_H
#define PARTICLE_H

#include "stellarobject.h"

class Particle : public StellarObject
{
public:
    Particle(int id, float mass, const QPointF& pos, QPointF init_vel = QPointF(0.0f, 0.0f));

    QPointF getVel() const { return vel_; }

    void updateState();
    void updatePosition();
    void updateVelocity();
    void setAcceleration(const QPointF& acc);
    void adjustAcc(const QPointF& acc);

private:
    QPointF vel_;
    QPointF acc_;

};

#endif // PARTICLE_H
