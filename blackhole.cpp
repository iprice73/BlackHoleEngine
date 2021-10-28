#include "blackhole.h"

BlackHole::BlackHole(const QPointF& pos, float mass, float r_s, float rot, float q) :
    pos_(pos),
    mass_(mass),
    schwarzchildRadius_(r_s),
    rotation_(rot),
    charge_(q)
{

}
