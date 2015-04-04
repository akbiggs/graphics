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
#include "boundingbox.h"

/* CONSTRUCTOR/DESTRUCTOR */

Player::Player() {
    this->wingRotation = WING_ROTATION_MIN;
    this->collider = BoundingBox(Vector3D(0, 0, 0), 2 * PLAYER_SCALE);
}

Player::~Player() {
}

/* METHODS */

Vector3D Player::getPos() const {
    return this->pos;
}

void Player::setPos(const Vector3D& p) {
    this->pos = p;
    this->collider.SetPos(this->pos);
}

Vector3D Player::getVelocity() const {
    return this->vel;
}

void Player::setVelocity(const Vector3D& vel) {
    this->vel = vel;
}

void Player::moveLeft() {
    Vector3D velocity = this->getVelocity();
    velocity[0] = -PLAYER_MOVE_SPEED;
    this->setVelocity(velocity);
}

void Player::moveRight() {
    Vector3D velocity = this->getVelocity();
    velocity[0] = PLAYER_MOVE_SPEED;
    this->setVelocity(velocity);
}

void Player::stopMovement() {
    Vector3D velocity = this->getVelocity();
    velocity[0] = 0;
    this->setVelocity(velocity);
}

bool Player::collidesWithObstacle(BoundingBox obstacle) {
    return this->collider.Intersects(obstacle);
}

void Player::update() {
    this->setPos(this->pos + this->vel);
    
    this->wingRotation += this->areWingsFlappingUp ? 2 : -2;
    this->wingRotation = this->areWingsFlappingUp ?
        fmin(WING_ROTATION_MAX, this->wingRotation) :
        fmax(WING_ROTATION_MIN, this->wingRotation);
    
    if (this->areWingsExtendedFully()) {
        this->areWingsFlappingUp = !this->areWingsFlappingUp;
    }
}

bool Player::areWingsExtendedFully() const {
    return this->wingRotation == WING_ROTATION_MIN || this->wingRotation == WING_ROTATION_MAX;
}

void Player::render() {
    glPushMatrix();
    
    colour(Colour::white);
    
    // render body
    translate(this->pos);
    drawCube();
    
    // render both left and right wings
    this->renderWing(false);
    this->renderWing(true);
    
//    this->collider.render();

    glPopMatrix();
}

void Player::renderWing(bool isLeftWing) {
    glPushMatrix();
    
    // move to wing joint
    Vector3D offsetFromPlayerCenter = isLeftWing ? Vector3D(0.4, 0.2, 0) : Vector3D(-0.4, 0.2, 0);
    translate(offsetFromPlayerCenter);
    
    // rotate + scale
    rotate(Vector3D(0, 0, isLeftWing ? this->wingRotation : -this->wingRotation));
    scale(Vector3D(1, 0.2, 0.5));
    
    // move to center of wing, render
    glTranslatef(isLeftWing ? 0.5 : -0.5, 0, 0);
    drawCube();

    glPopMatrix();
}