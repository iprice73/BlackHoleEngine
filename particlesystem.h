#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "blackhole.h"
#include "particle.h"

#include <QList>

class ParticleSystem
{
public:
    ParticleSystem();

    const QList<Particle*>& getParticles() const { return particles_; }
    const QList<BlackHole*>& getBlackHoles() const { return blackholes_; }

    void updateParticles();

    void addParticle(Particle* p);
    void addBlackHole(BlackHole* b);
    void eraseParticles();
    void eraseBlackHoles();

private:
    QList<Particle*> particles_;
    QList<BlackHole*> blackholes_;

    template <class T>
    QPointF calculateAccelerationTo(Particle* src, T* dest) const;

    template <class T>
    float distanceTo(Particle* src, T* dest) const;

    float softDist(float dist, float e) const ;

    void eraseOnCollision(Particle* p);
    void generate(int n);

    void calculateAcceleration() const;
    void adjustBlackHole() const;
};

#endif // PARTICLESYSTEM_H
