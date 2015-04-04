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
#include <math.h>

/* CONSTRUCTOR/DESTRUCTOR */

Player::Player() {
    this->wingRotation = WING_ROTATION_MIN;
    this->collider = BoundingBox(Vector3D(0, 0, 0), 0.5 * Vector3D(1, 0.2, 0.5));
    this->isDead = false;
    this->lightFlashCounter = 0;
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
    
    // restrict player's movement to boundaries
    Vector3D clampedPos = this->getPos();
    if (clampedPos[0] < -4) {
        clampedPos[0] = -4;
    } else if (clampedPos[0] > 4) {
        clampedPos[0] = 4;
    }
    this->setPos(clampedPos);
    
    this->wingRotation += this->areWingsFlappingUp ? 2 : -2;
    this->wingRotation = this->areWingsFlappingUp ?
        fmin(WING_ROTATION_MAX, this->wingRotation) :
        fmax(WING_ROTATION_MIN, this->wingRotation);
    
    if (this->areWingsExtendedFully()) {
        this->areWingsFlappingUp = !this->areWingsFlappingUp;
    }
    
    
    
    this->lightFlashCounter++;
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
    
    glPopMatrix();
    
    this->collider.render();
    
    GLfloat lightPos[] = {this->pos[0], this->pos[1] + 1, this->pos[2], 1.0};
    
    // fade in and out the light repeatedly
    float intensity = (float) -std::abs((double)(this->lightFlashCounter % 200) / 200 - 0.5) + 1;
    GLfloat ambientLight[] = {intensity, intensity, intensity, 1.0};

    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);

    // apply normalization and light ambience this frame
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_NORMALIZE);

    // widen strokes
    glLineWidth(2);

    // render light
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
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