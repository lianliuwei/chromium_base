// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Osc/sample/fill_box_layout.h"

#include "ui/gfx/insets.h"
#include "ui/gfx/rect.h"
#include "views/view.h"

using namespace views;

FillBoxLayout::FillBoxLayout(FillBoxLayout::Orientation orientation,
                     int inside_border_horizontal_spacing,
                     int inside_border_vertical_spacing,
                     int between_child_spacing)
    : orientation_(orientation),
      inside_border_horizontal_spacing_(inside_border_horizontal_spacing),
      inside_border_vertical_spacing_(inside_border_vertical_spacing),
      between_child_spacing_(between_child_spacing) {
}

FillBoxLayout::~FillBoxLayout() {
}

void FillBoxLayout::Layout(views::View* host) {
  gfx::Rect child_area(host->GetLocalBounds());
  child_area.Inset(host->GetInsets());
  child_area.Inset(inside_border_horizontal_spacing_,
                   inside_border_vertical_spacing_);
  int x = child_area.x();
  int y = child_area.y();
  int show_views = 0;
  for (int i = 0; i < host->child_count(); ++i) {
    View* child = host->child_at(i);
    if (child->IsVisible()) {
      ++show_views;
    }
  }
  if (show_views == 0)
    return; // no view need to layout
  int view_need;
  if (orientation_ == kHorizontal) {
    view_need = (child_area.width() - 
      (show_views - 1) * between_child_spacing_) / show_views;
  } else {
    view_need = (child_area.height() - 
      (show_views - 1) * between_child_spacing_) / show_views;
  }
  
  if (view_need <= 0)
    return; // no space to layout
  for (int i = 0; i < host->child_count(); ++i) {
    View* child = host->child_at(i);
    if (child->IsVisible()) {
      gfx::Rect bounds(x, y, child_area.width(), child_area.height());
      if (orientation_ == kHorizontal) {
        bounds.set_width(view_need);
        x += view_need + between_child_spacing_;
      } else {
        bounds.set_height(view_need);
        y += view_need + between_child_spacing_;
      }
      child->SetBoundsRect(bounds);
    }
  }
}

gfx::Size FillBoxLayout::GetPreferredSize(views::View* host) {
  gfx::Rect bounds;
  int position = 0;
  for (int i = 0; i < host->child_count(); ++i) {
    View* child = host->child_at(i);
    if (child->IsVisible()) {
      gfx::Size size(child->GetPreferredSize());
      if (orientation_ == kHorizontal) {
        gfx::Rect child_bounds(position, 0, size.width(), size.height());
        bounds = bounds.Union(child_bounds);
        position += size.width();
      } else {
        gfx::Rect child_bounds(0, position, size.width(), size.height());
        bounds = bounds.Union(child_bounds);
        position += size.height();
      }
      position += between_child_spacing_;
    }
  }
  gfx::Insets insets(host->GetInsets());
  return gfx::Size(
    bounds.width() + insets.width() + 2 * inside_border_horizontal_spacing_,
    bounds.height() + insets.height() + 2 * inside_border_vertical_spacing_);
}