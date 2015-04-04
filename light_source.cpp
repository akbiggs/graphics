/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements light_source.h

***********************************************************/

#include <cmath>
#include "light_source.h"

void PointLight::shade( Ray3D& ray ) {
	// TODO: implement this function to fill in values for ray.col 
	// using phong shading.  Make sure your vectors are normalized, and
	// clamp colour values to 1.0.
	//
	// It is assumed at this point that the intersection information in ray 
	// is available.  So be sure that traverseScene() is called on the ray 
	// before this function.

        Point3D p = ray.intersection.point;
        Vector3D n = ray.intersection.normal;
		n.normalize();
        //Vector3D s = ray.dir;
		Vector3D ld = this->_pos - p;
		ld.normalize();
        
        Vector3D di = -ray.dir;
		di.normalize();
        
        Colour Ia = this->_col_ambient;
        Colour Id = this->_col_diffuse;
        Colour Is = this->_col_specular;
        

        Colour ra = ray.intersection.mat->ambient;
        Colour rd = ray.intersection.mat->diffuse;
        Colour rs = ray.intersection.mat->specular;
        
//        ray.col = rd;
//        return;        
        //Vector3D m = 2 * (n.dot(s)) * n - s;
		
		//reflection direction
        Vector3D de = 2 * (n.dot(ld)) * n - ld;
		de.normalize();
		
        double alpha = ray.intersection.mat->specular_exp;
        
		//scene signature
		//ray.col = rd;
		
		//diffuse
		//ray.col = (fmax(0, n.dot(ld)) * rd * Id) + (ra * Ia);
		
		//phong shading
        ray.col = fmax(0, n.dot(ld)) * rd * Id +
                ra * Ia +
                pow(fmax(0, di.dot(de)), alpha) * rs * Is;
		ray.col.clamp();
}

