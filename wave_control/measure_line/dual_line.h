#pragma once

#include "wave_control/measure_line/measure_line.h"

// for range measure
class DualLine : public MeasureLine {
public:
  Part& From();
  Part& To();

  double From_pos();
  double to_pos();
  void set_from_pos(double pos);
  void set_to_pos(double pos);

};