#pragma once

#include "wave_control/osc_wave.h"
#include "wave_control/simple_ana_wave.h"
#include "wave_control/wave_group/trigger_part.h"
#include "wave_control/wave_group/horizontal_part.h"
#include "wave_control/wave_group/vertical_part.h"
#include "wave_control/wave_group/wave_group_observer.h"

// helper for YTWaveContainerView
// turn osc_wave to part.
class WaveGroup {
public:
  void AddOscWave(OscWave* osc_wave);
  void RemoveOscWave(OscWave* osc_wave);

  void AddSimpleAnaWave(SimpleAnaWave* ana_wave);
  void RemoveSimpleAnaWave(SimpleAnaWave* ana_wave);

  // trigger
  typedef std::vector<TriggerPart*> Triggers;

  Triggers::iterator trigger_begin() { return children_.begin(); }
  Triggers::iterator trigger_end() { return children_.end(); }
  int trigger_count() const;
  TriggerPart* trigger_at(int index);
  void AddTriggerObserver(WaveGroupObserver* observer);
  void RemoveTriggerObserver(WaveGroupObserver* observer);

  // horizontal
  typedef std::vector<HorizontalPart*> Horizontals;

  Horizontals::iterator horizontal_begin();
  Horizontals::iterator horizonal_end();
  int horizontal_count() const;
  HorizontalPart* horizontal_at(int index);
  void AddHorizontalObserver(WaveGroupObserver* observer);
  void RemoveHorizontalObserver(WaveGroupObserver* observer);

  // vertical
  typedef std::vector<VerticalPart*> Verticals;

  Verticals::iterator vertical_begin();
  Verticals::iterator vertical_end();
  int vertical_count() const;
  VerticalPart* vertical_at(int index);
  void AddVerticalObserver(WaveGroupObserver* observer);
  void RemoveVerticalObserver(WaveGroupObserver* observer);

private:
};