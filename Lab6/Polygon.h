/* 
 * File:   Polygon.h
 * Author: Tianxiang Chen
 *
 * Created on August 28, 2017, 1:11 AM
 */

#ifndef POLYGON_H
#define POLYGON_H

#include "Shape.h"
#include "easygl.h"

class Polygon : public Shape {
private:
   t_point relVertex[100];   
   int nPoint;
   
   // Private helper functions.
   t_point getVecBetweenPoints (t_point start, t_point end) const;
   
public:
   Polygon (string _name, string _colour, float _xcen, float _ycen,
            float _xcoords[100], float _ycoords[100], int _nPoint);
   
   // virtual keyword is optional in all the function declarations below, since
   // the base class Shape already declared them virtual. But it is good 
   // practice to repeat it again here, for clarity.
   virtual ~Polygon();
   
   
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
};

#endif /* POLYGON_H */

