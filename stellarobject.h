#ifndef STELLAROBJECT_H
#define STELLAROBJECT_H

#include <QObject>
#include <QPointF>

class StellarObject : public QObject
{
public:
    StellarObject(int id, float mass, const QPointF& pos);

    int getID() const { return id_; }
    float getX() const { return pos_.x(); }
    float getY() const { return pos_.y(); }
    float getMass() const { return mass_; }
    QPointF getPos() const { return pos_; }

    bool operator==(const StellarObject& other);
    bool operator!=(const StellarObject& other);

protected:
    int id_;
    float mass_;
    QPointF pos_;

};

#endif // STELLAROBJECT_H
