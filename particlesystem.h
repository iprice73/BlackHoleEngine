#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "blackhole.h"
#include "particle.h"

#include <QList>

class ParticleSystem
{
public:
    ParticleSystem(int w, int h);

    const BlackHole* getBlackHole() const { return bh_; }
    const QList<Particle*>& getParticles() const { return particles_; }
    void updateParticles();

    void addParticle(Particle* p);
    void eraseAll();

private:
    QList<Particle*> particles_;
    BlackHole* bh_;

    // TODO: newton metric and porper inserts of bodys

    QPointF calculateAcceleration(Particle* src, Particle* dest = nullptr) const;
    float distance(Particle* src, Particle* dest = nullptr) const;
    float softDist(float dist, float e) const ;

    void generateParticles(int n);
    void eraseOnCollision();

    void calculateAcceleration() const;
    void adjustBlackHole() const;
};

#endif // PARTICLESYSTEM_H
