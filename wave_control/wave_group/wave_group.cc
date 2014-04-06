#include "wave_control/wave_group/wave_group.h"

#include <algorithm>

using namespace std;

void WaveGroup::AddTriggerObserver(WaveGroupObserver* observer) {
  trigger_observer_.AddObserver(observer);
}

void WaveGroup::RemoveTriggerObserver(WaveGroupObserver* observer) {
  trigger_observer_.RemoveObserver(observer);
}

bool WaveGroup::HasTriggerObserver(WaveGroupObserver* observer) {
  return trigger_observer_.HasObserver(observer);
}

void WaveGroup::AddHorizontalObserver(WaveGroupObserver* observer) {
  horizontal_observer_.AddObserver(observer);
}

void WaveGroup::RemoveHorizontalObserver(WaveGroupObserver* observer) {
  horizontal_observer_.RemoveObserver(observer);
}

bool WaveGroup::HasHorizontalObserver(WaveGroupObserver* observer) {
  return horizontal_observer_.HasObserver(observer);
}

void WaveGroup::AddVerticalObserver(WaveGroupObserver* observer) {
  vertical_observer_.AddObserver(observer);
}

void WaveGroup::RemoveVerticalObserver(WaveGroupObserver* observer) {
  vertical_observer_.RemoveObserver(observer);
}

bool WaveGroup::HasVerticalObserver(WaveGroupObserver* observer) {
  return vertical_observer_.HasObserver(observer);
}

void WaveGroup::NotifyTriggerGroupChanged() {
  FOR_EACH_OBSERVER(WaveGroupObserver, trigger_observer_, OnPartGroupChanged());
}

void WaveGroup::NotifyTriggerChanged(int id) {
  FOR_EACH_OBSERVER(WaveGroupObserver, trigger_observer_, OnPartChanged(id));
}

void WaveGroup::NotifyTriggerMoved(int id) {
  FOR_EACH_OBSERVER(WaveGroupObserver, trigger_observer_, OnPartMoved(id));
}




