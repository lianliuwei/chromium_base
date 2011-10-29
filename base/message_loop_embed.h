// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MESSAGE_LOOP_EMBED_H_
#define BASE_MESSAGE_LOOP_EMBED_H_
#pragma once

#include "base/message_loop.h"

//-----------------------------------------------------------------------------
// MessageLoopForEmbed replace MessageLoopUI with methods the need to Embedding 
// a MessageLoop to a exist native MessageLoop like MFC. it return the TYPE_UI
// so we need no change the up user. same methods have different affect. user
// must take care yourself.
//
// This class is typically used like so:
//   MessageLoopForUI::current()->...call some method...
//
class BASE_EXPORT MessageLoopForEmbed : public MessageLoopForUI {
public:
    MessageLoopForEmbed() {
    }
    // must take care because loop type maybe MessageLoopForUI
    // Returns the MessageLoopForEmbed of the current thread.
    static MessageLoopForEmbed* current() {
        MessageLoop* loop = MessageLoop::current();
        DCHECK_EQ(MessageLoop::TYPE_UI, loop->type());
        return static_cast<MessageLoopForEmbed*>(loop);
    }

#if defined(OS_WIN)
    virtual void DidProcessMessage(const MSG& message);
#endif  // defined(OS_WIN)

    // the UI message loop is handled by be Embedding side. So Run() should
    // never be called. Instead use Start(), which will forward all the native 
    // UI events to the native message loop.
    void Start();
    
    // those should no be call.
    virtual void AddObserver(Observer* observer);
    virtual void RemoveObserver(Observer* observer);
    virtual void Run(Dispatcher* dispatcher);
};

#endif  // BASE_MESSAGE_LOOP_EMBED_H_