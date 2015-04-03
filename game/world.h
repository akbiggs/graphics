/* 
 * File:   world.h
 * Author: g1biggse
 *
 * Created on March 31, 2015, 1:02 AM
 */

#ifndef WORLD_H
#define	WORLD_H

#include "player.h"
#include "camera.h"
#include "obstacle.h"
#include <vector>

class World {
public:
    World();
    virtual ~World();
    
    void update();
    void render();

    double lastLoopTime;
    double loopTimeAccumulated;
    
private:
    void renderLanes();
    void renderLane(const Colour c);
    
    Player player;
    Camera camera;
    
    std::vector<Obstacle> obstacles;
};

#endif	/* WORLD_H */

