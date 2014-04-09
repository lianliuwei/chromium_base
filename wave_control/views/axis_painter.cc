#include "wave_control/views/axis_painter.h"

#include "base/logging.h"
#include "ui/gfx/canvas_skia.h"
#include "SkDashPathEffect.h"

// must be very careful with pixel

AxisPainter::AxisPainter(SkColor line, int line_width, 
                         SkColor grid, 
                         int v_grid, int v_grid_div, 
                         int h_grid, int h_grid_div)
    : line_(line) 
    , line_width_(line_width)
    , grid_(grid)
    , v_grid_(v_grid)
    , v_grid_div_(v_grid_div)
    , h_grid_(h_grid)
    , h_grid_div_(h_grid_div) {
    CHECK(v_grid_ > 0 && v_grid_div_ > 0 
        && h_grid_ > 0 && h_grid_div_ > 0) << "grid and grid div must be postive";
    gfx::Size size = GetMinimumSize();
    CHECK(line_width_ < size.width() 
        && line_width_ < size.height()) << "line width is too width";
}

void AxisPainter::Paint(int w, int h, gfx::Canvas* canvas) {
    gfx::Size size(w, h);
    CHECK(NormalSize(size));
    CHECK(size.width() == w && size.height() == h);
    canvas->Save();
    PaintGrid(w, h, canvas, true);
    PaintGrid(w, h, canvas, false);
    PaintAxis(w, h, canvas, true);
    PaintAxis(w, h, canvas, false);
    canvas->Restore();
}

void AxisPainter::PaintGrid(int w, int h, gfx::Canvas* canvas, bool vertical) {
    SkPaint paint;
    paint.setStyle(SkPaint::kStroke_Style);
    paint.setStrokeWidth(SkIntToScalar(1));
    paint.setColor(grid_);

//  too slow
//  SkScalar intervals[] = { SkIntToScalar(1), SkIntToScalar(1) };
//  SkPathEffect* effect = new SkDashPathEffect(
//    intervals, arraysize(intervals), SkIntToScalar(2));
//  paint.setPathEffect(effect);
//  
    int count = vertical ? v_grid_*2 : h_grid_*2;
    int step = vertical ? (h+1)/count : (w+1)/count;
  for (int i = 1; i < count; i++) {
    if(i == count/2) // no draw the middle line
      continue;
    // the location is start from the 0 sub 1
    if (vertical) {
      canvas->AsCanvasSkia()->drawLine(SkIntToScalar(0), 
                                       SkIntToScalar(step*i - 1), 
                                       SkIntToScalar(w), 
                                       SkIntToScalar(step*i - 1), 
                                       paint);
    } else {
      canvas->AsCanvasSkia()->drawLine(SkIntToScalar(step*i - 1), 
                                       SkIntToScalar(0), 
                                       SkIntToScalar(step*i - 1), 
                                       SkIntToScalar(h), 
                                       paint);
    }
  }
    paint.setColor(line_); // using the more obvious color
  // draw the middle line
  if (vertical) {
    canvas->AsCanvasSkia()->drawLine(SkIntToScalar(0), 
                                     SkIntToScalar(step*count/2 - 1), 
                                     SkIntToScalar(w), 
                                     SkIntToScalar(step*count/2 - 1), 
                                     paint);
  } else {
    canvas->AsCanvasSkia()->drawLine(SkIntToScalar(step*count/2 - 1), 
                                     SkIntToScalar(0), 
                                     SkIntToScalar(step*count/2 - 1), 
                                     SkIntToScalar(h), 
                                     paint);
  }
}

void AxisPainter::PaintAxis(int w, int h, gfx::Canvas* canvas, bool vertical) {
  SkPaint paint;
  paint.setStyle(SkPaint::kStroke_Style);
  paint.setStrokeWidth(SkIntToScalar(1));
  paint.setColor(line_);
  int count = vertical ? v_grid_*v_grid_div_*2 : h_grid_*h_grid_div_*2;
  int step = vertical ? (h+1)/count : (w+1)/count;
  int hwidth = (line_width_ - 1) / 2;
  for (int i = 1; i < count; i++) {
    if (vertical) {
      canvas->AsCanvasSkia()->drawLine(SkIntToScalar((w+1)/2-1 - hwidth), 
                                        SkIntToScalar(step*i - 1), 
                                        SkIntToScalar((w+1)/2-1 + hwidth + 1), 
                                        SkIntToScalar(step*i - 1), 
                                        paint);
    } else {
      canvas->AsCanvasSkia()->drawLine(SkIntToScalar(step*i - 1), 
                                        SkIntToScalar((h+1)/2-1 - hwidth), 
                                        SkIntToScalar(step*i - 1), 
                                        SkIntToScalar((h+1)/2-1 + hwidth + 1), 
                                        paint);
    }
  }
}

bool AxisPainter::NormalSize(gfx::Size& size) {
  // cx(y) < every div 2 pixel the size is to small
  int hdiv = h_grid_*2*h_grid_div_;
  int vdiv =v_grid_*2*v_grid_div_;
  if (size.width() < 2*hdiv - 1 || size.height() < 2*vdiv - 1) 
    return false;
  size.set_width((size.width()+1)/hdiv*hdiv - 1);
  size.set_height((size.height()+1)/vdiv*vdiv - 1);
  return true;
}

gfx::Size AxisPainter::GetMinimumSize() {
  int hdiv = h_grid_*2*h_grid_div_;
  int vdiv =v_grid_*2*v_grid_div_;
  return gfx::Size(2*hdiv + 1, 2*vdiv + 1); //at least 2 pixel
}