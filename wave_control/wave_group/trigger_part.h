#pragma once

#include "wave_control/wave_range.h"

class TriggerPart {
public:
  virtual ~TriggerPart();

  SkColor color();

  WaveRange offset_range();
  double offset();
  bool show();
  // Relate to Y or no.
  bool IsRelate();
};
