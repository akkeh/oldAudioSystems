#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <cstdlib>


class TestWin : public Fl_Window {
public:
    TestWin(int w, int h, const char* title);
    ~TestWin();
    Fl_Button* but;
    Fl_Input* inp;
    Fl_Output* out;

private:
    static void copy(Fl_Widget*, void*);    // callback in class can only be static (this pointer does not exist)
    inline void copy_i();   // inlined in copy() function;
};


int main(int argc, const char** argv) {
    int I = atoi(argv[1]);
    TestWin** win = new TestWin*[I];
    for(int i=0; i<I; i++) {
        win[i] = new TestWin(10*i, 10*i, "Test win!");
    };
    return Fl::run();

}

TestWin::TestWin(int w, int h, const char* title) : Fl_Window(w, h, title) {
    begin();
        but = new Fl_Button(10, 150, 70, 70, "&Button");
        but->callback(copy, this);  // sends this-pointer to callback (class is accesable in callback function)
        
        inp = new Fl_Input(50, 50, 140, 30, "Input:");
        out = new Fl_Output(50, 100, 140, 30, "&Output:");
    end();
    // Fl::resizeable(this);    // not declared?
    this->set_modal();
    show();
};

TestWin::~TestWin() {};

void TestWin::copy(Fl_Widget* o, void* v) {
    ((TestWin*)v)->copy_i();
}

void TestWin::copy_i() {
    out->value(inp->value());   //value gets and sets
    this->set_non_modal();
}
