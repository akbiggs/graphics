/* 
 * File:   boundingbox.h
 * Author: g1biggse
 *
 * Created on April 3, 2015, 3:07 PM
 */

#ifndef BOUNDINGBOX_H
#define	BOUNDINGBOX_H

#include "utils.h"

class BoundingBox {
public:
    BoundingBox();
    BoundingBox(Vector3D pos, Vector3D extents);
    virtual ~BoundingBox();
    
    Vector3D GetPos() const;
    void SetPos(const Vector3D& other);
    
    Vector3D GetExtents() const;
    
    bool Intersects(const BoundingBox& other) const;
    
    void render();
    
private:
    double GetLeft() const;
    double GetRight() const;
    double GetTop() const;
    double GetBottom() const;
    double GetFront() const;
    double GetBack() const;
    
    Vector3D pos;
    Vector3D extents;
};

#endif	/* BOUNDINGBOX_H */

