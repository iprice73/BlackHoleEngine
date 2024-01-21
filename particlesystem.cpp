#include "particlesystem.h"

#include <algorithm>
#include <QRandomGenerator>
#include <QDebug>

constexpr float G = 6.67e-8;

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

void ParticleSystem::blackHoleForce(Particle* p){
    for (const auto& bh : blackholes_) {
        auto acc = calculateAccelerationTo<BlackHole>(p, bh);
        p->adjustAcc(acc);
    }
}

void ParticleSystem::particleForce(Particle* p){
    for (const auto& other_p : particles_) {
        if (p != other_p) {
            auto acc = calculateAccelerationTo<Particle>(p, other_p);
            p->adjustAcc(acc);
        }
    }
}

float ParticleSystem::calculateDistance(float dx, float dy) const {
    return qSqrt(dx * dx + dy * dy);
}

template <class T>
QPointF ParticleSystem::calculateAccelerationTo(Particle* first, T* second) const {
    float dx = second->getX() - first->getX();
    float dy = second->getY() - first->getY();
    float distance = calculateDistance(dx, dy);

    auto second_mass = second->getMass();

    float acc_x = (G * second_mass * dx) / (distance * distance * distance);
    float acc_y = (G * second_mass * dy) / (distance * distance * distance);

    return {acc_x, acc_y};
}

void ParticleSystem::calculateGravityForces() {
    for (const auto& p : particles_) {
        particleForce(p);
        blackHoleForce(p);
    }
}

void ParticleSystem::updateParticles()
{
    calculateGravityForces();
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























