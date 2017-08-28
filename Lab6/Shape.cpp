#include <iostream>
#include "Shape.h"
using namespace std;

Shape::Shape () {
   name = "";
   colour = "";
}


Shape::Shape (string _name, string _colour, float _xcen, float _ycen) {
   name = _name;
   colour = _colour;
   xcen = _xcen;
   ycen = _ycen;
}


Shape::~Shape () {
   // Don't need to do anything. The destructors for the two strings in 
   // Shape will automatically be called by "destructor chaining".
}


string Shape::getName () const {
   return name;
}


void Shape::setName (string _name) {
   name = _name;
}


string Shape::getColour () const {
   return colour;
}


void Shape::setColour (string _colour) {
   colour = _colour;
}


// This implementation of translate will work for all derived classes if 
// you are careful how you store your data. If you aren't careful, you will
// need to override it in some of your derived classes.
void Shape::translate (float xShift, float yShift) {
   xcen += xShift;
   ycen += yShift;
}   


float Shape::getXcen () const {
   return xcen;
}


void Shape::setXcen (float _xcen) {
   xcen = _xcen;
}


float Shape::getYcen () const {
   return ycen;
}


void Shape::setYcen (float _ycen) {
   ycen = _ycen;
}


void Shape::print () const {
   cout.precision(ShapePrecision);
   cout.setf(ios::fixed);
   cout << name << " " << colour << " ";
   cout << "center: (" << getXcen() << "," << getYcen() << ") ";
}


// Used to check if we clicked on a shape. Default implementation below.
// Just return false (so clicking disabled unless a derived class overrides
// this).
bool Shape::pointInside (float x, float y) const {
   return false;
}
