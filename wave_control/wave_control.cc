#include "wave_control/wave_control.h"

#include "wave_control/wave_control_visitor.h"

void WaveControl::Accept(WaveControlVisitor* visitor) {
  visitor->VisitWaveControl(this);
}


int WaveControl::WaveContainerAt(WaveContainer* container) {
  for (size_t i = 0; i < item_count(); ++i) {
    if (GetItemAt(i) == container) {
      return i;
    }
  }
  NOTREACHED();
  return 0;
}

bool WaveControl::HasWaveContainer(WaveContainer* container) {
  for (size_t i = 0; i < item_count(); ++i) {
    if (GetItemAt(i) == container) {
      return true;
    }
  }
  return false;
}

void WaveControl::AddContainer(WaveContainer* container) {

}

void WaveControl::RemoveContainer(WaveContainer* container) {
  size_t i = WaveContainerAt(container);
  RemoveAt(i);
}
