/* 
 * File:   player.h
 * Author: g1biggse
 *
 * Created on March 31, 2015, 1:03 AM
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "utils.h"
#include "boundingbox.h"

const double WING_OFFSET_X = 0.4;
const double WING_OFFSET_Y = 0.2;
const double WING_OFFSET_Z = 0.0;

const double WING_ROTATION_MAX = 45;
const double WING_ROTATION_MIN = 0;

//const Vector3D& PLAYER_SCALE = Vector3D(1, 0.2, 0.5);
const double PLAYER_MOVE_SPEED = 0.1;

class Player {
public:
    Player();
    virtual ~Player();
    
    Vector3D getPos() const;
    void setPos(const Vector3D& p);
    
    Vector3D getVelocity() const;
    void setVelocity(const Vector3D& vel);
    
    void moveLeft();
    void moveRight();
    void stopMovement();
    
    bool collidesWithObstacle(BoundingBox obstacle);
    
    void update();
    void render();
    
    bool isDead;
    
private:
    bool areWingsExtendedFully() const;
    
    void renderWing(bool isLeftWing);
    
    Vector3D pos;
    Vector3D vel;
    
    float wingRotation;
    bool areWingsFlappingUp;
    
    BoundingBox collider;
    
    int lightFlashCounter;
};

#endif	/* PLAYER_H */

