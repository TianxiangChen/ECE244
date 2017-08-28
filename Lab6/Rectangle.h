/* 
 * File:   rectangle.h
 * Author: Tianxiang Chen
 *
 * Created on August 28, 2017, 12:26 AM
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"
#include "easygl.h"
#include <math.h>

class Rectangle : public Shape {
private:
//unlike Triangle.h, the width and height are stored for rectangle.
   float width, height;   
   
public:
   Rectangle (string _name, string _colour, float _xcen, float _ycen,
            float _width, float _height);
   
   // virtual keyword is optional in all the function declarations below, since
   // the base class Shape already declared them virtual. But it is good 
   // practice to repeat it again here, for clarity.
   virtual ~Rectangle();
   
   
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
};


#endif /* RECTANGLE_H */

