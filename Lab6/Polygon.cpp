#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Polygon.h"
using namespace std;


Polygon::Polygon (string _name, string _colour, float _xcen, float _ycen,
            float xcoords[100], float ycoords[100], int _nPoint) 
              : Shape (_name, _colour, _xcen, _ycen) {
   
    nPoint = _nPoint;
    for (int i = 0; i < nPoint; i++) {
      relVertex[i].x = xcoords[i];
      relVertex[i].y = ycoords[i];
   }
}


Polygon::~Polygon () {
   // No dynamic memory to delete
}


void Polygon::print () const {
   Shape::print();
   cout << "polygon";
   for (int i = 0; i < nPoint; i++) {
      cout << " (" << getXcen() + relVertex[i].x << "," 
              << getYcen() + relVertex[i].y << ")";
   }
   cout << endl;
}


void Polygon::scale (float scaleFac) {
   for (int i = 0; i < nPoint; i++) {
      relVertex[i].x *= scaleFac;
      relVertex[i].y *= scaleFac;
   }
}
   

float Polygon::computeArea () const {   
    float area = 0;         // Accumulates area in the loop
    int j = nPoint-1;  // The last vertex is the 'previous' one to the first

    t_point coords[nPoint];
    for (int i = 0; i < nPoint; i++) 
    {
        coords[i].x = getXcen() + relVertex[i].x;
        coords[i].y = getYcen() + relVertex[i].y;
    }
    
    for (int i=0; i<nPoint; i++)
    { 
        area = area +  (coords[j].x+coords[i].x) * (coords[j].y-coords[i].y);
        j = i;  //j is previous vertex to i
    }
   return abs(area/2);
}


float Polygon::computePerimeter () const {
   float perimeter = 0;
   float sideLength = 0;
   int endIndex;
   t_point dist;
    
   for (int i = 0; i < nPoint; i++) {
      endIndex = (i + 1);
      dist = getVecBetweenPoints (relVertex[i], relVertex[endIndex]);
      sideLength = sqrt (dist.x * dist.x + dist.y * dist.y);
      perimeter += sideLength;
   }
   return perimeter;
}


void Polygon::draw (easygl* window) const {
   // Load up the data structure needed by easygl, and draw the triangle
   // using the easygl::draw_polygon call.
   t_point coords[nPoint];  // This data type is in easygl_constants.h
   for (int i = 0; i < nPoint; i++) {
      coords[i].x = getXcen() + relVertex[i].x;
      coords[i].y = getYcen() + relVertex[i].y;
   }
   window->gl_setcolor(getColour());
   window->gl_fillpoly(coords, nPoint);
}


bool Polygon::pointInside (float x, float y) const {
   t_point coords[nPoint];
   for (int i = 0; i < nPoint; i++) {
      coords[i].x = getXcen() + relVertex[i].x;
      coords[i].y = getYcen() + relVertex[i].y;
   }
    
   int i, j, c = 0;
  for (i = 0, j = nPoint-1; i < nPoint; j = i++) 
  {
      if ( ((coords[i].y>y) != (coords[j].y>y)) &&(x < (coords[j].x-coords[i].x) * (y-coords[i].y) / (coords[j].y-coords[i].y) + coords[i].x) )
       c = !c;
  }
  return c;
}


// Private helper functions below.  Working out triangle area etc. 
// requires some vector math, so these helper functions are useful.

// Return the (x,y) vector between start and end points.
t_point Polygon::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}

