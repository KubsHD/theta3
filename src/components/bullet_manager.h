#ifndef BULLET_SYSTEM_H
#define BULLET_SYSTEM_H

#pragma once

#include <core/ecs.h>
#include <core/types.h>

class BulletManager : public Component
{
public:
    BulletManager();
    ~BulletManager();
    
    void init() override;
    
    void update() override;
    
    void render(Renderer *ren) override;
    

//    template<typename T>
//    void spawn<T>(Vec2 pos, Vec2 vel);

private:

};

#endif


/*

Lasers:
- Weapon attachment
- 

*/
