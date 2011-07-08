#include "base/memory/singleton.h"

class FooClass {
public:
 static FooClass* GetInstance(); 
 void Bar() {
     int i = 1;
     i++;
 }
private:
 FooClass() {
    int i = 1;
    i++;
 }
 friend struct DefaultSingletonTraits<FooClass>;

 DISALLOW_COPY_AND_ASSIGN(FooClass);
};

FooClass* FooClass::GetInstance() {
    return Singleton<FooClass>::get();
}

int main(int argc, char** argv)
{
    base::AtExitManager exit_manager;

    FooClass::GetInstance()->Bar();
    return 0;
}