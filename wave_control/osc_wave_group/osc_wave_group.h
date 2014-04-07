#pragma once

#include <vector>

#include "wave_control/osc_wave.h"
#include "wave_control/simple_ana_wave.h"
#include "wave_control/osc_wave_group/trigger_part.h"
#include "wave_control/osc_wave_group/horizontal_part.h"
#include "wave_control/osc_wave_group/vertical_part.h"
#include "wave_control/osc_wave_group/osc_wave_group_observer.h"

// helper for YTWaveContainerView
// turn osc_wave to part.
class OscWaveGroup {
public:
  OscWaveGroup() {}
  virtual ~OscWaveGroup();

  virtual void AddOscWave(OscWave* osc_wave) = 0;
  virtual void RemoveOscWave(OscWave* osc_wave) = 0;
  virtual bool HasOscWave(OscWave* osc_wave) = 0;
 
  // trigger
  typedef std::vector<TriggerPart*> Triggers;

  Triggers::iterator trigger_begin() { return triggers_.begin(); }
  Triggers::iterator trigger_end() { return triggers_.end(); }
  int trigger_count() const { return triggers_.size(); } 
  TriggerPart* trigger_at(int index) { return triggers_[index]; }
  void AddTriggerObserver(OscWaveGroupObserver* observer);
  void RemoveTriggerObserver(OscWaveGroupObserver* observer);
  bool HasTriggerObserver(OscWaveGroupObserver* observer);

  // horizontal
  typedef std::vector<HorizontalPart*> Horizontals;

  Horizontals::iterator horizontal_begin() { return horizontals_.begin(); }
  Horizontals::iterator horizonal_end() { return horizontals_.end(); }
  int horizontal_count() const { return horizontals_.size(); }
  HorizontalPart* horizontal_at(int index) { return horizontals_[index]; }
  void AddHorizontalObserver(OscWaveGroupObserver* observer);
  void RemoveHorizontalObserver(OscWaveGroupObserver* observer);
  bool HasHorizontalObserver(OscWaveGroupObserver* observer);

  // vertical
  typedef std::vector<VerticalPart*> Verticals;

  Verticals::iterator vertical_begin() { return verticals_.begin(); }
  Verticals::iterator vertical_end() { return verticals_.end(); }
  int vertical_count() const { return verticals_.size(); }
  VerticalPart* vertical_at(int index) { return verticals_[index]; }
  void AddVerticalObserver(OscWaveGroupObserver* observer);
  void RemoveVerticalObserver(OscWaveGroupObserver* observer);
  bool HasVerticalObserver(OscWaveGroupObserver* observer);

protected:
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
  ObserverList<OscWaveGroupObserver> trigger_observer_;
  ObserverList<OscWaveGroupObserver> horizontal_observer_;
  ObserverList<OscWaveGroupObserver> vertical_observer_;
};