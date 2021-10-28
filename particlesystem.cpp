#include "particlesystem.h"

#include <QRandomGenerator>

ParticleSystem::ParticleSystem() : bh_(new BlackHole(QPointF(300, 300), 600, 2, 2, 2))
{
    generateParticles(5);
}

void ParticleSystem::generateParticles(int n)
{
    for (int i = 0; i < n; i++) {
//        auto mass = QRandomGenerator::global()->bounded(200);
        auto mass = 200;
        auto x = QRandomGenerator::global()->bounded(600);
        auto y = QRandomGenerator::global()->bounded(600);
        auto* p = new Particle(mass, QPointF(x, y));
        particles_ << p;
    }
}

float ParticleSystem::distance(Particle* src, Particle* dest) const
{
    QPointF pos = (dest) ? dest->getPos() : bh_->getPos();
    return sqrt(pow(pos.x() - src->getX(), 2) + pow(pos.y() - src->getY(), 2));
}

QPointF ParticleSystem::calculateAcceleration(Particle* src, Particle* dest) const {
    QPointF pos = (dest) ? dest->getPos() : bh_->getPos();
    float mass = (dest) ? dest->getMass() : bh_->getMass();

    float dist, ax, ay;
    dist = distance(src, dest);
    ax = 0.03 * mass * (pos.x() - src->getX()) / (dist * dist);
    ay = 0.03 * mass * (pos.y() - src->getY()) / (dist * dist);

    return QPointF(ax, ay);
}

void ParticleSystem::calculateAcceleration() const
{
    for (qsizetype i = 0; i < particles_.size(); i++) {
        for (qsizetype j = 0; j < particles_.size(); j++) {
            if (i != j) {
                auto acc = calculateAcceleration(particles_[i], particles_[j]);
                particles_[i]->setAcceleration(acc);
            }
        }
    }
}

void ParticleSystem::adjustBlackHole() const
{
    for (const auto& p : particles_) {
        p->adjustAcc(calculateAcceleration(p));
    }
}

void ParticleSystem::updateParticles() const
{
    calculateAcceleration();
    adjustBlackHole();
}
