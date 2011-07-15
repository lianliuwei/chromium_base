#include <iostream>

#include "base/memory/scoped_ptr.h"

using namespace std;

class Foo
{
public:
    Foo(char* s){
        string_ = s;
        cout<<"new Foo: "<<"the char* is: "<<string_<<endl;
    }
    ~Foo(){
        cout<<"del Foo: "<<"the char* is: "<<string_<<endl;
    }
    void Method(){
        cout<<"Foo'Method Method: "<<"the char* is: "<<string_<<endl;
    }
private:
    char* string_;
};

void SomeFunc(Foo* f){
    f->Method();
    delete f;
}

int main(int argc, char** argv)
{
    scoped_ptr<Foo> foo;          // No pointer managed.
    foo.reset(new Foo("wee"));    // Now a pointer is managed.
    foo.reset(new Foo("wee2"));   // Foo("wee") was destroyed.
    foo.reset(new Foo("wee3"));   // Foo("wee2") was destroyed.
    foo->Method();                // Foo::Method() called.
    foo.get()->Method();          // Foo::Method() called.
    SomeFunc(foo.release());      // SomeFunc takes ownership, foo no longer
                               // manages a pointer.
    foo.reset(new Foo("wee4"));   // foo manages a pointer again.
    foo.reset();                  // Foo("wee4") destroyed, foo no longer

    return 0;
}