#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include <QObject>

class BlackHole : public QObject
{
public:
    BlackHole(float mass, float r_s, float rot, float q);

private:
    float mass_;
    float schwarzchildRadius_;
    float rotation_;
    float charge_;
};

#endif // BLACKHOLE_H
