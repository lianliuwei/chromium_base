#ifndef OSC_UI_VIEW_LINE_DAT_WAVE_VIEW_H_ 
#define OSC_UI_VIEW_LINE_DAT_WAVE_VIEW_H_
#pragma once

#include "ui/gfx/transform.h"
#include "views/view.h"

// LineDataWaveView plot the wave Form of the Line Data, it sample or cut the
// wave manual to achieve high freq plot (this is key in Osc app) no matter the
// data range is large or the data is many. 
// the data is own by the controller.
// input data are logic value using the Logic to real transform Matrix 
// to Transform
class LineDataWaveView : public views::View
{
public:
  typedef std::vector<double> DataBuffer;
  
  struct LineData {
    double begin; // begin logic value of the buffer
    double end;  // end logic value of the buffer
    DataBuffer* buffer;
  };

  enum ShowStyle {
    kLine,
    kDot, 
    kLineAndDot,
    // when two point away from each other then threshold value show the dot.
    KLineAndAutoDot,
  };

  LineDataWaveView() {};
  virtual ~LineDataWaveView() {};

  void set_wave_color(SkColor color);
  SkColor wave_color() const;

  void set_dot_color(SkColor color);
  SkColor dot_color() const;

  void set_show_style(ShowStyle style);
  ShowStyle show_style() const;

  // set the data for show, the data is own by others.
  void set_line_data(LineData line_data);
  const LineData line_data() const;

  void set_logic_to_real_transform(ui::Transform logic_to_real_transform);
  ui::Transform logic_to_real_transform();

private:
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  
  // for test hit on the wave, so we can move the wave
  virtual bool HitTest(const gfx::Point& l) const OVERRIDE;

  // for dragged the wave
  virtual bool OnMouseDragged(const views::MouseEvent& event) OVERRIDE;

  void PaintWave(gfx::Canvas* canvas);

private:
  // data to plot on the View
  LineData line_data_;

  SkColor wave_color_;

  SkColor dot_color_;

  ShowStyle show_sytle_;

  // TODO rename to logic
  ui::Transform logic_to_real_transform_;
};

#endif // OSC_UI_VIEW_LINE_DAT_WAVE_VIEW_H_

