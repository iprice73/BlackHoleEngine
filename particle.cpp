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
    updateTrace();
    setAcceleration(QPointF(0.f, 0.f)); // Reset acc to prevent infinity jumps
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

void Particle::updateTrace()
{
    const qsizetype max_trace = 1000;
    trace_.append(pos_);
    if (trace_.size() >= max_trace) {
        trace_.pop_front();
    }
}

