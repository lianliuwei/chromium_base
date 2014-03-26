#pragma once

#include "wave_control/wave.h"

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"

#include "wave_control/ana_wave_data.h"

class OscWaveDelegate {
};

class WaveRange {
  double start;
  double end;
};

// impl details.
// TODO move to impl, no in interface head file.
class OscRange : public base::RefCounted<OscRange> {
  WaveRange range();
  int div();
  WaveRange offset_range();
  double offset();
};

class Trigger : public base::RefCounted<Trigger> {
public:
  SkColor color();

  WaveRange offset_range();
  double offset();
  bool show();
  // Relate to Y or no.
  bool IsRelate();
};


// used ptr to find if two option is the some.
// TODO whether compare() can replace trigger and Osc Range.
class OscWave : public Wave {
public:
  virtual OscWave* AsOscWave() OVERRIDE { return this; }

  AnaWaveData& Data();

  // map to osc hardware operate.
  void MoveToX(double pos);
  void MoveToY(double pos);
  void MoveTrigger(double pos);
  void ZoomInX();
  void ZoomOutX();
  void ZoomInY();
  void ZoomOutY();

  // hardware property.

  bool IsSameTrigger(OscWave* osc_wave);
  WaveRange trigger_offset_range();
  double trigger_offset();
  bool trigger_show();
  bool trigger_is_relate();

  bool IsSameVertical(OscWave* osc_wave);
  WaveRange vertical_range();
  WaveRange vertical_offset_range();
  double vertical_offset();

  bool IsSameHorizonal(OscWave* osc_wave);
  OscRange* horizonal_property();
  OscRange horizonal_range();
  WaveRange horizonal_offset_range();
  double horizon_offset();
  
  // using this to optimize the wave draw.
  enum UpdateType {
    kTrigger,
    kAll,
  };
  void DataUpdate();
  void PropertyChanged();

  // command
  // for do FFT.
  void DoRangeCommand(int command_id, Range range);

  void DoCommand(int command_id);


private:

};
