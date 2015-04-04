/* 
 * File:   world.cpp
 * Author: g1biggse
 * 
 * Created on March 31, 2015, 1:02 AM
 */

#include "world.h"
#include "camera.h"
#include "utils.h"

#include <stdio.h>
#include <GL/gl.h>

/* CONSTRUCTOR/DESTRUCTOR */

World::World() {
    Vector3D offset = Vector3D(0, 1, 10);
    this->camera.setOffsetFromPlayer(offset);
    
    this->player.setPos(Vector3D(0, 1, 0));
    this->player.setVelocity(Vector3D(0, 0, -0.2));
    
    this->numObstacles = 0;
    
    this->addObstacle(Vector3D(0, 0, -50));
    this->addObstacle(Vector3D(-4, 0, -50));
}

World::~World() {
//    this->obstacles.clear();
}

/* METHODS */

void World::addObstacle(Vector3D pos) {
    this->obstacles[numObstacles++] = BoundingBox(pos, Vector3D(1, 1, 1));
}

void World::update() {
    this->camera.update(this->player);
    this->player.update();
    
    for (int i = 0; i < this->numObstacles; i++) {
        printf("Intersection: %d\n", this->player.collidesWithObstacle(this->obstacles[i]));
    }
}


void World::render() {
//    glPushMatrix();
//    glTranslatef(0, 0, -5);
//    drawCube();
//    glPopMatrix();
    glPushMatrix();
        
        this->camera.apply();
        
        this->renderLanes();
        
        for (int i = 0; i < this->numObstacles; i++) {
            this->renderObstacle(this->obstacles[i]);
        }
        
        this->player.render();

    glPopMatrix();
}

void World::renderLanes() {
    this->renderLane(Colour::red);

    glPushMatrix();
        glTranslatef(4, 0, 0);
        this->renderLane(Colour::green);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-4, 0, 0);
        this->renderLane(Colour::blue);
    glPopMatrix();
}

void World::renderLane(const Colour c) {
    glPushMatrix();
    
    colour(c);
    glScalef(2, 0.01, 10000);
    
    drawCube();
    
    glPopMatrix();
}

void World::renderObstacle(BoundingBox obstacle) {
    glColor3f(0, 0, 0);
    
//    cube(Vector3D(4, 0, -50), Vector3D::zero, Vector3D::one);
//    printf("%f %f %f\n", obstacle.GetPos()[0], obstacle.GetPos()[1], obstacle.GetPos()[2]);
//    printf("%f %f %f\n", (2 * obstacle.GetExtents())[0], (2 * obstacle.GetExtents())[1], (2 * obstacle.GetExtents())[2]);
    cube(obstacle.GetPos(), Vector3D(0, 0, 0), 2 * obstacle.GetExtents());
}