#include "blackhole.h"

BlackHole::BlackHole(int id, float mass, const QPointF &pos, float rot, float q) :
    StellarObject(id, mass, pos),
    rotation_(rot),
    charge_(q)
{

}
