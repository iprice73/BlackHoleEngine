#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "stellarobject.h"

class BlackHole : public StellarObject
{
public:
    BlackHole(int id, float mass, const QPointF& pos, float rot, float q);

    float getRsch() const { return schwarzchildRadius_; }
    float getRot() const { return rotation_; }
    float getCharge() const { return charge_; }

private:

    float schwarzchildRadius_;
    float rotation_;
    float charge_;

};

#endif // BLACKHOLE_H
