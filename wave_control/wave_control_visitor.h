#pragma once

#include "wave_control/wave_control.h"

class WaveControlVisitor {
public:
  WaveControlVisitor() {}

  virtual void VisitWaveControl(WaveControl* wave_control) = 0;

protected:
  virtual ~WaveControlVisitor() {}
};