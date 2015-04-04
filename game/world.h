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
#include "utils.h"

class World {
public:
    World();
    virtual ~World();
    
    bool needsRestart();
    void addObstacle(Vector3D pos);
    
    void keydown(unsigned char key);
    void keyup(unsigned char key);
    
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
    
    int spawnObstacleTimer;
};

#endif	/* WORLD_H */

