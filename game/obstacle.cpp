/* 
 * File:   obstacle.cpp
 * Author: g1biggse
 * 
 * Created on April 3, 2015, 3:01 PM
 */

#include "obstacle.h"

Obstacle::Obstacle(Vector3D& p, Vector3D& s) : pos(p), size(s), collider(p, 0.5 * size) {
}

Obstacle::~Obstacle() {
}

void Obstacle::update() {
    
}

void Obstacle::render() {
    glPushAttrib(GL_CURRENT_BIT);
    
    cube(this->pos, );
    
    glPopAttrib();
}