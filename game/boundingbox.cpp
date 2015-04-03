/* 
 * File:   boundingbox.cpp
 * Author: g1biggse
 * 
 * Created on April 3, 2015, 3:07 PM
 */

#include <GL/gl.h>

#include "utils.h"
#include "boundingbox.h"

BoundingBox::BoundingBox() {
}

BoundingBox::BoundingBox(Vector3D& p, Vector3D& e) : pos(p), extents(e) {
}

BoundingBox::~BoundingBox() {
}

void BoundingBox::SetPos(const Vector3D& other) {
    this->pos = other;
}

bool BoundingBox::Intersects(const BoundingBox& other) const {
    return this->GetLeft() <= other.GetRight() && this->GetRight() >= other.GetLeft() &&
            this->GetTop() >= other.GetBottom() && this->GetBottom() <= other.GetTop() &&
            this->GetFront() <= other.GetBack() && this->GetBack() >= other.GetFront();
}

/* Render the bounding box. Assumes no transformation has been applied. */
void BoundingBox::render() {
    glPushMatrix();
    glPushAttrib(GL_POLYGON_BIT);
    
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        cube(this->pos, Vector3D::zero, 2 * this->extents);
        
    glPopAttrib();
    glPopMatrix();
}

double BoundingBox::GetLeft() const {
    return this->pos[0] - this->extents[0];
}

double BoundingBox::GetRight() const {
    return this->pos[0] + this->extents[0];
}

double BoundingBox::GetTop() const {
    return this->pos[1] + this->extents[1];
}

double BoundingBox::GetBottom() const {
    return this->pos[1] - this->extents[1];
}

double BoundingBox::GetFront() const {
    return this->pos[2] - this->extents[2];
}

double BoundingBox::GetBack() const {
    return this->pos[2] + this->extents[2];
}