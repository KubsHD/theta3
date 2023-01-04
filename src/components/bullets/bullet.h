#ifndef BULLET_H
#define BULLET_H

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

#endif
