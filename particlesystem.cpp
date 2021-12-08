#include "particlesystem.h"

#include <algorithm>
#include <QRandomGenerator>
#include <QDebug>

ParticleSystem::ParticleSystem()
{

}

void ParticleSystem::eraseOnCollision(Particle* p)
{
    auto it = std::find(particles_.begin(), particles_.end(), p);
    if (it != particles_.end()) {
        particles_.erase(it);
    }
}

void ParticleSystem::generate(int n)
{
    for (int i = 0; i < n; i++) {
    //        auto mass = QRandomGenerator::global()->bounded(100);
            auto mass = 100;
            auto x = QRandomGenerator::global()->bounded(100);
            auto y = QRandomGenerator::global()->bounded(100);
            auto* p = new Particle(i, mass, QPointF(x, y));
            particles_ << p;
        }
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

float ParticleSystem::rk4(float x0, float y0, float x, float h) const
{

}

template <class T>
void ParticleSystem::handleParticle(Particle* src, T* dest, float dist) {
    if (dist < 5) {
        eraseOnCollision(src);
        dest->addMass(src->getMass());
    } else {
        auto acc = calculateAccelerationTo<T>(src, dest, softDist(dist, 0.01));
        src->adjustAcc(acc);
    }
}

void ParticleSystem::manageParticles()
{
    for (const auto& src : particles_) {
        for (const auto& dest : particles_) {
            if (src != dest) {
                handleParticle<Particle>(src, dest, distanceTo<Particle>(src, dest));
            }
        }
    }
}

template <class T>
QPointF ParticleSystem::calculateAccelerationTo(Particle* src, T* dest, float dist) const
{
    const double G = 6.67e-3;
    float ax, ay;
    ax = G * dest->getMass() * (dest->getX() - src->getX()) / (pow(dist, 3));
    ay = G * dest->getMass() * (dest->getY() - src->getY()) / (pow(dist, 3));

    return QPointF(ax, ay);
}

void ParticleSystem::adjustBlackHole()
{
    for (const auto& p : particles_) {
        for (const auto& b : blackholes_) {
            handleParticle<BlackHole>(p, b, distanceTo<BlackHole>(p, b));
        }
    }
}

void ParticleSystem::updateParticles()
{
    manageParticles();
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
}

void ParticleSystem::eraseBlackHoles() {
    blackholes_.clear();
}

QPointF ParticleSystem::calculateSchwarzschildMetric() const
{
//    for (const auto& p : particles_) {
//        auto init_vel = p->getVel();

//    }
}


























