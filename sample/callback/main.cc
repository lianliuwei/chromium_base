#include <iostream>

#include "base/logging.h"
#include "base/command_line.h"
#include "base/callback.h"
#include "base/bind.h"

 int Return5() { return 5; }
 int ReturnN(int n) { return n; }
 void PrintHi() { LOG(INFO) << "hi."; }
 /* Binding a class method. */
 class Ref : public base::RefCountedThreadSafe<Ref> {
 public:
     int Foo() { return 3; }
     void PrintBye() { LOG(INFO) << "bye."; }
     int FooN(int n) {return n; }
 };
 // /* Binding a class method in a non-refcounted class.
class NoRef {
public:
int Foo() { return 4; }
void PrintWhy() { LOG(INFO) << "why???"; }
};
int Identity(int n) { return n; }

int main(int argc, char** argv)
{
    using namespace logging;

    CommandLine::Init(argc, argv);

    InitLogging(L"debug.log", 
        LOG_TO_BOTH_FILE_AND_SYSTEM_DEBUG_LOG, 
        DONT_LOCK_LOG_FILE,
        DELETE_OLD_LOG_FILE,
        DISABLE_DCHECK_FOR_NON_OFFICIAL_RELEASE_BUILDS);

     // /* Binding a normal function. */
     base::Callback<int(void)> func_cb = base::Bind(&Return5);
     LOG(INFO) << func_cb.Run();  // Prints 5.
    
     base::Callback<int(int)> func_cb2 = base::Bind(&ReturnN);
     LOG(INFO) << func_cb2.Run(1);

     base::Closure void_func_cb = base::Bind(&PrintHi);
     void_func_cb.Run();  // Prints: hi.
    
     // /* Binding a class method. */    
     scoped_refptr<Ref> ref = new Ref();
     base::Callback<int(void)> ref_cb = base::Bind(&Ref::Foo, ref.get());
     LOG(INFO) << ref_cb.Run();  // Prints out 3.
    
     base::Closure void_ref_cb = base::Bind(&Ref::PrintBye, ref.get());
     void_ref_cb.Run();  // Prints: bye.

     NoRef no_ref;
     base::Callback<int(void)> no_ref_cb =
         base::Bind(&NoRef::Foo, base::Unretained(&no_ref));
     LOG(INFO) << no_ref_cb.Run();  // Prints out 4.
    
     base::Closure void_no_ref_cb =
         base::Bind(&NoRef::PrintWhy, base::Unretained(&no_ref));
     void_no_ref_cb.Run();  // Prints: why???
    
     /* Binding a reference. */
     int value = 1;
     base::Callback<int(void)> bound_copy_cb = base::Bind(&Identity, value);
     base::Callback<int(void)> bound_ref_cb =
         base::Bind(&Identity, base::ConstRef(value));
     LOG(INFO) << bound_copy_cb.Run();  // Prints 1.
     LOG(INFO) << bound_ref_cb.Run();  // Prints 1.
     value = 2;
     LOG(INFO) << bound_copy_cb.Run();  // Prints 1.
     LOG(INFO) << bound_ref_cb.Run();  // Prints 2.

    //close to release global obj
    CloseLogFile();
    CommandLine::Reset();
    
    return 0;
}