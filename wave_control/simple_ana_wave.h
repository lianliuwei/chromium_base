#pragma once

#include "wave_control/wave.h"
#include "wave_control/ana_wave_data.h"

enum AnaWaveShowStyle {
  
};

class SimpleAnaWave : public Wave {
public:
  // implement wave
  virtual SimpleAnaWave* AsSimpleAnaWave() OVERRIDE { return this; }

  AnaWaveData& Data();

  // just for save the range, so no notify to the view.
  // all change is done be the view.
  WaveRange vertical_range();
  void set_vertical_range(const WaveRange& wave_range);
  double vertical_offset();
  void set_vertical_offset(double offset);

  WaveRange horizontal_range();
  void set_horizontal_range(const WaveRange& wave_range);
  double horizontal_offset();
  void set_horizontal_offset(double offset);

  // command
  // for do FFT.
  void DoRangeCommand(int command_id, WaveRange range);
 
  void DoCommand(int command_id);


private:

};
