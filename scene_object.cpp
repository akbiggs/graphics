/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements scene_object.h

***********************************************************/

#include <cmath>
#include <iostream>
#include "scene_object.h"

bool UnitSquare::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// TODO: implement intersection code for UnitSquare, which is
	// defined on the xy-plane, with vertices (0.5, 0.5, 0), 
	// (-0.5, 0.5, 0), (-0.5, -0.5, 0), (0.5, -0.5, 0), and normal
	// (0, 0, 1).
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.
        Ray3D modelRay = worldToModel * ray;
        
        Point3D a = modelRay.origin;
        Vector3D d = modelRay.dir;
        
        Point3D p1 = Point3D(0.5, 0.5, 0);
        Point3D p2 = Point3D(-0.5, 0.5, 0);
        Point3D p3 = Point3D(0.5, -0.5, 0);
        Point3D p4 = Point3D(-0.5, -0.5, 0);
        
        Vector3D n1 = Vector3D(p2 - p1).cross(Vector3D(p3 - p1));
        Vector3D n2 = Vector3D(p3 - p2).cross(Vector3D(p4 - p2));
        
        double lam;
        Vector3D ry;

        //printf("%f\n", d.dot(n1));
        
        //calculate square intersections with two triangles
        if (d.dot(n1) == 0) {
            if (not ray.intersection.none) {
                ray.intersection.none = true;
                return false;
            }
        } else {
            
            lam = ((p1 - a).dot(n1))/d.dot(n1);
            ry = (a + lam * d);
            if ((ry[1] <= 0.5) && (ry[1] >= -0.5)
                    && (ry[0] <= 0.5) && (ry[0] >= -0.5)) {
                if (ray.intersection.t_value > lam || ray.intersection.none) {
                    ray.intersection.point = modelToWorld * (a + lam * d);
                    ray.intersection.normal = transNorm(worldToModel, Vector3D(0,0,1));
                    ray.intersection.normal.normalize();

                    ray.intersection.t_value = lam;
                    ray.intersection.none = false;
                    return true;
                }
                return false;
            }
            //p1 = (0.5, 0.5, 0);
            //p2 = (-0.5, 0.5, 0);
            //p3 = (0.5, -0.5, 0);
            //p4 = (-0.5, -0.5, 0);
        }
        
        if (d.dot(n2) == 0) {
            if (not ray.intersection.none) {
                ray.intersection.none = true;
                return false;
            }
        } else {
            lam = ((p2 - a).dot(n2))/d.dot(n2);
            ry = (a + lam * d);
            if ((ry[1] <= 0.5) && (ry[1] >= -0.5)
                    && (ry[0] <= 0.5) && (ry[0] >= -0.5)) {
                if (ray.intersection.t_value > lam || ray.intersection.none) {
                    ray.intersection.point = modelToWorld * (a + lam * d);
                    ray.intersection.normal = transNorm(worldToModel, Vector3D(0,0,1));
                    ray.intersection.normal.normalize();

                    ray.intersection.t_value = lam;
                    ray.intersection.none = false;
                    return true;
                }
                return false;
            }
        }

	return false;
}

bool UnitSphere::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// TODO: implement intersection code for UnitSphere, which is centred 
	// on the origin.  
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.
    
        Ray3D modelRay = worldToModel * ray;
        
        Point3D a = modelRay.origin;
        Vector3D d = modelRay.dir;
        
        double A = d.dot(d);
        double B = a.dot(d);
        double C = a.dot(a) - 1;
        
        double D = B * B - A * C;
        
        if (D < 0) {
            if (ray.intersection.none) {
                return false;
            } else {
                ray.intersection.none = true;
                return false;
            }
        } else { 
                double lam;
                if (D == 0) {
                    lam = (-B / A);
                } else {
                    double lam1 = (-B / A) + (sqrt(D) / A);
                    double lam2 = (-B / A) - (sqrt(D) / A);
                        
                    if (ray.intersection.t_value > lam2 || ray.intersection.t_value > lam1 || ray.intersection.none) {

                        if (lam1 < 0 && lam2 < 0) {
                            ray.intersection.none = true;
                            return false;
                        } else if (lam1 > 0 && lam2 < 0) {
                            lam = lam1;
                        } else if (lam1 > lam2 && lam2 > 0) {
                            lam = lam2;
                        } else {
                            printf("WTF LAMBDAS %f %f\n", lam1, lam2);
                        }
						
                        ray.intersection.point = modelToWorld * (a + lam * d);
						Vector3D normal = ray.intersection.point;
						normal.normalize();
						
                        ray.intersection.normal = transNorm(worldToModel, -normal);
                        ray.intersection.normal.normalize();

                        ray.intersection.t_value = lam;
                        ray.intersection.none = false;
                        return true;
                    }
                }
        }
        return false;
}

