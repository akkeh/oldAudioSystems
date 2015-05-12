#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

void butcb(Fl_Widget* o, void*) {
    Fl_Button* b = (Fl_Button*)o;   // cast widget-pointer to button-pointer
    b->label("clicked!");
    b->resize(10, 150, 140, 30);
    b->redraw();
}

int main() {
    Fl_Window win(300, 200, "test-screen");
    win.begin();
        Fl_Button but(10, 150, 70, 30, "button1");
    win.end();
    but.callback(butcb);
    win.show();
   
  
    return Fl::run();
}
