#ifndef PARTICLE_H
#define PARTICLE_H

#include <QObject>
#include <QPointF>

class Particle : public QObject
{
public:
    Particle();
    Particle(float mass, const QPointF& point, QPointF init_vel = QPointF(0.0f, 0.0f));

    float getMass() const { return mass_; }
    QPointF getPos() const { return pos_; }
    QPointF getVel() const { return vel_; }
    float getX() const { return pos_.x(); }
    float getY() const { return pos_.y(); }

    void updateState();
    void updatePosition();
    void updateVelocity();
    void setAcceleration(const QPointF& acc);
    void adjustAcc(const QPointF& acc);

private:
    float mass_;
    QPointF pos_;
    QPointF vel_;
    QPointF acc_;

};

#endif // PARTICLE_H
