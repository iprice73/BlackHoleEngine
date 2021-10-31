#ifndef PARTICLEINSERTER_H
#define PARTICLEINSERTER_H

#include <QObject>

#include "particle.h"

class ParticleInserter : public QObject
{
public:
    ParticleInserter();

    Particle* createParticle();
    void setBegin(const QPointF& pos);
    void setEnd(const QPointF& pos);

private:
    QPointF begin_;
    QPointF end_;

    QPointF calculateVelocity() const;
    float distanceX() const;
    float distanceY() const;
};

#endif // PARTICLEINSERTER_H
