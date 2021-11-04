#include "particle.h"

#include <QtDebug>

Particle::Particle(int id, float mass, const QPointF& pos, QPointF init_vel) :
    StellarObject(id, mass, pos),
    vel_(init_vel)
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

