/* 
 * File:   world.cpp
 * Author: g1biggse
 * 
 * Created on March 31, 2015, 1:02 AM
 */

#include "world.h"
#include "camera.h"
#include <stdio.h>
#include <GL/gl.h>

/* CONSTRUCTOR/DESTRUCTOR */

World::World() {
    Vector3D offset = Vector3D(0, 1, 10);
    this->camera.setOffsetFromPlayer(offset);
    
    this->player.setPos(Vector3D(0, 1, 0));
    this->player.setVelocity(Vector3D(0, 0, 1));
}

World::World(const World& orig) : player(orig.player) {
    printf("wtf\n");
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
        
        this->renderLane(Colour::red);

        glPushMatrix();
            glTranslatef(2, 0, 0);
            this->renderLane(Colour::green);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2, 0, 0);
            this->renderLane(Colour::blue);
        glPopMatrix();
        
        this->player.render();

    glPopMatrix();
}

void World::renderLane(const Colour c) {
    glPushMatrix();
    
    colour(c);
    glScalef(1, 0.01, 10000);
    
    drawCube();
    
    glPopMatrix();
}