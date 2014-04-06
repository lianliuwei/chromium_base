#pragma once

#include "wave_control/wave_range.h"

struct PeakValue {
  double start;
  double end;
  double max;
  double min;
};

class AnaWaveData {
public:
  virtual WaveRange data_range();
  virtual double* data();
  virtual int size();

  // offset is in logic coord.
  virtual double GetValue(double offset);
  virtual PeakValue GetRangePeak(double start, double offset);
  virtual double MaxY();
  virtual double MinY();
};
