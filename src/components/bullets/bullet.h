#pragma once

#include <core/types.h>
#include <render/Renderer.h>

class Bullet
{
public:
    Bullet();
    ~Bullet();

    virtual void update() = 0;
    virtual void render(Renderer* ren) = 0;
private:

};
