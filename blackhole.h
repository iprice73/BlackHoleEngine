#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include <QObject>
#include <QPointF>

class BlackHole : public QObject
{
public:
    BlackHole(const QPointF& pos, float mass, float r_s, float rot, float q);

    QPointF getPos() const { return pos_; }
    float getMass() const { return mass_; }
    float getRsch() const { return schwarzchildRadius_; }
    float getRot() const { return rotation_; }
    float getCharge() const { return charge_; }

private:
    QPointF pos_;
    float mass_;
    float schwarzchildRadius_;
    float rotation_;
    float charge_;


};

#endif // BLACKHOLE_H
