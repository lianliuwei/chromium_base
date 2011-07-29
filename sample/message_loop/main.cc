#include "base/message_loop.h"
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

    MessageLoop messageloop(MessageLoop::TYPE_DEFAULT);
    scoped_refptr<Foo> foo(new Foo());
    MessageLoop::current()->PostTask(FROM_HERE, 
        base::Bind(&Foo::Test0, foo.get()));
    MessageLoop::current()->PostTask(FROM_HERE,
        base::Bind(&MessageLoop::Quit, base::Unretained(MessageLoop::current())));

    messageloop.Run();

    return 0;
}