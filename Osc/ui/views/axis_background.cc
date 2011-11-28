#include "Osc/ui/views/axis_background.h"

#include "ui/gfx/canvas_skia.h"
#include "views/view.h"

// TODO() maybe use double buffer. when size no change no redraw.
void AxisBackground::Paint( gfx::Canvas* canvas, views::View* view ) const {
    // Fill the background. Note that we don't constrain to the bounds as
    // canvas is already clipped for us.
    canvas->AsCanvasSkia()->drawColor(get_color());
    // paint the axis
    axis_painter_->Paint(view->width(), view->height(), canvas);
}

bool AxisBackground::NormalSize( gfx::Size& size ) {
    return axis_painter_->NormalSize(size);
}

gfx::Size AxisBackground::GetMinimumSize() {
    return axis_painter_->GetMinimumSize();
}

AxisBackground::AxisBackground( SkColor background, 
                               SkColor line, int line_width, 
                               SkColor grid, 
                               int v_grid, int v_grid_div, 
                               int h_grid, int h_grid_div ) 
    : axis_painter_(new AxisPainter(line, line_width, 
                                    grid, 
                                    v_grid, v_grid_div, 
                                    h_grid, h_grid_div)) {
    SetNativeControlColor(background);
}
