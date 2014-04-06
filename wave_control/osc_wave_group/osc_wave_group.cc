#include "wave_control/osc_wave_group/osc_wave_group.h"

#include <algorithm>

using namespace std;

void OscWaveGroup::AddTriggerObserver(OscWaveGroupObserver* observer) {
  trigger_observer_.AddObserver(observer);
}

void OscWaveGroup::RemoveTriggerObserver(OscWaveGroupObserver* observer) {
  trigger_observer_.RemoveObserver(observer);
}

bool OscWaveGroup::HasTriggerObserver(OscWaveGroupObserver* observer) {
  return trigger_observer_.HasObserver(observer);
}

void OscWaveGroup::AddHorizontalObserver(OscWaveGroupObserver* observer) {
  horizontal_observer_.AddObserver(observer);
}

void OscWaveGroup::RemoveHorizontalObserver(OscWaveGroupObserver* observer) {
  horizontal_observer_.RemoveObserver(observer);
}

bool OscWaveGroup::HasHorizontalObserver(OscWaveGroupObserver* observer) {
  return horizontal_observer_.HasObserver(observer);
}

void OscWaveGroup::AddVerticalObserver(OscWaveGroupObserver* observer) {
  vertical_observer_.AddObserver(observer);
}

void OscWaveGroup::RemoveVerticalObserver(OscWaveGroupObserver* observer) {
  vertical_observer_.RemoveObserver(observer);
}

bool OscWaveGroup::HasVerticalObserver(OscWaveGroupObserver* observer) {
  return vertical_observer_.HasObserver(observer);
}

void OscWaveGroup::NotifyTriggerGroupChanged() {
  FOR_EACH_OBSERVER(OscWaveGroupObserver, trigger_observer_, OnPartGroupChanged());
}

void OscWaveGroup::NotifyTriggerChanged(int id) {
  FOR_EACH_OBSERVER(OscWaveGroupObserver, trigger_observer_, OnPartChanged(id));
}

void OscWaveGroup::NotifyTriggerMoved(int id) {
  FOR_EACH_OBSERVER(OscWaveGroupObserver, trigger_observer_, OnPartMoved(id));
}




