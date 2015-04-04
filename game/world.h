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
#include "utils.h"

class World {
public:
    World();
    virtual ~World();
    
    void addObstacle(Vector3D pos);
    
    void update();
    void render();

    double lastLoopTime;
    double loopTimeAccumulated;
    
private:
    void renderLanes();
    void renderLane(const Colour c);
    
    void renderObstacle(BoundingBox obstacle);
    
    Player player;
    Camera camera;
    
    BoundingBox obstacles[10];
    int numObstacles;
};

#endif	/* WORLD_H */

