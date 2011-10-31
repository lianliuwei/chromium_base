// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/message_pump_embed_win.h"

#include <math.h>

#include "base/logging.h"
#include "base/win/wrapped_window_proc.h"

namespace base {

static const wchar_t kWndClass[] = L"Chrome_MessagePumpForEmbedWindow";

// Message sent to get an additional time slice for pumping (processing) another
// task (a series of such messages creates a continuous task pump).
static const int kMsgHaveWork = WM_USER + 2;

MessagePumpForEmbed::MessagePumpForEmbed()
    : have_work_(0)
    , delegate_(NULL) {
    InitMessageWnd();
}

MessagePumpForEmbed::~MessagePumpForEmbed() {
    DestroyWindow(message_hwnd_);
    UnregisterClass(kWndClass, GetModuleHandle(NULL));
}

void MessagePumpForEmbed::ScheduleWork() {
    if (InterlockedExchange(&have_work_, 1))
        return;  // Someone else continued the pumping.

    // Make sure the MessagePump does some work for us.
    PostMessage(message_hwnd_, kMsgHaveWork, reinterpret_cast<WPARAM>(this), 0);
}

void MessagePumpForEmbed::ScheduleDelayedWork(const TimeTicks& delayed_work_time) {
    //
    // We would *like* to provide high resolution timers.  Windows timers using
    // SetTimer() have a 10ms granularity.  We have to use WM_TIMER as a wakeup
    // mechanism because the application can enter modal windows loops where it
    // is not running our MessageLoop; the only way to have our timers fire in
    // these cases is to post messages there.
    //
    // To provide sub-10ms timers, we process timers directly from our run loop.
    // For the common case, timers will be processed there as the run loop does
    // its normal work.  However, we *also* set the system timer so that WM_TIMER
    // events fire.  This mops up the case of timers not being able to work in
    // modal message loops.  It is possible for the SetTimer to pop and have no
    // pending timers, because they could have already been processed by the
    // run loop itself.
    //
    // We use a single SetTimer corresponding to the timer that will expire
    // soonest.  As new timers are created and destroyed, we update SetTimer.
    // Getting a spurrious SetTimer event firing is benign, as we'll just be
    // processing an empty timer queue.
    //
    delayed_work_time_ = delayed_work_time;

    int delay_msec = GetCurrentDelay();
    DCHECK_GE(delay_msec, 0);
    if (delay_msec < USER_TIMER_MINIMUM)
        delay_msec = USER_TIMER_MINIMUM;

    // Create a WM_TIMER event that will wake us up to check for any pending
    // timers (in case we are running within a nested, external sub-pump).
    SetTimer(message_hwnd_, reinterpret_cast<UINT_PTR>(this), delay_msec, NULL);
}

void MessagePumpForEmbed::Run( Delegate* delegate ) {
    NOTREACHED() << "MessagePumpForEmbed should no replace the Native loop";
}

void MessagePumpForEmbed::Start( Delegate* delegate ) {
    CHECK(delegate_ == NULL) << "Call Start more then once.";
    delegate_ = delegate;
}

void MessagePumpForEmbed::Quit() {
    CHECK(delegate_ != NULL) << "Call Quit without call Start.";
    delegate_ = NULL;
}

void MessagePumpForEmbed::InitMessageWnd() {
    HINSTANCE hinst = GetModuleHandle(NULL);

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = base::win::WrappedWindowProc<WndProcThunk>;
    wc.hInstance = hinst;
    wc.lpszClassName = kWndClass;
    RegisterClassEx(&wc);

    message_hwnd_ =
        CreateWindow(kWndClass, 0, 0, 0, 0, 0, 0, HWND_MESSAGE, 0, hinst, 0);
    DCHECK(message_hwnd_);
}

// static
LRESULT CALLBACK MessagePumpForEmbed::WndProcThunk(
    HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message) {
    case kMsgHaveWork:
        reinterpret_cast<MessagePumpForEmbed*>(wparam)->HandleWorkMessage();
        break;
    case WM_TIMER:
        reinterpret_cast<MessagePumpForEmbed*>(wparam)->HandleTimerMessage();
        break;
    }
    return DefWindowProc(hwnd, message, wparam, lparam);    
}

void MessagePumpForEmbed::HandleWorkMessage() {
    // If we are being called outside of the context of Run, then don't try to do
    // any work.  This could correspond to a MessageBox call or something of that
    // sort.
    if (!delegate_) {
        // Since we handled a kMsgHaveWork message, we must still update this flag.
        InterlockedExchange(&have_work_, 0);
        return;
    }

    // Now give the delegate a chance to do some work.  He'll let us know if he
    // needs to do more work.
    if (delegate_->DoWork())
        ScheduleWork();
}

void MessagePumpForEmbed::HandleTimerMessage() {
    KillTimer(message_hwnd_, reinterpret_cast<UINT_PTR>(this));

    // If we are being called outside of the context of Run, then don't do
    // anything.  This could correspond to a MessageBox call or something of
    // that sort.
    if (!delegate_)
        return;

    delegate_->DoDelayedWork(&delayed_work_time_);
    if (!delayed_work_time_.is_null()) {
        // A bit gratuitous to set delayed_work_time_ again, but oh well.
        ScheduleDelayedWork(delayed_work_time_);
    }
}

int MessagePumpForEmbed::GetCurrentDelay() const {
    if (delayed_work_time_.is_null())
        return -1;

    // Be careful here.  TimeDelta has a precision of microseconds, but we want a
    // value in milliseconds.  If there are 5.5ms left, should the delay be 5 or
    // 6?  It should be 6 to avoid executing delayed work too early.
    double timeout =
        ceil((delayed_work_time_ - TimeTicks::Now()).InMillisecondsF());

    // If this value is negative, then we need to run delayed work soon.
    int delay = static_cast<int>(timeout);
    if (delay < 0)
        delay = 0;

    return delay;
}

}