/* 
 * File:   player.cpp
 * Author: g1biggse
 * 
 * Created on March 31, 2015, 1:03 AM
 */

#include <GL/gl.h>
#include <stdio.h>
#include <cmath>

#include "player.h"
#include "utils.h"


/* CONSTRUCTOR/DESTRUCTOR */

Player::Player() {
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

/* METHODS */

Vector3D Player::getPos() const {
    return this->pos;
}

void Player::setVelocity(const Vector3D& vel) {
    this->vel = vel;
}

void Player::update() {
    this->pos = this->pos + this->vel;
    
    this->wingRotation = this->areWingsFlappingUp ?
        fmin(WING_ROTATION_MAX, this->wingRotation++) :
        fmax(WING_ROTATION_MIN, this->wingRotation--);
}

void Player::render() {
    glPushMatrix();
    
    // render body
    translateByVector(this->pos);
    drawCube();
    
    // render both left and right wings
    this->renderWing(false);
    this->renderWing(true);

    glPopMatrix();
}

void Player::renderWing(bool isLeftWing) {
    glPushMatrix();
    
    // move to wing joint
    Vector3D offsetFromPlayerCenter = isLeftWing ? Vector3D(0.4, 0.2, 0) : Vector3D(-0.4, 0.2, 0);
    translateByVector(offsetFromPlayerCenter);
    
    // rotate + scale
    rotate(Vector3D(0, 0, isLeftWing ? this->wingRotation : -this->wingRotation));
    scale(Vector3D(1, 0.2, 0.5));
    
    // move to center of wing, render
    glTranslatef(0.5, 0, 0);
    drawCube();
            
    glPopMatrix();
}