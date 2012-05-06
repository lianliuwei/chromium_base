#include "Osc/ui/views/line_data_wave_view.h"

#include <math.h>

#include "base/logging.h"
#include "ui/gfx/point.h"
#include "ui/gfx/canvas_skia.h"

namespace {

  static const int kAutoShowDotThreshold = 10;

  static const int kDotWidth = 4;

  static const int kLineWidth = 1;

  int SymmetricRound(double x) {
    return static_cast<int>(
      x > 0
      ? std::floor(x + 0.5f)
      : std::ceil(x - 0.5f));
  }

  int TransformX(const ui::Transform transform, double x) {
    gfx::Point point(x, 0);
    transform.TransformPoint(point);
   return point.x();
  }

  int TransformReverseX(const ui::Transform transform, int x) {
    gfx::Point point(x, 0);
    CHECK(transform.TransformPointReverse(point)) << "Invalid transform matrix";
    return point.x();
  }

  int TransformX(const ui::Transform transform, int x) {
    SkScalar p[4] = {
      SkDoubleToScalar(x),
      0,
      0,
      1};
      transform.matrix().map(p);
      return SymmetricRound(p[0]);
  }

  int TransformY(const ui::Transform transform, double y) {
    SkScalar p[4] = {
      0,
      SkDoubleToScalar(y),
      0,
      1};
      transform.matrix().map(p);
      return SymmetricRound(p[1]);
  }

  // return true for have intersect, false for no
  bool RangeIntersect(int* intersect_left, int* intersect_right, 
    int range_1_left, int range_1_right, 
    int range_2_left, int range_2_right) {
      CHECK(range_1_left <= range_1_right) << "the coord is defalut windows coord";
      CHECK(range_2_left <= range_2_right) << "the coord is defalut windows coord";
      if(range_1_right < range_2_left || range_2_right < range_1_left)
        return false;
      *intersect_left = std::max(range_1_left, range_2_left);
      *intersect_right = std::min(range_1_right, range_2_right);
      return true;
  }

  // the sample process get the max, min, start, end value of a step
  // value. those value are all real Y coordinate Value.
  struct SampleElement {
    int max;
    int min;
    int begin;
    int end;
  };

  SampleElement SampleRangeData(const LineDataWaveView::DataBuffer& buffer, 
      const ui::Transform transform, int begin_index, int end_index) {
    LineDataWaveView::DataBuffer::const_iterator it = buffer.begin();
    DCHECK(begin_index >=0 && begin_index < static_cast<int>(buffer.size()));
    DCHECK(end_index >=0 && static_cast<int>(buffer.size()));
    LineDataWaveView::DataBuffer::const_iterator begin = it + begin_index;
    LineDataWaveView::DataBuffer::const_iterator end = it + end_index;
    double max = *max_element(it + begin_index, it + end_index);
    double min = *min_element(it + begin_index, it + end_index);
    int real_max = TransformY(transform, max);
    int real_min = TransformY(transform, min);
    if (real_max < real_min) { // the logic coord may be up side down
      int temp = real_max;
      real_max = real_min;
      real_min = real_max;
    }
    SampleElement sample = {
        real_max,
        real_min,
        TransformY(transform, *(begin)),
        TransformY(transform, *(end))};
    return sample;
  }

}

