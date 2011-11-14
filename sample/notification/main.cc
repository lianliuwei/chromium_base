#include "base/logging.h"
#include "base/command_line.h"
#include "base/at_exit.h"
#include "notification/notification_service.h"
#include "notification/notification_registrar.h"
#include "notification/notification_observer.h"
#include "notification/notification_types.h"
#include "notification/notification_service_impl.h"

enum testType
{
    TEST_TYPE_START = content::NOTIFICATION_CONTENT_END,
    //source is the class A object point
    //details is the Foo() arg1
    CALL_CLASS_A_FOO,
};
class A
{
public:
    A() {}
    ~A() {}
    void Foo(int arg1) {
        using namespace content;
        NotificationService* service 
            = NotificationService::current();
        service->Notify(CALL_CLASS_A_FOO, Source<A>(this), Details<int>(&arg1));
    }
protected:
private:
};

class AListener : public content::NotificationObserver
{
public:
    AListener() {
        using namespace content;
        registrar_.Add(this, NOTIFICATION_ALL, NotificationService::AllSources());
        registrar_.Add(this, CALL_CLASS_A_FOO, NotificationService::AllSources());
    }

    virtual void Observe( int type, 
                          const content::NotificationSource& source,
                          const content::NotificationDetails& details ) {
        using namespace content;
        switch (type) { 
            //because the NOTIFICATION_ALL type called with the origin type not the 
            //NOTIFICATION_ALL type so this no execute
            case NOTIFICATION_ALL:
                LOG(INFO) << "some Notify somethings";
                break;
            case CALL_CLASS_A_FOO: {
                Details<int> dp = static_cast<Details<int>>(details);
                LOG(INFO) << "some one call the A::Foo arg1 = " << *(dp.ptr());
                break;
            }
            default:
                NOTREACHED();
        }
    }

private:
    content::NotificationRegistrar registrar_;
};

int main(int argc, char* argv[])
{
    using namespace logging;
    
    base::AtExitManager atexit;

    CommandLine::Init(argc, argv);

    InitLogging(L"debug.log", 
        LOG_TO_BOTH_FILE_AND_SYSTEM_DEBUG_LOG, 
        DONT_LOCK_LOG_FILE,
        DELETE_OLD_LOG_FILE,
        DISABLE_DCHECK_FOR_NON_OFFICIAL_RELEASE_BUILDS);

    NotificationServiceImpl nsi;
    A a1, a2;
    AListener listener;
    a1.Foo(1);
    a2.Foo(2);
    return 0;
}