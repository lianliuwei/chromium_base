#include "wave_control/osc_wave.h"

#include "wave_control/wave_visitor.h"

void OscWave::Accept(WaveVisitor* visitor) {
    visitor->VisitOscWave(this);
}

void OscWave::AddObserver(OscWaveObserver* observer) {
  observer_list_.AddObserver(observer);
}

void OscWave::RemoveObserver(OscWaveObserver* observer) {
  observer_list_.RemoveObserver(observer);
}

bool OscWave::HasObserver(OscWaveObserver* observer) {
  return observer_list_.HasObserver(observer);
}

void OscWave::NotifyChanged(int change_set) {
  FOR_EACH_OBSERVER(OscWaveObserver, observer_list_, OnOscWaveChanged(this, change_set));
}

