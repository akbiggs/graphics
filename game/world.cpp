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
    this->player.setVelocity(Vector3D(0, 0, 1));
    
    this->obstacles.push_back(Obstacle(Vector3D(2, 0, -10), Vector3D(0.5, 0.5, 0.5)));
    this->obstacles.push_back(Obstacle(Vector3D(-2, 0, -10), Vector3D(0.5, 0.5, 0.5)));
}

World::~World() {
}

/* METHODS */

void World::update() {
    this->camera.update(this->player);
    this->player.update();
}

void World::render() {
    glPushMatrix();
        
        this->camera.apply();
        
        this->renderLanes();
        
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