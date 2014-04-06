#pragma once

#include "wave_control/wave_range.h"

class TriggerPart {
public:
  virtual SkColor color() = 0;
  virtual bool show() = 0;

  virtual WaveRange offset_range() = 0;
  virtual double offset() = 0;
  virtual void set_offset(double offset) = 0;
  // Relate to Y or no.
  virtual bool IsRelate() = 0;

protected:
  virtual ~TriggerPart() {}
};
