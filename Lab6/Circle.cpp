#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Circle.h"
using namespace std;


Circle::Circle (string _name, string _colour, float _xcen, float _ycen,
            float _radius) 
              : Shape (_name, _colour, _xcen, _ycen) {
    radius = _radius;
}


Circle::~Circle () {
   // No dynamic memory to delete
}


void Circle::print () const {
   Shape::print();
   cout << "circle radius: "<<radius<<endl;
}


void Circle::scale (float scaleFac) {
    radius *= scaleFac;
}
   

float Circle::computeArea () const {
   float area;
   area = PI * radius * radius;
   return area;
}


float Circle::computePerimeter () const {
   float perimeter = 0;
   perimeter = 2 * PI * radius;
   return perimeter;
}


void Circle::draw (easygl* window) const {
    // Load up the data structure needed by easygl, and draw the triangle
    // using the easygl::draw_polygon call. 
    window->gl_setcolor(getColour());
    window->gl_fillarc(getXcen(), getYcen(), radius, 0, 360);
}


bool Circle::pointInside (float x, float y) const {
    if(pow(x-getXcen(),2) + pow(y-getYcen(),2) < pow(radius,2))
        return true;
    return false;
}
