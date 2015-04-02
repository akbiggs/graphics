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

class World {
public:
    World();
    World(const World& orig);
    virtual ~World();
    
    void update();
    void render();

    double lastLoopTime;
    double loopTimeAccumulated;
    
private:
    void renderLane(const Colour c);
    
    Player player;
    Camera camera;
};

#endif	/* WORLD_H */

