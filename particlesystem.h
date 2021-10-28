#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "blackhole.h"
#include "particle.h"

#include <QList>

class ParticleSystem
{
public:
    ParticleSystem();

private:
    QList<Particle*> particles_;
    BlackHole* bh_;

    // TODO: Add position to blackhole, newton metric and porper inserts of bodys

    void generateParticles(int n);
    float distance(Particle* src, Particle* dest) const;
    void calculateAcceleration() const;
    void updateParticles() const;
};

#endif // PARTICLESYSTEM_H
