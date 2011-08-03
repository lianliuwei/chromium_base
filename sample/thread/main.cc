#include "base/threading/thread.h"
#include "base/at_exit.h"
#include "base/logging.h"
#include "base/command_line.h"
#include "base/memory/scoped_ptr.h"
#include "base/bind.h"

class Foo : public base::RefCounted<Foo>
{
public:
    Foo() : test_count_(0) {}

    void Test0() {
        ++test_count_;
    }
    void Test1(int arg) {
        LOG(INFO) << "current thread ID :" << base::PlatformThread::CurrentId()
        << " arg :" << arg << " test_count_ :" << test_count_;
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
    using namespace logging;

    base::AtExitManager atexit;
    CommandLine::Init(argc, argv);

    InitLogging(L"debug.log", 
        LOG_TO_BOTH_FILE_AND_SYSTEM_DEBUG_LOG, 
        LOCK_LOG_FILE,
        DELETE_OLD_LOG_FILE,
        DISABLE_DCHECK_FOR_NON_OFFICIAL_RELEASE_BUILDS);

    base::Thread thread("thread with messageloop");
    thread.Start();
    MessageLoop* messageloop = thread.message_loop();
    scoped_refptr<Foo> foo(new Foo());
    messageloop->PostTask(FROM_HERE, 
        base::Bind(&Foo::Test0, foo.get()));
    messageloop->PostTask(FROM_HERE, 
        base::Bind(&Foo::Test1, foo.get(), 10));
    base::PlatformThread::Sleep(2000);
    thread.Stop();

    return 0;
}