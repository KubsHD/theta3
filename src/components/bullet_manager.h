/*****************************************************************//**
 * \file   bullet_manager.h
 * \brief  this component manage bullet system
 * 
 * \date   January 2023
 *********************************************************************/
#ifndef BULLET_SYSTEM_H
#define BULLET_SYSTEM_H

#pragma once

#include <core/ecs.h>
#include <core/types.h>
/// <summary>
/// this class manage bullets in game
/// </summary>
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

