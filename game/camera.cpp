/* 
 * File:   camera.cpp
 * Author: g1biggse
 * 
 * Created on April 1, 2015, 10:32 PM
 */

#include "camera.h"
#include "utils.h"
#include "player.h"
#include "GL/glu.h"
#include <iostream>

Camera::Camera() {
    this->rotation = Vector3D(0, 0, -1);
}

Camera::Camera(const Camera& orig) {
}

Camera::~Camera() {
}

void Camera::setOffsetFromPlayer(const Vector3D& offset) {
    this->offsetFromPlayer = Vector3D(offset);
}

void Camera::update(const Player& player) {
    this->pos = player.getPos() + Vector3D(0, 4, 8);//this->offsetFromPlayer;
}

void Camera::apply() {
    Vector3D lookAtCenter = this->pos + this->rotation;
    gluLookAt(this->pos[0], this->pos[1], this->pos[2],
              lookAtCenter[0], lookAtCenter[1], lookAtCenter[2],
              0, 1, 0);
}
