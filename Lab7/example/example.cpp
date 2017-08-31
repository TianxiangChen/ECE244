#include <iostream>
#include "../easygl.h"
using namespace std;

// Create the window, with name on top and background colour as specified.
// Make it global so callbacks can access it easily.
easygl window ("My Window", WHITE);

int main() {

   window.set_world_coordinates (0., 0., 1000., 1000.);
   cout << "Passing control to window event handler.\n";

   // This routine will return when the user presses the "Proceed" button.
   // Until then, it will respond to button clicks etc., and call the 
   // easygl::drawscreen () function to redraw the graphics area.
   window.gl_event_loop ();
   return (0);
}


void easygl::drawscreen (void) {

/* redrawing routine for still pictures.  Graphics package calls  *
 * this routine to do redrawing after the user changes the window *
 * in any way.                                                    */

   t_point polypts[3] = {{500.,400.},{450.,480.},{550.,480.}};
   t_point polypts2[4] = {{700.,400.},{650.,480.},{750.,480.}, {800.,400.}};
 
   window.gl_clearscreen();  /* Should precede drawing for all drawscreens */

   window.gl_setfontsize (10);
   window.gl_setlinestyle (SOLID);
   window.gl_setlinewidth (1);
   window.gl_setcolor (BLACK);

   window.gl_drawtext (110.,55.,"colors",150.);
   window.gl_setcolor (LIGHTGREY);
   window.gl_fillrect (150.,30.,200.,80.);
   window.gl_setcolor (DARKGREY);
   window.gl_fillrect (200.,30.,250.,80.);
   window.gl_setcolor (WHITE);
   window.gl_fillrect (250.,30.,300.,80.);
   window.gl_setcolor (BLACK);
   window.gl_fillrect (300.,30.,350.,80.);
   window.gl_setcolor (BLUE);
   window.gl_fillrect (350.,30.,400.,80.);
   window.gl_setcolor (GREEN);
   window.gl_fillrect (400.,30.,450.,80.);
   window.gl_setcolor (YELLOW);
   window.gl_fillrect (450.,30.,500.,80.);
   window.gl_setcolor (CYAN);
   window.gl_fillrect (500.,30.,550.,80.);
   window.gl_setcolor (RED);
   window.gl_fillrect (550.,30.,600.,80.);
   window.gl_setcolor (DARKGREEN);
   window.gl_fillrect (600.,30.,650.,80.);
   window.gl_setcolor (MAGENTA);
   window.gl_fillrect (650.,30.,700.,80.);
   window.gl_setcolor (WHITE);
   window.gl_drawtext (400.,55.,"fillrect",150.);

   window.gl_setcolor (BLACK);
   window.gl_drawtext (250.,150.,"drawline",150.);
   window.gl_setlinestyle (SOLID);
   window.gl_drawline (200.,120.,200.,200.);
   window.gl_setlinestyle (DASHED);
   window.gl_drawline (300.,120.,300.,200.);

   window.gl_setcolor (MAGENTA);
   window.gl_drawtext (450, 160, "drawellipticarc", 150);
   window.gl_drawellipticarc (550, 160, 30, 60, 90, 270);
   window.gl_drawtext (720, 160, "fillellipticarc", 150);
   window.gl_fillellipticarc (800, 160, 30, 60, 90, 270);

   window.gl_setcolor (BLUE);
   window.gl_drawtext (190.,300.,"drawarc",150.);
   window.gl_drawarc (190.,300.,50.,0.,270.);
   window.gl_drawarc (300.,300.,50.,0.,-180.);
   window.gl_fillarc (410.,300.,50.,90., -90.);
   window.gl_fillarc (520.,300.,50.,0.,360.);
   window.gl_setcolor (BLACK);
   window.gl_drawtext (520.,300.,"fillarc",150.);
   window.gl_setcolor (BLUE);
   window.gl_fillarc (630.,300.,50.,90.,180.);
   window.gl_fillarc (740.,300.,50.,90.,270.);
   window.gl_fillarc (850.,300.,50.,90.,30.);
   window.gl_setcolor (RED);
   window.gl_fillpoly(polypts,3);
   window.gl_fillpoly(polypts2,4);
   window.gl_setcolor (BLACK);
   window.gl_drawtext (500.,450.,"fillpoly",150.);
   window.gl_setcolor (DARKGREEN);
   window.gl_drawtext (500.,610.,"drawrect",150.);
   window.gl_drawrect (350.,550.,650.,670.); 
  
   window.gl_setcolor (BLACK);
   window.gl_setfontsize (8);
   window.gl_drawtext (100.,770.,"8 Point Text",800.);
   window.gl_setfontsize (12);
   window.gl_drawtext (400.,770.,"12 Point Text",800.);
   window.gl_setfontsize (18);
   window.gl_drawtext (700.,770.,"18 Point Text",800.);
   window.gl_setfontsize (25);
   window.gl_drawtext (100.,850.,"24 Point Text",800.);

   window.gl_setfontsize (10);
  
   window.gl_setlinestyle (SOLID);
   window.gl_drawtext (200.,900.,"Thin line (width 1)",800.);
   window.gl_setlinewidth (1);
   window.gl_drawline (100.,920.,300.,920.);
   window.gl_drawtext (500.,900.,"Width 3 Line",800.);
   window.gl_setlinewidth (3);
   window.gl_drawline (400.,920.,600.,920.);
   window.gl_drawtext (800.,900.,"Width 6 Line",800.);
   window.gl_setlinewidth (6);
   window.gl_drawline (700.,920.,900.,920.);
}
