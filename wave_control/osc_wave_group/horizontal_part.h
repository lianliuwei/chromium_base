#pragma once

#include "wave_control/wave_range.h"

class OscWave;

class HorizontalPart {
public:
  virtual SkColor color() = 0;
  virtual bool show() = 0;
  virtual string16 text() = 0;
  virtual SkBitmap icon() = 0;

  virtual WaveRange range() = 0;
  virtual WaveRange offset_range() = 0;
  virtual double offset() = 0;

  virtual int div() = 0;
  virtual int window_size() = 0;

  virtual OscWave* osc_wave() = 0;

protected:
  virtual ~HorizontalPart() {}
};