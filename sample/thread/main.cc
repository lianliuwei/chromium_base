#include "base/threading/thread.h"
#include "base/at_exit.h"
#include "base/memory/scoped_ptr.h"
#include "base/bind.h"

class Foo : public base::RefCounted<Foo>
{
public:
    Foo() : test_count_(0) {}

    void Test0() {
        ++test_count_;
    }
private:
    ~Foo() {}
    int test_count_;
    const std::string result_;
private:
    friend class base::RefCounted<Foo>;
};
int main(int argc, char** argv)
{
    base::AtExitManager atexit;
    
    base::Thread thread("thread with messageloop");
    thread.Start();
    MessageLoop* messageloop = thread.message_loop();
    scoped_refptr<Foo> foo(new Foo());
    messageloop->PostTask(FROM_HERE, 
        base::Bind(&Foo::Test0, foo.get()));
    base::PlatformThread::Sleep(200);
    thread.Stop();

    return 0;
}