/* 
 * File:   obstacle.cpp
 * Author: g1biggse
 * 
 * Created on April 3, 2015, 3:01 PM
 */

#include "obstacle.h"
#include "stdio.h"

Obstacle::Obstacle(Vector3D& p, Vector3D& s) {
    this->pos = new Vector3D(p[0], p[1], p[2]);
    this->size = new Vector3D(s[0], s[1], s[2]);
    
    Vector3D colliderExtents = 0.5 * s;
    this->collider = new BoundingBox(*(this->pos), colliderExtents);
}

Obstacle::~Obstacle() {
}

void Obstacle::update() {
    
}

void Obstacle::render() {
//    glPushAttrib(GL_CURRENT_BIT);
    printf("%f\n", (*(this->size))[0]);
    cube(*(this->pos), Vector3D::zero, *(this->size));
    
//    glPopAttrib();
}