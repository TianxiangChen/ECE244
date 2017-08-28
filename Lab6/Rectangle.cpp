#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Rectangle.h"
using namespace std;


Rectangle::Rectangle (string _name, string _colour, float _xcen, float _ycen,
            float _width, float _height) 
              : Shape (_name, _colour, _xcen, _ycen) {
    width = _width;
    height = _height;
}


Rectangle::~Rectangle () {
   // No dynamic memory to delete
}


void Rectangle::print () const {
   Shape::print();
   cout << "rectangle width: "<<width<<" height: "<<height<<endl;
}


void Rectangle::scale (float scaleFac) {
    width *= scaleFac;
    height *= scaleFac;
}
   

float Rectangle::computeArea () const {
   float area;
   area = width * height;
   return area;
}


float Rectangle::computePerimeter () const {
   float perimeter = 0;
   perimeter = 2 * (width + height);
   return perimeter;
}


void Rectangle::draw (easygl* window) const {
    // Load up the data structure needed by easygl, and draw the triangle
    // using the easygl::draw_polygon call.
    float x1, y1, x2, y2;
    x1 = getXcen() - width/2;
    y1 = getYcen() + height/2;
    
    x2 = getXcen() + width/2;
    y2 = getYcen() - height/2;
    
    window->gl_setcolor(getColour());
    window->gl_fillrect(x1, y1, x2, y2);
}


bool Rectangle::pointInside (float x, float y) const {
    if(abs(x-getXcen() < width/2) && abs(y-getYcen()) < height/2)
        return true;
    return false;
}
