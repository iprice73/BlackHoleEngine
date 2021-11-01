#include "particle.h"

#include <QtDebug>

Particle::Particle()
{

}

Particle::Particle(int id, float mass, const QPointF& point, QPointF init_vel) :
    id_(id),
    mass_(mass),
    pos_(point),
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

bool Particle::operator==(const Particle &right)
{
    return (right.getID() == id_);
}
