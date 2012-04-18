// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FILL_LAYOUT_BOX_LAYOUT_H_
#define FILL_LAYOUT_BOX_LAYOUT_H_
#pragma once

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "views/layout/layout_manager.h"

namespace gfx {
class Size;
}
namespace views {
class View;
}

// A Layout manager that arranges child views vertically or horizontally in a
// side-by-side fashion with spacing around and between the child views. The
// child views are always Fill each space.
class VIEWS_EXPORT FillBoxLayout : public views::LayoutManager {
 public:
  enum Orientation {
    kHorizontal,
    kVertical,
  };

  // Use |inside_border_horizontal_spacing| and
  // |inside_border_vertical_spacing| to add additional space between the child
  // view area and the host view border. |between_child_spacing| controls the
  // space in between child views.
  FillBoxLayout(Orientation orientation,
            int inside_border_horizontal_spacing,
            int inside_border_vertical_spacing,
            int between_child_spacing);
  virtual ~FillBoxLayout();

  // Overridden from views::LayoutManager:
  virtual void Layout(views::View* host) OVERRIDE;
  virtual gfx::Size GetPreferredSize(views::View* host) OVERRIDE;

 private:
  const Orientation orientation_;

  // Spacing between child views and host view border.
  const int inside_border_horizontal_spacing_;
  const int inside_border_vertical_spacing_;

  // Spacing to put in between child views.
  const int between_child_spacing_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(FillBoxLayout);
};

#endif // FILL_LAYOUT_BOX_LAYOUT_H_
