#pragma once

#include "wave_control/measure_line/measure_line.h"

// for point measure
// value get from the subclass of wave.
class SingleLine : public MeasureLine {
public:
  Part& Get();

  double pos();
  void set_pos(double pos);

  double info_pos();
  string16 info();

private:

};