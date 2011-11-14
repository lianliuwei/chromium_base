// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_NOTIFICATION_TYPE_H_
#define CONTENT_PUBLIC_BROWSER_NOTIFICATION_TYPE_H_
#pragma once

// This file describes various types used to describe and filter notifications
// that pass through the NotificationService.
//
namespace content {

enum NotificationType {
  NOTIFICATION_CONTENT_START = 0,

  // General -----------------------------------------------------------------

  // Special signal value to represent an interest in all notifications.
  // Not valid when posting a notification.
  NOTIFICATION_ALL = NOTIFICATION_CONTENT_START,

  // The app is done processing user actions, now is a good time to do
  // some background work.
  NOTIFICATION_IDLE,

  // Means that the app has just started doing something in response to a
  // user action, and that background processes shouldn't run if avoidable.
  NOTIFICATION_BUSY,

  // Custom notifications used by the embedder should start from here.
  NOTIFICATION_CONTENT_END,
};

}  // namespace content

#endif  // CONTENT_PUBLIC_BROWSER_NOTIFICATION_TYPE_H_
