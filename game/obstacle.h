/* 
 * File:   obstacle.h
 * Author: g1biggse
 *
 * Created on April 3, 2015, 3:01 PM
 */

#ifndef OBSTACLE_H
#define	OBSTACLE_H

#include "utils.h"
#include "boundingbox.h"

class Obstacle {
public:
    Obstacle(Vector3D& p, Vector3D& s);
    virtual ~Obstacle();
    
    void update();
    void render();
private:
    Vector3D* pos;
    Vector3D* size;
    BoundingBox* collider;
};

#endif	/* OBSTACLE_H */

