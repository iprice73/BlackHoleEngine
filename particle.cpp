#include "particle.h"

Particle::Particle()
{

}

Particle::Particle(float mass, const QPointF& point, QPointF init_vel) : mass_(mass), pos_(point), vel_(init_vel)
{

}

void Particle::updateState()
{
    updateVelocity();
    updatePosition();
}

void Particle::updatePosition()
{
    pos_ += vel_;
}

void Particle::updateVelocity()
{
    vel_ += acc_;
}

void Particle::setAcceleration(const QPointF &acc) {
    acc_ = acc;
}

void Particle::adjustAcc(const QPointF &acc)
{
    acc_ += acc;
}
