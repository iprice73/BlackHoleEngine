#include "stellarobject.h"

StellarObject::StellarObject(int id, float mass, const QPointF &pos) :
    id_(id),
    mass_(mass),
    pos_(pos)
{

}

bool StellarObject::operator==(const StellarObject &other) {
    return id_ == other.getID();
}

bool StellarObject::operator!=(const StellarObject &other) {
    return id_ != other.getID();
}
