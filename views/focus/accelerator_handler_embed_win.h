// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef VIEWS_FOCUS_ACCELERATOR_HANDLER_EMBED_WIN_H_
#define VIEWS_FOCUS_ACCELERATOR_HANDLER_EMBED_WIN_H_
#pragma once

#include <Windows.h>

#include "base/basictypes.h"
#include "views/views_export.h"

namespace views {

class VIEWS_EXPORT AcceleratorHandlerEmbedWin {
 public:
    static bool Attach();
    static bool Detach();
    static LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam);

private:
    static HHOOK hHook;
    AcceleratorHandlerEmbedWin(); // just static

    DISALLOW_COPY_AND_ASSIGN(AcceleratorHandlerEmbedWin);
};

}

#endif  // VIEWS_FOCUS_ACCELERATOR_HANDLER_EMBED_WIN_H_