void LineDataWaveView::PaintWave( gfx::Canvas* canvas )
{
  if (line_data_.buffer == NULL)
    return;
  int real_begin = TransformX(logic_to_real_transform_, line_data_.begin);
  int real_end = TransformX(logic_to_real_transform_, line_data_.end);
  int real_length = real_end - real_begin;
  CHECK(real_begin <= real_end);
  int view_begin = GetLocalBounds().x();
  int view_end = GetLocalBounds().right();
  int plot_begin, plot_end;
  if (!RangeIntersect(&plot_begin, &plot_end, 
    real_begin, real_end, view_begin, view_end))
    return; // no data need to show
  int vector_size = static_cast<int>(line_data_.buffer->size());
  ui::Transform vector_to_real_x;
  // convert to float manual, or the divide is using int lost precision
  vector_to_real_x.SetScaleX(static_cast<float>(real_length) / (vector_size - 1));
  vector_to_real_x.SetTranslateX(real_begin);
  // get How many point to show
  int vector_start = TransformReverseX(vector_to_real_x, plot_begin);
  int vector_end = TransformReverseX(vector_to_real_x, plot_end);
  // add two point separate add begin and end for show the wave like cut when
  // the wave range is cut off by the view.
  if (vector_start != 0 )
    vector_start -= 1;
  if (vector_end != vector_size -1)
    vector_end += 1;
  // show line, show dot
  bool draw_line = show_sytle_ != kDot;
  bool auto_show_dot = vector_size == 1 ? true : 
    real_length / (vector_size - 1) >= kAutoShowDotThreshold;
  bool draw_dot = show_sytle_ == kDot || show_sytle_ == kLineAndDot ||
    (show_sytle_ == KLineAndAutoDot) && auto_show_dot;
  // prepare the paint
  SkPaint dot_paint;
  dot_paint.setStrokeWidth(kDotWidth);
  dot_paint.setColor(dot_color_);
  SkPaint line_paint;
  line_paint.setStrokeWidth(kLineWidth);
  line_paint.setColor(wave_color_);
  line_paint.setAntiAlias(true);
  SkCanvas* sk_canvas = canvas->AsCanvasSkia();
  DataBuffer* buffer = line_data_.buffer;
  // need sample
  if (2 * real_length < vector_size) {
    // pixel by pixel
    int begin_y = TransformY(logic_to_real_transform_, (*buffer)[vector_start]);
    for (int i = plot_begin; i < plot_end; i ++) {
      int begin_index = TransformReverseX(vector_to_real_x, i);
      int end_index = TransformReverseX(vector_to_real_x, i + 1);
      SampleElement sample = SampleRangeData(*buffer, logic_to_real_transform_, 
        begin_index, end_index);
      if (draw_line) {
        sk_canvas->drawLine(SkIntToScalar(i), SkIntToScalar(begin_y), 
        SkIntToScalar(i + 1), SkIntToScalar(sample.begin), line_paint);
        sk_canvas->drawLine(SkIntToScalar(i), SkIntToScalar(sample.max), 
          SkIntToScalar(i), SkIntToScalar(sample.min), line_paint);
      }
      if (draw_dot) {
        sk_canvas->drawPoint(SkIntToScalar(i), SkIntToScalar(sample.begin), dot_paint);
        sk_canvas->drawPoint(SkIntToScalar(i), SkIntToScalar(sample.end), dot_paint);
        sk_canvas->drawPoint(SkIntToScalar(i), SkIntToScalar(sample.max), dot_paint);
        sk_canvas->drawPoint(SkIntToScalar(i), SkIntToScalar(sample.min), dot_paint);
      }
      begin_y = sample.end;
    }
  } else {
    // TODO test if drawPoints can save plot time
    // draw a line segment and the back dot
    for (int i = vector_start; i < vector_end; i++) {
      int begin_x = TransformX(vector_to_real_x, i);
      int begin_y = TransformY(logic_to_real_transform_, (*buffer)[i]);
      int end_x = TransformX(vector_to_real_x, i+1);
      int end_y = TransformY(logic_to_real_transform_, (*buffer)[i+1]);
      if (draw_line)
        sk_canvas->drawLine(SkIntToScalar(begin_x), SkIntToScalar(begin_y),
        SkIntToScalar(end_x), SkIntToScalar(end_y), line_paint);
      if (draw_dot)
        sk_canvas->drawPoint(SkIntToScalar(begin_x), SkIntToScalar(begin_y),
        dot_paint);
    }
  }
  // draw the last dot;
  if (draw_dot) {
    double logic_y = (*buffer)[vector_end];
    sk_canvas->drawPoint(TransformX(vector_to_real_x, vector_end),
      TransformY(logic_to_real_transform_, logic_y), dot_paint);
  }
}

void LineDataWaveView::OnPaint( gfx::Canvas* canvas ) {
  views::View::OnPaint(canvas); // draw the background border first.
  PaintWave(canvas);
}

bool LineDataWaveView::HitTest( const gfx::Point& l ) const {
  return false;
}

bool LineDataWaveView::OnMouseDragged( const views::MouseEvent& event ) {
  return false;
}

void LineDataWaveView::set_wave_color( SkColor color ) {
  if (color != wave_color_) {
    wave_color_ = color;
    SchedulePaint();    
  }
}

void LineDataWaveView::set_dot_color( SkColor color ) {
  if (color != dot_color_) {
    dot_color_ = color;
    SchedulePaint();    
  }
}

void LineDataWaveView::set_show_style( ShowStyle style ) {
  if (style != show_sytle_) {
    show_sytle_ = style;
    SchedulePaint();    
  }
}

void LineDataWaveView::set_line_data( const LineData line_data ) {
  // data allow no the same, just repaint it.
  line_data_ = line_data;
  SchedulePaint();
}

void LineDataWaveView::set_logic_to_real_transform(
  ui::Transform logic_to_real_transform ) {
    if (logic_to_real_transform != logic_to_real_transform_) {
      logic_to_real_transform_ = logic_to_real_transform;
      SchedulePaint();
    }
}
