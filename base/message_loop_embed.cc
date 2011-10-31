#include "base/message_loop_embed.h"

#if defined(OS_WIN)
#include "base/message_pump_embed_win.h"
#endif

MessageLoopForEmbed::MessageLoopForEmbed()
{
    //replace the pump with Embed pump
    pump_ = new base::MessagePumpForEmbed();
}

MessageLoopForEmbed::~MessageLoopForEmbed()
{
    CHECK(state_ != NULL) << "You need to call Start to Start the MessageLoopForEmbed";
    delete state_;
    state_ = NULL;
}

void MessageLoopForEmbed::DidProcessMessage( const MSG& message )
{
    LOG(WARNING) << "have no affect.";
}

void MessageLoopForEmbed::AddObserver( Observer* observer )
{
    LOG(WARNING) << "this MessageLoop no Implement the Observer. no Notify.";
}

void MessageLoopForEmbed::RemoveObserver( Observer* observer )
{
    LOG(WARNING) << "this MessageLoop no Implement the Observer. no Notify.";
}

void MessageLoopForEmbed::Run( Dispatcher* dispatcher )
{
    NOTREACHED();
}

void MessageLoopForEmbed::Start()
{
    base::MessagePumpForEmbed* pump = 
        static_cast<base::MessagePumpForEmbed*>(pump_.get());
    CHECK(state_ == NULL) << "Call Start more the Once";
    state_ = new RunState();
    state_->run_depth = 1;
    state_->quit_received = false;
    pump->Start(this);
}

