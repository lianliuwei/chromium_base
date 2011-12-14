#ifndef OSC_UI_VIEWS_AXIS_PAINTER_H_
#define OSC_UI_VIEWS_AXIS_PAINTER_H_
#pragma once

#include "views/painter.h"
#include "ui/gfx/size.h"

class AxisPainter : public views::Painter
{
public:
    explicit AxisPainter(SkColor line, int line_width, 
        SkColor grid, int v_grid, int v_grid_div, int h_grid, int h_grid_div);
    virtual ~AxisPainter() {};

public:
    // Overridden from views::Painter
    // the w h must be normal
    virtual void Paint( int w, int h, gfx::Canvas* canvas );

    // if true the size set to the biggest of the cx(y) % (2*grid*div) == 0 size, 
    // if false the size no change the cx(y) is too small.
    bool NormalSize(gfx::Size& size);

    gfx::Size GetMinimumSize();

private:
    // paint the dash 2*grid-1 grid lines
    // the w h must be normal
    // the vertical is the Axis direction 
    // draw the grid intersect the Axis
    void PaintGrid( int w, int h, gfx::Canvas* canvas, bool vertical );
    
    // paint the 2 Axis lines in the middle
    // the w h must be normal
    // the vertical is the Axis direction
    // draw the line the on the Axis
    void PaintAxis( int w, int h, gfx::Canvas* canvas, bool vertical );

private:
    SkColor line_;
    
    SkColor grid_;

    // 2*v_grid_ div the  Height 
    int v_grid_;

    // 2*h_grid_ div the width
    int h_grid_;

    // how much to div the v_grid
    int v_grid_div_;

    // how much to div the h_grid
    int h_grid_div_;

    // size of the grid line must be odd to symmetry
    int line_width_;

    DISALLOW_COPY_AND_ASSIGN(AxisPainter);
};

#endif //OSC_UI_VIEWS_AXIS_PAINTER_H_