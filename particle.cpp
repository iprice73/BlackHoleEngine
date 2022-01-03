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
    updateAccForChart();
    updateVelOverTime();
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

float Particle::getMag(const QPointF &vec) const
{
    return sqrt(pow(vec.x(), 2) + pow(vec.y(), 2));
}

void Particle::updateAccForChart()
{
    static int i = 0;
    const qsizetype max_size = 5000;
    acc_over_time.append(QPointF(i++, getMag(getAcc())));
    if (acc_over_time.size() >= max_size) {
        acc_over_time.pop_front();
    }
}

void Particle::updateVelOverTime()
{
    static int i = 0;
    const qsizetype max_size = 5000;
    vel_over_time.append(QPointF(i++, getMag(getVel())));
    if (vel_over_time.size() >= max_size) {
        vel_over_time.pop_front();
    }
}

void Particle::updateTrace()
{
    const qsizetype max_trace = 1000;
    trace_.append(pos_);
    if (trace_.size() >= max_trace) {
        trace_.pop_front();
    }
}

