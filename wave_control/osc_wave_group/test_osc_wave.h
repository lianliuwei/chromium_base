#pragma once

#include "wave_control/osc_wave.h"

class TestOscWave : public OscWave {
public:
  // implement wave
  virtual string16 name();
  virtual SkColor color();
  virtual SkBitmap icon();

  // implement OscWave
  virtual AnaWaveData& Data();
  virtual void MoveToX(double pos);
  virtual void MoveToY(double pos);
  virtual void MoveTrigger(double pos);
  virtual void ZoomInX();
  virtual void ZoomOutX();
  virtual void ZoomInY();
  virtual void ZoomOutY();
  virtual bool IsSameTrigger(OscWave* osc_wave);
  virtual WaveRange trigger_offset_range();
  virtual double trigger_offset();
  virtual bool trigger_show();
  virtual bool trigger_is_relate();
  virtual OscWave* trigger_wave();
  virtual bool IsSameVertical(OscWave* osc_wave);
  virtual int vertical_div();
  virtual int vertical_window_size();
  virtual WaveRange vertical_range();
  virtual WaveRange vertical_offset_range();
  virtual double vertical_offset();
  virtual bool IsSameHorizontal(OscWave* osc_wave);
  virtual int horizontal_div();
  virtual int horizontal_window_size();
  virtual WaveRange horizontal_range();
  virtual WaveRange horizontal_offset_range();
  virtual double horizontal_offset();
  virtual void DoCommand(int command_id);
  virtual void DoRangeCommand(int command_id, WaveRange range);


};