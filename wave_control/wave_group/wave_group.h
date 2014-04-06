#pragma once

#include <vector>

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
  WaveGroup();

  virtual void AddOscWave(OscWave* osc_wave) = 0;
  virtual void RemoveOscWave(OscWave* osc_wave) = 0;
  virtual bool HasOscWave(OscWave* osc_wave) = 0;

  virtual void AddSimpleAnaWave(SimpleAnaWave* ana_wave) = 0;
  virtual void RemoveSimpleAnaWave(SimpleAnaWave* ana_wave) = 0;
 
  // trigger
  typedef std::vector<TriggerPart*> Triggers;

  Triggers::iterator trigger_begin() { return triggers_.begin(); }
  Triggers::iterator trigger_end() { return triggers_.end(); }
  int trigger_count() const { return triggers_.size(); } 
  TriggerPart* trigger_at(int index) { return triggers_[index]; }
  void AddTriggerObserver(WaveGroupObserver* observer);
  void RemoveTriggerObserver(WaveGroupObserver* observer);
  bool HasTriggerObserver(WaveGroupObserver* observer);

  // horizontal
  typedef std::vector<HorizontalPart*> Horizontals;

  Horizontals::iterator horizontal_begin() { return horizontals_.begin(); }
  Horizontals::iterator horizonal_end() { return horizontals_.end(); }
  int horizontal_count() const { return horizontals_.size(); }
  HorizontalPart* horizontal_at(int index) { return horizontals_[index]; }
  void AddHorizontalObserver(WaveGroupObserver* observer);
  void RemoveHorizontalObserver(WaveGroupObserver* observer);
  bool HasHorizontalObserver(WaveGroupObserver* observer);

  // vertical
  typedef std::vector<VerticalPart*> Verticals;

  Verticals::iterator vertical_begin() { return verticals_.begin(); }
  Verticals::iterator vertical_end() { return verticals_.end(); }
  int vertical_count() const { return verticals_.size(); }
  VerticalPart* vertical_at(int index) { return verticals_[index]; }
  void AddVerticalObserver(WaveGroupObserver* observer);
  void RemoveVerticalObserver(WaveGroupObserver* observer);
  bool HasVerticalObserver(WaveGroupObserver* observer);

protected:
  virtual ~WaveGroup();

  void NotifyTriggerGroupChanged();
  void NotifyTriggerChanged(int id);
  void NotifyTriggerMoved(int id);
  void NotifyHorizontalGroupChanged();
  void NotifyHorizontalChanged(int id);
  void NotifyHorizontalMoved(int id);
  void NotifyVerticalGroupChanged();
  void NotifyVerticalChanged(int id);
  void NotifyVerticalMoved(int id);

  Triggers triggers_;
  Horizontals horizontals_;
  Verticals verticals_;

private:
  ObserverList<WaveGroupObserver> trigger_observer_;
  ObserverList<WaveGroupObserver> horizontal_observer_;
  ObserverList<WaveGroupObserver> vertical_observer_;
};