#ifndef OSC_UI_VIEWS_AXIS_BACKGROUND_H_
#define OSC_UI_VIEWS_AXIS_BACKGROUND_H_
#pragma once

#include "base/memory/scoped_ptr.h"
#include "views/background.h"
#include "wave_control/views/axis_painter.h"

// fill the background with the color and using the axis_painter_ to
// paint on it, and the provide the method to help the layout
class AxisBackground : public views::Background {
public:
    AxisBackground(SkColor background,
                   SkColor line, int line_width, 
                   SkColor grid, 
                   int v_grid, int v_grid_div, 
                   int h_grid, int h_grid_div);
    virtual ~AxisBackground() {}

    // overrides from views::background
    virtual void Paint( gfx::Canvas* canvas, views::View* view ) const;

    // see commit in axis_painter.h
    bool NormalSize(gfx::Size& size);

    // see commit in axis_painter.h
    gfx::Size GetMinimumSize();
private:
    // the painter of axis
    scoped_ptr<AxisPainter> axis_painter_;
    
    DISALLOW_COPY_AND_ASSIGN(AxisBackground);
};

#endif //OSC_UI_VIEWS_AXIS_BACKGROUND_H_