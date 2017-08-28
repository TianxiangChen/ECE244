/* 
 * Project name: ECE244 LAB6
 * Author: Tianxiang Chen
 * 
 *
 * This lab asks us to use inheritance to draw some shapes
 * (triangle, rectangle, circle and polygon).
 * We are given the Shape and ShapeArray files, which is the base class.
 */

#include <iostream>
#include "Shape.h"
#include "ShapeArray.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Polygon.h"
using namespace std;



/*********** Function declarations ***********/

int parser (ShapeArray& shapeArray);
bool parseNameAndColour (stringstream& linestream, string& name, 
          string& colour);
void addTri(stringstream& linestream, ShapeArray& shapeArray);
void addRect(stringstream& linestream, ShapeArray& shapeArray);
void addCirc(stringstream& linestream, ShapeArray& shapeArray);
void addPolygon(stringstream& linestream, ShapeArray& shapeArray);

/************** Function definitions *********/

int main(int argc, char** argv) {

   ShapeArray shapeArray;
   int returnVal;
   
   returnVal = parser(shapeArray);
   return returnVal;
}


// Parse commands and execute them, updating the state of the ShapeArray 
// object as necessary, until EOF.
int parser (ShapeArray& shapeArray) {
   string str;
   cout << "> ";  // Prompt for input
   
   while (getline(cin, str)) {   // While more input data, get one line at a time
      stringstream linestream(str);  // Build a stringstream from the line.
      string command;
      
      linestream >> command;   // First word on the line is the command
      
      if (!linestream.fail()) {
         // Call the appropriate routine to execute the command
         if (command == "tri") {
            addTri(linestream, shapeArray);
         }
         else if (command == "rect") {
            addRect(linestream, shapeArray);
         }
         else if (command == "circ") {
            addCirc(linestream, shapeArray);
         }
         else if (command == "poly") {
             addPolygon(linestream, shapeArray);
         }
         else if (command == "translate") {
            shapeArray.translate (linestream);
         }
         else if (command == "scale") {
            shapeArray.scale (linestream);
         }
         else if (command == "remove") {
            shapeArray.remove (linestream);
         }
         else if (command == "printall") {
            shapeArray.printAll (linestream);
         }
         else if (command == "area") {
            shapeArray.computeArea (linestream);
         }
         else if (command == "perimeter") {
            shapeArray.computePerimeter (linestream);
         }
         else if (command == "draw") {
            shapeArray.handleDraw(linestream);
         }
         else {
            cout << "Error: invalid command\n";
         }
      }
      else {   // Extracting the command from the linestream failed.
         cout << "Error: invalid command\n";
      }
      
      cout << "> ";   // Prompt for input
   }
   return 0;
}


// Parse a name and colour from the line stored in linestream. Return true
// if successful, false if there is an input error.
// Pass back the name and colCode by reference.
bool parseNameAndColour (stringstream& linestream, string& name, 
          string& colour) {
   
   linestream >> name;
   if (linestream.fail()) {
      cout << "Error: missing or invalid name\n";
      return false;
   }
   
   linestream >> colour;
   if (linestream.fail()) {
      cout << "Error: missing or invalid colour\n";
      return false;
   }
   
   return true;
}


void addTri(stringstream& linestream, ShapeArray& shapeArray) {
   string name, colour;
   float xcoords[3], ycoords[3], xcen, ycen;
   if (!parseNameAndColour (linestream, name, colour)) 
      return;
   
   linestream >> xcoords[0] >> ycoords[0] >> xcoords[1] >> ycoords[1] 
              >> xcoords[2] >> ycoords[2];
   if (linestream.fail ()) {
      cout << "Error: invalid coordinates\n";
      return;
   }
 
   // Want to store this shape as a center, and point offsets from the 
   // center.
   xcen = 0;
   ycen = 0;
   for (int i = 0; i < 3; i++) {
      xcen += xcoords[i];
      ycen += ycoords[i];
   }
   xcen /= 3;
   ycen /= 3;
   
   for (int i = 0; i < 3; i++) {
      xcoords[i] -= xcen;
      ycoords[i] -= ycen;
   }
      
   Triangle* tri = new Triangle (name, colour, xcen, ycen, xcoords, ycoords);
   shapeArray.addShape (tri);
   cout << "Success\n";
}


void addRect(stringstream& linestream, ShapeArray& shapeArray) {
    string name, colour;
    float xcen, ycen, width, height;
    
    if (!parseNameAndColour (linestream, name, colour))
       return;
    
    linestream >> xcen >> ycen >> width >> height;
    if (linestream.fail()) {
       cout << "Error: invalid center, width or height\n";
       return;
    }
    
    Rectangle *rect = new Rectangle(name, colour, xcen, ycen, width, height);
    shapeArray.addShape(rect);
    cout << "Success\n";
}


void addCirc(stringstream& linestream, ShapeArray& shapeArray) {
    string name, colour;
    float xcen, ycen, radius;
    
    if (!parseNameAndColour (linestream, name, colour))
       return;
    
    linestream >> xcen >> ycen >> radius;
    if (linestream.fail()) {
       cout << "Error: invalid center or radius\n";
       return;
    }
    
    Circle *cir = new Circle(name, colour, xcen, ycen, radius);
    shapeArray.addShape(cir);
    cout << "Success\n";
}

void addPolygon(stringstream& linestream, ShapeArray& shapeArray) {
    string name, colour;
    float xcen, ycen;
    int nPoint = 0;
    const int MAX_POINTS = 100;
    float xcoords[MAX_POINTS], ycoords[MAX_POINTS];
    
    if (!parseNameAndColour (linestream, name, colour))
       return;
    
    while(!linestream.fail()){
        linestream >> xcoords[nPoint] >> ycoords[nPoint];
        if(!linestream.fail())
            nPoint++;
    }
    
    if (nPoint < 3) {
      cout << "Error: Polygon must have at least 3 vertices.\n";
      return;
   }
    
   xcen = 0;
   ycen = 0;
   for (int i = 0; i < nPoint; i++) {
      xcen += xcoords[i];
      ycen += ycoords[i];
   }
   xcen /= nPoint;
   ycen /= nPoint;
   
   for (int i = 0; i < nPoint; i++) {
      xcoords[i] -= xcen;
      ycoords[i] -= ycen;
   }
      
   Polygon* poly = new Polygon (name, colour, xcen, ycen, xcoords, ycoords, nPoint);
   shapeArray.addShape (poly);
    cout << "Success\n";
}