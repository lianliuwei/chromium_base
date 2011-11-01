// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "views/focus/accelerator_handler_embed_win.h"

#include "base/logging.h"
#include "views/widget/widget.h"
#include "views/focus/focus_manager.h"

namespace views {

HHOOK AcceleratorHandlerEmbedWin::hHook = NULL;

AcceleratorHandlerEmbedWin::AcceleratorHandlerEmbedWin() {
}
//static
bool AcceleratorHandlerEmbedWin::Attach() {
    CHECK(hHook == NULL) << "call Attach() twice";
    hHook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)HookProc,
        NULL, GetCurrentThreadId()); // hook the call ui Thread.
    PCHECK(hHook);
    return true;
}
//static
bool AcceleratorHandlerEmbedWin::Detach() {
    CHECK(hHook != NULL) << "call Attach() before.";
    BOOL ret = UnhookWindowsHookEx(hHook);
    PCHECK(ret);
    hHook=0;
    return true;
}
//static
LRESULT CALLBACK AcceleratorHandlerEmbedWin::HookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    bool process_message = true;
    if (nCode>=0){
        MSG msg = *((MSG*)lParam);
        if (msg.message >= WM_KEYFIRST && msg.message <= WM_KEYLAST) {
            Widget* widget = Widget::GetTopLevelWidgetForNativeView(msg.hwnd);
            FocusManager* focus_manager = widget ? widget->GetFocusManager() : NULL;
            if (focus_manager) {
                switch (msg.message) {
                    case WM_KEYDOWN:
                    case WM_SYSKEYDOWN: {
                        KeyEvent event(msg);
                        focus_manager->OnKeyEvent(event); // to notify the focus_manager
                        break;
                    }
                }
            }
        }
    }
    if (hHook) 
        return(CallNextHookEx(hHook,nCode,wParam,lParam));
    else { 
        return(CallNextHookEx(NULL,nCode,wParam,lParam)); 
    }    // same as return(0);
    return(0);
}

}    // namespace views