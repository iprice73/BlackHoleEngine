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

    void blackHoleForce(Particle* p);
    void particleForce(Particle* p);

    void calculateGravityForces();

    float calculateDistance(float dx, float dy) const;

    template <class T>
    QPointF calculateAccelerationTo(Particle* frist, T* second) const;


    float rk4(float x0, float y0, float x, float h) const;


    void manageParticles();
    void eraseOnCollision(Particle* p);
    void generate(int n);

    void adjustBlackHole();
};

#endif // PARTICLESYSTEM_H
