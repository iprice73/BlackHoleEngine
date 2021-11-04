#include "particlesystem.h"

#include <algorithm>
#include <QRandomGenerator>

ParticleSystem::ParticleSystem()
{
//    generateParticles(10);
      particles_ << new Particle(0, 0.00001, QPointF(100000, 1000000)); // pure evil
}

void ParticleSystem::generateParticles(int n)
{
    for (int i = 0; i < n; i++) {
//        auto mass = QRandomGenerator::global()->bounded(100);
        auto mass = 1;
        auto x = QRandomGenerator::global()->bounded(600);
        auto y = QRandomGenerator::global()->bounded(600);
        auto* p = new Particle(i, mass, QPointF(x, y));
        particles_ << p;
    }
}

void ParticleSystem::eraseOnCollision()
{
//    for (const auto& p : particles_) {
//        if (distance(p) < 30) {
//            auto it = std::find(particles_.begin(), particles_.end(), p);
//            if (it != particles_.end()) particles_.erase(it);
//        }
//    }
}

template <class T>
float ParticleSystem::distanceTo(Particle* src, T* dest) const
{
    return sqrt(pow(dest->getX() - src->getX(), 2) + pow(dest->getY() - src->getY(), 2));
}

float ParticleSystem::softDist(float dist, float e) const
{
    return sqrt(pow(dist, 2) + pow(e, 2));
}

template <class T>
QPointF ParticleSystem::calculateAccelerationTo(Particle* src, T* dest) const
{
    const double G = 1;
    float dist, ax, ay, e = 0.01;
    dist = softDist(distanceTo<T>(src, dest), e);
    ax = 0.03 * G * dest->getMass() * (dest->getX() - src->getX()) / (dist * dist);
    ay = 0.03 * G * dest->getMass() * (dest->getY() - src->getY()) / (dist * dist);

    return QPointF(ax, ay);
}

void ParticleSystem::calculateAcceleration() const
{
    for (qsizetype i = 0; i < particles_.size(); i++) {
        for (qsizetype j = 0; j < particles_.size(); j++) {
            if (i != j) {
                auto acc = calculateAccelerationTo<Particle>(particles_[i], particles_[j]);
                particles_[i]->setAcceleration(acc);
            }
        }
    }
}

void ParticleSystem::adjustBlackHole() const
{
    for (const auto& p : particles_) {
        for (const auto& b : blackholes_) {
            p->adjustAcc(calculateAccelerationTo<BlackHole>(p, b));
        }
    }
}

void ParticleSystem::updateParticles()
{
    eraseOnCollision();
    calculateAcceleration();
    adjustBlackHole();
}

void ParticleSystem::addParticle(Particle *p)
{
    particles_ << p;
}

void ParticleSystem::addBlackHole(BlackHole *b)
{
    blackholes_ << b;
}

void ParticleSystem::eraseParticles()
{
    particles_.clear();
    particles_ << new Particle(0, 0.00001, QPointF(100000, 1000000)); // pure evil 2
}

void ParticleSystem::eraseBlackHoles() {
    blackholes_.clear();
}
