#pragma once

#include "wave_control/wave_range.h"

struct PeakValue {
  double begin;
  double end;
  double max;
  double min;
};

class AnaWaveData {
public:
  AnaWaveData() {}
  virtual WaveRange data_range() = 0;
  virtual double* data() = 0;
  virtual int size() = 0;

  // offset is in logic coord.
  virtual double GetValue(double offset);
  virtual PeakValue GetRangePeak(int start, int range_size);
  virtual double MaxY();
  virtual double MinY();

protected:
  virtual ~AnaWaveData() {}
};
