#include "particlesystem.h"

#include <QRandomGenerator>

ParticleSystem::ParticleSystem()
{
    generateParticles(4);
}

void ParticleSystem::generateParticles(int n)
{
    for (int i = 0; i < n; i++) {
        auto* p = new Particle(200, QPointF(200, 200));
        particles_ << p;
    }
}

float ParticleSystem::distance(Particle* src, Particle* dest) const
{
    return sqrt(pow(dest->getX() - src->getX(), 2) + pow(dest->getY() - src->getY(), 2));
}

void ParticleSystem::calculateAcceleration() const
{

}

void ParticleSystem::updateParticles() const
{
    for (const auto& p : particles_) {
        p->updateState();
    }
}
