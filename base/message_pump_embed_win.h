// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MESSAGE_PUMP_EMBED_WIN_H_
#define BASE_MESSAGE_PUMP_EMBED_WIN_H_
#pragma once

#include "base/compiler_specific.h"
#include "base/message_pump.h"
#include "base/time.h"

namespace base {

// This class implements a MessagePump needed for TYPE_EMBED MessageLoops on
// Windows platform.
class MessagePumpForEmbed : public MessagePump {
public:
    MessagePumpForEmbed();
    virtual ~MessagePumpForEmbed();

    // MessagePump methods:
    virtual void Run(Delegate* delegate) OVERRIDE;
    virtual void ScheduleWork() OVERRIDE;
    virtual void ScheduleDelayedWork(const TimeTicks& delayed_work_time) OVERRIDE;
    virtual void Quit() OVERRIDE;

    virtual void Start(Delegate* delegate);

private:
    static LRESULT CALLBACK WndProcThunk(
        HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
    void InitMessageWnd();
    void HandleWorkMessage();
    void HandleTimerMessage();
    int GetCurrentDelay() const;

    Delegate* delegate_;
    
    // The time at which delayed work should run.
    TimeTicks delayed_work_time_;

    // A boolean value used to indicate if there is a kMsgDoWork message pending
    // in the Windows Message queue.  There is at most one such message, and it
    // can drive execution of tasks when a native message pump is running.
    LONG have_work_;

    // A hidden message-only window.
    HWND message_hwnd_;

    DISALLOW_COPY_AND_ASSIGN(MessagePumpForEmbed);
};

}  // namespace base
#endif  // BASE_MESSAGE_PUMP_WIN_WIN_H_