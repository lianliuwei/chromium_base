#pragma once

#include "wave_control/wave.h"

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/observer_list.h"

#include "wave_control/ana_wave_data.h"
#include "wave_control/osc_wave_observer.h"

// used ptr to find if two option is the same.
// TODO whether compare() can replace trigger and Osc Range.
class OscWave : public Wave {
public:
  // implement Wave
  virtual Type type_id() const { return kOsc; }
  virtual OscWave* AsOscWave() OVERRIDE { return this; }
  virtual void Accept(WaveVisitor* visitor) OVERRIDE;

  virtual AnaWaveData& Data() = 0;

  // map to osc hardware operate.
  virtual void MoveToX(double pos) = 0;
  virtual void MoveToY(double pos) = 0;
  virtual void MoveTrigger(double pos) = 0;
  virtual void ZoomInX() = 0;
  virtual void ZoomOutX() = 0;
  virtual void ZoomInY() = 0;
  virtual void ZoomOutY() = 0;

  // hardware property.

  virtual bool IsSameTrigger(OscWave* osc_wave) = 0;
  virtual WaveRange trigger_offset_range() = 0;
  virtual double trigger_offset() = 0;
  virtual bool trigger_show() = 0;
  virtual bool trigger_is_relate() = 0;
  virtual OscWave* trigger_wave() = 0;
  virtual SkColor trigger_color() = 0;

  virtual bool IsSameVertical(OscWave* osc_wave) = 0;
  virtual int vertical_div() = 0;
  virtual int vertical_window_size() = 0; // how many div show in window
  virtual WaveRange vertical_range() = 0;
  virtual WaveRange vertical_offset_range() = 0;
  virtual double vertical_offset() = 0;
  virtual SkColor vertical_color() = 0;
  virtual bool vertical_show() = 0;

  virtual bool IsSameHorizontal(OscWave* osc_wave) = 0;
  virtual int horizontal_div() = 0;
  virtual int horizontal_window_size() = 0; // how many div show in window
  virtual WaveRange horizontal_range() = 0;
  virtual WaveRange horizontal_offset_range() = 0;
  virtual double horizontal_offset() = 0;
  virtual SkColor horizontal_color() = 0;
  virtual bool horizontal_show() = 0;

  // using this to optimize the wave draw.
  enum UpdateType {
    kTrigger = 1 << 0,
    kTriggerOffset = 1 << 1,
    kVertical =  1 << 2,
    kVerticalOffset = 1 << 3,
    kHorizontal = 1 << 4,
    kHorizontalOffset = 1 << 5,
    kData = 1 << 6,
  };

  void AddObserver(OscWaveObserver* observer);
  void RemoveObserver(OscWaveObserver* observer);
  bool HasObserver(OscWaveObserver* observer);

  // command
  virtual void DoCommand(int command_id) = 0;
  // for do FFT.
  virtual void DoRangeCommand(int command_id, WaveRange range) = 0;

protected:
  void NotifyChanged(int change_set);

private:
  ObserverList<OscWaveObserver> observer_list_;
};
