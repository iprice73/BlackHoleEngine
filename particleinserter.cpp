#include "particleinserter.h"

ParticleInserter::ParticleInserter()
{

}

Particle *ParticleInserter::createParticle()
{
    return new Particle(1, 100, begin_, calculateVelocity());
}

void ParticleInserter::setBegin(const QPointF &pos)
{
    begin_ = pos;
}

void ParticleInserter::setEnd(const QPointF &pos)
{
    end_ = pos;
}

QPointF ParticleInserter::calculateVelocity() const
{
    float dist_x, dist_y;
    dist_x = distanceX();
    dist_y = distanceY();
    dist_x = (dist_x >= 100) ? 100 : dist_x;
    dist_y = (dist_y >= 100) ? 100 : dist_y;

    return QPointF(dist_x / 10, dist_y / 10);
}

float ParticleInserter::distanceX() const
{
    return end_.x() - begin_.x();
}

float ParticleInserter::distanceY() const
{
    return end_.y() - begin_.y();
}

