/* 
 * File:   player.h
 * Author: g1biggse
 *
 * Created on March 31, 2015, 1:03 AM
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "utils.h"

const double WING_OFFSET_X = 0.4;
const double WING_OFFSET_Y = 0.2;
const double WING_OFFSET_Z = 0.0;

const double WING_ROTATION_MAX = 45;
const double WING_ROTATION_MIN = 0;

class Player {
public:
    Player();
    Player(const Player& orig);
    virtual ~Player();
    
    Vector3D getPos() const;
    
    void setVelocity(const Vector3D& vel);
    
    void update();
    void render();
    
private:
    void renderWing(bool isLeftWing);
    
    Vector3D pos;
    Vector3D vel;
    
    float wingRotation;
    bool areWingsFlappingUp;
};

#endif	/* PLAYER_H */

