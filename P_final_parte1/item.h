#ifndef ITEM_H
#define ITEM_H

#include <math.h>

class item
{
public:
    item();
    item(float x, float y);
    ~item();
    void setVel(float x, float y);
    void actualizar(float dt);

    float getPx() const;
    void setPx(float value);

    float getPy() const;
    void setPy(float value);

private:
    float vx;
    float vy;
    float px;
    float py;
};

#endif // ITEM_H

