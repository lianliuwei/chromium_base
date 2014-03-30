#pragma once

#include "wave_control/wave_range.h"

// impl details.
// TODO move to impl, no in interface head file.
class HorizontalPart {
  WaveRange range();
  WaveRange offset_range();
  double offset();

  int div();
  int window_div();
};