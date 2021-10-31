#include "particlesystem.h"

#include <algorithm>
#include <QRandomGenerator>

ParticleSystem::ParticleSystem(int w, int h) : bh_(new BlackHole(QPointF(w / 2, h / 2), 10000, 2, 2, 2))
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
    for (const auto& p : particles_) {
        if (distance(p) < 30) {
            auto it = std::find(particles_.begin(), particles_.end(), p);
            if (it != particles_.end()) particles_.erase(it);
        }
    }
}

float ParticleSystem::distance(Particle* src, Particle* dest) const
{
    QPointF pos = (dest) ? dest->getPos() : bh_->getPos();
    return sqrt(pow(pos.x() - src->getX(), 2) + pow(pos.y() - src->getY(), 2));
}

float ParticleSystem::softDist(float dist, float e) const
{
    return sqrt(pow(dist, 2) + pow(e, 2));
}

QPointF ParticleSystem::calculateAcceleration(Particle* src, Particle* dest) const {
    QPointF pos = (dest) ? dest->getPos() : bh_->getPos();
    float mass = (dest) ? dest->getMass() : bh_->getMass();
    const double G = 1;
    float dist, ax, ay, e = 0.01;
    dist = softDist(distance(src, dest), e);
    ax = 0.03 * G * mass * (pos.x() - src->getX()) / (dist * dist);
    ay = 0.03 * G * mass * (pos.y() - src->getY()) / (dist * dist);

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

void ParticleSystem::eraseAll()
{
    particles_.clear();
    particles_ << new Particle(0, 0.00001, QPointF(100000, 1000000)); // pure evil 2
}
