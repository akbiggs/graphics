/* 
 * File:   camera.h
 * Author: g1biggse
 *
 * Created on April 1, 2015, 10:32 PM
 */

#ifndef CAMERA_H
#define	CAMERA_H

#include "player.h"
#include "utils.h"

class Camera {
public:
    Camera();
    Camera(const Camera& orig);
    virtual ~Camera();
    
    void setOffsetFromPlayer(const Vector3D& offset);
    
    void update(const Player& player);
    void apply();
    
private:
    Vector3D pos;
    Vector3D rotation;
    Vector3D offsetFromPlayer;
};

#endif	/* CAMERA_H */

